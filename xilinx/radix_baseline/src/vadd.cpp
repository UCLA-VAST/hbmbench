
#define WRITE_BURST 256

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

void read(
  // shift%2 == 0
  ap_uint<512> *src0_0,
  ap_uint<512> *src0_1,
  ap_uint<512> *src0_2,
  ap_uint<512> *src0_3,
  ap_uint<512> *src0_4,
  ap_uint<512> *src0_5,
  ap_uint<512> *src0_6,
  ap_uint<512> *src0_7,
  // shift%2 == 1
  ap_uint<512> *src1_0,
  ap_uint<512> *src1_1,
  ap_uint<512> *src1_2,
  ap_uint<512> *src1_3,
  ap_uint<512> *src1_4,
  ap_uint<512> *src1_5,
  ap_uint<512> *src1_6,
  ap_uint<512> *src1_7,
  hls::stream<ap_uint<512> >& dst0, 
  int repeat_num, int data_num, int shift
) {
	for (int r = 0; r < repeat_num; r++) {
#pragma HLS loop_flatten off
    if (shift%2 == 0) {
  		for (int i = 0; i < data_num; i++) {
#pragma HLS pipeline II=1
	  		ap_uint<512> temp = src0_0[i];
		  	ap_uint<512> temp_delayed = HLS_REG(temp);

			  dst0.write(temp_delayed);					
		  }
    } else {
		  for (int i = 0; i < data_num; i++) {
#pragma HLS pipeline II=1
			  ap_uint<512> temp = src1_0[i];
			  ap_uint<512> temp_delayed = HLS_REG(temp);

			  dst0.write(temp_delayed);					
		  }
    }
    if (shift%2 == 0) {
  		for (int i = 0; i < data_num; i++) {
#pragma HLS pipeline II=1
	  		ap_uint<512> temp = src0_1[i];
		  	ap_uint<512> temp_delayed = HLS_REG(temp);

			  dst0.write(temp_delayed);					
		  }
    } else {
		  for (int i = 0; i < data_num; i++) {
#pragma HLS pipeline II=1
			  ap_uint<512> temp = src1_1[i];
			  ap_uint<512> temp_delayed = HLS_REG(temp);

			  dst0.write(temp_delayed);					
		  }
    }
    if (shift%2 == 0) {
  		for (int i = 0; i < data_num; i++) {
#pragma HLS pipeline II=1
	  		ap_uint<512> temp = src0_2[i];
		  	ap_uint<512> temp_delayed = HLS_REG(temp);

			  dst0.write(temp_delayed);					
		  }
    } else {
		  for (int i = 0; i < data_num; i++) {
#pragma HLS pipeline II=1
			  ap_uint<512> temp = src1_2[i];
			  ap_uint<512> temp_delayed = HLS_REG(temp);

			  dst0.write(temp_delayed);					
		  }
    }
    if (shift%2 == 0) {
  		for (int i = 0; i < data_num; i++) {
#pragma HLS pipeline II=1
	  		ap_uint<512> temp = src0_3[i];
		  	ap_uint<512> temp_delayed = HLS_REG(temp);

			  dst0.write(temp_delayed);					
		  }
    } else {
		  for (int i = 0; i < data_num; i++) {
#pragma HLS pipeline II=1
			  ap_uint<512> temp = src1_3[i];
			  ap_uint<512> temp_delayed = HLS_REG(temp);

			  dst0.write(temp_delayed);					
		  }
    }
    if (shift%2 == 0) {
  		for (int i = 0; i < data_num; i++) {
#pragma HLS pipeline II=1
	  		ap_uint<512> temp = src0_4[i];
		  	ap_uint<512> temp_delayed = HLS_REG(temp);

			  dst0.write(temp_delayed);					
		  }
    } else {
		  for (int i = 0; i < data_num; i++) {
#pragma HLS pipeline II=1
			  ap_uint<512> temp = src1_4[i];
			  ap_uint<512> temp_delayed = HLS_REG(temp);

			  dst0.write(temp_delayed);					
		  }
    }
    if (shift%2 == 0) {
  		for (int i = 0; i < data_num; i++) {
#pragma HLS pipeline II=1
	  		ap_uint<512> temp = src0_5[i];
		  	ap_uint<512> temp_delayed = HLS_REG(temp);

			  dst0.write(temp_delayed);					
		  }
    } else {
		  for (int i = 0; i < data_num; i++) {
#pragma HLS pipeline II=1
			  ap_uint<512> temp = src1_5[i];
			  ap_uint<512> temp_delayed = HLS_REG(temp);

			  dst0.write(temp_delayed);					
		  }
    }
    if (shift%2 == 0) {
  		for (int i = 0; i < data_num; i++) {
#pragma HLS pipeline II=1
	  		ap_uint<512> temp = src0_6[i];
		  	ap_uint<512> temp_delayed = HLS_REG(temp);

			  dst0.write(temp_delayed);					
		  }
    } else {
		  for (int i = 0; i < data_num; i++) {
#pragma HLS pipeline II=1
			  ap_uint<512> temp = src1_6[i];
			  ap_uint<512> temp_delayed = HLS_REG(temp);

			  dst0.write(temp_delayed);					
		  }
    }
    if (shift%2 == 0) {
  		for (int i = 0; i < data_num; i++) {
#pragma HLS pipeline II=1
	  		ap_uint<512> temp = src0_7[i];
		  	ap_uint<512> temp_delayed = HLS_REG(temp);

			  dst0.write(temp_delayed);					
		  }
    } else {
		  for (int i = 0; i < data_num; i++) {
#pragma HLS pipeline II=1
			  ap_uint<512> temp = src1_7[i];
			  ap_uint<512> temp_delayed = HLS_REG(temp);

			  dst0.write(temp_delayed);					
		  }
    }
	}

	ap_uint<512> terminate_data = ((ap_uint<512>)1)<<511;
	dst0.write(terminate_data);
}

