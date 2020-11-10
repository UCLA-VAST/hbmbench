
#include <ap_int.h>
#include <ap_utils.h>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <hls_stream.h>

template<class T>
T HLS_REG(T in){
#pragma HLS pipeline
#pragma HLS inline off
#pragma HLS interface port=return register
    return in;
}

void read_tar_data(const ap_uint<128>* tar_data_port,
	hls::stream<ap_uint<128> > & tar_data_fifo0, 
	hls::stream<ap_uint<128> > & tar_data_fifo1, 
	hls::stream<ap_uint<128> > & tar_data_fifo2, 
	hls::stream<ap_uint<128> > & tar_data_fifo3, 
	hls::stream<ap_uint<128> > & tar_data_fifo4, 
	hls::stream<ap_uint<128> > & tar_data_fifo5, 
	hls::stream<ap_uint<128> > & tar_data_fifo6, 
	const unsigned int tar_len
)
{
	for(int t = 0 ; t < tar_len ; t++ ){
		for(int ch_pe = 0 ; ch_pe < 28/4 ; ch_pe++ ){
#pragma HLS pipeline II=1
	                ap_uint<128> tar_value = tar_data_port[t*28/4+ch_pe];
			switch(ch_pe){
				case 0 : 
					tar_data_fifo0.write(HLS_REG(HLS_REG(tar_value)));
                                        break;
				case 1 : 
					tar_data_fifo1.write(HLS_REG(HLS_REG(tar_value)));
                                        break;
				case 2 : 
					tar_data_fifo2.write(HLS_REG(HLS_REG(tar_value)));
                                        break;
				case 3 : 
					tar_data_fifo3.write(HLS_REG(HLS_REG(tar_value)));
                                        break;
				case 4 : 
					tar_data_fifo4.write(HLS_REG(HLS_REG(tar_value)));
                                        break;
				case 5 : 
					tar_data_fifo5.write(HLS_REG(HLS_REG(tar_value)));
                                        break;
				default :
					tar_data_fifo6.write(HLS_REG(HLS_REG(tar_value)));
                                        break;
			}
        	}
        }
}

void split_tar_data(
	hls::stream<ap_uint<128> > & tar_data_in, 
	hls::stream<unsigned int> & tar_data_out0, 
	hls::stream<unsigned int> & tar_data_out1, 
	hls::stream<unsigned int> & tar_data_out2, 
	hls::stream<unsigned int> & tar_data_out3, 
	const unsigned int tar_len
)
{
	for(int t = 0 ; t < tar_len ; t++ ){
#pragma HLS pipeline II=1
                ap_uint<128> tar_value = tar_data_in.read();
		ap_uint<32> tar_value0_temp = tar_value(31,0); unsigned int tar_value0 = tar_value0_temp;
		ap_uint<32> tar_value1_temp = tar_value(63,32); unsigned int tar_value1 = tar_value1_temp;
		ap_uint<32> tar_value2_temp = tar_value(95,64); unsigned int tar_value2 = tar_value2_temp;
		ap_uint<32> tar_value3_temp = tar_value(127,96); unsigned int tar_value3 = tar_value3_temp;
		tar_data_out0.write(tar_value0);
		tar_data_out1.write(tar_value1);
		tar_data_out2.write(tar_value2);
		tar_data_out3.write(tar_value3);
        }
}

