
#include "xcl2.hpp"
#include <algorithm>
#include <vector>
#include <ap_int.h>
#include <cstdlib>
#include <chrono>

#define CH_NUM 8
#define BUCKET_PER_CH 8
#define SHIFT_NUM 2
using data_t = ap_uint<512>;

#define MAX_HBM_BANKCOUNT 32
#define BANK_NAME(n) n | XCL_MEM_TOPOLOGY
const int bank[MAX_HBM_BANKCOUNT] = {
  BANK_NAME(0),  BANK_NAME(1),  BANK_NAME(2),  BANK_NAME(3),  BANK_NAME(4),
  BANK_NAME(5),  BANK_NAME(6),  BANK_NAME(7),  BANK_NAME(8),  BANK_NAME(9),
  BANK_NAME(10), BANK_NAME(11), BANK_NAME(12), BANK_NAME(13), BANK_NAME(14),
  BANK_NAME(15), BANK_NAME(16), BANK_NAME(17), BANK_NAME(18), BANK_NAME(19),
  BANK_NAME(20), BANK_NAME(21), BANK_NAME(22), BANK_NAME(23), BANK_NAME(24),
  BANK_NAME(25), BANK_NAME(26), BANK_NAME(27), BANK_NAME(28), BANK_NAME(29),
  BANK_NAME(30), BANK_NAME(31)};

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
 
	int total_size = 1024*256*16;	
	int alloc_size = 1024*256;	