void write(
  hls::stream<ap_uint<512> >& src0, 
  // shift%2 == 0
  ap_uint<512> *dst0_0, 
  ap_uint<512> *dst0_1, 
  ap_uint<512> *dst0_2, 
  ap_uint<512> *dst0_3, 
  ap_uint<512> *dst0_4, 
  ap_uint<512> *dst0_5, 
  ap_uint<512> *dst0_6, 
  ap_uint<512> *dst0_7, 
  // shift%2 == 1
  ap_uint<512> *dst1_0, 
  ap_uint<512> *dst1_1, 
  ap_uint<512> *dst1_2, 
  ap_uint<512> *dst1_3, 
  ap_uint<512> *dst1_4, 
  ap_uint<512> *dst1_5, 
  ap_uint<512> *dst1_6, 
  ap_uint<512> *dst1_7, 
  int repeat_num, int data_num, int shift
)
{
	char terminate0 = 0;
	int cnt0 = 0;
	int cnt1 = 0;
	int cnt2 = 0;
	int cnt3 = 0;
	int cnt4 = 0;
	int cnt5 = 0;
	int cnt6 = 0;
	int cnt7 = 0;
	while(
		terminate0 == 0 ||
		0
	){
		if( terminate0 == 0 ){
			for( int cnt = 0; cnt < WRITE_BURST; cnt++ ){
#pragma HLS pipeline II=1			
				ap_uint<512> temp;
				char success = src0.read_nb(temp);
				ap_uint<512> temp_delayed = HLS_REG(temp);
				if( success == 1 ){
					if( temp_delayed(511,511) == 1 ){
						terminate0 = 1;
					}
				}
				if( success == 1 && terminate0 == 0 ){
					ap_uint<3> sel = (temp_delayed>>(3*shift))&7;
					switch( sel ){
						case 0:
              if (shift%2 == 0)
							  dst0_0[cnt0%32768] = temp_delayed;
              else
                dst1_0[cnt0%32768] = temp_delayed;
              
							cnt0++;
							break;
						case 1:
              if (shift%2 == 0)
							  dst0_1[cnt1%32768] = temp_delayed;
              else
                dst1_1[cnt1%32768] = temp_delayed;
              
							cnt1++;
							break;
						case 2:
              if (shift%2 == 0)
							  dst0_2[cnt2%32768] = temp_delayed;
              else
                dst1_2[cnt2%32768] = temp_delayed;
              
							cnt2++;
							break;
						case 3:
              if (shift%2 == 0)
							  dst0_3[cnt3%32768] = temp_delayed;
              else
                dst1_3[cnt3%32768] = temp_delayed;
              
							cnt3++;
							break;
						case 4:
              if (shift%2 == 0)
							  dst0_4[cnt4%32768] = temp_delayed;
              else
                dst1_4[cnt4%32768] = temp_delayed;
              
							cnt4++;
							break;
						case 5:
              if (shift%2 == 0)
							  dst0_5[cnt5%32768] = temp_delayed;
              else
                dst1_5[cnt5%32768] = temp_delayed;
              
							cnt5++;
							break;
						case 6:
              if (shift%2 == 0)
							  dst0_6[cnt6%32768] = temp_delayed;
              else
                dst1_6[cnt6%32768] = temp_delayed;
              
							cnt6++;
							break;
						default:
              if (shift%2 == 0)
							  dst0_7[cnt7%32768] = temp_delayed;
              else
                dst1_7[cnt7%32768] = temp_delayed;
              
							cnt7++;
							break;
					}
				}
			}
		}		
	}

}

