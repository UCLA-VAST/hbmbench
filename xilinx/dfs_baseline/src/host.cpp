
#include "xcl2.hpp"
#include <algorithm>
#include <vector>
#include <ap_int.h>
#include <time.h>
#include <cstdlib>
#include <chrono>

#define CH_NUM 28 
#define PE_NUM 1 
#define QUEUE_SIZE 512 

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

	const unsigned int tar_len = 1024/PE_NUM;
	//const int tar_len = 16/PE_NUM;
	const int arr_len = 1024*64;
	//const int arr_len = 1024;
	unsigned int max_depth = logf(arr_len)/logf(2);

	//print the configuration we are working with
	printf("defines:\n");
	printf("CH_NUM :%d PE_NUM:%d\n", CH_NUM, PE_NUM);
	printf("  Target length %d (%f MB)\n", tar_len, (float)tar_len*sizeof(unsigned int)/1024/1024 );
	printf("  Array length %d (%f MB)\n", arr_len, (float)arr_len*sizeof(ap_uint<512>)/1024/1024 );
	printf(" Max_depth : %d\n", max_depth);

	std::string binaryFile = argv[1];
	cl_int err;
	cl::Context context;
	cl::Kernel krnl_vector_add;
	cl::CommandQueue q;

	printf("Generating random input data...");
	fflush(stdout);
	// Allocate Memory in Host Memory
	
	std::vector<std::vector<ap_uint<512>, aligned_allocator<ap_uint<512> > > > host_arr;
	for (int i = 0; i < CH_NUM; i++) {
		std::vector<ap_uint<512>, aligned_allocator<ap_uint<512> > > curr(arr_len*PE_NUM);
		// std::generate(curr.begin(), curr.end(), std::rand);
		if( i == 0 ){
			unsigned int depth = 1;
			unsigned int node_per_depth = 1;
			for (int j = 0; j < arr_len - 1; j++) {
				unsigned int node_id_current_depth = j - (node_per_depth - 1);
				unsigned int arr_value = rand();
				unsigned int left_child_id = node_per_depth*2 - 1 + node_id_current_depth*2;
				unsigned int right_child_id = node_per_depth*2 - 1 + node_id_current_depth*2 + 1;
				for (int k = 0; k < PE_NUM; k++) {
					curr[k*arr_len+j] = ((ap_uint<512>)arr_value) + (((ap_uint<512>)depth)<<32) + (((ap_uint<512>)left_child_id)<<64) + (((ap_uint<512>)right_child_id)<<96);
				}
				if( node_id_current_depth == node_per_depth - 1 ){
					depth++;
					node_per_depth *= 2;
				}
			}
		}
		else{
			for (int j = 0; j < arr_len; j++) {
				for (int k = 0; k < PE_NUM; k++) {
					curr[k*arr_len+j] = host_arr[0][k*arr_len+j];
				}
			}
		}
		host_arr.push_back(std::move(curr));
	}

	std::vector<unsigned int, aligned_allocator<unsigned int> > host_tar_data(tar_len*CH_NUM*PE_NUM);
	// std::generate(curr.begin(), curr.end(), std::rand);
	for (unsigned int j = 0; j < tar_len; j++) {
		int addr;
		if( arr_len > RAND_MAX ){
			addr = rand32()%arr_len;
		}
		else{
			addr = rand()%arr_len;
		}
		unsigned int value = (host_arr[0][addr])&0xffffffff;
		host_tar_data[j*CH_NUM*PE_NUM] = value; 
		for (int i = 1; i < CH_NUM*PE_NUM; i++) {
			host_tar_data[j*CH_NUM*PE_NUM+i] = host_tar_data[j*CH_NUM*PE_NUM];
		}
	}
    
	std::vector<unsigned int, aligned_allocator<unsigned int> > host_tar_addr(tar_len*CH_NUM*PE_NUM);
	for (unsigned int j = 0; j < tar_len*CH_NUM*PE_NUM; j++) {
		host_tar_addr[j] = 0;
	}

	std::vector<unsigned int, aligned_allocator<unsigned int> > host_answer(tar_len);

	printf("done\n");
        printf("Generating host answer...");
        fflush(stdout);

	unsigned int queue[QUEUE_SIZE];
    
	long long search_num = 0;
        double ddr_bandwidth;

        //generate CPU answer
	auto cpu_start = std::chrono::steady_clock::now(); 

	for(unsigned int t = 0 ; t < tar_len; t++ ){
                unsigned int tar_value = host_tar_data[t*CH_NUM*PE_NUM];
		unsigned int tree_addr = 0;
		unsigned int arr_value = 0xffffffff; 
		unsigned int queue_ptr = 0;

		while(1){
			unsigned int addr = tree_addr;
			ap_uint<512> arr_data_temp = host_arr[0][addr];
			search_num++;
			unsigned int right_node_addr = arr_data_temp(127,96);
			unsigned int left_node_addr = arr_data_temp(95,64);
			unsigned int depth = arr_data_temp(63,32);
			arr_value = arr_data_temp(31,0);

			//printf("addr:%d arr_value:%d depth:%d left_node_addr:%d right_node_addr:%d queue_ptr:%d \n", addr, arr_value, depth, left_node_addr, right_node_addr, queue_ptr);
			if( tar_value == arr_value ){
				//printf("(%d) Target value of %d found at addr %d \n", t, tar_value, tree_addr);
				break;
			}
			else{
				if( queue_ptr < 0 || queue_ptr >= QUEUE_SIZE ){
					printf("addr:%d arr_value:%d depth:%d left_node_addr:%d right_node_addr:%d queue_ptr:%d \n", addr, arr_value, depth, left_node_addr, right_node_addr, queue_ptr);
					printf("queue_ptr out of bound\n");
					exit(1);
				}
					 
				if( depth < max_depth ){
					tree_addr = left_node_addr;
					queue[queue_ptr] = right_node_addr;
					queue_ptr++;
				}
				else{ //at max depth
					queue_ptr--;
					tree_addr = queue[queue_ptr];
				}				 
			}
		}
                host_answer[t] = tree_addr;
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
    OCL_CHECK(err, err = krnl_vector_add.setArg(CH_NUM + 4, max_depth));

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
