
#include "xcl2.hpp"
#include <algorithm>
#include <vector>
#include <ap_int.h>
#include <cstdlib>
#include <chrono>

#define CH_NUM 8
#define BUCKET_PER_CH 8
using data_t = ap_uint<512>;

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
 
	int alloc_size = 2097152*8/8;
	int data_num = alloc_size;
	int data_num_check = data_num;
	if( BUCKET_PER_CH == 1 ){
		data_num_check -= 4096;
	}
	else{
		data_num_check -= 0*BUCKET_PER_CH;
	}
	//int data_num = 1024*8/8;
	int repeat_num = 1;
	//int repeat_num = 16;
	int total_size = data_num*repeat_num;
	//int data_offset = alloc_size/data_num;

	printf("# of HBM channels being used: %d (Buckets per channel : %d)\n", CH_NUM, BUCKET_PER_CH);
	printf("DATA TRANSFER SIZE (per buffer) %d (%f MB)\n", total_size, (float)total_size*sizeof(data_t)/1024/1024 );
	printf("DATA ALLOCATION SIZE (per buffer) %d (%f MB)\n", alloc_size, (float)alloc_size*sizeof(data_t)/1024/1024 );

    std::string binaryFile = argv[1];
    //size_t vector_size_bytes = sizeof(data_t) * alloc_size;
    cl_int err;
    cl::Context context;
    cl::Kernel krnl_vector_add;
    cl::CommandQueue q;

    // Allocate Memory in Host Memory
    std::vector<std::vector<data_t, aligned_allocator<data_t> > > host_buffer_in;
    for (int i = 0; i < CH_NUM; i++) {
      std::vector<data_t, aligned_allocator<data_t> > curr(alloc_size);
      host_buffer_in.push_back(std::move(curr));
    }

    for (int i = 0; i < CH_NUM; i++) {
      // std::generate(curr.begin(), curr.end(), std::rand);
      for (int j1 = 0; j1 < CH_NUM; j1++) {
      for (int j2 = 0; j2 < data_num/CH_NUM; j2++) {
        //curr[j] = CH_NUM*alloc_size-(i*alloc_size+j);
        host_buffer_in[i][j2*CH_NUM+j1] = (data_t)i*data_num*8/CH_NUM + j1*data_num/CH_NUM + j2;
        //curr[j] = ((data_t)rand()<<)+(j%CH_NUM);
        //curr[j] = rand();
      }
      }
    }

    //srand(0);
    //for (int i = 0; i < CH_NUM; i++) {
    //  std::random_shuffle (host_buffer_in[i].begin(), host_buffer_in[i].end() );
   // }

    std::vector<std::vector<data_t, aligned_allocator<data_t> > > host_buffer_out;
    for (int i = 0; i < CH_NUM*BUCKET_PER_CH; i++) {
      host_buffer_out.push_back(
        std::move(std::vector<data_t, aligned_allocator<data_t> >(alloc_size/BUCKET_PER_CH, 0))
      );
    }
    
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

	//if( device.getInfo<CL_DEVICE_NAME>() != "xilinx_u50_gen3x16_xdma_201920_3" ){
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
    std::vector<cl::Buffer> buffer_in;
    std::vector<cl::Buffer> buffer_out; 

    for (int i = 0; i < CH_NUM; i++) {
      OCL_CHECK(err,
        cl::Buffer curr_in(
          context,
          CL_MEM_USE_HOST_PTR | CL_MEM_READ_ONLY,
          sizeof(data_t) * alloc_size,
          host_buffer_in[i].data(),
          &err);
      );
      buffer_in.push_back(std::move(curr_in));
    }

    for (int i = 0; i < CH_NUM*BUCKET_PER_CH; i++) {
      OCL_CHECK(err,
        cl::Buffer curr_out(
          context,
          CL_MEM_USE_HOST_PTR | CL_MEM_WRITE_ONLY,
          sizeof(data_t) * alloc_size/BUCKET_PER_CH,
          host_buffer_out[i].data(),
          &err);
      );

      buffer_out.push_back(std::move(curr_out));
    }

    // set argument
    for (int i = 0; i < CH_NUM; i++) {
      OCL_CHECK(err, err = krnl_vector_add.setArg(i, buffer_in[i]));
    }
    for (int i = 0; i < CH_NUM; i++) {
      for (int j = 0; j < BUCKET_PER_CH; j++) {
        OCL_CHECK(err, err = krnl_vector_add.setArg(CH_NUM + i*BUCKET_PER_CH+j, buffer_out[i*BUCKET_PER_CH+j]));
      }
    }
    OCL_CHECK(err, err = krnl_vector_add.setArg(CH_NUM + CH_NUM * BUCKET_PER_CH + 0, repeat_num));
    OCL_CHECK(err, err = krnl_vector_add.setArg(CH_NUM + CH_NUM * BUCKET_PER_CH + 1, data_num_check));

    int launch_num = 1;


    printf("move data to HBM\n");
    // Copy input data to device global memory
    for ( int i = 0; i < CH_NUM; i++) {
      OCL_CHECK(err, err = q.enqueueMigrateMemObjects({buffer_in[i]}, 0 /* 0 means from host*/));      
    }
    for ( int i = 0; i < CH_NUM*BUCKET_PER_CH; i++) {
      OCL_CHECK(err, err = q.enqueueMigrateMemObjects({buffer_out[i]}, 0 /* 0 means from host*/));      
    }

    q.finish();

    // Launch the Kernel
    printf("start kernel\n");
    auto start = std::chrono::steady_clock::now(); 

    OCL_CHECK(err, err = q.enqueueTask(krnl_vector_add));
    q.finish();

    auto end = std::chrono::steady_clock::now(); 
    double time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count(); 
    time_taken *= 1e-9; 

    printf("move data back to host\n");
    // Copy Result from Device Global Memory to Host Local Memory
    for ( int i = 0; i < CH_NUM*BUCKET_PER_CH; i++) {
      OCL_CHECK(err,
        err = q.enqueueMigrateMemObjects({buffer_out[i]}, CL_MIGRATE_MEM_OBJECT_HOST));      
    }

    printf("finish\n");
    q.finish();



    printf("Kernel time is %f s\n", time_taken);
    printf("Equivalent bandwidth for read & write is %f GB/s\n", 
      1.0 * total_size // read / write size for each HBM port 
      * sizeof(data_t) 
      * launch_num // number of iterations of kernel launch 
      * 2 // read and write
      / 1e9 // convert to GB
      / time_taken // total time in second
      * CH_NUM // number of PEs
      );

    // Compare the results of the Device to the simulation
	//int* data_cnt = (int*)malloc( sizeof(int) * (alloc_size * CH_NUM + 1) );
	int* data_cnt = (int*)malloc( sizeof(int) * (data_num *8/8* CH_NUM ) );
	//for(int i = 0 ; i < alloc_size * CH_NUM + 1 ; i++ ){

	for(int i = 0 ; i < data_num *8/8* CH_NUM ; i++ ){
		data_cnt[i] = 0;
	}


	int out_of_bound_cnt = 0;
	int error_cnt = 0;
	for (int i = 0; i < CH_NUM; i++) {
		for (int j1 = 0; j1 < BUCKET_PER_CH; j1++) {
			int answer_ch = (i/BUCKET_PER_CH)*BUCKET_PER_CH+j1;
			int j2_bound = data_num_check/BUCKET_PER_CH;
			for (int j2 = 0; j2 < j2_bound; j2++) {
				data_t obtained_data = host_buffer_out[i*BUCKET_PER_CH+j1][j2];
				int trunc_data = (int)obtained_data;
				if( trunc_data < data_num *8/8* CH_NUM ){
					data_cnt[trunc_data]++;
				}
				else{
					printf("data %d's addr %d out of bound(%d)\n", trunc_data, trunc_data, data_num *8/8* CH_NUM );
					out_of_bound_cnt++;
				}
				//int j = j1*alloc_size/BUCKET_PER_CH + j2;
				int match = 1;
				int obtained_ch = (obtained_data>>(21 - 3)) & 7;
					if ( obtained_ch != answer_ch ) {
						match = 0;
						error_cnt++;
					}
				//if( (i%8 == 0 && j1%4 == 0 && j2 < 4 ) || (match == 0 && error_cnt < 10 )){
				if(match == 0 && error_cnt < 10 ){
					if(match==0){printf("(Incorrect) ");}
					printf("(answer ch:%d bucket:(%d,%d) data index:%d) data:%x its ch :%d\t\n", answer_ch, i, j1, j2, trunc_data, obtained_ch);
				}
			}
		}
	}

	printf("CH test Error_cnt : %d / %d \n", error_cnt, CH_NUM*data_num);

	printf("addr out of bound cnt : %d / %d\n", out_of_bound_cnt, data_num*CH_NUM);

	
	int* expected_cnt = (int*)malloc( sizeof(int) * (data_num *8/8* CH_NUM ) );
	for(int i = 0 ; i < data_num *8/8* CH_NUM ; i++ ){
		expected_cnt[i] = 0;
	}

	for (int i = 0; i < CH_NUM; i++) {
		// std::generate(curr.begin(), curr.end(), std::rand);
		for (int j1 = 0; j1 < CH_NUM; j1++) {
			for (int j2 = 0; j2 < data_num/CH_NUM; j2++) {
				if( j2*CH_NUM+j1 < data_num_check ){
					expected_cnt[ (data_t)i*data_num*8/CH_NUM + j1*data_num/CH_NUM + j2 ] = 1;
				}
			}
		}
	}


	error_cnt = 0;
	//for(int i = alloc_size * CH_NUM ; i > 0 ; i-- ){
	for (int i = 0; i < CH_NUM; i++) {
		for (int j = 0; j < data_num; j++) {
			if( data_cnt[i*data_num*8/8+j] != expected_cnt[i*data_num*8/8+j] ){
				error_cnt++;
				if( error_cnt < 10 ){
					printf("expected %d number of %x, but found %d\n", 1, (i*data_num*8/8+j), data_cnt[i*data_num*8/8+j]);
				}
			}		
		}		
	}
	printf("data test error_cnt : %d / %d\n", error_cnt, data_num*CH_NUM);



    //std::cout << "TEST " << (match ? "PASSED" : "FAILED") << std::endl;
    //return (match ? EXIT_SUCCESS : EXIT_FAILURE);
    return EXIT_SUCCESS;
}
