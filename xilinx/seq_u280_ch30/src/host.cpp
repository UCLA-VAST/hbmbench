
#include "xcl2.hpp"
#include <algorithm>
#include <vector>
#include <ap_int.h>
#include <cstdlib>
#include <chrono>

#define CH_NUM 30 
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
 
	int total_size = 1024*1024*16;
	int alloc_size = 1024*1024;
	int repeat_num = total_size/alloc_size;
  	bool run_write = true;
	bool run_read = true;

	printf("TOTAL DATA TRANSFER SIZE (per CH) %d (%f MB)\n", total_size, (float)total_size*sizeof(data_t)/1024/1024 );
	printf("DATA ALLOCATION SIZE (per CH) %d (%f MB)\n", alloc_size, (float)alloc_size*sizeof(data_t)/1024/1024 );
	printf("run_write : %d run_read : %d \n", run_write, run_read);

    std::string binaryFile = argv[1];
    size_t vector_size_bytes = sizeof(data_t) * alloc_size;
    cl_int err;
    cl::Context context;
    cl::Kernel krnl_vector_add;
    cl::CommandQueue q;

    // Allocate Memory in Host Memory
    std::vector<std::vector<data_t, aligned_allocator<data_t> > > host_buffer_in;
    for (int i = 0; i < CH_NUM; i++) {
      std::vector<data_t, aligned_allocator<data_t> > curr(alloc_size);
      // std::generate(curr.begin(), curr.end(), std::rand);
      for (int j = 0; j < alloc_size; j++) {
        curr[j] = j;
      }
      host_buffer_in.push_back(std::move(curr));
    }
    
    std::vector<std::vector<data_t, aligned_allocator<data_t> > > host_buffer_out;
    for (int i = 0; i < CH_NUM; i++) {
      host_buffer_out.push_back(
        std::move(std::vector<data_t, aligned_allocator<data_t> >(alloc_size, 0))
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

	if( device.getInfo<CL_DEVICE_NAME>() != "xilinx_u280_xdma_201920_3" ){
                std::cout  << "Skipping device : " << device.getInfo<CL_DEVICE_NAME>() << std::endl;
		continue;
	}
        std::cout << "Trying to program device[" << i
                  << "]: " << device.getInfo<CL_DEVICE_NAME>() << std::endl;
	auto s = std::chrono::steady_clock::now(); 
        OCL_CHECK(err,
                  cl::Program program(context, {device}, bins, NULL, &err));
        if (err != CL_SUCCESS) {
            std::cout << "Failed to program device[" << i
                      << "] with xclbin file!\n";
        } else {
		auto e1 = std::chrono::steady_clock::now(); 
		double t1 = std::chrono::duration_cast<std::chrono::nanoseconds>(e1 - s).count(); 
		t1 *= 1e-9; 
	    	printf("time is %f s\n", t1);

            std::cout << "Device[" << i << "]: program successful!\n";
            OCL_CHECK(err, krnl_vector_add = cl::Kernel(program, "vadd", &err));
		auto e2 = std::chrono::steady_clock::now(); 
		double t2 = std::chrono::duration_cast<std::chrono::nanoseconds>(e2 - s).count(); 
		t2 *= 1e-9; 
	    	printf("time is %f s\n", t2);

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
          vector_size_bytes,
          host_buffer_in[i].data(),
          &err);
      );

      OCL_CHECK(err,
        cl::Buffer curr_out(
          context,
          CL_MEM_USE_HOST_PTR | CL_MEM_WRITE_ONLY,
          vector_size_bytes,
          host_buffer_out[i].data(),
          &err);
      );

      buffer_in.push_back(std::move(curr_in));
      buffer_out.push_back(std::move(curr_out));
    }

    // set argument
    for (int i = 0; i < CH_NUM; i++) {
      OCL_CHECK(err, err = krnl_vector_add.setArg(i, buffer_in[i]));
      OCL_CHECK(err, err = krnl_vector_add.setArg(i+CH_NUM, buffer_out[i]));
    }
    OCL_CHECK(err, err = krnl_vector_add.setArg(CH_NUM * 2+0, repeat_num));
    OCL_CHECK(err, err = krnl_vector_add.setArg(CH_NUM * 2+1, alloc_size));
    OCL_CHECK(err, err = krnl_vector_add.setArg(CH_NUM * 2+2, run_write));
    OCL_CHECK(err, err = krnl_vector_add.setArg(CH_NUM * 2+3, run_read));

    int launch_num = 1;


    printf("move data to HBM\n");
    // Copy input data to device global memory
    for ( int i = 0; i < CH_NUM; i++) {
      OCL_CHECK(err, err = q.enqueueMigrateMemObjects({buffer_in[i]}, 0 /* 0 means from host*/));      
    }
    q.finish();

    printf("start kernel\n");
    auto start = std::chrono::steady_clock::now(); 
    // Launch the Kernel
    for (int i = 0; i < launch_num; i++) {
      OCL_CHECK(err, err = q.enqueueTask(krnl_vector_add));
    }
    q.finish();

    auto end = std::chrono::steady_clock::now(); 
    double time_taken =  
      std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count(); 
    time_taken *= 1e-9; 

    printf("move data back to host\n");
    // Copy Result from Device Global Memory to Host Local Memory
    for ( int i = 0; i < CH_NUM; i++) {
      OCL_CHECK(err,
        err = q.enqueueMigrateMemObjects({buffer_out[i]}, CL_MIGRATE_MEM_OBJECT_HOST));      
    }

    printf("finish\n");
    q.finish();



    printf("Kernel time is %f s\n", time_taken);
    printf("Equivalent bandwidth for read & write is %f GB/s\n", 
      1.0 * total_size // read / write size for each HBM port 
      * sizeof(data_t) 
      * (int(run_write) + int(run_read)) // accumulate write and read bandwidth
      * launch_num // number of iterations of kernel launch 
      / 1e9 // convert to GB
      / time_taken // total time in second
      * CH_NUM // number of PEs
      );

    // Compare the results of the Device to the simulation
    int error_cnt = 0;
    for (int i = 0; i < CH_NUM; i++) {
      for (int j = 0; j < alloc_size; j++) {
        int match = 1;
        if (host_buffer_out[i][j] != host_buffer_in[i][j]) {
          match = 0;
          error_cnt++;
        }
        //if( ((i == 0 || i==CH_NUM-1) && (j < 5)) || (match == 0 && error_cnt < 10 )){
        if(match == 0 && error_cnt < 10){
          printf("(%d,%d) \t %d \t %d\n", i,j, int(host_buffer_out[i][j]), int(host_buffer_in[i][j]));
        }
      }
    }

    printf("Error_cnt : %d / %d \n", error_cnt, CH_NUM*alloc_size);
    //std::cout << "TEST " << (match ? "PASSED" : "FAILED") << std::endl;
    //return (match ? EXIT_SUCCESS : EXIT_FAILURE);
    return EXIT_SUCCESS;
}
