/**********
Copyright (c) 2018, Xilinx, Inc.
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors
may be used to endorse or promote products derived from this software
without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**********/

#include "xcl2.hpp"
#include <algorithm>
#include <vector>
#include <ap_int.h>
#include <cstdlib>
#include <chrono>

#define CH_NUM 24 

int main(int argc, char **argv) {
	printf("start host\n");

	srand(0);

	// if (argc != 6) {
	//     std::cout << "Usage: " << argv[0] << " <XCLBIN File> pseudo_alloc_size real_alloc_size if_run_write if_run_read" << std::endl;
	//     return EXIT_FAILURE;
	// }
	// int alloc_size = atoi(argv[2]);
	// int real_alloc_size = atoi(argv[3]);
	// bool run_write = atoi(argv[4]);
	// bool run_read = atoi(argv[5]);

	//const int matrix_size = CH_NUM*64;
	const int matrix_size = CH_NUM*1024;
	//const int repeat_num = 1;
	const int repeat_num = 128;
	printf("Matrix size: %d x %d\n", matrix_size, matrix_size);
	printf("Repeats: %d\n", repeat_num);

	std::string binaryFile = argv[1];
	cl_int err;
	cl::Context context;
	cl::Kernel krnl_vector_add;
	cl::CommandQueue q;

	std::vector<unsigned int, aligned_allocator<unsigned int> > host_A(matrix_size*matrix_size);
	std::vector<unsigned int, aligned_allocator<unsigned int> > host_x(matrix_size);
	std::vector<unsigned int, aligned_allocator<unsigned int> > host_y(matrix_size);
	std::vector<unsigned int, aligned_allocator<unsigned int> > host_device_y(matrix_size);

	unsigned int random_seed;
	random_seed = time(NULL);
	//random_seed = 12345;
	srand(random_seed);
	printf("Random seed: %u\n", random_seed);

	printf("Generating random input data...");
	fflush(stdout);
	for( int i = 0 ; i < matrix_size ; i++ ){
		for( int j = 0 ; j < matrix_size ; j++ ){
			host_A[i*matrix_size+j] = rand()%4;
			//host_A[i*matrix_size+j] = (float)j*0.001+i*0.01;
		}
	}
	for( int i = 0 ; i < matrix_size ; i++ ){
		host_x[i] = rand()%4;
		//host_x[i] = (float)i*0.01;
		host_y[i] = 0;
		host_device_y[i] = 0;
	}
	printf("done\n");


	printf("Performing convolution on CPU... (no repeat)\n");
	fflush(stdout);

	auto start_cpu = std::chrono::steady_clock::now(); 
#pragma omp parallel for
	for( int i = 0 ; i < matrix_size ; i++ ){
		host_y[i] = 0;
		for( int j = 0 ; j < matrix_size ; j++ ){
			host_y[i] += host_A[i*matrix_size+j] * host_x[j];
		}
	}
	auto end_cpu = std::chrono::steady_clock::now(); 
	double time_cpu = std::chrono::duration_cast<std::chrono::nanoseconds>(end_cpu - start_cpu).count(); 
	time_cpu *= 1e-9; 
	printf("done (%f sec)\n", time_cpu);
	printf("CPU GFLOPS: %f\n", 2.0f*matrix_size*matrix_size/1000000000/time_cpu);
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

		if( device.getInfo<CL_DEVICE_NAME>() != "xilinx_u50_gen3x16_xdma_201920_3" ){
		//if( device.getInfo<CL_DEVICE_NAME>() != "xilinx_u280_xdma_201920_3" ){
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
	std::vector<cl::Buffer> buffer_A;

	for (int i = 0; i < CH_NUM; i++) {
		OCL_CHECK(err,
				cl::Buffer currA(
					context,
					CL_MEM_USE_HOST_PTR | CL_MEM_READ_ONLY,
					matrix_size*matrix_size/CH_NUM*sizeof(float),
					host_A.data()+matrix_size*matrix_size/CH_NUM*i,
					&err);
			 );

		buffer_A.push_back(std::move(currA));
	}

	OCL_CHECK(err,
			cl::Buffer buffer_x(
				context,
				CL_MEM_USE_HOST_PTR | CL_MEM_READ_ONLY,
				matrix_size*sizeof(float),
				host_x.data(),
				&err);
		 );

	OCL_CHECK(err,
			cl::Buffer buffer_y(
				context,
				CL_MEM_USE_HOST_PTR | CL_MEM_WRITE_ONLY,
				matrix_size*sizeof(float),
				host_device_y.data(),
				&err);
		 );

	// set argument
	for (int i = 0; i < CH_NUM; i++) {
		OCL_CHECK(err, err = krnl_vector_add.setArg(i, buffer_A[i]));

	}
	OCL_CHECK(err, err = krnl_vector_add.setArg(CH_NUM + 0, buffer_x));
	OCL_CHECK(err, err = krnl_vector_add.setArg(CH_NUM + 1, buffer_y));
	OCL_CHECK(err, err = krnl_vector_add.setArg(CH_NUM + 2, matrix_size));
	OCL_CHECK(err, err = krnl_vector_add.setArg(CH_NUM + 3, repeat_num));

	int launch_num = 1;


	printf("move data to HBM\n");
	// Copy input data to device global memory
	for ( int i = 0; i < CH_NUM; i++) {
		OCL_CHECK(err, err = q.enqueueMigrateMemObjects({buffer_A[i]}, 0 /* 0 means from host*/));      
	}
	OCL_CHECK(err, err = q.enqueueMigrateMemObjects({buffer_x}, 0 /* 0 means from host*/));      
	q.finish();

	printf("start kernel\n");
	auto start = std::chrono::steady_clock::now(); 
	// Launch the Kernel
	for (int i = 0; i < launch_num; i++) {
		OCL_CHECK(err, err = q.enqueueTask(krnl_vector_add));
	}
	q.finish();

	auto end = std::chrono::steady_clock::now(); 
	double time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count(); 
	time_taken *= 1e-9; 

	printf("move data back to host\n");
	// Copy Result from Device Global Memory to Host Local Memory
	OCL_CHECK(err,
			err = q.enqueueMigrateMemObjects({buffer_y}, CL_MIGRATE_MEM_OBJECT_HOST));      

	printf("finish\n");
	q.finish();

	printf("Kernel time is %f s\n", time_taken);

	float gflops =  
		2.0f * repeat_num * matrix_size * matrix_size 
		* launch_num // number of iterations of kernel launch 
		/ 1e9 // convert to GB
		/ time_taken // total time in second
		;
	printf("GFLOPS:%f (%f GB/s)\n", gflops, gflops*2.0);

	// Compare the results of the Device to the simulation

	int mismatch_cnt = 0;
	for( int i = 0 ; i < matrix_size ; i++ ){
		bool mismatch = false;
		if( host_y[i] != host_device_y[i] ){
			mismatch = true;
			mismatch_cnt++;
		}
		//if( (mismatch == true && mismatch_cnt < 10) || (i < 5 ) ){
		if(mismatch == true && mismatch_cnt < 10) {
			printf("(i:%d) cpu:%d fpga:%d\n", i, host_y[i], host_device_y[i] );
		}
	}

	if( mismatch_cnt == 0 ){
		printf("Success!\n");
	}
	else{
		printf("%d/%d failed\n", mismatch_cnt, matrix_size);
	}



	//std::cout << "TEST " << (match ? "PASSED" : "FAILED") << std::endl;
	//return (match ? EXIT_SUCCESS : EXIT_FAILURE);
	return EXIT_SUCCESS;
}
