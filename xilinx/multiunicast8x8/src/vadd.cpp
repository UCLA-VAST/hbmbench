
#include <ap_int.h>
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


void read(bool enable,
  const ap_uint<512> *src,
  hls::stream<ap_uint<512> >& dest, 
  int repeat_num, int data_num
) {
	if (enable) {
		for (int r = 0; r < repeat_num; r++) {
#pragma HLS loop_flatten off
			for (int i = 0; i < data_num; i++) {
#pragma HLS pipeline II=1
				ap_uint<512> temp = src[i];
				ap_uint<512> temp_delayed = HLS_REG(HLS_REG(temp));
				dest.write(temp_delayed);
			}
		}
	}
	else{
		for (int r = 0; r < repeat_num; r++) {
#pragma HLS loop_flatten off
			for (int i = 0; i < data_num; i++) {
#pragma HLS pipeline II=1
				dest.write((ap_uint<512>)(i));
			}			
		}
	}
}

void write(bool enable,
  hls::stream<ap_uint<512> >& src, 
  ap_uint<512> *dest0, 
  ap_uint<512> *dest1, 
  ap_uint<512> *dest2, 
  ap_uint<512> *dest3, 
  ap_uint<512> *dest4, 
  ap_uint<512> *dest5, 
  ap_uint<512> *dest6, 
  ap_uint<512> *dest7, 
  int repeat_num, int data_num
) {
	if (enable) {
		for (int r = 0; r < repeat_num; r++) {
#pragma HLS loop_flatten off
			for (int i = 0; i < data_num/8; i++) {
#pragma HLS pipeline II=1
				ap_uint<512> temp = src.read();
				ap_uint<512> temp_delayed = HLS_REG(HLS_REG(temp));
				dest0[i] = temp_delayed;
			}
			for (int i = 0; i < data_num/8; i++) {
#pragma HLS pipeline II=1
				ap_uint<512> temp = src.read();
				ap_uint<512> temp_delayed = HLS_REG(HLS_REG(temp));
				dest1[i] = temp_delayed;
			}
			for (int i = 0; i < data_num/8; i++) {
#pragma HLS pipeline II=1
				ap_uint<512> temp = src.read();
				ap_uint<512> temp_delayed = HLS_REG(HLS_REG(temp));
				dest2[i] = temp_delayed;
			}
			for (int i = 0; i < data_num/8; i++) {
#pragma HLS pipeline II=1
				ap_uint<512> temp = src.read();
				ap_uint<512> temp_delayed = HLS_REG(HLS_REG(temp));
				dest3[i] = temp_delayed;
			}
			for (int i = 0; i < data_num/8; i++) {
#pragma HLS pipeline II=1
				ap_uint<512> temp = src.read();
				ap_uint<512> temp_delayed = HLS_REG(HLS_REG(temp));
				dest4[i] = temp_delayed;
			}
			for (int i = 0; i < data_num/8; i++) {
#pragma HLS pipeline II=1
				ap_uint<512> temp = src.read();
				ap_uint<512> temp_delayed = HLS_REG(HLS_REG(temp));
				dest5[i] = temp_delayed;
			}
			for (int i = 0; i < data_num/8; i++) {
#pragma HLS pipeline II=1
				ap_uint<512> temp = src.read();
				ap_uint<512> temp_delayed = HLS_REG(HLS_REG(temp));
				dest6[i] = temp_delayed;
			}
			for (int i = 0; i < data_num/8; i++) {
#pragma HLS pipeline II=1
				ap_uint<512> temp = src.read();
				ap_uint<512> temp_delayed = HLS_REG(HLS_REG(temp));
				dest7[i] = temp_delayed;
			}
		}
	}
	else{
		ap_uint<512> dummy;
		for (int r = 0; r < repeat_num; r++) {
#pragma HLS loop_flatten off
			for (int i = 0; i < data_num/8; i++) {
#pragma HLS pipeline II=1
				ap_uint<512> temp = src.read();
				dummy = HLS_REG(HLS_REG(temp));
			}
		}
		if( dummy == 0 ){ //never happens
			dest0[0] = dummy;
		}
	}
}