#ifndef HLS
extern "C" {
#endif

void vadd(
  // shift%2 == 0
  ap_uint<512> *in0_0_0,
  ap_uint<512> *in0_0_1,
  ap_uint<512> *in0_0_2,
  ap_uint<512> *in0_0_3,
  ap_uint<512> *in0_0_4,
  ap_uint<512> *in0_0_5,
  ap_uint<512> *in0_0_6,
  ap_uint<512> *in0_0_7,
  ap_uint<512> *in0_1_0,
  ap_uint<512> *in0_1_1,
  ap_uint<512> *in0_1_2,
  ap_uint<512> *in0_1_3,
  ap_uint<512> *in0_1_4,
  ap_uint<512> *in0_1_5,
  ap_uint<512> *in0_1_6,
  ap_uint<512> *in0_1_7,
  ap_uint<512> *in0_2_0,
  ap_uint<512> *in0_2_1,
  ap_uint<512> *in0_2_2,
  ap_uint<512> *in0_2_3,
  ap_uint<512> *in0_2_4,
  ap_uint<512> *in0_2_5,
  ap_uint<512> *in0_2_6,
  ap_uint<512> *in0_2_7,
  ap_uint<512> *in0_3_0,
  ap_uint<512> *in0_3_1,
  ap_uint<512> *in0_3_2,
  ap_uint<512> *in0_3_3,
  ap_uint<512> *in0_3_4,
  ap_uint<512> *in0_3_5,
  ap_uint<512> *in0_3_6,
  ap_uint<512> *in0_3_7,
  ap_uint<512> *in0_4_0,
  ap_uint<512> *in0_4_1,
  ap_uint<512> *in0_4_2,
  ap_uint<512> *in0_4_3,
  ap_uint<512> *in0_4_4,
  ap_uint<512> *in0_4_5,
  ap_uint<512> *in0_4_6,
  ap_uint<512> *in0_4_7,
  ap_uint<512> *in0_5_0,
  ap_uint<512> *in0_5_1,
  ap_uint<512> *in0_5_2,
  ap_uint<512> *in0_5_3,
  ap_uint<512> *in0_5_4,
  ap_uint<512> *in0_5_5,
  ap_uint<512> *in0_5_6,
  ap_uint<512> *in0_5_7,
  ap_uint<512> *in0_6_0,
  ap_uint<512> *in0_6_1,
  ap_uint<512> *in0_6_2,
  ap_uint<512> *in0_6_3,
  ap_uint<512> *in0_6_4,
  ap_uint<512> *in0_6_5,
  ap_uint<512> *in0_6_6,
  ap_uint<512> *in0_6_7,
  ap_uint<512> *in0_7_0,
  ap_uint<512> *in0_7_1,
  ap_uint<512> *in0_7_2,
  ap_uint<512> *in0_7_3,
  ap_uint<512> *in0_7_4,
  ap_uint<512> *in0_7_5,
  ap_uint<512> *in0_7_6,
  ap_uint<512> *in0_7_7,
  ap_uint<512> *out0_0_0, 
  ap_uint<512> *out0_0_1, 
  ap_uint<512> *out0_0_2, 
  ap_uint<512> *out0_0_3, 
  ap_uint<512> *out0_0_4, 
  ap_uint<512> *out0_0_5, 
  ap_uint<512> *out0_0_6, 
  ap_uint<512> *out0_0_7, 
  ap_uint<512> *out0_1_0, 
  ap_uint<512> *out0_1_1, 
  ap_uint<512> *out0_1_2, 
  ap_uint<512> *out0_1_3, 
  ap_uint<512> *out0_1_4, 
  ap_uint<512> *out0_1_5, 
  ap_uint<512> *out0_1_6, 
  ap_uint<512> *out0_1_7, 
  ap_uint<512> *out0_2_0, 
  ap_uint<512> *out0_2_1, 
  ap_uint<512> *out0_2_2, 
  ap_uint<512> *out0_2_3, 
  ap_uint<512> *out0_2_4, 
  ap_uint<512> *out0_2_5, 
  ap_uint<512> *out0_2_6, 
  ap_uint<512> *out0_2_7, 
  ap_uint<512> *out0_3_0, 
  ap_uint<512> *out0_3_1, 
  ap_uint<512> *out0_3_2, 
  ap_uint<512> *out0_3_3, 
  ap_uint<512> *out0_3_4, 
  ap_uint<512> *out0_3_5, 
  ap_uint<512> *out0_3_6, 
  ap_uint<512> *out0_3_7, 
  ap_uint<512> *out0_4_0, 
  ap_uint<512> *out0_4_1, 
  ap_uint<512> *out0_4_2, 
  ap_uint<512> *out0_4_3, 
  ap_uint<512> *out0_4_4, 
  ap_uint<512> *out0_4_5, 
  ap_uint<512> *out0_4_6, 
  ap_uint<512> *out0_4_7, 
  ap_uint<512> *out0_5_0, 
  ap_uint<512> *out0_5_1, 
  ap_uint<512> *out0_5_2, 
  ap_uint<512> *out0_5_3, 
  ap_uint<512> *out0_5_4, 
  ap_uint<512> *out0_5_5, 
  ap_uint<512> *out0_5_6, 
  ap_uint<512> *out0_5_7, 
  ap_uint<512> *out0_6_0, 
  ap_uint<512> *out0_6_1, 
  ap_uint<512> *out0_6_2, 
  ap_uint<512> *out0_6_3, 
  ap_uint<512> *out0_6_4, 
  ap_uint<512> *out0_6_5, 
  ap_uint<512> *out0_6_6, 
  ap_uint<512> *out0_6_7, 
  ap_uint<512> *out0_7_0, 
  ap_uint<512> *out0_7_1, 
  ap_uint<512> *out0_7_2, 
  ap_uint<512> *out0_7_3, 
  ap_uint<512> *out0_7_4, 
  ap_uint<512> *out0_7_5, 
  ap_uint<512> *out0_7_6, 
  ap_uint<512> *out0_7_7, 
  // shift%2 == 1
  ap_uint<512> *in1_0_0,
  ap_uint<512> *in1_0_1,
  ap_uint<512> *in1_0_2,
  ap_uint<512> *in1_0_3,
  ap_uint<512> *in1_0_4,
  ap_uint<512> *in1_0_5,
  ap_uint<512> *in1_0_6,
  ap_uint<512> *in1_0_7,
  ap_uint<512> *in1_1_0,
  ap_uint<512> *in1_1_1,
  ap_uint<512> *in1_1_2,
  ap_uint<512> *in1_1_3,
  ap_uint<512> *in1_1_4,
  ap_uint<512> *in1_1_5,
  ap_uint<512> *in1_1_6,
  ap_uint<512> *in1_1_7,
  ap_uint<512> *in1_2_0,
  ap_uint<512> *in1_2_1,
  ap_uint<512> *in1_2_2,
  ap_uint<512> *in1_2_3,
  ap_uint<512> *in1_2_4,
  ap_uint<512> *in1_2_5,
  ap_uint<512> *in1_2_6,
  ap_uint<512> *in1_2_7,
  ap_uint<512> *in1_3_0,
  ap_uint<512> *in1_3_1,
  ap_uint<512> *in1_3_2,
  ap_uint<512> *in1_3_3,
  ap_uint<512> *in1_3_4,
  ap_uint<512> *in1_3_5,
  ap_uint<512> *in1_3_6,
  ap_uint<512> *in1_3_7,
  ap_uint<512> *in1_4_0,
  ap_uint<512> *in1_4_1,
  ap_uint<512> *in1_4_2,
  ap_uint<512> *in1_4_3,
  ap_uint<512> *in1_4_4,
  ap_uint<512> *in1_4_5,
  ap_uint<512> *in1_4_6,
  ap_uint<512> *in1_4_7,
  ap_uint<512> *in1_5_0,
  ap_uint<512> *in1_5_1,
  ap_uint<512> *in1_5_2,
  ap_uint<512> *in1_5_3,
  ap_uint<512> *in1_5_4,
  ap_uint<512> *in1_5_5,
  ap_uint<512> *in1_5_6,
  ap_uint<512> *in1_5_7,
  ap_uint<512> *in1_6_0,
  ap_uint<512> *in1_6_1,
  ap_uint<512> *in1_6_2,
  ap_uint<512> *in1_6_3,
  ap_uint<512> *in1_6_4,
  ap_uint<512> *in1_6_5,
  ap_uint<512> *in1_6_6,
  ap_uint<512> *in1_6_7,
  ap_uint<512> *in1_7_0,
  ap_uint<512> *in1_7_1,
  ap_uint<512> *in1_7_2,
  ap_uint<512> *in1_7_3,
  ap_uint<512> *in1_7_4,
  ap_uint<512> *in1_7_5,
  ap_uint<512> *in1_7_6,
  ap_uint<512> *in1_7_7,
  ap_uint<512> *out1_0_0, 
  ap_uint<512> *out1_0_1, 
  ap_uint<512> *out1_0_2, 
  ap_uint<512> *out1_0_3, 
  ap_uint<512> *out1_0_4, 
  ap_uint<512> *out1_0_5, 
  ap_uint<512> *out1_0_6, 
  ap_uint<512> *out1_0_7, 
  ap_uint<512> *out1_1_0, 
  ap_uint<512> *out1_1_1, 
  ap_uint<512> *out1_1_2, 
  ap_uint<512> *out1_1_3, 
  ap_uint<512> *out1_1_4, 
  ap_uint<512> *out1_1_5, 
  ap_uint<512> *out1_1_6, 
  ap_uint<512> *out1_1_7, 
  ap_uint<512> *out1_2_0, 
  ap_uint<512> *out1_2_1, 
  ap_uint<512> *out1_2_2, 
  ap_uint<512> *out1_2_3, 
  ap_uint<512> *out1_2_4, 
  ap_uint<512> *out1_2_5, 
  ap_uint<512> *out1_2_6, 
  ap_uint<512> *out1_2_7, 
  ap_uint<512> *out1_3_0, 
  ap_uint<512> *out1_3_1, 
  ap_uint<512> *out1_3_2, 
  ap_uint<512> *out1_3_3, 
  ap_uint<512> *out1_3_4, 
  ap_uint<512> *out1_3_5, 
  ap_uint<512> *out1_3_6, 
  ap_uint<512> *out1_3_7, 
  ap_uint<512> *out1_4_0, 
  ap_uint<512> *out1_4_1, 
  ap_uint<512> *out1_4_2, 
  ap_uint<512> *out1_4_3, 
  ap_uint<512> *out1_4_4, 
  ap_uint<512> *out1_4_5, 
  ap_uint<512> *out1_4_6, 
  ap_uint<512> *out1_4_7, 
  ap_uint<512> *out1_5_0, 
  ap_uint<512> *out1_5_1, 
  ap_uint<512> *out1_5_2, 
  ap_uint<512> *out1_5_3, 
  ap_uint<512> *out1_5_4, 
  ap_uint<512> *out1_5_5, 
  ap_uint<512> *out1_5_6, 
  ap_uint<512> *out1_5_7, 
  ap_uint<512> *out1_6_0, 
  ap_uint<512> *out1_6_1, 
  ap_uint<512> *out1_6_2, 
  ap_uint<512> *out1_6_3, 
  ap_uint<512> *out1_6_4, 
  ap_uint<512> *out1_6_5, 
  ap_uint<512> *out1_6_6, 
  ap_uint<512> *out1_6_7, 
  ap_uint<512> *out1_7_0, 
  ap_uint<512> *out1_7_1, 
  ap_uint<512> *out1_7_2, 
  ap_uint<512> *out1_7_3, 
  ap_uint<512> *out1_7_4, 
  ap_uint<512> *out1_7_5, 
  ap_uint<512> *out1_7_6, 
  ap_uint<512> *out1_7_7, 
  int repeat_num,
  int data_num,
  int shift
) {
// Here Vitis kernel contains one s_axilite interface which will be used by host application to configure the kernel.
// Here bundle control is defined which is s_axilite interface and associated with all the arguments (in1, in2, out_r and data_num),
// control interface must also be associated with "return".
// All the global memory access arguments must be associated to one m_axi(AXI Master Interface). Here all three arguments(in1, in2, out_r) are
// associated to bundle gmem which means that a AXI master interface named "gmem" will be created in Kernel and all these variables will be
// accessing global memory through this interface.
// Multiple interfaces can also be created based on the requirements. For example when multiple memory accessing arguments need access to
// global memory simultaneously, user can create multiple master interfaces and can connect to different arguments.

#pragma HLS INTERFACE m_axi port = in0_0_0 offset = slave bundle = hbm0 
#pragma HLS INTERFACE m_axi port = in1_0_0 offset = slave bundle = hbm0 
#pragma HLS INTERFACE m_axi port = in0_0_1 offset = slave bundle = hbm0 
#pragma HLS INTERFACE m_axi port = in1_0_1 offset = slave bundle = hbm0 
#pragma HLS INTERFACE m_axi port = in0_0_2 offset = slave bundle = hbm0 
#pragma HLS INTERFACE m_axi port = in1_0_2 offset = slave bundle = hbm0 
#pragma HLS INTERFACE m_axi port = in0_0_3 offset = slave bundle = hbm0 
#pragma HLS INTERFACE m_axi port = in1_0_3 offset = slave bundle = hbm0 
#pragma HLS INTERFACE m_axi port = in0_0_4 offset = slave bundle = hbm0 
#pragma HLS INTERFACE m_axi port = in1_0_4 offset = slave bundle = hbm0 
#pragma HLS INTERFACE m_axi port = in0_0_5 offset = slave bundle = hbm0 
#pragma HLS INTERFACE m_axi port = in1_0_5 offset = slave bundle = hbm0 
#pragma HLS INTERFACE m_axi port = in0_0_6 offset = slave bundle = hbm0 
#pragma HLS INTERFACE m_axi port = in1_0_6 offset = slave bundle = hbm0 
#pragma HLS INTERFACE m_axi port = in0_0_7 offset = slave bundle = hbm0 
#pragma HLS INTERFACE m_axi port = in1_0_7 offset = slave bundle = hbm0 
#pragma HLS INTERFACE m_axi port = in0_1_0 offset = slave bundle = hbm1 
#pragma HLS INTERFACE m_axi port = in1_1_0 offset = slave bundle = hbm1 
#pragma HLS INTERFACE m_axi port = in0_1_1 offset = slave bundle = hbm1 
#pragma HLS INTERFACE m_axi port = in1_1_1 offset = slave bundle = hbm1 
#pragma HLS INTERFACE m_axi port = in0_1_2 offset = slave bundle = hbm1 
#pragma HLS INTERFACE m_axi port = in1_1_2 offset = slave bundle = hbm1 
#pragma HLS INTERFACE m_axi port = in0_1_3 offset = slave bundle = hbm1 
#pragma HLS INTERFACE m_axi port = in1_1_3 offset = slave bundle = hbm1 
#pragma HLS INTERFACE m_axi port = in0_1_4 offset = slave bundle = hbm1 
#pragma HLS INTERFACE m_axi port = in1_1_4 offset = slave bundle = hbm1 
#pragma HLS INTERFACE m_axi port = in0_1_5 offset = slave bundle = hbm1 
#pragma HLS INTERFACE m_axi port = in1_1_5 offset = slave bundle = hbm1 
#pragma HLS INTERFACE m_axi port = in0_1_6 offset = slave bundle = hbm1 
#pragma HLS INTERFACE m_axi port = in1_1_6 offset = slave bundle = hbm1 
#pragma HLS INTERFACE m_axi port = in0_1_7 offset = slave bundle = hbm1 
#pragma HLS INTERFACE m_axi port = in1_1_7 offset = slave bundle = hbm1 
#pragma HLS INTERFACE m_axi port = in0_2_0 offset = slave bundle = hbm2 
#pragma HLS INTERFACE m_axi port = in1_2_0 offset = slave bundle = hbm2 
#pragma HLS INTERFACE m_axi port = in0_2_1 offset = slave bundle = hbm2 
#pragma HLS INTERFACE m_axi port = in1_2_1 offset = slave bundle = hbm2 
#pragma HLS INTERFACE m_axi port = in0_2_2 offset = slave bundle = hbm2 
#pragma HLS INTERFACE m_axi port = in1_2_2 offset = slave bundle = hbm2 
#pragma HLS INTERFACE m_axi port = in0_2_3 offset = slave bundle = hbm2 
#pragma HLS INTERFACE m_axi port = in1_2_3 offset = slave bundle = hbm2 
#pragma HLS INTERFACE m_axi port = in0_2_4 offset = slave bundle = hbm2 
#pragma HLS INTERFACE m_axi port = in1_2_4 offset = slave bundle = hbm2 
#pragma HLS INTERFACE m_axi port = in0_2_5 offset = slave bundle = hbm2 
#pragma HLS INTERFACE m_axi port = in1_2_5 offset = slave bundle = hbm2 
#pragma HLS INTERFACE m_axi port = in0_2_6 offset = slave bundle = hbm2 
#pragma HLS INTERFACE m_axi port = in1_2_6 offset = slave bundle = hbm2 
#pragma HLS INTERFACE m_axi port = in0_2_7 offset = slave bundle = hbm2 
#pragma HLS INTERFACE m_axi port = in1_2_7 offset = slave bundle = hbm2 
#pragma HLS INTERFACE m_axi port = in0_3_0 offset = slave bundle = hbm3 
#pragma HLS INTERFACE m_axi port = in1_3_0 offset = slave bundle = hbm3 
#pragma HLS INTERFACE m_axi port = in0_3_1 offset = slave bundle = hbm3 
#pragma HLS INTERFACE m_axi port = in1_3_1 offset = slave bundle = hbm3 
#pragma HLS INTERFACE m_axi port = in0_3_2 offset = slave bundle = hbm3 
#pragma HLS INTERFACE m_axi port = in1_3_2 offset = slave bundle = hbm3 
#pragma HLS INTERFACE m_axi port = in0_3_3 offset = slave bundle = hbm3 
#pragma HLS INTERFACE m_axi port = in1_3_3 offset = slave bundle = hbm3 
#pragma HLS INTERFACE m_axi port = in0_3_4 offset = slave bundle = hbm3 
#pragma HLS INTERFACE m_axi port = in1_3_4 offset = slave bundle = hbm3 
#pragma HLS INTERFACE m_axi port = in0_3_5 offset = slave bundle = hbm3 
#pragma HLS INTERFACE m_axi port = in1_3_5 offset = slave bundle = hbm3 
#pragma HLS INTERFACE m_axi port = in0_3_6 offset = slave bundle = hbm3 
#pragma HLS INTERFACE m_axi port = in1_3_6 offset = slave bundle = hbm3 
#pragma HLS INTERFACE m_axi port = in0_3_7 offset = slave bundle = hbm3 
#pragma HLS INTERFACE m_axi port = in1_3_7 offset = slave bundle = hbm3 
#pragma HLS INTERFACE m_axi port = in0_4_0 offset = slave bundle = hbm4 
#pragma HLS INTERFACE m_axi port = in1_4_0 offset = slave bundle = hbm4 
#pragma HLS INTERFACE m_axi port = in0_4_1 offset = slave bundle = hbm4 
#pragma HLS INTERFACE m_axi port = in1_4_1 offset = slave bundle = hbm4 
#pragma HLS INTERFACE m_axi port = in0_4_2 offset = slave bundle = hbm4 
#pragma HLS INTERFACE m_axi port = in1_4_2 offset = slave bundle = hbm4 
#pragma HLS INTERFACE m_axi port = in0_4_3 offset = slave bundle = hbm4 
#pragma HLS INTERFACE m_axi port = in1_4_3 offset = slave bundle = hbm4 
#pragma HLS INTERFACE m_axi port = in0_4_4 offset = slave bundle = hbm4 
#pragma HLS INTERFACE m_axi port = in1_4_4 offset = slave bundle = hbm4 
#pragma HLS INTERFACE m_axi port = in0_4_5 offset = slave bundle = hbm4 
#pragma HLS INTERFACE m_axi port = in1_4_5 offset = slave bundle = hbm4 
#pragma HLS INTERFACE m_axi port = in0_4_6 offset = slave bundle = hbm4 
#pragma HLS INTERFACE m_axi port = in1_4_6 offset = slave bundle = hbm4 
#pragma HLS INTERFACE m_axi port = in0_4_7 offset = slave bundle = hbm4 
#pragma HLS INTERFACE m_axi port = in1_4_7 offset = slave bundle = hbm4 
#pragma HLS INTERFACE m_axi port = in0_5_0 offset = slave bundle = hbm5 
#pragma HLS INTERFACE m_axi port = in1_5_0 offset = slave bundle = hbm5 
#pragma HLS INTERFACE m_axi port = in0_5_1 offset = slave bundle = hbm5 
#pragma HLS INTERFACE m_axi port = in1_5_1 offset = slave bundle = hbm5 
#pragma HLS INTERFACE m_axi port = in0_5_2 offset = slave bundle = hbm5 
#pragma HLS INTERFACE m_axi port = in1_5_2 offset = slave bundle = hbm5 
#pragma HLS INTERFACE m_axi port = in0_5_3 offset = slave bundle = hbm5 
#pragma HLS INTERFACE m_axi port = in1_5_3 offset = slave bundle = hbm5 
#pragma HLS INTERFACE m_axi port = in0_5_4 offset = slave bundle = hbm5 
#pragma HLS INTERFACE m_axi port = in1_5_4 offset = slave bundle = hbm5 
#pragma HLS INTERFACE m_axi port = in0_5_5 offset = slave bundle = hbm5 
#pragma HLS INTERFACE m_axi port = in1_5_5 offset = slave bundle = hbm5 
#pragma HLS INTERFACE m_axi port = in0_5_6 offset = slave bundle = hbm5 
#pragma HLS INTERFACE m_axi port = in1_5_6 offset = slave bundle = hbm5 
#pragma HLS INTERFACE m_axi port = in0_5_7 offset = slave bundle = hbm5 
#pragma HLS INTERFACE m_axi port = in1_5_7 offset = slave bundle = hbm5 
#pragma HLS INTERFACE m_axi port = in0_6_0 offset = slave bundle = hbm6 
#pragma HLS INTERFACE m_axi port = in1_6_0 offset = slave bundle = hbm6 
#pragma HLS INTERFACE m_axi port = in0_6_1 offset = slave bundle = hbm6 
#pragma HLS INTERFACE m_axi port = in1_6_1 offset = slave bundle = hbm6 
#pragma HLS INTERFACE m_axi port = in0_6_2 offset = slave bundle = hbm6 
#pragma HLS INTERFACE m_axi port = in1_6_2 offset = slave bundle = hbm6 
#pragma HLS INTERFACE m_axi port = in0_6_3 offset = slave bundle = hbm6 
#pragma HLS INTERFACE m_axi port = in1_6_3 offset = slave bundle = hbm6 
#pragma HLS INTERFACE m_axi port = in0_6_4 offset = slave bundle = hbm6 
#pragma HLS INTERFACE m_axi port = in1_6_4 offset = slave bundle = hbm6 
#pragma HLS INTERFACE m_axi port = in0_6_5 offset = slave bundle = hbm6 
#pragma HLS INTERFACE m_axi port = in1_6_5 offset = slave bundle = hbm6 
#pragma HLS INTERFACE m_axi port = in0_6_6 offset = slave bundle = hbm6 
#pragma HLS INTERFACE m_axi port = in1_6_6 offset = slave bundle = hbm6 
#pragma HLS INTERFACE m_axi port = in0_6_7 offset = slave bundle = hbm6 
#pragma HLS INTERFACE m_axi port = in1_6_7 offset = slave bundle = hbm6 
#pragma HLS INTERFACE m_axi port = in0_7_0 offset = slave bundle = hbm7 
#pragma HLS INTERFACE m_axi port = in1_7_0 offset = slave bundle = hbm7 
#pragma HLS INTERFACE m_axi port = in0_7_1 offset = slave bundle = hbm7 
#pragma HLS INTERFACE m_axi port = in1_7_1 offset = slave bundle = hbm7 
#pragma HLS INTERFACE m_axi port = in0_7_2 offset = slave bundle = hbm7 
#pragma HLS INTERFACE m_axi port = in1_7_2 offset = slave bundle = hbm7 
#pragma HLS INTERFACE m_axi port = in0_7_3 offset = slave bundle = hbm7 
#pragma HLS INTERFACE m_axi port = in1_7_3 offset = slave bundle = hbm7 
#pragma HLS INTERFACE m_axi port = in0_7_4 offset = slave bundle = hbm7 
#pragma HLS INTERFACE m_axi port = in1_7_4 offset = slave bundle = hbm7 
#pragma HLS INTERFACE m_axi port = in0_7_5 offset = slave bundle = hbm7 
#pragma HLS INTERFACE m_axi port = in1_7_5 offset = slave bundle = hbm7 
#pragma HLS INTERFACE m_axi port = in0_7_6 offset = slave bundle = hbm7 
#pragma HLS INTERFACE m_axi port = in1_7_6 offset = slave bundle = hbm7 
#pragma HLS INTERFACE m_axi port = in0_7_7 offset = slave bundle = hbm7 
#pragma HLS INTERFACE m_axi port = in1_7_7 offset = slave bundle = hbm7 
#pragma HLS INTERFACE m_axi port = out0_0_0 offset = slave bundle = hbm8 
#pragma HLS INTERFACE m_axi port = out1_0_0 offset = slave bundle = hbm8 
#pragma HLS INTERFACE m_axi port = out0_0_1 offset = slave bundle = hbm8 
#pragma HLS INTERFACE m_axi port = out1_0_1 offset = slave bundle = hbm8 
#pragma HLS INTERFACE m_axi port = out0_0_2 offset = slave bundle = hbm8 
#pragma HLS INTERFACE m_axi port = out1_0_2 offset = slave bundle = hbm8 
#pragma HLS INTERFACE m_axi port = out0_0_3 offset = slave bundle = hbm8 
#pragma HLS INTERFACE m_axi port = out1_0_3 offset = slave bundle = hbm8 
#pragma HLS INTERFACE m_axi port = out0_0_4 offset = slave bundle = hbm8 
#pragma HLS INTERFACE m_axi port = out1_0_4 offset = slave bundle = hbm8 
#pragma HLS INTERFACE m_axi port = out0_0_5 offset = slave bundle = hbm8 
#pragma HLS INTERFACE m_axi port = out1_0_5 offset = slave bundle = hbm8 
#pragma HLS INTERFACE m_axi port = out0_0_6 offset = slave bundle = hbm8 
#pragma HLS INTERFACE m_axi port = out1_0_6 offset = slave bundle = hbm8 
#pragma HLS INTERFACE m_axi port = out0_0_7 offset = slave bundle = hbm8 
#pragma HLS INTERFACE m_axi port = out1_0_7 offset = slave bundle = hbm8 
#pragma HLS INTERFACE m_axi port = out0_1_0 offset = slave bundle = hbm9 
#pragma HLS INTERFACE m_axi port = out1_1_0 offset = slave bundle = hbm9 
#pragma HLS INTERFACE m_axi port = out0_1_1 offset = slave bundle = hbm9 
#pragma HLS INTERFACE m_axi port = out1_1_1 offset = slave bundle = hbm9 
#pragma HLS INTERFACE m_axi port = out0_1_2 offset = slave bundle = hbm9 
#pragma HLS INTERFACE m_axi port = out1_1_2 offset = slave bundle = hbm9 
#pragma HLS INTERFACE m_axi port = out0_1_3 offset = slave bundle = hbm9 
#pragma HLS INTERFACE m_axi port = out1_1_3 offset = slave bundle = hbm9 
#pragma HLS INTERFACE m_axi port = out0_1_4 offset = slave bundle = hbm9 
#pragma HLS INTERFACE m_axi port = out1_1_4 offset = slave bundle = hbm9 
#pragma HLS INTERFACE m_axi port = out0_1_5 offset = slave bundle = hbm9 
#pragma HLS INTERFACE m_axi port = out1_1_5 offset = slave bundle = hbm9 
#pragma HLS INTERFACE m_axi port = out0_1_6 offset = slave bundle = hbm9 
#pragma HLS INTERFACE m_axi port = out1_1_6 offset = slave bundle = hbm9 
#pragma HLS INTERFACE m_axi port = out0_1_7 offset = slave bundle = hbm9 
#pragma HLS INTERFACE m_axi port = out1_1_7 offset = slave bundle = hbm9 
#pragma HLS INTERFACE m_axi port = out0_2_0 offset = slave bundle = hbm10 
#pragma HLS INTERFACE m_axi port = out1_2_0 offset = slave bundle = hbm10 
#pragma HLS INTERFACE m_axi port = out0_2_1 offset = slave bundle = hbm10 
#pragma HLS INTERFACE m_axi port = out1_2_1 offset = slave bundle = hbm10 
#pragma HLS INTERFACE m_axi port = out0_2_2 offset = slave bundle = hbm10 
#pragma HLS INTERFACE m_axi port = out1_2_2 offset = slave bundle = hbm10 
#pragma HLS INTERFACE m_axi port = out0_2_3 offset = slave bundle = hbm10 
#pragma HLS INTERFACE m_axi port = out1_2_3 offset = slave bundle = hbm10 
#pragma HLS INTERFACE m_axi port = out0_2_4 offset = slave bundle = hbm10 
#pragma HLS INTERFACE m_axi port = out1_2_4 offset = slave bundle = hbm10 
#pragma HLS INTERFACE m_axi port = out0_2_5 offset = slave bundle = hbm10 
#pragma HLS INTERFACE m_axi port = out1_2_5 offset = slave bundle = hbm10 
#pragma HLS INTERFACE m_axi port = out0_2_6 offset = slave bundle = hbm10 
#pragma HLS INTERFACE m_axi port = out1_2_6 offset = slave bundle = hbm10 
#pragma HLS INTERFACE m_axi port = out0_2_7 offset = slave bundle = hbm10 
#pragma HLS INTERFACE m_axi port = out1_2_7 offset = slave bundle = hbm10 
#pragma HLS INTERFACE m_axi port = out0_3_0 offset = slave bundle = hbm11 
#pragma HLS INTERFACE m_axi port = out1_3_0 offset = slave bundle = hbm11 
#pragma HLS INTERFACE m_axi port = out0_3_1 offset = slave bundle = hbm11 
#pragma HLS INTERFACE m_axi port = out1_3_1 offset = slave bundle = hbm11 
#pragma HLS INTERFACE m_axi port = out0_3_2 offset = slave bundle = hbm11 
#pragma HLS INTERFACE m_axi port = out1_3_2 offset = slave bundle = hbm11 
#pragma HLS INTERFACE m_axi port = out0_3_3 offset = slave bundle = hbm11 
#pragma HLS INTERFACE m_axi port = out1_3_3 offset = slave bundle = hbm11 
#pragma HLS INTERFACE m_axi port = out0_3_4 offset = slave bundle = hbm11 
#pragma HLS INTERFACE m_axi port = out1_3_4 offset = slave bundle = hbm11 
#pragma HLS INTERFACE m_axi port = out0_3_5 offset = slave bundle = hbm11 
#pragma HLS INTERFACE m_axi port = out1_3_5 offset = slave bundle = hbm11 
#pragma HLS INTERFACE m_axi port = out0_3_6 offset = slave bundle = hbm11 
#pragma HLS INTERFACE m_axi port = out1_3_6 offset = slave bundle = hbm11 
#pragma HLS INTERFACE m_axi port = out0_3_7 offset = slave bundle = hbm11 
#pragma HLS INTERFACE m_axi port = out1_3_7 offset = slave bundle = hbm11 
#pragma HLS INTERFACE m_axi port = out0_4_0 offset = slave bundle = hbm12 
#pragma HLS INTERFACE m_axi port = out1_4_0 offset = slave bundle = hbm12 
#pragma HLS INTERFACE m_axi port = out0_4_1 offset = slave bundle = hbm12 
#pragma HLS INTERFACE m_axi port = out1_4_1 offset = slave bundle = hbm12 
#pragma HLS INTERFACE m_axi port = out0_4_2 offset = slave bundle = hbm12 
#pragma HLS INTERFACE m_axi port = out1_4_2 offset = slave bundle = hbm12 
#pragma HLS INTERFACE m_axi port = out0_4_3 offset = slave bundle = hbm12 
#pragma HLS INTERFACE m_axi port = out1_4_3 offset = slave bundle = hbm12 
#pragma HLS INTERFACE m_axi port = out0_4_4 offset = slave bundle = hbm12 
#pragma HLS INTERFACE m_axi port = out1_4_4 offset = slave bundle = hbm12 
#pragma HLS INTERFACE m_axi port = out0_4_5 offset = slave bundle = hbm12 
#pragma HLS INTERFACE m_axi port = out1_4_5 offset = slave bundle = hbm12 
#pragma HLS INTERFACE m_axi port = out0_4_6 offset = slave bundle = hbm12 
#pragma HLS INTERFACE m_axi port = out1_4_6 offset = slave bundle = hbm12 
#pragma HLS INTERFACE m_axi port = out0_4_7 offset = slave bundle = hbm12 
#pragma HLS INTERFACE m_axi port = out1_4_7 offset = slave bundle = hbm12 
#pragma HLS INTERFACE m_axi port = out0_5_0 offset = slave bundle = hbm13 
#pragma HLS INTERFACE m_axi port = out1_5_0 offset = slave bundle = hbm13 
#pragma HLS INTERFACE m_axi port = out0_5_1 offset = slave bundle = hbm13 
#pragma HLS INTERFACE m_axi port = out1_5_1 offset = slave bundle = hbm13 
#pragma HLS INTERFACE m_axi port = out0_5_2 offset = slave bundle = hbm13 
#pragma HLS INTERFACE m_axi port = out1_5_2 offset = slave bundle = hbm13 
#pragma HLS INTERFACE m_axi port = out0_5_3 offset = slave bundle = hbm13 
#pragma HLS INTERFACE m_axi port = out1_5_3 offset = slave bundle = hbm13 
#pragma HLS INTERFACE m_axi port = out0_5_4 offset = slave bundle = hbm13 
#pragma HLS INTERFACE m_axi port = out1_5_4 offset = slave bundle = hbm13 
#pragma HLS INTERFACE m_axi port = out0_5_5 offset = slave bundle = hbm13 
#pragma HLS INTERFACE m_axi port = out1_5_5 offset = slave bundle = hbm13 
#pragma HLS INTERFACE m_axi port = out0_5_6 offset = slave bundle = hbm13 
#pragma HLS INTERFACE m_axi port = out1_5_6 offset = slave bundle = hbm13 
#pragma HLS INTERFACE m_axi port = out0_5_7 offset = slave bundle = hbm13 
#pragma HLS INTERFACE m_axi port = out1_5_7 offset = slave bundle = hbm13 
#pragma HLS INTERFACE m_axi port = out0_6_0 offset = slave bundle = hbm14 
#pragma HLS INTERFACE m_axi port = out1_6_0 offset = slave bundle = hbm14 
#pragma HLS INTERFACE m_axi port = out0_6_1 offset = slave bundle = hbm14 
#pragma HLS INTERFACE m_axi port = out1_6_1 offset = slave bundle = hbm14 
#pragma HLS INTERFACE m_axi port = out0_6_2 offset = slave bundle = hbm14 
#pragma HLS INTERFACE m_axi port = out1_6_2 offset = slave bundle = hbm14 
#pragma HLS INTERFACE m_axi port = out0_6_3 offset = slave bundle = hbm14 
#pragma HLS INTERFACE m_axi port = out1_6_3 offset = slave bundle = hbm14 
#pragma HLS INTERFACE m_axi port = out0_6_4 offset = slave bundle = hbm14 
#pragma HLS INTERFACE m_axi port = out1_6_4 offset = slave bundle = hbm14 
#pragma HLS INTERFACE m_axi port = out0_6_5 offset = slave bundle = hbm14 
#pragma HLS INTERFACE m_axi port = out1_6_5 offset = slave bundle = hbm14 
#pragma HLS INTERFACE m_axi port = out0_6_6 offset = slave bundle = hbm14 
#pragma HLS INTERFACE m_axi port = out1_6_6 offset = slave bundle = hbm14 
#pragma HLS INTERFACE m_axi port = out0_6_7 offset = slave bundle = hbm14 
#pragma HLS INTERFACE m_axi port = out1_6_7 offset = slave bundle = hbm14 
#pragma HLS INTERFACE m_axi port = out0_7_0 offset = slave bundle = hbm15 
#pragma HLS INTERFACE m_axi port = out1_7_0 offset = slave bundle = hbm15 
#pragma HLS INTERFACE m_axi port = out0_7_1 offset = slave bundle = hbm15 
#pragma HLS INTERFACE m_axi port = out1_7_1 offset = slave bundle = hbm15 
#pragma HLS INTERFACE m_axi port = out0_7_2 offset = slave bundle = hbm15 
#pragma HLS INTERFACE m_axi port = out1_7_2 offset = slave bundle = hbm15 
#pragma HLS INTERFACE m_axi port = out0_7_3 offset = slave bundle = hbm15 
#pragma HLS INTERFACE m_axi port = out1_7_3 offset = slave bundle = hbm15 
#pragma HLS INTERFACE m_axi port = out0_7_4 offset = slave bundle = hbm15 
#pragma HLS INTERFACE m_axi port = out1_7_4 offset = slave bundle = hbm15 
#pragma HLS INTERFACE m_axi port = out0_7_5 offset = slave bundle = hbm15 
#pragma HLS INTERFACE m_axi port = out1_7_5 offset = slave bundle = hbm15 
#pragma HLS INTERFACE m_axi port = out0_7_6 offset = slave bundle = hbm15 
#pragma HLS INTERFACE m_axi port = out1_7_6 offset = slave bundle = hbm15 
#pragma HLS INTERFACE m_axi port = out0_7_7 offset = slave bundle = hbm15 
#pragma HLS INTERFACE m_axi port = out1_7_7 offset = slave bundle = hbm15 

#pragma HLS INTERFACE s_axilite port = repeat_num bundle = control
#pragma HLS INTERFACE s_axilite port = data_num bundle = control
#pragma HLS INTERFACE s_axilite port = shift bundle = control
#pragma HLS INTERFACE s_axilite port = return bundle = control

#pragma HLS dataflow

  hls::stream<ap_uint<512> > user_fifo0_0 ;   
  hls::stream<ap_uint<512> > user_fifo1_0 ;   
  hls::stream<ap_uint<512> > user_fifo2_0 ;   
  hls::stream<ap_uint<512> > user_fifo3_0 ;   
  hls::stream<ap_uint<512> > user_fifo4_0 ;   
  hls::stream<ap_uint<512> > user_fifo5_0 ;   
  hls::stream<ap_uint<512> > user_fifo6_0 ;   
  hls::stream<ap_uint<512> > user_fifo7_0 ;   

#pragma HLS STREAM variable=user_fifo0_0  depth=512 dim=1
#pragma HLS STREAM variable=user_fifo1_0  depth=512 dim=1
#pragma HLS STREAM variable=user_fifo2_0  depth=512 dim=1
#pragma HLS STREAM variable=user_fifo3_0  depth=512 dim=1
#pragma HLS STREAM variable=user_fifo4_0  depth=512 dim=1
#pragma HLS STREAM variable=user_fifo5_0  depth=512 dim=1
#pragma HLS STREAM variable=user_fifo6_0  depth=512 dim=1
#pragma HLS STREAM variable=user_fifo7_0  depth=512 dim=1
#pragma HLS RESOURCE variable=user_fifo0_0 core=FIFO_BRAM
#pragma HLS RESOURCE variable=user_fifo1_0 core=FIFO_BRAM
#pragma HLS RESOURCE variable=user_fifo2_0 core=FIFO_BRAM
#pragma HLS RESOURCE variable=user_fifo3_0 core=FIFO_BRAM
#pragma HLS RESOURCE variable=user_fifo4_0 core=FIFO_BRAM
#pragma HLS RESOURCE variable=user_fifo5_0 core=FIFO_BRAM
#pragma HLS RESOURCE variable=user_fifo6_0 core=FIFO_BRAM
#pragma HLS RESOURCE variable=user_fifo7_0 core=FIFO_BRAM

  read(
  in0_0_0,
  in0_0_1,
  in0_0_2,
  in0_0_3,
  in0_0_4,
  in0_0_5,
  in0_0_6,
  in0_0_7,
  in1_0_0,
  in1_0_1,
  in1_0_2,
  in1_0_3,
  in1_0_4,
  in1_0_5,
  in1_0_6,
  in1_0_7,
	user_fifo0_0, 
	repeat_num, data_num, shift);
  read(
  in0_1_0,
  in0_1_1,
  in0_1_2,
  in0_1_3,
  in0_1_4,
  in0_1_5,
  in0_1_6,
  in0_1_7,
  in1_1_0,
  in1_1_1,
  in1_1_2,
  in1_1_3,
  in1_1_4,
  in1_1_5,
  in1_1_6,
  in1_1_7,
	user_fifo1_0, 
	repeat_num, data_num, shift);
  read(
  in0_2_0,
  in0_2_1,
  in0_2_2,
  in0_2_3,
  in0_2_4,
  in0_2_5,
  in0_2_6,
  in0_2_7,
  in1_2_0,
  in1_2_1,
  in1_2_2,
  in1_2_3,
  in1_2_4,
  in1_2_5,
  in1_2_6,
  in1_2_7,
	user_fifo2_0, 
	repeat_num, data_num, shift);
  read(
  in0_3_0,
  in0_3_1,
  in0_3_2,
  in0_3_3,
  in0_3_4,
  in0_3_5,
  in0_3_6,
  in0_3_7,
  in1_3_0,
  in1_3_1,
  in1_3_2,
  in1_3_3,
  in1_3_4,
  in1_3_5,
  in1_3_6,
  in1_3_7,
	user_fifo3_0, 
	repeat_num, data_num, shift);
  read(
  in0_4_0,
  in0_4_1,
  in0_4_2,
  in0_4_3,
  in0_4_4,
  in0_4_5,
  in0_4_6,
  in0_4_7,
  in1_4_0,
  in1_4_1,
  in1_4_2,
  in1_4_3,
  in1_4_4,
  in1_4_5,
  in1_4_6,
  in1_4_7,
	user_fifo4_0, 
	repeat_num, data_num, shift);
  read(
  in0_5_0,
  in0_5_1,
  in0_5_2,
  in0_5_3,
  in0_5_4,
  in0_5_5,
  in0_5_6,
  in0_5_7,
  in1_5_0,
  in1_5_1,
  in1_5_2,
  in1_5_3,
  in1_5_4,
  in1_5_5,
  in1_5_6,
  in1_5_7,
	user_fifo5_0, 
	repeat_num, data_num, shift);
  read(
  in0_6_0,
  in0_6_1,
  in0_6_2,
  in0_6_3,
  in0_6_4,
  in0_6_5,
  in0_6_6,
  in0_6_7,
  in1_6_0,
  in1_6_1,
  in1_6_2,
  in1_6_3,
  in1_6_4,
  in1_6_5,
  in1_6_6,
  in1_6_7,
	user_fifo6_0, 
	repeat_num, data_num, shift);
  read(
  in0_7_0,
  in0_7_1,
  in0_7_2,
  in0_7_3,
  in0_7_4,
  in0_7_5,
  in0_7_6,
  in0_7_7,
  in1_7_0,
  in1_7_1,
  in1_7_2,
  in1_7_3,
  in1_7_4,
  in1_7_5,
  in1_7_6,
  in1_7_7,
	user_fifo7_0, 
	repeat_num, data_num, shift);

  write(
	user_fifo0_0, 
	out0_0_0, 
	out0_0_1, 
	out0_0_2, 
	out0_0_3, 
	out0_0_4, 
	out0_0_5, 
	out0_0_6, 
	out0_0_7, 
	out1_0_0, 
	out1_0_1, 
	out1_0_2, 
	out1_0_3, 
	out1_0_4, 
	out1_0_5, 
	out1_0_6, 
	out1_0_7, 
	repeat_num, data_num, shift);
  write(
	user_fifo1_0, 
	out0_1_0, 
	out0_1_1, 
	out0_1_2, 
	out0_1_3, 
	out0_1_4, 
	out0_1_5, 
	out0_1_6, 
	out0_1_7, 
	out1_1_0, 
	out1_1_1, 
	out1_1_2, 
	out1_1_3, 
	out1_1_4, 
	out1_1_5, 
	out1_1_6, 
	out1_1_7, 
	repeat_num, data_num, shift);
  write(
	user_fifo2_0, 
	out0_2_0, 
	out0_2_1, 
	out0_2_2, 
	out0_2_3, 
	out0_2_4, 
	out0_2_5, 
	out0_2_6, 
	out0_2_7, 
	out1_2_0, 
	out1_2_1, 
	out1_2_2, 
	out1_2_3, 
	out1_2_4, 
	out1_2_5, 
	out1_2_6, 
	out1_2_7, 
	repeat_num, data_num, shift);
  write(
	user_fifo3_0, 
	out0_3_0, 
	out0_3_1, 
	out0_3_2, 
	out0_3_3, 
	out0_3_4, 
	out0_3_5, 
	out0_3_6, 
	out0_3_7, 
	out1_3_0, 
	out1_3_1, 
	out1_3_2, 
	out1_3_3, 
	out1_3_4, 
	out1_3_5, 
	out1_3_6, 
	out1_3_7, 
	repeat_num, data_num, shift);
  write(
	user_fifo4_0, 
	out0_4_0, 
	out0_4_1, 
	out0_4_2, 
	out0_4_3, 
	out0_4_4, 
	out0_4_5, 
	out0_4_6, 
	out0_4_7, 
	out1_4_0, 
	out1_4_1, 
	out1_4_2, 
	out1_4_3, 
	out1_4_4, 
	out1_4_5, 
	out1_4_6, 
	out1_4_7, 
	repeat_num, data_num, shift);
  write(
	user_fifo5_0, 
	out0_5_0, 
	out0_5_1, 
	out0_5_2, 
	out0_5_3, 
	out0_5_4, 
	out0_5_5, 
	out0_5_6, 
	out0_5_7, 
	out1_5_0, 
	out1_5_1, 
	out1_5_2, 
	out1_5_3, 
	out1_5_4, 
	out1_5_5, 
	out1_5_6, 
	out1_5_7, 
	repeat_num, data_num, shift);
  write(
	user_fifo6_0, 
	out0_6_0, 
	out0_6_1, 
	out0_6_2, 
	out0_6_3, 
	out0_6_4, 
	out0_6_5, 
	out0_6_6, 
	out0_6_7, 
	out1_6_0, 
	out1_6_1, 
	out1_6_2, 
	out1_6_3, 
	out1_6_4, 
	out1_6_5, 
	out1_6_6, 
	out1_6_7, 
	repeat_num, data_num, shift);
  write(
	user_fifo7_0, 
	out0_7_0, 
	out0_7_1, 
	out0_7_2, 
	out0_7_3, 
	out0_7_4, 
	out0_7_5, 
	out0_7_6, 
	out0_7_7, 
	out1_7_0, 
	out1_7_1, 
	out1_7_2, 
	out1_7_3, 
	out1_7_4, 
	out1_7_5, 
	out1_7_6, 
	out1_7_7, 
	repeat_num, data_num, shift);

}
#ifndef HLS
} // end of extern C
#endif