//	int total_size = 16*16*16;	
//	int alloc_size = 16*16;	

	int repeat_num = total_size/alloc_size;

	printf("# of HBM channels being used: %d (Buckets per channel : %d)\n", CH_NUM, BUCKET_PER_CH);
	printf("DATA TRANSFER SIZE (per buffer) %d (%f MB)\n", total_size, (float)total_size*sizeof(data_t)/1024/1024 );
	printf("DATA ALLOCATION SIZE (per buffer) %d (%f MB)\n", alloc_size, (float)alloc_size*2*sizeof(data_t)/1024/1024 );

  std::string binaryFile = argv[1];
  size_t vector_size_bytes = sizeof(data_t) * alloc_size;
  cl_int err;
  cl::Context context;
  cl::Kernel krnl_vector_add;
  cl::CommandQueue q;

  // Allocate Memory in Host Memory
  srand(0);
  std::vector<std::vector<data_t, aligned_allocator<data_t> > > host_buffer_in;
  for (int i = 0; i < CH_NUM*BUCKET_PER_CH; i++) {
    std::vector<data_t, aligned_allocator<data_t> > curr(alloc_size/BUCKET_PER_CH);
    for (int j = 0; j < alloc_size/BUCKET_PER_CH; j++) {
      curr[j] = CH_NUM*alloc_size-(i*alloc_size/BUCKET_PER_CH+j);      
    }
    host_buffer_in.push_back(std::move(curr));
  }  
    
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
  cl_mem_ext_ptr_t inBufExt[CH_NUM*BUCKET_PER_CH];
  cl_mem_ext_ptr_t outBufExt[CH_NUM*BUCKET_PER_CH];

  for (int i = 0; i < CH_NUM; i++) {
    for (int j = 0; j < BUCKET_PER_CH; j++) {
      inBufExt[i*BUCKET_PER_CH + j].obj = host_buffer_in[i*BUCKET_PER_CH + j].data();
      inBufExt[i*BUCKET_PER_CH + j].param = 0;
      inBufExt[i*BUCKET_PER_CH + j].flags = bank[i];
    }
  }
 
  for (int i = 0; i < CH_NUM; i++) {
    for (int j = 0; j < BUCKET_PER_CH; j++) {
      outBufExt[i*BUCKET_PER_CH + j].obj = host_buffer_out[i*BUCKET_PER_CH + j].data();
      outBufExt[i*BUCKET_PER_CH + j].param = 0;
      outBufExt[i*BUCKET_PER_CH + j].flags = bank[CH_NUM + i];
    }
  }

  for (int i = 0; i < CH_NUM*BUCKET_PER_CH; i++) {
    OCL_CHECK(err,
      cl::Buffer curr_in(
          context,
          CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE | CL_MEM_EXT_PTR_XILINX,
          vector_size_bytes/BUCKET_PER_CH,
          &inBufExt[i],          
          &err);
      );
      buffer_in.push_back(std::move(curr_in));
  }

  for (int i = 0; i < CH_NUM*BUCKET_PER_CH; i++) {
    OCL_CHECK(err,
      cl::Buffer curr_out(
        context,
        CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE | CL_MEM_EXT_PTR_XILINX,
        vector_size_bytes/BUCKET_PER_CH,
        &outBufExt[i],
        &err);
    );

    buffer_out.push_back(std::move(curr_out));
  }

  printf("move data to HBM\n");
  // Copy input data to device global memory
  for ( int i = 0; i < CH_NUM*BUCKET_PER_CH; i++) {
    OCL_CHECK(err, err = q.enqueueMigrateMemObjects({buffer_in[i]}, 0 /* 0 means from host*/));      
  }
  for ( int i = 0; i < CH_NUM*BUCKET_PER_CH; i++) {
    OCL_CHECK(err, err = q.enqueueMigrateMemObjects({buffer_out[i]}, 0 /* 0 means from host*/));      
  }

  q.finish();

  // set argument
  for (int i = 0; i < CH_NUM; i++) {
    for (int j = 0; j < BUCKET_PER_CH; j++) {
      OCL_CHECK(err, err = krnl_vector_add.setArg(
        i*BUCKET_PER_CH + j, 
        buffer_in[i*BUCKET_PER_CH + j]));
    }
  }
  for (int i = 0; i < CH_NUM; i++) {
    for (int j = 0; j < BUCKET_PER_CH; j++) {
      OCL_CHECK(err, err = krnl_vector_add.setArg(
        CH_NUM*BUCKET_PER_CH + i*BUCKET_PER_CH + j,
        buffer_out[j*CH_NUM + i]));
    }
  }
  for (int i = 0; i < CH_NUM; i++) {
    for (int j = 0; j < BUCKET_PER_CH; j++) {
      OCL_CHECK(err, err = krnl_vector_add.setArg(
        CH_NUM*BUCKET_PER_CH*2 + i*BUCKET_PER_CH + j, 
        buffer_out[i*BUCKET_PER_CH + j]));
    }
  }
  for (int i = 0; i < CH_NUM; i++) {
    for (int j = 0; j < BUCKET_PER_CH; j++) {
      OCL_CHECK(err, err = krnl_vector_add.setArg(
        CH_NUM*BUCKET_PER_CH*3 + i*BUCKET_PER_CH + j,
        buffer_in[j*CH_NUM + i]));
    }
  } 

  OCL_CHECK(err, err = krnl_vector_add.setArg(CH_NUM*BUCKET_PER_CH*4 + 0, repeat_num));
  OCL_CHECK(err, err = krnl_vector_add.setArg(CH_NUM*BUCKET_PER_CH*4 + 1, alloc_size/BUCKET_PER_CH));  

  int launch_num = 1;


  double time_taken = 0;
  for (int s = 0; s < SHIFT_NUM; s++) {  
    OCL_CHECK(err, err = krnl_vector_add.setArg(CH_NUM*BUCKET_PER_CH*4 + 2, s));
  
    // Launch the Kernel
    printf("start kernel\n");
    auto start = std::chrono::steady_clock::now(); 

    OCL_CHECK(err, err = q.enqueueTask(krnl_vector_add));
    q.finish();

    auto end = std::chrono::steady_clock::now(); 
    time_taken += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count(); 
  }
    
  time_taken *= 1e-9; 
  printf("move data back to host\n");
  // Copy Result from Device Global Memory to Host Local Memory
  if (SHIFT_NUM%2 == 1) {
    for ( int i = 0; i < CH_NUM*BUCKET_PER_CH; i++) {
      OCL_CHECK(err,
        err = q.enqueueMigrateMemObjects({buffer_out[i]}, CL_MIGRATE_MEM_OBJECT_HOST));      
    }
  } else {
    for ( int i = 0; i < CH_NUM*BUCKET_PER_CH; i++) {
      OCL_CHECK(err,
        err = q.enqueueMigrateMemObjects({buffer_in[i]}, CL_MIGRATE_MEM_OBJECT_HOST));      
    }
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
      * SHIFT_NUM
      );


  // Compare the results of the Device to the simulation
  int error_cnt = 0;
  for (int i = 0; i < CH_NUM; i++) {
    for (int j1 = 0; j1 < BUCKET_PER_CH; j1++) {
      int answer_ch = i;
      for (int j2 = 0; j2 < alloc_size/BUCKET_PER_CH; j2++) {
        int obtained_ch;
        if (SHIFT_NUM%2 == 1) {
	        obtained_ch = 
            (host_buffer_out[i*BUCKET_PER_CH+j1][j2]>>(3*(SHIFT_NUM-1))) & 7;
        } else {
          obtained_ch = 
            (host_buffer_in[i*BUCKET_PER_CH+j1][j2]>>(3*(SHIFT_NUM-1))) & 7;
        }
        if ( obtained_ch != answer_ch ) {         
          error_cnt++;
        }        
      }
    }
  }

  printf("Error_cnt : %d / %d \n", error_cnt, CH_NUM*alloc_size);  
  return EXIT_SUCCESS;
}