#ifndef HLS
extern "C" {
#endif

void vadd(
  const ap_uint<512> *in0,
  const ap_uint<512> *in1,
  const ap_uint<512> *in2,
  const ap_uint<512> *in3,
  const ap_uint<512> *in4,
  const ap_uint<512> *in5,
  const ap_uint<512> *in6,
  const ap_uint<512> *in7,
  ap_uint<512> *out0_0, 
  ap_uint<512> *out0_1, 
  ap_uint<512> *out0_2, 
  ap_uint<512> *out0_3, 
  ap_uint<512> *out0_4, 
  ap_uint<512> *out0_5, 
  ap_uint<512> *out0_6, 
  ap_uint<512> *out0_7, 
  ap_uint<512> *out1_0, 
  ap_uint<512> *out1_1, 
  ap_uint<512> *out1_2, 
  ap_uint<512> *out1_3, 
  ap_uint<512> *out1_4, 
  ap_uint<512> *out1_5, 
  ap_uint<512> *out1_6, 
  ap_uint<512> *out1_7, 
  ap_uint<512> *out2_0, 
  ap_uint<512> *out2_1, 
  ap_uint<512> *out2_2, 
  ap_uint<512> *out2_3, 
  ap_uint<512> *out2_4, 
  ap_uint<512> *out2_5, 
  ap_uint<512> *out2_6, 
  ap_uint<512> *out2_7, 
  ap_uint<512> *out3_0, 
  ap_uint<512> *out3_1, 
  ap_uint<512> *out3_2, 
  ap_uint<512> *out3_3, 
  ap_uint<512> *out3_4, 
  ap_uint<512> *out3_5, 
  ap_uint<512> *out3_6, 
  ap_uint<512> *out3_7, 
  ap_uint<512> *out4_0, 
  ap_uint<512> *out4_1, 
  ap_uint<512> *out4_2, 
  ap_uint<512> *out4_3, 
  ap_uint<512> *out4_4, 
  ap_uint<512> *out4_5, 
  ap_uint<512> *out4_6, 
  ap_uint<512> *out4_7, 
  ap_uint<512> *out5_0, 
  ap_uint<512> *out5_1, 
  ap_uint<512> *out5_2, 
  ap_uint<512> *out5_3, 
  ap_uint<512> *out5_4, 
  ap_uint<512> *out5_5, 
  ap_uint<512> *out5_6, 
  ap_uint<512> *out5_7, 
  ap_uint<512> *out6_0, 
  ap_uint<512> *out6_1, 
  ap_uint<512> *out6_2, 
  ap_uint<512> *out6_3, 
  ap_uint<512> *out6_4, 
  ap_uint<512> *out6_5, 
  ap_uint<512> *out6_6, 
  ap_uint<512> *out6_7, 
  ap_uint<512> *out7_0, 
  ap_uint<512> *out7_1, 
  ap_uint<512> *out7_2, 
  ap_uint<512> *out7_3, 
  ap_uint<512> *out7_4, 
  ap_uint<512> *out7_5, 
  ap_uint<512> *out7_6, 
  ap_uint<512> *out7_7, 
  int repeat_num,
  int data_num, //bytes
  bool run_write,
  bool run_read
) {
// Here Vitis kernel contains one s_axilite interface which will be used by host application to configure the kernel.
// Here bundle control is defined which is s_axilite interface and associated with all the arguments (in1, in2, out_r and data_num),
// control interface must also be associated with "return".
// All the global memory access arguments must be associated to one m_axi(AXI Master Interface). Here all three arguments(in1, in2, out_r) are
// associated to bundle gmem which means that a AXI master interface named "gmem" will be created in Kernel and all these variables will be
// accessing global memory through this interface.
// Multiple interfaces can also be created based on the requirements. For example when multiple memory accessing arguments need access to
// global memory simultaneously, user can create multiple master interfaces and can connect to different arguments.

#pragma HLS INTERFACE m_axi port = in0 offset = slave bundle = hbm0 
#pragma HLS INTERFACE m_axi port = in1 offset = slave bundle = hbm1 
#pragma HLS INTERFACE m_axi port = in2 offset = slave bundle = hbm2 
#pragma HLS INTERFACE m_axi port = in3 offset = slave bundle = hbm3 
#pragma HLS INTERFACE m_axi port = in4 offset = slave bundle = hbm4 
#pragma HLS INTERFACE m_axi port = in5 offset = slave bundle = hbm5 
#pragma HLS INTERFACE m_axi port = in6 offset = slave bundle = hbm6 
#pragma HLS INTERFACE m_axi port = in7 offset = slave bundle = hbm7 

#pragma HLS INTERFACE m_axi port = out0_0 offset = slave bundle = hbm8 
#pragma HLS INTERFACE m_axi port = out0_1 offset = slave bundle = hbm8 
#pragma HLS INTERFACE m_axi port = out0_2 offset = slave bundle = hbm8 
#pragma HLS INTERFACE m_axi port = out0_3 offset = slave bundle = hbm8 
#pragma HLS INTERFACE m_axi port = out0_4 offset = slave bundle = hbm8 
#pragma HLS INTERFACE m_axi port = out0_5 offset = slave bundle = hbm8 
#pragma HLS INTERFACE m_axi port = out0_6 offset = slave bundle = hbm8 
#pragma HLS INTERFACE m_axi port = out0_7 offset = slave bundle = hbm8 
#pragma HLS INTERFACE m_axi port = out1_0 offset = slave bundle = hbm9 
#pragma HLS INTERFACE m_axi port = out1_1 offset = slave bundle = hbm9 
#pragma HLS INTERFACE m_axi port = out1_2 offset = slave bundle = hbm9 
#pragma HLS INTERFACE m_axi port = out1_3 offset = slave bundle = hbm9 
#pragma HLS INTERFACE m_axi port = out1_4 offset = slave bundle = hbm9 
#pragma HLS INTERFACE m_axi port = out1_5 offset = slave bundle = hbm9 
#pragma HLS INTERFACE m_axi port = out1_6 offset = slave bundle = hbm9 
#pragma HLS INTERFACE m_axi port = out1_7 offset = slave bundle = hbm9 
#pragma HLS INTERFACE m_axi port = out2_0 offset = slave bundle = hbm10 
#pragma HLS INTERFACE m_axi port = out2_1 offset = slave bundle = hbm10 
#pragma HLS INTERFACE m_axi port = out2_2 offset = slave bundle = hbm10 
#pragma HLS INTERFACE m_axi port = out2_3 offset = slave bundle = hbm10 
#pragma HLS INTERFACE m_axi port = out2_4 offset = slave bundle = hbm10 
#pragma HLS INTERFACE m_axi port = out2_5 offset = slave bundle = hbm10 
#pragma HLS INTERFACE m_axi port = out2_6 offset = slave bundle = hbm10 
#pragma HLS INTERFACE m_axi port = out2_7 offset = slave bundle = hbm10 
#pragma HLS INTERFACE m_axi port = out3_0 offset = slave bundle = hbm11 
#pragma HLS INTERFACE m_axi port = out3_1 offset = slave bundle = hbm11 
#pragma HLS INTERFACE m_axi port = out3_2 offset = slave bundle = hbm11 
#pragma HLS INTERFACE m_axi port = out3_3 offset = slave bundle = hbm11 
#pragma HLS INTERFACE m_axi port = out3_4 offset = slave bundle = hbm11 
#pragma HLS INTERFACE m_axi port = out3_5 offset = slave bundle = hbm11 
#pragma HLS INTERFACE m_axi port = out3_6 offset = slave bundle = hbm11 
#pragma HLS INTERFACE m_axi port = out3_7 offset = slave bundle = hbm11 
#pragma HLS INTERFACE m_axi port = out4_0 offset = slave bundle = hbm12 
#pragma HLS INTERFACE m_axi port = out4_1 offset = slave bundle = hbm12 
#pragma HLS INTERFACE m_axi port = out4_2 offset = slave bundle = hbm12 
#pragma HLS INTERFACE m_axi port = out4_3 offset = slave bundle = hbm12 
#pragma HLS INTERFACE m_axi port = out4_4 offset = slave bundle = hbm12 
#pragma HLS INTERFACE m_axi port = out4_5 offset = slave bundle = hbm12 
#pragma HLS INTERFACE m_axi port = out4_6 offset = slave bundle = hbm12 
#pragma HLS INTERFACE m_axi port = out4_7 offset = slave bundle = hbm12 
#pragma HLS INTERFACE m_axi port = out5_0 offset = slave bundle = hbm13 
#pragma HLS INTERFACE m_axi port = out5_1 offset = slave bundle = hbm13 
#pragma HLS INTERFACE m_axi port = out5_2 offset = slave bundle = hbm13 
#pragma HLS INTERFACE m_axi port = out5_3 offset = slave bundle = hbm13 
#pragma HLS INTERFACE m_axi port = out5_4 offset = slave bundle = hbm13 
#pragma HLS INTERFACE m_axi port = out5_5 offset = slave bundle = hbm13 
#pragma HLS INTERFACE m_axi port = out5_6 offset = slave bundle = hbm13 
#pragma HLS INTERFACE m_axi port = out5_7 offset = slave bundle = hbm13 
#pragma HLS INTERFACE m_axi port = out6_0 offset = slave bundle = hbm14 
#pragma HLS INTERFACE m_axi port = out6_1 offset = slave bundle = hbm14 
#pragma HLS INTERFACE m_axi port = out6_2 offset = slave bundle = hbm14 
#pragma HLS INTERFACE m_axi port = out6_3 offset = slave bundle = hbm14 
#pragma HLS INTERFACE m_axi port = out6_4 offset = slave bundle = hbm14 
#pragma HLS INTERFACE m_axi port = out6_5 offset = slave bundle = hbm14 
#pragma HLS INTERFACE m_axi port = out6_6 offset = slave bundle = hbm14 
#pragma HLS INTERFACE m_axi port = out6_7 offset = slave bundle = hbm14 
#pragma HLS INTERFACE m_axi port = out7_0 offset = slave bundle = hbm15 
#pragma HLS INTERFACE m_axi port = out7_1 offset = slave bundle = hbm15 
#pragma HLS INTERFACE m_axi port = out7_2 offset = slave bundle = hbm15 
#pragma HLS INTERFACE m_axi port = out7_3 offset = slave bundle = hbm15 
#pragma HLS INTERFACE m_axi port = out7_4 offset = slave bundle = hbm15 
#pragma HLS INTERFACE m_axi port = out7_5 offset = slave bundle = hbm15 
#pragma HLS INTERFACE m_axi port = out7_6 offset = slave bundle = hbm15 
#pragma HLS INTERFACE m_axi port = out7_7 offset = slave bundle = hbm15 

#pragma HLS INTERFACE s_axilite port = repeat_num bundle = control
#pragma HLS INTERFACE s_axilite port = data_num bundle = control
#pragma HLS INTERFACE s_axilite port = run_write bundle = control
#pragma HLS INTERFACE s_axilite port = run_read bundle = control
#pragma HLS INTERFACE s_axilite port = return bundle = control

#pragma HLS dataflow

  hls::stream<ap_uint<512> > fifo0 ;   
  hls::stream<ap_uint<512> > fifo1 ;   
  hls::stream<ap_uint<512> > fifo2 ;   
  hls::stream<ap_uint<512> > fifo3 ;   
  hls::stream<ap_uint<512> > fifo4 ;   
  hls::stream<ap_uint<512> > fifo5 ;   
  hls::stream<ap_uint<512> > fifo6 ;   
  hls::stream<ap_uint<512> > fifo7 ;   

#pragma HLS STREAM variable=fifo0  depth=2 dim=1
#pragma HLS STREAM variable=fifo1  depth=2 dim=1
#pragma HLS STREAM variable=fifo2  depth=2 dim=1
#pragma HLS STREAM variable=fifo3  depth=2 dim=1
#pragma HLS STREAM variable=fifo4  depth=2 dim=1
#pragma HLS STREAM variable=fifo5  depth=2 dim=1
#pragma HLS STREAM variable=fifo6  depth=2 dim=1
#pragma HLS STREAM variable=fifo7  depth=2 dim=1
#pragma HLS RESOURCE variable=fifo0 core=FIFO_SRL
#pragma HLS RESOURCE variable=fifo1 core=FIFO_SRL
#pragma HLS RESOURCE variable=fifo2 core=FIFO_SRL
#pragma HLS RESOURCE variable=fifo3 core=FIFO_SRL
#pragma HLS RESOURCE variable=fifo4 core=FIFO_SRL
#pragma HLS RESOURCE variable=fifo5 core=FIFO_SRL
#pragma HLS RESOURCE variable=fifo6 core=FIFO_SRL
#pragma HLS RESOURCE variable=fifo7 core=FIFO_SRL

  read(run_read, in0, fifo0, repeat_num, data_num);
  read(run_read, in1, fifo1, repeat_num, data_num);
  read(run_read, in2, fifo2, repeat_num, data_num);
  read(run_read, in3, fifo3, repeat_num, data_num);
  read(run_read, in4, fifo4, repeat_num, data_num);
  read(run_read, in5, fifo5, repeat_num, data_num);
  read(run_read, in6, fifo6, repeat_num, data_num);
  read(run_read, in7, fifo7, repeat_num, data_num);

  write(run_write, fifo0,
     out0_0, 
     out0_1, 
     out0_2, 
     out0_3, 
     out0_4, 
     out0_5, 
     out0_6, 
     out0_7, 
     repeat_num, data_num);
  write(run_write, fifo1,
     out1_0, 
     out1_1, 
     out1_2, 
     out1_3, 
     out1_4, 
     out1_5, 
     out1_6, 
     out1_7, 
     repeat_num, data_num);
  write(run_write, fifo2,
     out2_0, 
     out2_1, 
     out2_2, 
     out2_3, 
     out2_4, 
     out2_5, 
     out2_6, 
     out2_7, 
     repeat_num, data_num);
  write(run_write, fifo3,
     out3_0, 
     out3_1, 
     out3_2, 
     out3_3, 
     out3_4, 
     out3_5, 
     out3_6, 
     out3_7, 
     repeat_num, data_num);
  write(run_write, fifo4,
     out4_0, 
     out4_1, 
     out4_2, 
     out4_3, 
     out4_4, 
     out4_5, 
     out4_6, 
     out4_7, 
     repeat_num, data_num);
  write(run_write, fifo5,
     out5_0, 
     out5_1, 
     out5_2, 
     out5_3, 
     out5_4, 
     out5_5, 
     out5_6, 
     out5_7, 
     repeat_num, data_num);
  write(run_write, fifo6,
     out6_0, 
     out6_1, 
     out6_2, 
     out6_3, 
     out6_4, 
     out6_5, 
     out6_6, 
     out6_7, 
     repeat_num, data_num);
  write(run_write, fifo7,
     out7_0, 
     out7_1, 
     out7_2, 
     out7_3, 
     out7_4, 
     out7_5, 
     out7_6, 
     out7_7, 
     repeat_num, data_num);

}
#ifndef HLS
} // end of extern C
#endif
