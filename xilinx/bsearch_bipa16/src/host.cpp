
#include "xcl2.hpp"
#include <algorithm>
#include <vector>
#include <ap_int.h>
#include <time.h>
#include <cstdlib>
#include <chrono>

#define CH_NUM 28 
#define PE_NUM 16 

unsigned int rand32(void) { //RAND_MAX is often too small to set all 32 bits, construct a random 32-bit int 8 bits at a time
        unsigned int r = 0;
        for (int i=0; i<4; i++) r = (r << 8) | (rand() & 0xff);
        return r;
}

int main(int argc, char **argv) {
	printf("start host\n");

	// if (argc != 6) {
	//     std::cout << "Usage: " << argv[0] << " <XCLBIN File> pseudo_alloc_size real_alloc_size if_run_write if_run_read" << std::endl;
	//     return EXIT_FAILURE;
	// }
	// int alloc_size = atoi(argv[2]);
	// int real_alloc_size = atoi(argv[3]);
	// bool run_write = atoi(argv[4]);
	// bool run_read = atoi(argv[5]);

	const unsigned int tar_len = 1024*1024/PE_NUM;
	//const int tar_len = 512/PE_NUM;
	const int arr_len = 1024*256;
	//const int arr_len = 1024;

	//print the configuration we are working with
	printf("defines:\n");
	printf("CH_NUM :%d PE_NUM:%d\n", CH_NUM, PE_NUM);
	printf("  Target length %d (%f MB)\n", tar_len, (float)tar_len*sizeof(unsigned int)/1024/1024 );
	printf("  Array length %d (%f MB)\n", arr_len, (float)arr_len*sizeof(ap_uint<512>)/1024/1024 );


	std::string binaryFile = argv[1];
	cl_int err;
	cl::Context context;
	cl::Kernel krnl_vector_add;
	cl::CommandQueue q;

	printf("Generating random input data...");
	fflush(stdout);
	// Allocate Memory in Host Memory
	std::vector<unsigned int, aligned_allocator<unsigned int> > host_tar_data(tar_len*CH_NUM*PE_NUM);
	// std::generate(curr.begin(), curr.end(), std::rand);
	for (unsigned int j = 0; j < tar_len; j++) {
		if( arr_len > RAND_MAX ){
			host_tar_data[j*CH_NUM*PE_NUM] = rand32()%arr_len;
		}
		else{
			host_tar_data[j*CH_NUM*PE_NUM] = rand()%arr_len;
		}
		for (int i = 1; i < CH_NUM*PE_NUM; i++) {
			host_tar_data[j*CH_NUM*PE_NUM+i] = host_tar_data[j*CH_NUM*PE_NUM];
		}
	}
    
	std::vector<unsigned int, aligned_allocator<unsigned int> > host_tar_addr(tar_len*CH_NUM*PE_NUM);
	for (unsigned int j = 0; j < tar_len*CH_NUM*PE_NUM; j++) {
		host_tar_addr[j] = 0;
	}

	std::vector<std::vector<ap_uint<512>, aligned_allocator<ap_uint<512> > > > host_arr;
	for (int i = 0; i < CH_NUM; i++) {
		std::vector<ap_uint<512>, aligned_allocator<ap_uint<512> > > curr(arr_len*PE_NUM);
		// std::generate(curr.begin(), curr.end(), std::rand);
		for (int k = 0; k < PE_NUM; k++) {
		for (int j = 0; j < arr_len; j++) {
			curr[k*arr_len+j] = (ap_uint<512>)j;
		}
		}
		host_arr.push_back(std::move(curr));
	}

	std::vector<unsigned int, aligned_allocator<unsigned int> > host_answer(tar_len);

	printf("done\n");
        printf("Generating host answer...");
        fflush(stdout);

    
	long long search_num = 0;
        double ddr_bandwidth;

        //generate CPU answer
	auto cpu_start = std::chrono::steady_clock::now(); 
        for(unsigned int t = 0 ; t < tar_len; t++ ){
                unsigned int tar_value = host_tar_data[t*CH_NUM*PE_NUM];
                unsigned int left = 0;
                unsigned int right = arr_len-1;
                unsigned int middle;

                while( left <= right ){
                        search_num++;
                        middle = (left+right)/2;
                        //printf("%d ", middle);
                        unsigned int arr_value = (unsigned int)(host_arr[0][middle]);
                        if( arr_value < tar_value ){
                                left = middle + 1;
                        }
                        else if( arr_value > tar_value ){
                                right = middle - 1;
                        }
                        else{ //match
                                break;
                        }
                }

                host_answer[t] = middle;
        }

	auto cpu_end = std::chrono::steady_clock::now(); 
	double cpu_time = std::chrono::duration_cast<std::chrono::nanoseconds>(cpu_end - cpu_start).count(); 
	cpu_time *= 1e-9; 
        printf("done\n");

        printf("CPU # of searches : %fG in %f seconds (%f Gsearches/s)\n", (double)search_num * 1.0e-9, cpu_time, (double)search_num / cpu_time * 1.0e-9  );
        ddr_bandwidth = (double)search_num * sizeof(ap_uint<512>) / cpu_time * 1.0e-9; 
        printf("memory bandwidth %f GB/s\n", ddr_bandwidth);
        fflush(stdout);

    
    // OPENCL HOST CODE AREA START
    auto devices = xcl::get_xil_devices();
    auto fileBuf = xcl::read_binary_file(binaryFile);
    cl::Program::Binaries bins{{fileBuf.data(), fileBuf.size()}};
    int valid_device = 0;
    printf("Num of devices : %d\n", (int)devices.size());
    for (unsigned int i = 0; i < devices.size(); i++) {
        auto device = devices[i];
        // Creating Context and Command Queue for selected Device
        OCL_CHECK(err, context = cl::Context({device}, NULL, NULL, NULL, &err));
        OCL_CHECK(err,
                  q = cl::CommandQueue(
                      context, {device}, CL_QUEUE_PROFILING_ENABLE, &err));

	if( device.getInfo<CL_DEVICE_NAME>() != "xilinx_u280_xdma_201920_3" ){
                std::cout  << "Skipping device : " << device.getInfo<CL_DEVICE_NAME>() << std::endl;
		continue;
	}
        std::cout << "Trying to program device[" << i
                  << "]: " << device.getInfo<CL_DEVICE_NAME>() << std::endl;
        OCL_CHECK(err,
                  cl::Program program(context, {device}, bins, NULL, &err));
        if (err != CL_SUCCESS) {
            std::cout << "Failed to program device[" << i
                      << "] with xclbin file!\n";
        } else {
            std::cout << "Device[" << i << "]: program successful!\n";
            OCL_CHECK(err, krnl_vector_add = cl::Kernel(program, "vadd", &err));
            valid_device++;
            break; // we break because we found a valid device
        }
    }
    if (valid_device == 0) {
        std::cout << "Failed to program any device found, exit!\n";
        exit(EXIT_FAILURE);
    }

    // Allocate Buffer in Global Memory

	cl::Buffer device_tar_data(
          context,
          CL_MEM_USE_HOST_PTR | CL_MEM_READ_ONLY,
          tar_len*CH_NUM*PE_NUM*sizeof(unsigned int),
          host_tar_data.data(),
          &err
	);

    
	cl::Buffer device_tar_addr(
          context,
          CL_MEM_USE_HOST_PTR | CL_MEM_WRITE_ONLY,
          tar_len*CH_NUM*PE_NUM*sizeof(unsigned int),
          host_tar_addr.data(),
          &err
	);

    std::vector<cl::Buffer> device_arr; 
    for (int i = 0; i < CH_NUM; i++) {
      OCL_CHECK(err,
        cl::Buffer curr_arr(
          context,
          CL_MEM_USE_HOST_PTR | CL_MEM_READ_ONLY,
          arr_len*sizeof(ap_uint<512>)*PE_NUM,
          host_arr[i].data(),
          &err);
      );

      device_arr.push_back(std::move(curr_arr));
    }

    // set argument
    OCL_CHECK(err, err = krnl_vector_add.setArg(0, device_tar_data));
    OCL_CHECK(err, err = krnl_vector_add.setArg(1, device_tar_addr));
    for (int i = 0; i < CH_NUM; i++) {
      OCL_CHECK(err, err = krnl_vector_add.setArg(i+2, device_arr[i]));
    }
    OCL_CHECK(err, err = krnl_vector_add.setArg(CH_NUM + 2, tar_len));
    OCL_CHECK(err, err = krnl_vector_add.setArg(CH_NUM + 3, arr_len));

    printf("move data to HBM\n");
    // Copy input data to device global memory
    OCL_CHECK(err, err = q.enqueueMigrateMemObjects({device_tar_data}, 0 /* 0 means from host*/));      
    OCL_CHECK(err, err = q.enqueueMigrateMemObjects({device_tar_addr}, 0 /* 0 means from host*/));      
    for ( int i = 0; i < CH_NUM; i++) {
      OCL_CHECK(err, err = q.enqueueMigrateMemObjects({device_arr[i]}, 0 /* 0 means from host*/));      
    }
    q.finish();


    printf("start kernel\n");
    auto fpga_start = std::chrono::steady_clock::now(); 
    // Launch the Kernel
    OCL_CHECK(err, err = q.enqueueTask(krnl_vector_add));
    q.finish();

    auto fpga_end = std::chrono::steady_clock::now(); 
    double fpga_time =  std::chrono::duration_cast<std::chrono::nanoseconds>(fpga_end - fpga_start).count(); 
    fpga_time *= 1e-9; 

    printf("move data back to host\n");
    // Copy Result from Device Global Memory to Host Local Memory
    OCL_CHECK(err, err = q.enqueueMigrateMemObjects({device_tar_addr}, CL_MIGRATE_MEM_OBJECT_HOST));      
    q.finish();

        printf("done\n");

        fflush(stdout);

	//check results
        int mismatch = 0;
        for (int ker=0; ker<CH_NUM*PE_NUM; ker++) {
                for (unsigned int i=0; i<tar_len; i++) {
                        unsigned int got = host_tar_addr[i*CH_NUM*PE_NUM+ker];
                        unsigned int expected = host_answer[i];
                        if (got != expected) {
                                mismatch++;
                        }
                        //if ( (got != expected && mismatch < 10) || (10 <= i && i < 20 && ker%16==0) ){
                        if (got != expected && mismatch < 10) {
                                printf("kernel*pe %d, index %d, got %d, expected %d\n", ker, i, got, expected);
                        }
                }
        }
        //printf("mismatches %zu\n", mismatch);
        if (mismatch == 0) {
                printf("passed \n");
        }
        else {
                printf("%d failed\n", (int)mismatch);
        }

        printf("FPGA # of searches : %fG in %f seconds (%f Gsearches/s)\n", (double)search_num * CH_NUM*PE_NUM * 1.0e-9, fpga_time, (double)search_num * CH_NUM*PE_NUM / fpga_time * 1.0e-9  );
        ddr_bandwidth = (double)search_num * sizeof(ap_uint<512>) * CH_NUM*PE_NUM / fpga_time * 1.0e-9; 
        printf("memory bandwidth %f GB/s\n", ddr_bandwidth);



    //std::cout << "TEST " << (match ? "PASSED" : "FAILED") << std::endl;
    //return (match ? EXIT_SUCCESS : EXIT_FAILURE);
    return EXIT_SUCCESS;
}