void binsearch(const ap_uint<512>* arr_port, hls::stream<unsigned int> & tar_data_fifo, hls::stream<unsigned int> & tar_addr_fifo, const unsigned int tar_len, const unsigned int arr_len)
{
	for(int t = 0 ; t < tar_len ; t++ ){
                unsigned int tar_value = tar_data_fifo.read();
                unsigned int left = 0;
                unsigned int right = arr_len-1;
                unsigned int middle;

                while( left <= right ){
#pragma HLS pipeline II=1
                        middle = (left+right)/2;
                        unsigned int arr_value = (unsigned int)arr_port[middle];
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

                tar_addr_fifo.write(middle);
        }
}

void merge_tar_addr(
	hls::stream<unsigned int> & tar_addr_in0, 
	hls::stream<unsigned int> & tar_addr_in1, 
	hls::stream<unsigned int> & tar_addr_in2, 
	hls::stream<unsigned int> & tar_addr_in3, 
	hls::stream<ap_uint<128> > & tar_addr_out, 
	const unsigned int tar_len
)
{
	for(int t = 0 ; t < tar_len ; t++ ){
#pragma HLS pipeline II=1
		ap_uint<128> tar_addr;
		unsigned int tar_value0_temp = tar_addr_in0.read();
		unsigned int tar_value1_temp = tar_addr_in1.read();
		unsigned int tar_value2_temp = tar_addr_in2.read();
		unsigned int tar_value3_temp = tar_addr_in3.read();
		ap_uint<32> tar_value0 = tar_value0_temp;  
		tar_addr(31,0)= tar_value0; 
		ap_uint<32> tar_value1 = tar_value1_temp;  
		tar_addr(63,32)= tar_value1; 
		ap_uint<32> tar_value2 = tar_value2_temp;  
		tar_addr(95,64)= tar_value2; 
		ap_uint<32> tar_value3 = tar_value3_temp;  
		tar_addr(127,96)= tar_value3; 
		tar_addr_out.write(tar_addr);
        }
}

void write_tar_addr(ap_uint<128>* tar_addr_port,
	hls::stream<ap_uint<128> > & tar_addr_fifo0, 
	hls::stream<ap_uint<128> > & tar_addr_fifo1, 
	hls::stream<ap_uint<128> > & tar_addr_fifo2, 
	hls::stream<ap_uint<128> > & tar_addr_fifo3, 
	hls::stream<ap_uint<128> > & tar_addr_fifo4, 
	hls::stream<ap_uint<128> > & tar_addr_fifo5, 
	hls::stream<ap_uint<128> > & tar_addr_fifo6, 
	const unsigned int tar_len
)
{
	for(int t = 0 ; t < tar_len ; t++ ){
#pragma HLS loop_flatten off
		for(int ch_pe = 0 ; ch_pe < 28/4 ; ch_pe++ ){
#pragma HLS pipeline II=1
			ap_uint<128> tar_addr;
			switch(ch_pe){
				case 0 : 
					tar_addr = HLS_REG(HLS_REG(tar_addr_fifo0.read()));  
                                        break;
				case 1 : 
					tar_addr = HLS_REG(HLS_REG(tar_addr_fifo1.read()));  
                                        break;
				case 2 : 
					tar_addr = HLS_REG(HLS_REG(tar_addr_fifo2.read()));  
                                        break;
				case 3 : 
					tar_addr = HLS_REG(HLS_REG(tar_addr_fifo3.read()));  
                                        break;
				case 4 : 
					tar_addr = HLS_REG(HLS_REG(tar_addr_fifo4.read()));  
                                        break;
				case 5 : 
					tar_addr = HLS_REG(HLS_REG(tar_addr_fifo5.read()));  
                                        break;
				default :
					tar_addr = HLS_REG(HLS_REG(tar_addr_fifo6.read()));  
                                        break;
			}
			tar_addr_port[t*28/4+ch_pe] = tar_addr;
        	}
        }
}

#ifndef HLS
extern "C" {
#endif

void vadd(
  const ap_uint<128> *tar_data_port,
  ap_uint<128> *tar_addr_port,
  const ap_uint<512> *arr_port0,
  const ap_uint<512> *arr_port1,
  const ap_uint<512> *arr_port2,
  const ap_uint<512> *arr_port3,
  const ap_uint<512> *arr_port4,
  const ap_uint<512> *arr_port5,
  const ap_uint<512> *arr_port6,
  const ap_uint<512> *arr_port7,
  const ap_uint<512> *arr_port8,
  const ap_uint<512> *arr_port9,
  const ap_uint<512> *arr_port10,
  const ap_uint<512> *arr_port11,
  const ap_uint<512> *arr_port12,
  const ap_uint<512> *arr_port13,
  const ap_uint<512> *arr_port14,
  const ap_uint<512> *arr_port15,
  const ap_uint<512> *arr_port16,
  const ap_uint<512> *arr_port17,
  const ap_uint<512> *arr_port18,
  const ap_uint<512> *arr_port19,
  const ap_uint<512> *arr_port20,
  const ap_uint<512> *arr_port21,
  const ap_uint<512> *arr_port22,
  const ap_uint<512> *arr_port23,
  const ap_uint<512> *arr_port24,
  const ap_uint<512> *arr_port25,
  const ap_uint<512> *arr_port26,
  const ap_uint<512> *arr_port27,
  const unsigned int tar_len,
  const unsigned int arr_len
) {
#pragma HLS INTERFACE m_axi port = tar_data_port offset = slave bundle = hbm0  
#pragma HLS INTERFACE m_axi port = tar_addr_port offset = slave bundle = hbm1  
#pragma HLS INTERFACE m_axi port = arr_port0 offset = slave bundle = hbm2  
#pragma HLS INTERFACE m_axi port = arr_port1 offset = slave bundle = hbm3  
#pragma HLS INTERFACE m_axi port = arr_port2 offset = slave bundle = hbm4  
#pragma HLS INTERFACE m_axi port = arr_port3 offset = slave bundle = hbm5  
#pragma HLS INTERFACE m_axi port = arr_port4 offset = slave bundle = hbm6  
#pragma HLS INTERFACE m_axi port = arr_port5 offset = slave bundle = hbm7  
#pragma HLS INTERFACE m_axi port = arr_port6 offset = slave bundle = hbm8  
#pragma HLS INTERFACE m_axi port = arr_port7 offset = slave bundle = hbm9  
#pragma HLS INTERFACE m_axi port = arr_port8 offset = slave bundle = hbm10  
#pragma HLS INTERFACE m_axi port = arr_port9 offset = slave bundle = hbm11  
#pragma HLS INTERFACE m_axi port = arr_port10 offset = slave bundle = hbm12  
#pragma HLS INTERFACE m_axi port = arr_port11 offset = slave bundle = hbm13  
#pragma HLS INTERFACE m_axi port = arr_port12 offset = slave bundle = hbm14  
#pragma HLS INTERFACE m_axi port = arr_port13 offset = slave bundle = hbm15  
#pragma HLS INTERFACE m_axi port = arr_port14 offset = slave bundle = hbm16  
#pragma HLS INTERFACE m_axi port = arr_port15 offset = slave bundle = hbm17  
#pragma HLS INTERFACE m_axi port = arr_port16 offset = slave bundle = hbm18  
#pragma HLS INTERFACE m_axi port = arr_port17 offset = slave bundle = hbm19  
#pragma HLS INTERFACE m_axi port = arr_port18 offset = slave bundle = hbm20  
#pragma HLS INTERFACE m_axi port = arr_port19 offset = slave bundle = hbm21  
#pragma HLS INTERFACE m_axi port = arr_port20 offset = slave bundle = hbm22  
#pragma HLS INTERFACE m_axi port = arr_port21 offset = slave bundle = hbm23  
#pragma HLS INTERFACE m_axi port = arr_port22 offset = slave bundle = hbm24  
#pragma HLS INTERFACE m_axi port = arr_port23 offset = slave bundle = hbm25  
#pragma HLS INTERFACE m_axi port = arr_port24 offset = slave bundle = hbm26  
#pragma HLS INTERFACE m_axi port = arr_port25 offset = slave bundle = hbm27  
#pragma HLS INTERFACE m_axi port = arr_port26 offset = slave bundle = hbm28  
#pragma HLS INTERFACE m_axi port = arr_port27 offset = slave bundle = hbm29  

#pragma HLS INTERFACE s_axilite port = tar_len bundle = control
#pragma HLS INTERFACE s_axilite port = arr_len bundle = control
#pragma HLS INTERFACE s_axilite port = return bundle = control

#pragma HLS dataflow

  hls::stream<unsigned int> tar_data_fifo0 ;   
  hls::stream<unsigned int> tar_addr_fifo0 ;   
  hls::stream<unsigned int> tar_data_fifo1 ;   
  hls::stream<unsigned int> tar_addr_fifo1 ;   
  hls::stream<unsigned int> tar_data_fifo2 ;   
  hls::stream<unsigned int> tar_addr_fifo2 ;   
  hls::stream<unsigned int> tar_data_fifo3 ;   
  hls::stream<unsigned int> tar_addr_fifo3 ;   
  hls::stream<unsigned int> tar_data_fifo4 ;   
  hls::stream<unsigned int> tar_addr_fifo4 ;   
  hls::stream<unsigned int> tar_data_fifo5 ;   
  hls::stream<unsigned int> tar_addr_fifo5 ;   
  hls::stream<unsigned int> tar_data_fifo6 ;   
  hls::stream<unsigned int> tar_addr_fifo6 ;   
  hls::stream<unsigned int> tar_data_fifo7 ;   
  hls::stream<unsigned int> tar_addr_fifo7 ;   
  hls::stream<unsigned int> tar_data_fifo8 ;   
  hls::stream<unsigned int> tar_addr_fifo8 ;   
  hls::stream<unsigned int> tar_data_fifo9 ;   
  hls::stream<unsigned int> tar_addr_fifo9 ;   
  hls::stream<unsigned int> tar_data_fifo10 ;   
  hls::stream<unsigned int> tar_addr_fifo10 ;   
  hls::stream<unsigned int> tar_data_fifo11 ;   
  hls::stream<unsigned int> tar_addr_fifo11 ;   
  hls::stream<unsigned int> tar_data_fifo12 ;   
  hls::stream<unsigned int> tar_addr_fifo12 ;   
  hls::stream<unsigned int> tar_data_fifo13 ;   
  hls::stream<unsigned int> tar_addr_fifo13 ;   
  hls::stream<unsigned int> tar_data_fifo14 ;   
  hls::stream<unsigned int> tar_addr_fifo14 ;   
  hls::stream<unsigned int> tar_data_fifo15 ;   
  hls::stream<unsigned int> tar_addr_fifo15 ;   
  hls::stream<unsigned int> tar_data_fifo16 ;   
  hls::stream<unsigned int> tar_addr_fifo16 ;   
  hls::stream<unsigned int> tar_data_fifo17 ;   
  hls::stream<unsigned int> tar_addr_fifo17 ;   
  hls::stream<unsigned int> tar_data_fifo18 ;   
  hls::stream<unsigned int> tar_addr_fifo18 ;   
  hls::stream<unsigned int> tar_data_fifo19 ;   
  hls::stream<unsigned int> tar_addr_fifo19 ;   
  hls::stream<unsigned int> tar_data_fifo20 ;   
  hls::stream<unsigned int> tar_addr_fifo20 ;   
  hls::stream<unsigned int> tar_data_fifo21 ;   
  hls::stream<unsigned int> tar_addr_fifo21 ;   
  hls::stream<unsigned int> tar_data_fifo22 ;   
  hls::stream<unsigned int> tar_addr_fifo22 ;   
  hls::stream<unsigned int> tar_data_fifo23 ;   
  hls::stream<unsigned int> tar_addr_fifo23 ;   
  hls::stream<unsigned int> tar_data_fifo24 ;   
  hls::stream<unsigned int> tar_addr_fifo24 ;   
  hls::stream<unsigned int> tar_data_fifo25 ;   
  hls::stream<unsigned int> tar_addr_fifo25 ;   
  hls::stream<unsigned int> tar_data_fifo26 ;   
  hls::stream<unsigned int> tar_addr_fifo26 ;   
  hls::stream<unsigned int> tar_data_fifo27 ;   
  hls::stream<unsigned int> tar_addr_fifo27 ;   

  hls::stream<ap_uint<128> > tar_data128_fifo0;   
  hls::stream<ap_uint<128> > tar_addr128_fifo0;   
  hls::stream<ap_uint<128> > tar_data128_fifo1;   
  hls::stream<ap_uint<128> > tar_addr128_fifo1;   
  hls::stream<ap_uint<128> > tar_data128_fifo2;   
  hls::stream<ap_uint<128> > tar_addr128_fifo2;   
  hls::stream<ap_uint<128> > tar_data128_fifo3;   
  hls::stream<ap_uint<128> > tar_addr128_fifo3;   
  hls::stream<ap_uint<128> > tar_data128_fifo4;   
  hls::stream<ap_uint<128> > tar_addr128_fifo4;   
  hls::stream<ap_uint<128> > tar_data128_fifo5;   
  hls::stream<ap_uint<128> > tar_addr128_fifo5;   
  hls::stream<ap_uint<128> > tar_data128_fifo6;   
  hls::stream<ap_uint<128> > tar_addr128_fifo6;   

#pragma HLS STREAM variable=tar_data_fifo0  depth=2 dim=1
#pragma HLS STREAM variable=tar_addr_fifo0  depth=2 dim=1
#pragma HLS RESOURCE variable=tar_data_fifo0 core=FIFO_SRL
#pragma HLS RESOURCE variable=tar_addr_fifo0 core=FIFO_SRL
#pragma HLS STREAM variable=tar_data_fifo1  depth=2 dim=1
#pragma HLS STREAM variable=tar_addr_fifo1  depth=2 dim=1
#pragma HLS RESOURCE variable=tar_data_fifo1 core=FIFO_SRL
#pragma HLS RESOURCE variable=tar_addr_fifo1 core=FIFO_SRL
#pragma HLS STREAM variable=tar_data_fifo2  depth=2 dim=1
#pragma HLS STREAM variable=tar_addr_fifo2  depth=2 dim=1
#pragma HLS RESOURCE variable=tar_data_fifo2 core=FIFO_SRL
#pragma HLS RESOURCE variable=tar_addr_fifo2 core=FIFO_SRL
#pragma HLS STREAM variable=tar_data_fifo3  depth=2 dim=1
#pragma HLS STREAM variable=tar_addr_fifo3  depth=2 dim=1
#pragma HLS RESOURCE variable=tar_data_fifo3 core=FIFO_SRL
#pragma HLS RESOURCE variable=tar_addr_fifo3 core=FIFO_SRL
#pragma HLS STREAM variable=tar_data_fifo4  depth=2 dim=1
#pragma HLS STREAM variable=tar_addr_fifo4  depth=2 dim=1
#pragma HLS RESOURCE variable=tar_data_fifo4 core=FIFO_SRL
#pragma HLS RESOURCE variable=tar_addr_fifo4 core=FIFO_SRL
#pragma HLS STREAM variable=tar_data_fifo5  depth=2 dim=1
#pragma HLS STREAM variable=tar_addr_fifo5  depth=2 dim=1
#pragma HLS RESOURCE variable=tar_data_fifo5 core=FIFO_SRL
#pragma HLS RESOURCE variable=tar_addr_fifo5 core=FIFO_SRL
#pragma HLS STREAM variable=tar_data_fifo6  depth=2 dim=1
#pragma HLS STREAM variable=tar_addr_fifo6  depth=2 dim=1
#pragma HLS RESOURCE variable=tar_data_fifo6 core=FIFO_SRL
#pragma HLS RESOURCE variable=tar_addr_fifo6 core=FIFO_SRL
#pragma HLS STREAM variable=tar_data_fifo7  depth=2 dim=1
#pragma HLS STREAM variable=tar_addr_fifo7  depth=2 dim=1
#pragma HLS RESOURCE variable=tar_data_fifo7 core=FIFO_SRL
#pragma HLS RESOURCE variable=tar_addr_fifo7 core=FIFO_SRL
#pragma HLS STREAM variable=tar_data_fifo8  depth=2 dim=1
#pragma HLS STREAM variable=tar_addr_fifo8  depth=2 dim=1
#pragma HLS RESOURCE variable=tar_data_fifo8 core=FIFO_SRL
#pragma HLS RESOURCE variable=tar_addr_fifo8 core=FIFO_SRL
#pragma HLS STREAM variable=tar_data_fifo9  depth=2 dim=1
#pragma HLS STREAM variable=tar_addr_fifo9  depth=2 dim=1
#pragma HLS RESOURCE variable=tar_data_fifo9 core=FIFO_SRL
#pragma HLS RESOURCE variable=tar_addr_fifo9 core=FIFO_SRL
#pragma HLS STREAM variable=tar_data_fifo10  depth=2 dim=1
#pragma HLS STREAM variable=tar_addr_fifo10  depth=2 dim=1
#pragma HLS RESOURCE variable=tar_data_fifo10 core=FIFO_SRL
#pragma HLS RESOURCE variable=tar_addr_fifo10 core=FIFO_SRL
#pragma HLS STREAM variable=tar_data_fifo11  depth=2 dim=1
#pragma HLS STREAM variable=tar_addr_fifo11  depth=2 dim=1
#pragma HLS RESOURCE variable=tar_data_fifo11 core=FIFO_SRL
#pragma HLS RESOURCE variable=tar_addr_fifo11 core=FIFO_SRL
#pragma HLS STREAM variable=tar_data_fifo12  depth=2 dim=1
#pragma HLS STREAM variable=tar_addr_fifo12  depth=2 dim=1
#pragma HLS RESOURCE variable=tar_data_fifo12 core=FIFO_SRL
#pragma HLS RESOURCE variable=tar_addr_fifo12 core=FIFO_SRL
#pragma HLS STREAM variable=tar_data_fifo13  depth=2 dim=1
#pragma HLS STREAM variable=tar_addr_fifo13  depth=2 dim=1
#pragma HLS RESOURCE variable=tar_data_fifo13 core=FIFO_SRL
#pragma HLS RESOURCE variable=tar_addr_fifo13 core=FIFO_SRL
#pragma HLS STREAM variable=tar_data_fifo14  depth=2 dim=1
#pragma HLS STREAM variable=tar_addr_fifo14  depth=2 dim=1
#pragma HLS RESOURCE variable=tar_data_fifo14 core=FIFO_SRL
#pragma HLS RESOURCE variable=tar_addr_fifo14 core=FIFO_SRL
#pragma HLS STREAM variable=tar_data_fifo15  depth=2 dim=1
#pragma HLS STREAM variable=tar_addr_fifo15  depth=2 dim=1
#pragma HLS RESOURCE variable=tar_data_fifo15 core=FIFO_SRL
#pragma HLS RESOURCE variable=tar_addr_fifo15 core=FIFO_SRL
#pragma HLS STREAM variable=tar_data_fifo16  depth=2 dim=1
#pragma HLS STREAM variable=tar_addr_fifo16  depth=2 dim=1
#pragma HLS RESOURCE variable=tar_data_fifo16 core=FIFO_SRL
#pragma HLS RESOURCE variable=tar_addr_fifo16 core=FIFO_SRL
#pragma HLS STREAM variable=tar_data_fifo17  depth=2 dim=1
#pragma HLS STREAM variable=tar_addr_fifo17  depth=2 dim=1
#pragma HLS RESOURCE variable=tar_data_fifo17 core=FIFO_SRL
#pragma HLS RESOURCE variable=tar_addr_fifo17 core=FIFO_SRL
#pragma HLS STREAM variable=tar_data_fifo18  depth=2 dim=1
#pragma HLS STREAM variable=tar_addr_fifo18  depth=2 dim=1
#pragma HLS RESOURCE variable=tar_data_fifo18 core=FIFO_SRL
#pragma HLS RESOURCE variable=tar_addr_fifo18 core=FIFO_SRL
#pragma HLS STREAM variable=tar_data_fifo19  depth=2 dim=1
#pragma HLS STREAM variable=tar_addr_fifo19  depth=2 dim=1
#pragma HLS RESOURCE variable=tar_data_fifo19 core=FIFO_SRL
#pragma HLS RESOURCE variable=tar_addr_fifo19 core=FIFO_SRL
#pragma HLS STREAM variable=tar_data_fifo20  depth=2 dim=1
#pragma HLS STREAM variable=tar_addr_fifo20  depth=2 dim=1
#pragma HLS RESOURCE variable=tar_data_fifo20 core=FIFO_SRL
#pragma HLS RESOURCE variable=tar_addr_fifo20 core=FIFO_SRL
#pragma HLS STREAM variable=tar_data_fifo21  depth=2 dim=1
#pragma HLS STREAM variable=tar_addr_fifo21  depth=2 dim=1
#pragma HLS RESOURCE variable=tar_data_fifo21 core=FIFO_SRL
#pragma HLS RESOURCE variable=tar_addr_fifo21 core=FIFO_SRL
#pragma HLS STREAM variable=tar_data_fifo22  depth=2 dim=1
#pragma HLS STREAM variable=tar_addr_fifo22  depth=2 dim=1
#pragma HLS RESOURCE variable=tar_data_fifo22 core=FIFO_SRL
#pragma HLS RESOURCE variable=tar_addr_fifo22 core=FIFO_SRL
#pragma HLS STREAM variable=tar_data_fifo23  depth=2 dim=1
#pragma HLS STREAM variable=tar_addr_fifo23  depth=2 dim=1
#pragma HLS RESOURCE variable=tar_data_fifo23 core=FIFO_SRL
#pragma HLS RESOURCE variable=tar_addr_fifo23 core=FIFO_SRL
#pragma HLS STREAM variable=tar_data_fifo24  depth=2 dim=1
#pragma HLS STREAM variable=tar_addr_fifo24  depth=2 dim=1
#pragma HLS RESOURCE variable=tar_data_fifo24 core=FIFO_SRL
#pragma HLS RESOURCE variable=tar_addr_fifo24 core=FIFO_SRL
#pragma HLS STREAM variable=tar_data_fifo25  depth=2 dim=1
#pragma HLS STREAM variable=tar_addr_fifo25  depth=2 dim=1
#pragma HLS RESOURCE variable=tar_data_fifo25 core=FIFO_SRL
#pragma HLS RESOURCE variable=tar_addr_fifo25 core=FIFO_SRL
#pragma HLS STREAM variable=tar_data_fifo26  depth=2 dim=1
#pragma HLS STREAM variable=tar_addr_fifo26  depth=2 dim=1
#pragma HLS RESOURCE variable=tar_data_fifo26 core=FIFO_SRL
#pragma HLS RESOURCE variable=tar_addr_fifo26 core=FIFO_SRL
#pragma HLS STREAM variable=tar_data_fifo27  depth=2 dim=1
#pragma HLS STREAM variable=tar_addr_fifo27  depth=2 dim=1
#pragma HLS RESOURCE variable=tar_data_fifo27 core=FIFO_SRL
#pragma HLS RESOURCE variable=tar_addr_fifo27 core=FIFO_SRL

#pragma HLS STREAM variable=tar_data128_fifo0  depth=2 dim=1
#pragma HLS STREAM variable=tar_addr128_fifo0  depth=2 dim=1
#pragma HLS RESOURCE variable=tar_data128_fifo0 core=FIFO_SRL
#pragma HLS RESOURCE variable=tar_addr128_fifo0 core=FIFO_SRL
#pragma HLS STREAM variable=tar_data128_fifo1  depth=2 dim=1
#pragma HLS STREAM variable=tar_addr128_fifo1  depth=2 dim=1
#pragma HLS RESOURCE variable=tar_data128_fifo1 core=FIFO_SRL
#pragma HLS RESOURCE variable=tar_addr128_fifo1 core=FIFO_SRL
#pragma HLS STREAM variable=tar_data128_fifo2  depth=2 dim=1
#pragma HLS STREAM variable=tar_addr128_fifo2  depth=2 dim=1
#pragma HLS RESOURCE variable=tar_data128_fifo2 core=FIFO_SRL
#pragma HLS RESOURCE variable=tar_addr128_fifo2 core=FIFO_SRL
#pragma HLS STREAM variable=tar_data128_fifo3  depth=2 dim=1
#pragma HLS STREAM variable=tar_addr128_fifo3  depth=2 dim=1
#pragma HLS RESOURCE variable=tar_data128_fifo3 core=FIFO_SRL
#pragma HLS RESOURCE variable=tar_addr128_fifo3 core=FIFO_SRL
#pragma HLS STREAM variable=tar_data128_fifo4  depth=2 dim=1
#pragma HLS STREAM variable=tar_addr128_fifo4  depth=2 dim=1
#pragma HLS RESOURCE variable=tar_data128_fifo4 core=FIFO_SRL
#pragma HLS RESOURCE variable=tar_addr128_fifo4 core=FIFO_SRL
#pragma HLS STREAM variable=tar_data128_fifo5  depth=2 dim=1
#pragma HLS STREAM variable=tar_addr128_fifo5  depth=2 dim=1
#pragma HLS RESOURCE variable=tar_data128_fifo5 core=FIFO_SRL
#pragma HLS RESOURCE variable=tar_addr128_fifo5 core=FIFO_SRL
#pragma HLS STREAM variable=tar_data128_fifo6  depth=2 dim=1
#pragma HLS STREAM variable=tar_addr128_fifo6  depth=2 dim=1
#pragma HLS RESOURCE variable=tar_data128_fifo6 core=FIFO_SRL
#pragma HLS RESOURCE variable=tar_addr128_fifo6 core=FIFO_SRL

	read_tar_data(
		tar_data_port,
		tar_data128_fifo0, 
		tar_data128_fifo1, 
		tar_data128_fifo2, 
		tar_data128_fifo3, 
		tar_data128_fifo4, 
		tar_data128_fifo5, 
		tar_data128_fifo6, 
		tar_len
	);

	split_tar_data(
		tar_data128_fifo0, 
		tar_data_fifo0,
		tar_data_fifo1,
		tar_data_fifo2,
		tar_data_fifo3,
		tar_len
	);
	split_tar_data(
		tar_data128_fifo1, 
		tar_data_fifo4,
		tar_data_fifo5,
		tar_data_fifo6,
		tar_data_fifo7,
		tar_len
	);
	split_tar_data(
		tar_data128_fifo2, 
		tar_data_fifo8,
		tar_data_fifo9,
		tar_data_fifo10,
		tar_data_fifo11,
		tar_len
	);
	split_tar_data(
		tar_data128_fifo3, 
		tar_data_fifo12,
		tar_data_fifo13,
		tar_data_fifo14,
		tar_data_fifo15,
		tar_len
	);
	split_tar_data(
		tar_data128_fifo4, 
		tar_data_fifo16,
		tar_data_fifo17,
		tar_data_fifo18,
		tar_data_fifo19,
		tar_len
	);
	split_tar_data(
		tar_data128_fifo5, 
		tar_data_fifo20,
		tar_data_fifo21,
		tar_data_fifo22,
		tar_data_fifo23,
		tar_len
	);
	split_tar_data(
		tar_data128_fifo6, 
		tar_data_fifo24,
		tar_data_fifo25,
		tar_data_fifo26,
		tar_data_fifo27,
		tar_len
	);


	binsearch(arr_port0, tar_data_fifo0, tar_addr_fifo0, tar_len, arr_len);
	binsearch(arr_port1, tar_data_fifo1, tar_addr_fifo1, tar_len, arr_len);
	binsearch(arr_port2, tar_data_fifo2, tar_addr_fifo2, tar_len, arr_len);
	binsearch(arr_port3, tar_data_fifo3, tar_addr_fifo3, tar_len, arr_len);
	binsearch(arr_port4, tar_data_fifo4, tar_addr_fifo4, tar_len, arr_len);
	binsearch(arr_port5, tar_data_fifo5, tar_addr_fifo5, tar_len, arr_len);
	binsearch(arr_port6, tar_data_fifo6, tar_addr_fifo6, tar_len, arr_len);
	binsearch(arr_port7, tar_data_fifo7, tar_addr_fifo7, tar_len, arr_len);
	binsearch(arr_port8, tar_data_fifo8, tar_addr_fifo8, tar_len, arr_len);
	binsearch(arr_port9, tar_data_fifo9, tar_addr_fifo9, tar_len, arr_len);
	binsearch(arr_port10, tar_data_fifo10, tar_addr_fifo10, tar_len, arr_len);
	binsearch(arr_port11, tar_data_fifo11, tar_addr_fifo11, tar_len, arr_len);
	binsearch(arr_port12, tar_data_fifo12, tar_addr_fifo12, tar_len, arr_len);
	binsearch(arr_port13, tar_data_fifo13, tar_addr_fifo13, tar_len, arr_len);
	binsearch(arr_port14, tar_data_fifo14, tar_addr_fifo14, tar_len, arr_len);
	binsearch(arr_port15, tar_data_fifo15, tar_addr_fifo15, tar_len, arr_len);
	binsearch(arr_port16, tar_data_fifo16, tar_addr_fifo16, tar_len, arr_len);
	binsearch(arr_port17, tar_data_fifo17, tar_addr_fifo17, tar_len, arr_len);
	binsearch(arr_port18, tar_data_fifo18, tar_addr_fifo18, tar_len, arr_len);
	binsearch(arr_port19, tar_data_fifo19, tar_addr_fifo19, tar_len, arr_len);
	binsearch(arr_port20, tar_data_fifo20, tar_addr_fifo20, tar_len, arr_len);
	binsearch(arr_port21, tar_data_fifo21, tar_addr_fifo21, tar_len, arr_len);
	binsearch(arr_port22, tar_data_fifo22, tar_addr_fifo22, tar_len, arr_len);
	binsearch(arr_port23, tar_data_fifo23, tar_addr_fifo23, tar_len, arr_len);
	binsearch(arr_port24, tar_data_fifo24, tar_addr_fifo24, tar_len, arr_len);
	binsearch(arr_port25, tar_data_fifo25, tar_addr_fifo25, tar_len, arr_len);
	binsearch(arr_port26, tar_data_fifo26, tar_addr_fifo26, tar_len, arr_len);
	binsearch(arr_port27, tar_data_fifo27, tar_addr_fifo27, tar_len, arr_len);

	merge_tar_addr(
		tar_addr_fifo0,
		tar_addr_fifo1,
		tar_addr_fifo2,
		tar_addr_fifo3,
		tar_addr128_fifo0, 
		tar_len
	);
	merge_tar_addr(
		tar_addr_fifo4,
		tar_addr_fifo5,
		tar_addr_fifo6,
		tar_addr_fifo7,
		tar_addr128_fifo1, 
		tar_len
	);
	merge_tar_addr(
		tar_addr_fifo8,
		tar_addr_fifo9,
		tar_addr_fifo10,
		tar_addr_fifo11,
		tar_addr128_fifo2, 
		tar_len
	);
	merge_tar_addr(
		tar_addr_fifo12,
		tar_addr_fifo13,
		tar_addr_fifo14,
		tar_addr_fifo15,
		tar_addr128_fifo3, 
		tar_len
	);
	merge_tar_addr(
		tar_addr_fifo16,
		tar_addr_fifo17,
		tar_addr_fifo18,
		tar_addr_fifo19,
		tar_addr128_fifo4, 
		tar_len
	);
	merge_tar_addr(
		tar_addr_fifo20,
		tar_addr_fifo21,
		tar_addr_fifo22,
		tar_addr_fifo23,
		tar_addr128_fifo5, 
		tar_len
	);
	merge_tar_addr(
		tar_addr_fifo24,
		tar_addr_fifo25,
		tar_addr_fifo26,
		tar_addr_fifo27,
		tar_addr128_fifo6, 
		tar_len
	);

	write_tar_addr(
		tar_addr_port,
		tar_addr128_fifo0, 
		tar_addr128_fifo1, 
		tar_addr128_fifo2, 
		tar_addr128_fifo3, 
		tar_addr128_fifo4, 
		tar_addr128_fifo5, 
		tar_addr128_fifo6, 
		tar_len
	);

}
#ifndef HLS
} // end of extern C
#endif
