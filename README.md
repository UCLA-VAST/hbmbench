# FPGA HBM Benchmarks (Alveo U280, Stratix 10 MX)


## Contents:
* HLS microbenchmarks that measures effective BW (sequential, strided, bitwidth varied, many-to-many unicasting) and latency of FPGA HBM boards
* Dense matrix-vector multiplication
* Stencil
* Bucket sort, radix sort
* Binary search, depth-first search


## Target Platforms
* Xilinx Alveo U280, U50
* Intel Stratix 10 MX (to be updated)


## Citation
When using the files in this project, please cite:

* Y. Choi, Y. Chi, J. Wang, L. Guo, and J. Cong, "When HLS meets FPGA HBM: Benchmarking and bandwidth optimization," arXiv preprint arXiv:2010.06075, 2020.

Available at: https://arxiv.org/abs/2010.06075

## Prerequisites
* Intel Quartus (with AOCL) 19.4
* Xilinx Vitis (with Vivado HLS) 2019.2

Please refer to vendors' manual for installation steps.


## How to run
Please type "./run" in each project folder. It will generate a bitstream, compile host code, and run the program.

### If you are an UCLA VAST member:
* For Xilinx flow, please source "setup\_alveo.sh" in my home directory before compilation
* For Intel flow, please put "with-aocl" before the second and third line of "run" file:

    with-aocl make
    with-aocl ./host/host

## Description of the benchmarks

The below is a brief description of the benchmarks. Please see the cited arxiv paper for experimental result.

### Sequential access bandwidth
Measures the maximum memory bandwidth - repeatedly copies 64MB of data.
Supports read/write, read only, write only.

### Strided access bandwidth
Measures the effective bandwidth when accessing data with a fixed address stride.

### Sequential access with different bitwidth
Measures the effective bandwidth of sequential access after varying the bitwidth of the kernel's top function argument

### Many-to-many unicast bandwidth (for write)
Each PE reads from one PC and write to 8 different PCs. Data is transferred from a single source PC to a single destination PC in round-robin (many-to-many unicast).

### Read latency (pointer chasing)
Data read from a memory space is used to an address to access another memory space.

### Dense matrix-vector multiplication
We consider dense matrix-vector multiplication of $y=Ax$. The variables are stored in a 32b integer format. For ease of partitioning, matrix $A$ is assigned row and column size of PC\_num X 1024, where PC\_num is the number of PCs used in the experiment (24 to 28).

### Stencil
We apply a 3x3 Gaussian blur stencil kernel on an image of size 32768 X 32768$. Each data element is a 16-bit fixed-point number. The accelerator fetches data from all the input HBM PCs to the on-chip data-reuse line buffers, performs computation, and writes the data back to output HBM PCs.

### Bucket sort
We sort an array of keys that would be sent to buckets. Each bucket is stored in a single HBM PC, and this allows a second stage of sorting (e.g., with merge sort) to be independently performed for each bucket. We fetch keys from 8 read HBM PCs and send them to the buckets among 8 write HBM PCs. 

### Radix sort
Radix sort is composed of multiple iterations---each iteration sorting based on 3 (=log8) bits of the key. We switch the input and output PCs in each iteration and send the 512b/256b keys in a ping-pong fashion.

### Binary search
Binary search is conducted on an array with the size of 16MB. Each data element is set to 512b/256b. Each PE accesses one PC, and multiple PEs executes the search independent of each other.

### Depth-first search
Depth-first search is conducted on a binary tree implemented as a linked list. The value of each node and ID of the connected nodes form 512b/256b data. Each PE has a stack to store the address of the nodes to be searched later. 


## Copyright notice

The copyright notice of the Intel files:
[.... to be filled .....]

All the files in xilinx/ folder has been modified from the https://github.com/Xilinx/Vitis_Accel_Examples/ 19.2 version. The below is the original copyright notice from Xilinx:

/**********
Copyright (c) 2020, Xilinx, Inc.
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
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE,
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**********/

