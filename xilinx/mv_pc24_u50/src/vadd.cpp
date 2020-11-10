

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

void readA(
  const ap_uint<512>* A,
  hls::stream<ap_uint<512> > & fifo_A,
  int matrix_size,
  int repeat_num
)
{
	for(int r = 0 ; r < repeat_num ; r++){
#pragma HLS loop_flatten off
		for(int i = 0 ; i < matrix_size*matrix_size/24/16 ; i++ ){
#pragma HLS pipeline
			ap_uint<512> local_A = A[i];
			ap_uint<512> local_A_delay = HLS_REG(HLS_REG(local_A));
			fifo_A.write(local_A_delay);	
		}
	}
}

void mv(
  hls::stream<ap_uint<512> > & fifo_A0, 
  hls::stream<ap_uint<512> > & fifo_A1, 
  hls::stream<ap_uint<512> > & fifo_A2, 
  hls::stream<ap_uint<512> > & fifo_A3, 
  hls::stream<ap_uint<512> > & fifo_A4, 
  hls::stream<ap_uint<512> > & fifo_A5, 
  hls::stream<ap_uint<512> > & fifo_A6, 
  hls::stream<ap_uint<512> > & fifo_A7, 
  hls::stream<ap_uint<512> > & fifo_A8, 
  hls::stream<ap_uint<512> > & fifo_A9, 
  hls::stream<ap_uint<512> > & fifo_A10, 
  hls::stream<ap_uint<512> > & fifo_A11, 
  hls::stream<ap_uint<512> > & fifo_A12, 
  hls::stream<ap_uint<512> > & fifo_A13, 
  hls::stream<ap_uint<512> > & fifo_A14, 
  hls::stream<ap_uint<512> > & fifo_A15, 
  hls::stream<ap_uint<512> > & fifo_A16, 
  hls::stream<ap_uint<512> > & fifo_A17, 
  hls::stream<ap_uint<512> > & fifo_A18, 
  hls::stream<ap_uint<512> > & fifo_A19, 
  hls::stream<ap_uint<512> > & fifo_A20, 
  hls::stream<ap_uint<512> > & fifo_A21, 
  hls::stream<ap_uint<512> > & fifo_A22, 
  hls::stream<ap_uint<512> > & fifo_A23, 
  hls::stream<ap_uint<512> >& x, 
  hls::stream<ap_uint<512> > & fifo_y,
  int matrix_size,
  int repeat_num
)
{
         ap_uint<512> local_x0[24576/16];
         ap_uint<512> local_x1[24576/16];
         ap_uint<512> local_x2[24576/16];
         ap_uint<512> local_x3[24576/16];
         ap_uint<512> local_x4[24576/16];
         ap_uint<512> local_x5[24576/16];
         ap_uint<512> local_x6[24576/16];
         ap_uint<512> local_x7[24576/16];
         ap_uint<512> local_x8[24576/16];
         ap_uint<512> local_x9[24576/16];
         ap_uint<512> local_x10[24576/16];
         ap_uint<512> local_x11[24576/16];
         ap_uint<512> local_x12[24576/16];
         ap_uint<512> local_x13[24576/16];
         ap_uint<512> local_x14[24576/16];
         ap_uint<512> local_x15[24576/16];
         ap_uint<512> local_x16[24576/16];
         ap_uint<512> local_x17[24576/16];
         ap_uint<512> local_x18[24576/16];
         ap_uint<512> local_x19[24576/16];
         ap_uint<512> local_x20[24576/16];
         ap_uint<512> local_x21[24576/16];
         ap_uint<512> local_x22[24576/16];
         ap_uint<512> local_x23[24576/16];

        for(int i = 0 ; i < matrix_size/16 ; i++ ){
#pragma HLS pipeline
		ap_uint<512> x_temp = x.read();
		ap_uint<512> x_temp_delay = HLS_REG(HLS_REG(x_temp));
                local_x0[i] = x_temp_delay;
                local_x1[i] = x_temp_delay;
                local_x2[i] = x_temp_delay;
                local_x3[i] = x_temp_delay;
                local_x4[i] = x_temp_delay;
                local_x5[i] = x_temp_delay;
                local_x6[i] = x_temp_delay;
                local_x7[i] = x_temp_delay;
                local_x8[i] = x_temp_delay;
                local_x9[i] = x_temp_delay;
                local_x10[i] = x_temp_delay;
                local_x11[i] = x_temp_delay;
                local_x12[i] = x_temp_delay;
                local_x13[i] = x_temp_delay;
                local_x14[i] = x_temp_delay;
                local_x15[i] = x_temp_delay;
                local_x16[i] = x_temp_delay;
                local_x17[i] = x_temp_delay;
                local_x18[i] = x_temp_delay;
                local_x19[i] = x_temp_delay;
                local_x20[i] = x_temp_delay;
                local_x21[i] = x_temp_delay;
                local_x22[i] = x_temp_delay;
                local_x23[i] = x_temp_delay;
        }

        for(int r = 0 ; r < repeat_num ; r++){
#pragma HLS loop_flatten off
	        for(int i2 = 0 ; i2 < matrix_size/16/24 ; i2++ ){
			ap_uint<512>  y512_0 = 0;
			ap_uint<512>  y512_1 = 0;
			ap_uint<512>  y512_2 = 0;
			ap_uint<512>  y512_3 = 0;
			ap_uint<512>  y512_4 = 0;
			ap_uint<512>  y512_5 = 0;
			ap_uint<512>  y512_6 = 0;
			ap_uint<512>  y512_7 = 0;
			ap_uint<512>  y512_8 = 0;
			ap_uint<512>  y512_9 = 0;
			ap_uint<512>  y512_10 = 0;
			ap_uint<512>  y512_11 = 0;
			ap_uint<512>  y512_12 = 0;
			ap_uint<512>  y512_13 = 0;
			ap_uint<512>  y512_14 = 0;
			ap_uint<512>  y512_15 = 0;
			ap_uint<512>  y512_16 = 0;
			ap_uint<512>  y512_17 = 0;
			ap_uint<512>  y512_18 = 0;
			ap_uint<512>  y512_19 = 0;
			ap_uint<512>  y512_20 = 0;
			ap_uint<512>  y512_21 = 0;
			ap_uint<512>  y512_22 = 0;
			ap_uint<512>  y512_23 = 0;
        		for(int i1 = 0 ; i1 < 16 ; i1++ ){
                	        ap_uint<32>  acc_y0 = 0; 
                	        ap_uint<32>  acc_y1 = 0; 
                	        ap_uint<32>  acc_y2 = 0; 
                	        ap_uint<32>  acc_y3 = 0; 
                	        ap_uint<32>  acc_y4 = 0; 
                	        ap_uint<32>  acc_y5 = 0; 
                	        ap_uint<32>  acc_y6 = 0; 
                	        ap_uint<32>  acc_y7 = 0; 
                	        ap_uint<32>  acc_y8 = 0; 
                	        ap_uint<32>  acc_y9 = 0; 
                	        ap_uint<32>  acc_y10 = 0; 
                	        ap_uint<32>  acc_y11 = 0; 
                	        ap_uint<32>  acc_y12 = 0; 
                	        ap_uint<32>  acc_y13 = 0; 
                	        ap_uint<32>  acc_y14 = 0; 
                	        ap_uint<32>  acc_y15 = 0; 
                	        ap_uint<32>  acc_y16 = 0; 
                	        ap_uint<32>  acc_y17 = 0; 
                	        ap_uint<32>  acc_y18 = 0; 
                	        ap_uint<32>  acc_y19 = 0; 
                	        ap_uint<32>  acc_y20 = 0; 
                	        ap_uint<32>  acc_y21 = 0; 
                	        ap_uint<32>  acc_y22 = 0; 
                	        ap_uint<32>  acc_y23 = 0; 
	                        for( int j = 0 ; j < matrix_size/16 ; j++ ){
#pragma HLS pipeline
					ap_uint<512> local_A0 = fifo_A0.read();
                	        	ap_uint<18> A0_u0 = local_A0(17+32*0,32*0); 
                	        	ap_uint<18> A0_u1 = local_A0(17+32*1,32*1); 
                	        	ap_uint<18> A0_u2 = local_A0(17+32*2,32*2); 
                	        	ap_uint<18> A0_u3 = local_A0(17+32*3,32*3); 
                	        	ap_uint<18> A0_u4 = local_A0(17+32*4,32*4); 
                	        	ap_uint<18> A0_u5 = local_A0(17+32*5,32*5); 
                	        	ap_uint<18> A0_u6 = local_A0(17+32*6,32*6); 
                	        	ap_uint<18> A0_u7 = local_A0(17+32*7,32*7); 
                	        	ap_uint<18> A0_u8 = local_A0(17+32*8,32*8); 
                	        	ap_uint<18> A0_u9 = local_A0(17+32*9,32*9); 
                	        	ap_uint<18> A0_u10 = local_A0(17+32*10,32*10); 
                	        	ap_uint<18> A0_u11 = local_A0(17+32*11,32*11); 
                	        	ap_uint<18> A0_u12 = local_A0(17+32*12,32*12); 
                	        	ap_uint<18> A0_u13 = local_A0(17+32*13,32*13); 
                	        	ap_uint<18> A0_u14 = local_A0(17+32*14,32*14); 
                	        	ap_uint<18> A0_u15 = local_A0(17+32*15,32*15); 
					ap_uint<512> local_x0_temp = local_x0[j];
                        		ap_uint<18> x0_u0 = local_x0_temp(17+32*0,32*0); 
                        		ap_uint<18> x0_u1 = local_x0_temp(17+32*1,32*1); 
                        		ap_uint<18> x0_u2 = local_x0_temp(17+32*2,32*2); 
                        		ap_uint<18> x0_u3 = local_x0_temp(17+32*3,32*3); 
                        		ap_uint<18> x0_u4 = local_x0_temp(17+32*4,32*4); 
                        		ap_uint<18> x0_u5 = local_x0_temp(17+32*5,32*5); 
                        		ap_uint<18> x0_u6 = local_x0_temp(17+32*6,32*6); 
                        		ap_uint<18> x0_u7 = local_x0_temp(17+32*7,32*7); 
                        		ap_uint<18> x0_u8 = local_x0_temp(17+32*8,32*8); 
                        		ap_uint<18> x0_u9 = local_x0_temp(17+32*9,32*9); 
                        		ap_uint<18> x0_u10 = local_x0_temp(17+32*10,32*10); 
                        		ap_uint<18> x0_u11 = local_x0_temp(17+32*11,32*11); 
                        		ap_uint<18> x0_u12 = local_x0_temp(17+32*12,32*12); 
                        		ap_uint<18> x0_u13 = local_x0_temp(17+32*13,32*13); 
                        		ap_uint<18> x0_u14 = local_x0_temp(17+32*14,32*14); 
                        		ap_uint<18> x0_u15 = local_x0_temp(17+32*15,32*15); 
					ap_uint<512> local_A1 = fifo_A1.read();
                	        	ap_uint<18> A1_u0 = local_A1(17+32*0,32*0); 
                	        	ap_uint<18> A1_u1 = local_A1(17+32*1,32*1); 
                	        	ap_uint<18> A1_u2 = local_A1(17+32*2,32*2); 
                	        	ap_uint<18> A1_u3 = local_A1(17+32*3,32*3); 
                	        	ap_uint<18> A1_u4 = local_A1(17+32*4,32*4); 
                	        	ap_uint<18> A1_u5 = local_A1(17+32*5,32*5); 
                	        	ap_uint<18> A1_u6 = local_A1(17+32*6,32*6); 
                	        	ap_uint<18> A1_u7 = local_A1(17+32*7,32*7); 
                	        	ap_uint<18> A1_u8 = local_A1(17+32*8,32*8); 
                	        	ap_uint<18> A1_u9 = local_A1(17+32*9,32*9); 
                	        	ap_uint<18> A1_u10 = local_A1(17+32*10,32*10); 
                	        	ap_uint<18> A1_u11 = local_A1(17+32*11,32*11); 
                	        	ap_uint<18> A1_u12 = local_A1(17+32*12,32*12); 
                	        	ap_uint<18> A1_u13 = local_A1(17+32*13,32*13); 
                	        	ap_uint<18> A1_u14 = local_A1(17+32*14,32*14); 
                	        	ap_uint<18> A1_u15 = local_A1(17+32*15,32*15); 
					ap_uint<512> local_x1_temp = local_x1[j];
                        		ap_uint<18> x1_u0 = local_x1_temp(17+32*0,32*0); 
                        		ap_uint<18> x1_u1 = local_x1_temp(17+32*1,32*1); 
                        		ap_uint<18> x1_u2 = local_x1_temp(17+32*2,32*2); 
                        		ap_uint<18> x1_u3 = local_x1_temp(17+32*3,32*3); 
                        		ap_uint<18> x1_u4 = local_x1_temp(17+32*4,32*4); 
                        		ap_uint<18> x1_u5 = local_x1_temp(17+32*5,32*5); 
                        		ap_uint<18> x1_u6 = local_x1_temp(17+32*6,32*6); 
                        		ap_uint<18> x1_u7 = local_x1_temp(17+32*7,32*7); 
                        		ap_uint<18> x1_u8 = local_x1_temp(17+32*8,32*8); 
                        		ap_uint<18> x1_u9 = local_x1_temp(17+32*9,32*9); 
                        		ap_uint<18> x1_u10 = local_x1_temp(17+32*10,32*10); 
                        		ap_uint<18> x1_u11 = local_x1_temp(17+32*11,32*11); 
                        		ap_uint<18> x1_u12 = local_x1_temp(17+32*12,32*12); 
                        		ap_uint<18> x1_u13 = local_x1_temp(17+32*13,32*13); 
                        		ap_uint<18> x1_u14 = local_x1_temp(17+32*14,32*14); 
                        		ap_uint<18> x1_u15 = local_x1_temp(17+32*15,32*15); 
					ap_uint<512> local_A2 = fifo_A2.read();
                	        	ap_uint<18> A2_u0 = local_A2(17+32*0,32*0); 
                	        	ap_uint<18> A2_u1 = local_A2(17+32*1,32*1); 
                	        	ap_uint<18> A2_u2 = local_A2(17+32*2,32*2); 
                	        	ap_uint<18> A2_u3 = local_A2(17+32*3,32*3); 
                	        	ap_uint<18> A2_u4 = local_A2(17+32*4,32*4); 
                	        	ap_uint<18> A2_u5 = local_A2(17+32*5,32*5); 
                	        	ap_uint<18> A2_u6 = local_A2(17+32*6,32*6); 
                	        	ap_uint<18> A2_u7 = local_A2(17+32*7,32*7); 
                	        	ap_uint<18> A2_u8 = local_A2(17+32*8,32*8); 
                	        	ap_uint<18> A2_u9 = local_A2(17+32*9,32*9); 
                	        	ap_uint<18> A2_u10 = local_A2(17+32*10,32*10); 
                	        	ap_uint<18> A2_u11 = local_A2(17+32*11,32*11); 
                	        	ap_uint<18> A2_u12 = local_A2(17+32*12,32*12); 
                	        	ap_uint<18> A2_u13 = local_A2(17+32*13,32*13); 
                	        	ap_uint<18> A2_u14 = local_A2(17+32*14,32*14); 
                	        	ap_uint<18> A2_u15 = local_A2(17+32*15,32*15); 
					ap_uint<512> local_x2_temp = local_x2[j];
                        		ap_uint<18> x2_u0 = local_x2_temp(17+32*0,32*0); 
                        		ap_uint<18> x2_u1 = local_x2_temp(17+32*1,32*1); 
                        		ap_uint<18> x2_u2 = local_x2_temp(17+32*2,32*2); 
                        		ap_uint<18> x2_u3 = local_x2_temp(17+32*3,32*3); 
                        		ap_uint<18> x2_u4 = local_x2_temp(17+32*4,32*4); 
                        		ap_uint<18> x2_u5 = local_x2_temp(17+32*5,32*5); 
                        		ap_uint<18> x2_u6 = local_x2_temp(17+32*6,32*6); 
                        		ap_uint<18> x2_u7 = local_x2_temp(17+32*7,32*7); 
                        		ap_uint<18> x2_u8 = local_x2_temp(17+32*8,32*8); 
                        		ap_uint<18> x2_u9 = local_x2_temp(17+32*9,32*9); 
                        		ap_uint<18> x2_u10 = local_x2_temp(17+32*10,32*10); 
                        		ap_uint<18> x2_u11 = local_x2_temp(17+32*11,32*11); 
                        		ap_uint<18> x2_u12 = local_x2_temp(17+32*12,32*12); 
                        		ap_uint<18> x2_u13 = local_x2_temp(17+32*13,32*13); 
                        		ap_uint<18> x2_u14 = local_x2_temp(17+32*14,32*14); 
                        		ap_uint<18> x2_u15 = local_x2_temp(17+32*15,32*15); 
					ap_uint<512> local_A3 = fifo_A3.read();
                	        	ap_uint<18> A3_u0 = local_A3(17+32*0,32*0); 
                	        	ap_uint<18> A3_u1 = local_A3(17+32*1,32*1); 
                	        	ap_uint<18> A3_u2 = local_A3(17+32*2,32*2); 
                	        	ap_uint<18> A3_u3 = local_A3(17+32*3,32*3); 
                	        	ap_uint<18> A3_u4 = local_A3(17+32*4,32*4); 
                	        	ap_uint<18> A3_u5 = local_A3(17+32*5,32*5); 
                	        	ap_uint<18> A3_u6 = local_A3(17+32*6,32*6); 
                	        	ap_uint<18> A3_u7 = local_A3(17+32*7,32*7); 
                	        	ap_uint<18> A3_u8 = local_A3(17+32*8,32*8); 
                	        	ap_uint<18> A3_u9 = local_A3(17+32*9,32*9); 
                	        	ap_uint<18> A3_u10 = local_A3(17+32*10,32*10); 
                	        	ap_uint<18> A3_u11 = local_A3(17+32*11,32*11); 
                	        	ap_uint<18> A3_u12 = local_A3(17+32*12,32*12); 
                	        	ap_uint<18> A3_u13 = local_A3(17+32*13,32*13); 
                	        	ap_uint<18> A3_u14 = local_A3(17+32*14,32*14); 
                	        	ap_uint<18> A3_u15 = local_A3(17+32*15,32*15); 
					ap_uint<512> local_x3_temp = local_x3[j];
                        		ap_uint<18> x3_u0 = local_x3_temp(17+32*0,32*0); 
                        		ap_uint<18> x3_u1 = local_x3_temp(17+32*1,32*1); 
                        		ap_uint<18> x3_u2 = local_x3_temp(17+32*2,32*2); 
                        		ap_uint<18> x3_u3 = local_x3_temp(17+32*3,32*3); 
                        		ap_uint<18> x3_u4 = local_x3_temp(17+32*4,32*4); 
                        		ap_uint<18> x3_u5 = local_x3_temp(17+32*5,32*5); 
                        		ap_uint<18> x3_u6 = local_x3_temp(17+32*6,32*6); 
                        		ap_uint<18> x3_u7 = local_x3_temp(17+32*7,32*7); 
                        		ap_uint<18> x3_u8 = local_x3_temp(17+32*8,32*8); 
                        		ap_uint<18> x3_u9 = local_x3_temp(17+32*9,32*9); 
                        		ap_uint<18> x3_u10 = local_x3_temp(17+32*10,32*10); 
                        		ap_uint<18> x3_u11 = local_x3_temp(17+32*11,32*11); 
                        		ap_uint<18> x3_u12 = local_x3_temp(17+32*12,32*12); 
                        		ap_uint<18> x3_u13 = local_x3_temp(17+32*13,32*13); 
                        		ap_uint<18> x3_u14 = local_x3_temp(17+32*14,32*14); 
                        		ap_uint<18> x3_u15 = local_x3_temp(17+32*15,32*15); 
					ap_uint<512> local_A4 = fifo_A4.read();
                	        	ap_uint<18> A4_u0 = local_A4(17+32*0,32*0); 
                	        	ap_uint<18> A4_u1 = local_A4(17+32*1,32*1); 
                	        	ap_uint<18> A4_u2 = local_A4(17+32*2,32*2); 
                	        	ap_uint<18> A4_u3 = local_A4(17+32*3,32*3); 
                	        	ap_uint<18> A4_u4 = local_A4(17+32*4,32*4); 
                	        	ap_uint<18> A4_u5 = local_A4(17+32*5,32*5); 
                	        	ap_uint<18> A4_u6 = local_A4(17+32*6,32*6); 
                	        	ap_uint<18> A4_u7 = local_A4(17+32*7,32*7); 
                	        	ap_uint<18> A4_u8 = local_A4(17+32*8,32*8); 
                	        	ap_uint<18> A4_u9 = local_A4(17+32*9,32*9); 
                	        	ap_uint<18> A4_u10 = local_A4(17+32*10,32*10); 
                	        	ap_uint<18> A4_u11 = local_A4(17+32*11,32*11); 
                	        	ap_uint<18> A4_u12 = local_A4(17+32*12,32*12); 
                	        	ap_uint<18> A4_u13 = local_A4(17+32*13,32*13); 
                	        	ap_uint<18> A4_u14 = local_A4(17+32*14,32*14); 
                	        	ap_uint<18> A4_u15 = local_A4(17+32*15,32*15); 
					ap_uint<512> local_x4_temp = local_x4[j];
                        		ap_uint<18> x4_u0 = local_x4_temp(17+32*0,32*0); 
                        		ap_uint<18> x4_u1 = local_x4_temp(17+32*1,32*1); 
                        		ap_uint<18> x4_u2 = local_x4_temp(17+32*2,32*2); 
                        		ap_uint<18> x4_u3 = local_x4_temp(17+32*3,32*3); 
                        		ap_uint<18> x4_u4 = local_x4_temp(17+32*4,32*4); 
                        		ap_uint<18> x4_u5 = local_x4_temp(17+32*5,32*5); 
                        		ap_uint<18> x4_u6 = local_x4_temp(17+32*6,32*6); 
                        		ap_uint<18> x4_u7 = local_x4_temp(17+32*7,32*7); 
                        		ap_uint<18> x4_u8 = local_x4_temp(17+32*8,32*8); 
                        		ap_uint<18> x4_u9 = local_x4_temp(17+32*9,32*9); 
                        		ap_uint<18> x4_u10 = local_x4_temp(17+32*10,32*10); 
                        		ap_uint<18> x4_u11 = local_x4_temp(17+32*11,32*11); 
                        		ap_uint<18> x4_u12 = local_x4_temp(17+32*12,32*12); 
                        		ap_uint<18> x4_u13 = local_x4_temp(17+32*13,32*13); 
                        		ap_uint<18> x4_u14 = local_x4_temp(17+32*14,32*14); 
                        		ap_uint<18> x4_u15 = local_x4_temp(17+32*15,32*15); 
					ap_uint<512> local_A5 = fifo_A5.read();
                	        	ap_uint<18> A5_u0 = local_A5(17+32*0,32*0); 
                	        	ap_uint<18> A5_u1 = local_A5(17+32*1,32*1); 
                	        	ap_uint<18> A5_u2 = local_A5(17+32*2,32*2); 
                	        	ap_uint<18> A5_u3 = local_A5(17+32*3,32*3); 
                	        	ap_uint<18> A5_u4 = local_A5(17+32*4,32*4); 
                	        	ap_uint<18> A5_u5 = local_A5(17+32*5,32*5); 
                	        	ap_uint<18> A5_u6 = local_A5(17+32*6,32*6); 
                	        	ap_uint<18> A5_u7 = local_A5(17+32*7,32*7); 
                	        	ap_uint<18> A5_u8 = local_A5(17+32*8,32*8); 
                	        	ap_uint<18> A5_u9 = local_A5(17+32*9,32*9); 
                	        	ap_uint<18> A5_u10 = local_A5(17+32*10,32*10); 
                	        	ap_uint<18> A5_u11 = local_A5(17+32*11,32*11); 
                	        	ap_uint<18> A5_u12 = local_A5(17+32*12,32*12); 
                	        	ap_uint<18> A5_u13 = local_A5(17+32*13,32*13); 
                	        	ap_uint<18> A5_u14 = local_A5(17+32*14,32*14); 
                	        	ap_uint<18> A5_u15 = local_A5(17+32*15,32*15); 
					ap_uint<512> local_x5_temp = local_x5[j];
                        		ap_uint<18> x5_u0 = local_x5_temp(17+32*0,32*0); 
                        		ap_uint<18> x5_u1 = local_x5_temp(17+32*1,32*1); 
                        		ap_uint<18> x5_u2 = local_x5_temp(17+32*2,32*2); 
                        		ap_uint<18> x5_u3 = local_x5_temp(17+32*3,32*3); 
                        		ap_uint<18> x5_u4 = local_x5_temp(17+32*4,32*4); 
                        		ap_uint<18> x5_u5 = local_x5_temp(17+32*5,32*5); 
                        		ap_uint<18> x5_u6 = local_x5_temp(17+32*6,32*6); 
                        		ap_uint<18> x5_u7 = local_x5_temp(17+32*7,32*7); 
                        		ap_uint<18> x5_u8 = local_x5_temp(17+32*8,32*8); 
                        		ap_uint<18> x5_u9 = local_x5_temp(17+32*9,32*9); 
                        		ap_uint<18> x5_u10 = local_x5_temp(17+32*10,32*10); 
                        		ap_uint<18> x5_u11 = local_x5_temp(17+32*11,32*11); 
                        		ap_uint<18> x5_u12 = local_x5_temp(17+32*12,32*12); 
                        		ap_uint<18> x5_u13 = local_x5_temp(17+32*13,32*13); 
                        		ap_uint<18> x5_u14 = local_x5_temp(17+32*14,32*14); 
                        		ap_uint<18> x5_u15 = local_x5_temp(17+32*15,32*15); 
					ap_uint<512> local_A6 = fifo_A6.read();
                	        	ap_uint<18> A6_u0 = local_A6(17+32*0,32*0); 
                	        	ap_uint<18> A6_u1 = local_A6(17+32*1,32*1); 
                	        	ap_uint<18> A6_u2 = local_A6(17+32*2,32*2); 
                	        	ap_uint<18> A6_u3 = local_A6(17+32*3,32*3); 
                	        	ap_uint<18> A6_u4 = local_A6(17+32*4,32*4); 
                	        	ap_uint<18> A6_u5 = local_A6(17+32*5,32*5); 
                	        	ap_uint<18> A6_u6 = local_A6(17+32*6,32*6); 
                	        	ap_uint<18> A6_u7 = local_A6(17+32*7,32*7); 
                	        	ap_uint<18> A6_u8 = local_A6(17+32*8,32*8); 
                	        	ap_uint<18> A6_u9 = local_A6(17+32*9,32*9); 
                	        	ap_uint<18> A6_u10 = local_A6(17+32*10,32*10); 
                	        	ap_uint<18> A6_u11 = local_A6(17+32*11,32*11); 
                	        	ap_uint<18> A6_u12 = local_A6(17+32*12,32*12); 
                	        	ap_uint<18> A6_u13 = local_A6(17+32*13,32*13); 
                	        	ap_uint<18> A6_u14 = local_A6(17+32*14,32*14); 
                	        	ap_uint<18> A6_u15 = local_A6(17+32*15,32*15); 
					ap_uint<512> local_x6_temp = local_x6[j];
                        		ap_uint<18> x6_u0 = local_x6_temp(17+32*0,32*0); 
                        		ap_uint<18> x6_u1 = local_x6_temp(17+32*1,32*1); 
                        		ap_uint<18> x6_u2 = local_x6_temp(17+32*2,32*2); 
                        		ap_uint<18> x6_u3 = local_x6_temp(17+32*3,32*3); 
                        		ap_uint<18> x6_u4 = local_x6_temp(17+32*4,32*4); 
                        		ap_uint<18> x6_u5 = local_x6_temp(17+32*5,32*5); 
                        		ap_uint<18> x6_u6 = local_x6_temp(17+32*6,32*6); 
                        		ap_uint<18> x6_u7 = local_x6_temp(17+32*7,32*7); 
                        		ap_uint<18> x6_u8 = local_x6_temp(17+32*8,32*8); 
                        		ap_uint<18> x6_u9 = local_x6_temp(17+32*9,32*9); 
                        		ap_uint<18> x6_u10 = local_x6_temp(17+32*10,32*10); 
                        		ap_uint<18> x6_u11 = local_x6_temp(17+32*11,32*11); 
                        		ap_uint<18> x6_u12 = local_x6_temp(17+32*12,32*12); 
                        		ap_uint<18> x6_u13 = local_x6_temp(17+32*13,32*13); 
                        		ap_uint<18> x6_u14 = local_x6_temp(17+32*14,32*14); 
                        		ap_uint<18> x6_u15 = local_x6_temp(17+32*15,32*15); 
					ap_uint<512> local_A7 = fifo_A7.read();
                	        	ap_uint<18> A7_u0 = local_A7(17+32*0,32*0); 
                	        	ap_uint<18> A7_u1 = local_A7(17+32*1,32*1); 
                	        	ap_uint<18> A7_u2 = local_A7(17+32*2,32*2); 
                	        	ap_uint<18> A7_u3 = local_A7(17+32*3,32*3); 
                	        	ap_uint<18> A7_u4 = local_A7(17+32*4,32*4); 
                	        	ap_uint<18> A7_u5 = local_A7(17+32*5,32*5); 
                	        	ap_uint<18> A7_u6 = local_A7(17+32*6,32*6); 
                	        	ap_uint<18> A7_u7 = local_A7(17+32*7,32*7); 
                	        	ap_uint<18> A7_u8 = local_A7(17+32*8,32*8); 
                	        	ap_uint<18> A7_u9 = local_A7(17+32*9,32*9); 
                	        	ap_uint<18> A7_u10 = local_A7(17+32*10,32*10); 
                	        	ap_uint<18> A7_u11 = local_A7(17+32*11,32*11); 
                	        	ap_uint<18> A7_u12 = local_A7(17+32*12,32*12); 
                	        	ap_uint<18> A7_u13 = local_A7(17+32*13,32*13); 
                	        	ap_uint<18> A7_u14 = local_A7(17+32*14,32*14); 
                	        	ap_uint<18> A7_u15 = local_A7(17+32*15,32*15); 
					ap_uint<512> local_x7_temp = local_x7[j];
                        		ap_uint<18> x7_u0 = local_x7_temp(17+32*0,32*0); 
                        		ap_uint<18> x7_u1 = local_x7_temp(17+32*1,32*1); 
                        		ap_uint<18> x7_u2 = local_x7_temp(17+32*2,32*2); 
                        		ap_uint<18> x7_u3 = local_x7_temp(17+32*3,32*3); 
                        		ap_uint<18> x7_u4 = local_x7_temp(17+32*4,32*4); 
                        		ap_uint<18> x7_u5 = local_x7_temp(17+32*5,32*5); 
                        		ap_uint<18> x7_u6 = local_x7_temp(17+32*6,32*6); 
                        		ap_uint<18> x7_u7 = local_x7_temp(17+32*7,32*7); 
                        		ap_uint<18> x7_u8 = local_x7_temp(17+32*8,32*8); 
                        		ap_uint<18> x7_u9 = local_x7_temp(17+32*9,32*9); 
                        		ap_uint<18> x7_u10 = local_x7_temp(17+32*10,32*10); 
                        		ap_uint<18> x7_u11 = local_x7_temp(17+32*11,32*11); 
                        		ap_uint<18> x7_u12 = local_x7_temp(17+32*12,32*12); 
                        		ap_uint<18> x7_u13 = local_x7_temp(17+32*13,32*13); 
                        		ap_uint<18> x7_u14 = local_x7_temp(17+32*14,32*14); 
                        		ap_uint<18> x7_u15 = local_x7_temp(17+32*15,32*15); 
					ap_uint<512> local_A8 = fifo_A8.read();
                	        	ap_uint<18> A8_u0 = local_A8(17+32*0,32*0); 
                	        	ap_uint<18> A8_u1 = local_A8(17+32*1,32*1); 
                	        	ap_uint<18> A8_u2 = local_A8(17+32*2,32*2); 
                	        	ap_uint<18> A8_u3 = local_A8(17+32*3,32*3); 
                	        	ap_uint<18> A8_u4 = local_A8(17+32*4,32*4); 
                	        	ap_uint<18> A8_u5 = local_A8(17+32*5,32*5); 
                	        	ap_uint<18> A8_u6 = local_A8(17+32*6,32*6); 
                	        	ap_uint<18> A8_u7 = local_A8(17+32*7,32*7); 
                	        	ap_uint<18> A8_u8 = local_A8(17+32*8,32*8); 
                	        	ap_uint<18> A8_u9 = local_A8(17+32*9,32*9); 
                	        	ap_uint<18> A8_u10 = local_A8(17+32*10,32*10); 
                	        	ap_uint<18> A8_u11 = local_A8(17+32*11,32*11); 
                	        	ap_uint<18> A8_u12 = local_A8(17+32*12,32*12); 
                	        	ap_uint<18> A8_u13 = local_A8(17+32*13,32*13); 
                	        	ap_uint<18> A8_u14 = local_A8(17+32*14,32*14); 
                	        	ap_uint<18> A8_u15 = local_A8(17+32*15,32*15); 
					ap_uint<512> local_x8_temp = local_x8[j];
                        		ap_uint<18> x8_u0 = local_x8_temp(17+32*0,32*0); 
                        		ap_uint<18> x8_u1 = local_x8_temp(17+32*1,32*1); 
                        		ap_uint<18> x8_u2 = local_x8_temp(17+32*2,32*2); 
                        		ap_uint<18> x8_u3 = local_x8_temp(17+32*3,32*3); 
                        		ap_uint<18> x8_u4 = local_x8_temp(17+32*4,32*4); 
                        		ap_uint<18> x8_u5 = local_x8_temp(17+32*5,32*5); 
                        		ap_uint<18> x8_u6 = local_x8_temp(17+32*6,32*6); 
                        		ap_uint<18> x8_u7 = local_x8_temp(17+32*7,32*7); 
                        		ap_uint<18> x8_u8 = local_x8_temp(17+32*8,32*8); 
                        		ap_uint<18> x8_u9 = local_x8_temp(17+32*9,32*9); 
                        		ap_uint<18> x8_u10 = local_x8_temp(17+32*10,32*10); 
                        		ap_uint<18> x8_u11 = local_x8_temp(17+32*11,32*11); 
                        		ap_uint<18> x8_u12 = local_x8_temp(17+32*12,32*12); 
                        		ap_uint<18> x8_u13 = local_x8_temp(17+32*13,32*13); 
                        		ap_uint<18> x8_u14 = local_x8_temp(17+32*14,32*14); 
                        		ap_uint<18> x8_u15 = local_x8_temp(17+32*15,32*15); 
					ap_uint<512> local_A9 = fifo_A9.read();
                	        	ap_uint<18> A9_u0 = local_A9(17+32*0,32*0); 
                	        	ap_uint<18> A9_u1 = local_A9(17+32*1,32*1); 
                	        	ap_uint<18> A9_u2 = local_A9(17+32*2,32*2); 
                	        	ap_uint<18> A9_u3 = local_A9(17+32*3,32*3); 
                	        	ap_uint<18> A9_u4 = local_A9(17+32*4,32*4); 
                	        	ap_uint<18> A9_u5 = local_A9(17+32*5,32*5); 
                	        	ap_uint<18> A9_u6 = local_A9(17+32*6,32*6); 
                	        	ap_uint<18> A9_u7 = local_A9(17+32*7,32*7); 
                	        	ap_uint<18> A9_u8 = local_A9(17+32*8,32*8); 
                	        	ap_uint<18> A9_u9 = local_A9(17+32*9,32*9); 
                	        	ap_uint<18> A9_u10 = local_A9(17+32*10,32*10); 
                	        	ap_uint<18> A9_u11 = local_A9(17+32*11,32*11); 
                	        	ap_uint<18> A9_u12 = local_A9(17+32*12,32*12); 
                	        	ap_uint<18> A9_u13 = local_A9(17+32*13,32*13); 
                	        	ap_uint<18> A9_u14 = local_A9(17+32*14,32*14); 
                	        	ap_uint<18> A9_u15 = local_A9(17+32*15,32*15); 
					ap_uint<512> local_x9_temp = local_x9[j];
                        		ap_uint<18> x9_u0 = local_x9_temp(17+32*0,32*0); 
                        		ap_uint<18> x9_u1 = local_x9_temp(17+32*1,32*1); 
                        		ap_uint<18> x9_u2 = local_x9_temp(17+32*2,32*2); 
                        		ap_uint<18> x9_u3 = local_x9_temp(17+32*3,32*3); 
                        		ap_uint<18> x9_u4 = local_x9_temp(17+32*4,32*4); 
                        		ap_uint<18> x9_u5 = local_x9_temp(17+32*5,32*5); 
                        		ap_uint<18> x9_u6 = local_x9_temp(17+32*6,32*6); 
                        		ap_uint<18> x9_u7 = local_x9_temp(17+32*7,32*7); 
                        		ap_uint<18> x9_u8 = local_x9_temp(17+32*8,32*8); 
                        		ap_uint<18> x9_u9 = local_x9_temp(17+32*9,32*9); 
                        		ap_uint<18> x9_u10 = local_x9_temp(17+32*10,32*10); 
                        		ap_uint<18> x9_u11 = local_x9_temp(17+32*11,32*11); 
                        		ap_uint<18> x9_u12 = local_x9_temp(17+32*12,32*12); 
                        		ap_uint<18> x9_u13 = local_x9_temp(17+32*13,32*13); 
                        		ap_uint<18> x9_u14 = local_x9_temp(17+32*14,32*14); 
                        		ap_uint<18> x9_u15 = local_x9_temp(17+32*15,32*15); 
					ap_uint<512> local_A10 = fifo_A10.read();
                	        	ap_uint<18> A10_u0 = local_A10(17+32*0,32*0); 
                	        	ap_uint<18> A10_u1 = local_A10(17+32*1,32*1); 
                	        	ap_uint<18> A10_u2 = local_A10(17+32*2,32*2); 
                	        	ap_uint<18> A10_u3 = local_A10(17+32*3,32*3); 
                	        	ap_uint<18> A10_u4 = local_A10(17+32*4,32*4); 
                	        	ap_uint<18> A10_u5 = local_A10(17+32*5,32*5); 
                	        	ap_uint<18> A10_u6 = local_A10(17+32*6,32*6); 
                	        	ap_uint<18> A10_u7 = local_A10(17+32*7,32*7); 
                	        	ap_uint<18> A10_u8 = local_A10(17+32*8,32*8); 
                	        	ap_uint<18> A10_u9 = local_A10(17+32*9,32*9); 
                	        	ap_uint<18> A10_u10 = local_A10(17+32*10,32*10); 
                	        	ap_uint<18> A10_u11 = local_A10(17+32*11,32*11); 
                	        	ap_uint<18> A10_u12 = local_A10(17+32*12,32*12); 
                	        	ap_uint<18> A10_u13 = local_A10(17+32*13,32*13); 
                	        	ap_uint<18> A10_u14 = local_A10(17+32*14,32*14); 
                	        	ap_uint<18> A10_u15 = local_A10(17+32*15,32*15); 
					ap_uint<512> local_x10_temp = local_x10[j];
                        		ap_uint<18> x10_u0 = local_x10_temp(17+32*0,32*0); 
                        		ap_uint<18> x10_u1 = local_x10_temp(17+32*1,32*1); 
                        		ap_uint<18> x10_u2 = local_x10_temp(17+32*2,32*2); 
                        		ap_uint<18> x10_u3 = local_x10_temp(17+32*3,32*3); 
                        		ap_uint<18> x10_u4 = local_x10_temp(17+32*4,32*4); 
                        		ap_uint<18> x10_u5 = local_x10_temp(17+32*5,32*5); 
                        		ap_uint<18> x10_u6 = local_x10_temp(17+32*6,32*6); 
                        		ap_uint<18> x10_u7 = local_x10_temp(17+32*7,32*7); 
                        		ap_uint<18> x10_u8 = local_x10_temp(17+32*8,32*8); 
                        		ap_uint<18> x10_u9 = local_x10_temp(17+32*9,32*9); 
                        		ap_uint<18> x10_u10 = local_x10_temp(17+32*10,32*10); 
                        		ap_uint<18> x10_u11 = local_x10_temp(17+32*11,32*11); 
                        		ap_uint<18> x10_u12 = local_x10_temp(17+32*12,32*12); 
                        		ap_uint<18> x10_u13 = local_x10_temp(17+32*13,32*13); 
                        		ap_uint<18> x10_u14 = local_x10_temp(17+32*14,32*14); 
                        		ap_uint<18> x10_u15 = local_x10_temp(17+32*15,32*15); 
					ap_uint<512> local_A11 = fifo_A11.read();
                	        	ap_uint<18> A11_u0 = local_A11(17+32*0,32*0); 
                	        	ap_uint<18> A11_u1 = local_A11(17+32*1,32*1); 
                	        	ap_uint<18> A11_u2 = local_A11(17+32*2,32*2); 
                	        	ap_uint<18> A11_u3 = local_A11(17+32*3,32*3); 
                	        	ap_uint<18> A11_u4 = local_A11(17+32*4,32*4); 
                	        	ap_uint<18> A11_u5 = local_A11(17+32*5,32*5); 
                	        	ap_uint<18> A11_u6 = local_A11(17+32*6,32*6); 
                	        	ap_uint<18> A11_u7 = local_A11(17+32*7,32*7); 
                	        	ap_uint<18> A11_u8 = local_A11(17+32*8,32*8); 
                	        	ap_uint<18> A11_u9 = local_A11(17+32*9,32*9); 
                	        	ap_uint<18> A11_u10 = local_A11(17+32*10,32*10); 
                	        	ap_uint<18> A11_u11 = local_A11(17+32*11,32*11); 
                	        	ap_uint<18> A11_u12 = local_A11(17+32*12,32*12); 
                	        	ap_uint<18> A11_u13 = local_A11(17+32*13,32*13); 
                	        	ap_uint<18> A11_u14 = local_A11(17+32*14,32*14); 
                	        	ap_uint<18> A11_u15 = local_A11(17+32*15,32*15); 
					ap_uint<512> local_x11_temp = local_x11[j];
                        		ap_uint<18> x11_u0 = local_x11_temp(17+32*0,32*0); 
                        		ap_uint<18> x11_u1 = local_x11_temp(17+32*1,32*1); 
                        		ap_uint<18> x11_u2 = local_x11_temp(17+32*2,32*2); 
                        		ap_uint<18> x11_u3 = local_x11_temp(17+32*3,32*3); 
                        		ap_uint<18> x11_u4 = local_x11_temp(17+32*4,32*4); 
                        		ap_uint<18> x11_u5 = local_x11_temp(17+32*5,32*5); 
                        		ap_uint<18> x11_u6 = local_x11_temp(17+32*6,32*6); 
                        		ap_uint<18> x11_u7 = local_x11_temp(17+32*7,32*7); 
                        		ap_uint<18> x11_u8 = local_x11_temp(17+32*8,32*8); 
                        		ap_uint<18> x11_u9 = local_x11_temp(17+32*9,32*9); 
                        		ap_uint<18> x11_u10 = local_x11_temp(17+32*10,32*10); 
                        		ap_uint<18> x11_u11 = local_x11_temp(17+32*11,32*11); 
                        		ap_uint<18> x11_u12 = local_x11_temp(17+32*12,32*12); 
                        		ap_uint<18> x11_u13 = local_x11_temp(17+32*13,32*13); 
                        		ap_uint<18> x11_u14 = local_x11_temp(17+32*14,32*14); 
                        		ap_uint<18> x11_u15 = local_x11_temp(17+32*15,32*15); 
					ap_uint<512> local_A12 = fifo_A12.read();
                	        	ap_uint<18> A12_u0 = local_A12(17+32*0,32*0); 
                	        	ap_uint<18> A12_u1 = local_A12(17+32*1,32*1); 
                	        	ap_uint<18> A12_u2 = local_A12(17+32*2,32*2); 
                	        	ap_uint<18> A12_u3 = local_A12(17+32*3,32*3); 
                	        	ap_uint<18> A12_u4 = local_A12(17+32*4,32*4); 
                	        	ap_uint<18> A12_u5 = local_A12(17+32*5,32*5); 
                	        	ap_uint<18> A12_u6 = local_A12(17+32*6,32*6); 
                	        	ap_uint<18> A12_u7 = local_A12(17+32*7,32*7); 
                	        	ap_uint<18> A12_u8 = local_A12(17+32*8,32*8); 
                	        	ap_uint<18> A12_u9 = local_A12(17+32*9,32*9); 
                	        	ap_uint<18> A12_u10 = local_A12(17+32*10,32*10); 
                	        	ap_uint<18> A12_u11 = local_A12(17+32*11,32*11); 
                	        	ap_uint<18> A12_u12 = local_A12(17+32*12,32*12); 
                	        	ap_uint<18> A12_u13 = local_A12(17+32*13,32*13); 
                	        	ap_uint<18> A12_u14 = local_A12(17+32*14,32*14); 
                	        	ap_uint<18> A12_u15 = local_A12(17+32*15,32*15); 
					ap_uint<512> local_x12_temp = local_x12[j];
                        		ap_uint<18> x12_u0 = local_x12_temp(17+32*0,32*0); 
                        		ap_uint<18> x12_u1 = local_x12_temp(17+32*1,32*1); 
                        		ap_uint<18> x12_u2 = local_x12_temp(17+32*2,32*2); 
                        		ap_uint<18> x12_u3 = local_x12_temp(17+32*3,32*3); 
                        		ap_uint<18> x12_u4 = local_x12_temp(17+32*4,32*4); 
                        		ap_uint<18> x12_u5 = local_x12_temp(17+32*5,32*5); 
                        		ap_uint<18> x12_u6 = local_x12_temp(17+32*6,32*6); 
                        		ap_uint<18> x12_u7 = local_x12_temp(17+32*7,32*7); 
                        		ap_uint<18> x12_u8 = local_x12_temp(17+32*8,32*8); 
                        		ap_uint<18> x12_u9 = local_x12_temp(17+32*9,32*9); 
                        		ap_uint<18> x12_u10 = local_x12_temp(17+32*10,32*10); 
                        		ap_uint<18> x12_u11 = local_x12_temp(17+32*11,32*11); 
                        		ap_uint<18> x12_u12 = local_x12_temp(17+32*12,32*12); 
                        		ap_uint<18> x12_u13 = local_x12_temp(17+32*13,32*13); 
                        		ap_uint<18> x12_u14 = local_x12_temp(17+32*14,32*14); 
                        		ap_uint<18> x12_u15 = local_x12_temp(17+32*15,32*15); 
					ap_uint<512> local_A13 = fifo_A13.read();
                	        	ap_uint<18> A13_u0 = local_A13(17+32*0,32*0); 
                	        	ap_uint<18> A13_u1 = local_A13(17+32*1,32*1); 
                	        	ap_uint<18> A13_u2 = local_A13(17+32*2,32*2); 
                	        	ap_uint<18> A13_u3 = local_A13(17+32*3,32*3); 
                	        	ap_uint<18> A13_u4 = local_A13(17+32*4,32*4); 
                	        	ap_uint<18> A13_u5 = local_A13(17+32*5,32*5); 
                	        	ap_uint<18> A13_u6 = local_A13(17+32*6,32*6); 
                	        	ap_uint<18> A13_u7 = local_A13(17+32*7,32*7); 
                	        	ap_uint<18> A13_u8 = local_A13(17+32*8,32*8); 
                	        	ap_uint<18> A13_u9 = local_A13(17+32*9,32*9); 
                	        	ap_uint<18> A13_u10 = local_A13(17+32*10,32*10); 
                	        	ap_uint<18> A13_u11 = local_A13(17+32*11,32*11); 
                	        	ap_uint<18> A13_u12 = local_A13(17+32*12,32*12); 
                	        	ap_uint<18> A13_u13 = local_A13(17+32*13,32*13); 
                	        	ap_uint<18> A13_u14 = local_A13(17+32*14,32*14); 
                	        	ap_uint<18> A13_u15 = local_A13(17+32*15,32*15); 
					ap_uint<512> local_x13_temp = local_x13[j];
                        		ap_uint<18> x13_u0 = local_x13_temp(17+32*0,32*0); 
                        		ap_uint<18> x13_u1 = local_x13_temp(17+32*1,32*1); 
                        		ap_uint<18> x13_u2 = local_x13_temp(17+32*2,32*2); 
                        		ap_uint<18> x13_u3 = local_x13_temp(17+32*3,32*3); 
                        		ap_uint<18> x13_u4 = local_x13_temp(17+32*4,32*4); 
                        		ap_uint<18> x13_u5 = local_x13_temp(17+32*5,32*5); 
                        		ap_uint<18> x13_u6 = local_x13_temp(17+32*6,32*6); 
                        		ap_uint<18> x13_u7 = local_x13_temp(17+32*7,32*7); 
                        		ap_uint<18> x13_u8 = local_x13_temp(17+32*8,32*8); 
                        		ap_uint<18> x13_u9 = local_x13_temp(17+32*9,32*9); 
                        		ap_uint<18> x13_u10 = local_x13_temp(17+32*10,32*10); 
                        		ap_uint<18> x13_u11 = local_x13_temp(17+32*11,32*11); 
                        		ap_uint<18> x13_u12 = local_x13_temp(17+32*12,32*12); 
                        		ap_uint<18> x13_u13 = local_x13_temp(17+32*13,32*13); 
                        		ap_uint<18> x13_u14 = local_x13_temp(17+32*14,32*14); 
                        		ap_uint<18> x13_u15 = local_x13_temp(17+32*15,32*15); 
					ap_uint<512> local_A14 = fifo_A14.read();
                	        	ap_uint<18> A14_u0 = local_A14(17+32*0,32*0); 
                	        	ap_uint<18> A14_u1 = local_A14(17+32*1,32*1); 
                	        	ap_uint<18> A14_u2 = local_A14(17+32*2,32*2); 
                	        	ap_uint<18> A14_u3 = local_A14(17+32*3,32*3); 
                	        	ap_uint<18> A14_u4 = local_A14(17+32*4,32*4); 
                	        	ap_uint<18> A14_u5 = local_A14(17+32*5,32*5); 
                	        	ap_uint<18> A14_u6 = local_A14(17+32*6,32*6); 
                	        	ap_uint<18> A14_u7 = local_A14(17+32*7,32*7); 
                	        	ap_uint<18> A14_u8 = local_A14(17+32*8,32*8); 
                	        	ap_uint<18> A14_u9 = local_A14(17+32*9,32*9); 
                	        	ap_uint<18> A14_u10 = local_A14(17+32*10,32*10); 
                	        	ap_uint<18> A14_u11 = local_A14(17+32*11,32*11); 
                	        	ap_uint<18> A14_u12 = local_A14(17+32*12,32*12); 
                	        	ap_uint<18> A14_u13 = local_A14(17+32*13,32*13); 
                	        	ap_uint<18> A14_u14 = local_A14(17+32*14,32*14); 
                	        	ap_uint<18> A14_u15 = local_A14(17+32*15,32*15); 
					ap_uint<512> local_x14_temp = local_x14[j];
                        		ap_uint<18> x14_u0 = local_x14_temp(17+32*0,32*0); 
                        		ap_uint<18> x14_u1 = local_x14_temp(17+32*1,32*1); 
                        		ap_uint<18> x14_u2 = local_x14_temp(17+32*2,32*2); 
                        		ap_uint<18> x14_u3 = local_x14_temp(17+32*3,32*3); 
                        		ap_uint<18> x14_u4 = local_x14_temp(17+32*4,32*4); 
                        		ap_uint<18> x14_u5 = local_x14_temp(17+32*5,32*5); 
                        		ap_uint<18> x14_u6 = local_x14_temp(17+32*6,32*6); 
                        		ap_uint<18> x14_u7 = local_x14_temp(17+32*7,32*7); 
                        		ap_uint<18> x14_u8 = local_x14_temp(17+32*8,32*8); 
                        		ap_uint<18> x14_u9 = local_x14_temp(17+32*9,32*9); 
                        		ap_uint<18> x14_u10 = local_x14_temp(17+32*10,32*10); 
                        		ap_uint<18> x14_u11 = local_x14_temp(17+32*11,32*11); 
                        		ap_uint<18> x14_u12 = local_x14_temp(17+32*12,32*12); 
                        		ap_uint<18> x14_u13 = local_x14_temp(17+32*13,32*13); 
                        		ap_uint<18> x14_u14 = local_x14_temp(17+32*14,32*14); 
                        		ap_uint<18> x14_u15 = local_x14_temp(17+32*15,32*15); 
					ap_uint<512> local_A15 = fifo_A15.read();
                	        	ap_uint<18> A15_u0 = local_A15(17+32*0,32*0); 
                	        	ap_uint<18> A15_u1 = local_A15(17+32*1,32*1); 
                	        	ap_uint<18> A15_u2 = local_A15(17+32*2,32*2); 
                	        	ap_uint<18> A15_u3 = local_A15(17+32*3,32*3); 
                	        	ap_uint<18> A15_u4 = local_A15(17+32*4,32*4); 
                	        	ap_uint<18> A15_u5 = local_A15(17+32*5,32*5); 
                	        	ap_uint<18> A15_u6 = local_A15(17+32*6,32*6); 
                	        	ap_uint<18> A15_u7 = local_A15(17+32*7,32*7); 
                	        	ap_uint<18> A15_u8 = local_A15(17+32*8,32*8); 
                	        	ap_uint<18> A15_u9 = local_A15(17+32*9,32*9); 
                	        	ap_uint<18> A15_u10 = local_A15(17+32*10,32*10); 
                	        	ap_uint<18> A15_u11 = local_A15(17+32*11,32*11); 
                	        	ap_uint<18> A15_u12 = local_A15(17+32*12,32*12); 
                	        	ap_uint<18> A15_u13 = local_A15(17+32*13,32*13); 
                	        	ap_uint<18> A15_u14 = local_A15(17+32*14,32*14); 
                	        	ap_uint<18> A15_u15 = local_A15(17+32*15,32*15); 
					ap_uint<512> local_x15_temp = local_x15[j];
                        		ap_uint<18> x15_u0 = local_x15_temp(17+32*0,32*0); 
                        		ap_uint<18> x15_u1 = local_x15_temp(17+32*1,32*1); 
                        		ap_uint<18> x15_u2 = local_x15_temp(17+32*2,32*2); 
                        		ap_uint<18> x15_u3 = local_x15_temp(17+32*3,32*3); 
                        		ap_uint<18> x15_u4 = local_x15_temp(17+32*4,32*4); 
                        		ap_uint<18> x15_u5 = local_x15_temp(17+32*5,32*5); 
                        		ap_uint<18> x15_u6 = local_x15_temp(17+32*6,32*6); 
                        		ap_uint<18> x15_u7 = local_x15_temp(17+32*7,32*7); 
                        		ap_uint<18> x15_u8 = local_x15_temp(17+32*8,32*8); 
                        		ap_uint<18> x15_u9 = local_x15_temp(17+32*9,32*9); 
                        		ap_uint<18> x15_u10 = local_x15_temp(17+32*10,32*10); 
                        		ap_uint<18> x15_u11 = local_x15_temp(17+32*11,32*11); 
                        		ap_uint<18> x15_u12 = local_x15_temp(17+32*12,32*12); 
                        		ap_uint<18> x15_u13 = local_x15_temp(17+32*13,32*13); 
                        		ap_uint<18> x15_u14 = local_x15_temp(17+32*14,32*14); 
                        		ap_uint<18> x15_u15 = local_x15_temp(17+32*15,32*15); 
					ap_uint<512> local_A16 = fifo_A16.read();
                	        	ap_uint<18> A16_u0 = local_A16(17+32*0,32*0); 
                	        	ap_uint<18> A16_u1 = local_A16(17+32*1,32*1); 
                	        	ap_uint<18> A16_u2 = local_A16(17+32*2,32*2); 
                	        	ap_uint<18> A16_u3 = local_A16(17+32*3,32*3); 
                	        	ap_uint<18> A16_u4 = local_A16(17+32*4,32*4); 
                	        	ap_uint<18> A16_u5 = local_A16(17+32*5,32*5); 
                	        	ap_uint<18> A16_u6 = local_A16(17+32*6,32*6); 
                	        	ap_uint<18> A16_u7 = local_A16(17+32*7,32*7); 
                	        	ap_uint<18> A16_u8 = local_A16(17+32*8,32*8); 
                	        	ap_uint<18> A16_u9 = local_A16(17+32*9,32*9); 
                	        	ap_uint<18> A16_u10 = local_A16(17+32*10,32*10); 
                	        	ap_uint<18> A16_u11 = local_A16(17+32*11,32*11); 
                	        	ap_uint<18> A16_u12 = local_A16(17+32*12,32*12); 
                	        	ap_uint<18> A16_u13 = local_A16(17+32*13,32*13); 
                	        	ap_uint<18> A16_u14 = local_A16(17+32*14,32*14); 
                	        	ap_uint<18> A16_u15 = local_A16(17+32*15,32*15); 
					ap_uint<512> local_x16_temp = local_x16[j];
                        		ap_uint<18> x16_u0 = local_x16_temp(17+32*0,32*0); 
                        		ap_uint<18> x16_u1 = local_x16_temp(17+32*1,32*1); 
                        		ap_uint<18> x16_u2 = local_x16_temp(17+32*2,32*2); 
                        		ap_uint<18> x16_u3 = local_x16_temp(17+32*3,32*3); 
                        		ap_uint<18> x16_u4 = local_x16_temp(17+32*4,32*4); 
                        		ap_uint<18> x16_u5 = local_x16_temp(17+32*5,32*5); 
                        		ap_uint<18> x16_u6 = local_x16_temp(17+32*6,32*6); 
                        		ap_uint<18> x16_u7 = local_x16_temp(17+32*7,32*7); 
                        		ap_uint<18> x16_u8 = local_x16_temp(17+32*8,32*8); 
                        		ap_uint<18> x16_u9 = local_x16_temp(17+32*9,32*9); 
                        		ap_uint<18> x16_u10 = local_x16_temp(17+32*10,32*10); 
                        		ap_uint<18> x16_u11 = local_x16_temp(17+32*11,32*11); 
                        		ap_uint<18> x16_u12 = local_x16_temp(17+32*12,32*12); 
                        		ap_uint<18> x16_u13 = local_x16_temp(17+32*13,32*13); 
                        		ap_uint<18> x16_u14 = local_x16_temp(17+32*14,32*14); 
                        		ap_uint<18> x16_u15 = local_x16_temp(17+32*15,32*15); 
					ap_uint<512> local_A17 = fifo_A17.read();
                	        	ap_uint<18> A17_u0 = local_A17(17+32*0,32*0); 
                	        	ap_uint<18> A17_u1 = local_A17(17+32*1,32*1); 
                	        	ap_uint<18> A17_u2 = local_A17(17+32*2,32*2); 
                	        	ap_uint<18> A17_u3 = local_A17(17+32*3,32*3); 
                	        	ap_uint<18> A17_u4 = local_A17(17+32*4,32*4); 
                	        	ap_uint<18> A17_u5 = local_A17(17+32*5,32*5); 
                	        	ap_uint<18> A17_u6 = local_A17(17+32*6,32*6); 
                	        	ap_uint<18> A17_u7 = local_A17(17+32*7,32*7); 
                	        	ap_uint<18> A17_u8 = local_A17(17+32*8,32*8); 
                	        	ap_uint<18> A17_u9 = local_A17(17+32*9,32*9); 
                	        	ap_uint<18> A17_u10 = local_A17(17+32*10,32*10); 
                	        	ap_uint<18> A17_u11 = local_A17(17+32*11,32*11); 
                	        	ap_uint<18> A17_u12 = local_A17(17+32*12,32*12); 
                	        	ap_uint<18> A17_u13 = local_A17(17+32*13,32*13); 
                	        	ap_uint<18> A17_u14 = local_A17(17+32*14,32*14); 
                	        	ap_uint<18> A17_u15 = local_A17(17+32*15,32*15); 
					ap_uint<512> local_x17_temp = local_x17[j];
                        		ap_uint<18> x17_u0 = local_x17_temp(17+32*0,32*0); 
                        		ap_uint<18> x17_u1 = local_x17_temp(17+32*1,32*1); 
                        		ap_uint<18> x17_u2 = local_x17_temp(17+32*2,32*2); 
                        		ap_uint<18> x17_u3 = local_x17_temp(17+32*3,32*3); 
                        		ap_uint<18> x17_u4 = local_x17_temp(17+32*4,32*4); 
                        		ap_uint<18> x17_u5 = local_x17_temp(17+32*5,32*5); 
                        		ap_uint<18> x17_u6 = local_x17_temp(17+32*6,32*6); 
                        		ap_uint<18> x17_u7 = local_x17_temp(17+32*7,32*7); 
                        		ap_uint<18> x17_u8 = local_x17_temp(17+32*8,32*8); 
                        		ap_uint<18> x17_u9 = local_x17_temp(17+32*9,32*9); 
                        		ap_uint<18> x17_u10 = local_x17_temp(17+32*10,32*10); 
                        		ap_uint<18> x17_u11 = local_x17_temp(17+32*11,32*11); 
                        		ap_uint<18> x17_u12 = local_x17_temp(17+32*12,32*12); 
                        		ap_uint<18> x17_u13 = local_x17_temp(17+32*13,32*13); 
                        		ap_uint<18> x17_u14 = local_x17_temp(17+32*14,32*14); 
                        		ap_uint<18> x17_u15 = local_x17_temp(17+32*15,32*15); 
					ap_uint<512> local_A18 = fifo_A18.read();
                	        	ap_uint<18> A18_u0 = local_A18(17+32*0,32*0); 
                	        	ap_uint<18> A18_u1 = local_A18(17+32*1,32*1); 
                	        	ap_uint<18> A18_u2 = local_A18(17+32*2,32*2); 
                	        	ap_uint<18> A18_u3 = local_A18(17+32*3,32*3); 
                	        	ap_uint<18> A18_u4 = local_A18(17+32*4,32*4); 
                	        	ap_uint<18> A18_u5 = local_A18(17+32*5,32*5); 
                	        	ap_uint<18> A18_u6 = local_A18(17+32*6,32*6); 
                	        	ap_uint<18> A18_u7 = local_A18(17+32*7,32*7); 
                	        	ap_uint<18> A18_u8 = local_A18(17+32*8,32*8); 
                	        	ap_uint<18> A18_u9 = local_A18(17+32*9,32*9); 
                	        	ap_uint<18> A18_u10 = local_A18(17+32*10,32*10); 
                	        	ap_uint<18> A18_u11 = local_A18(17+32*11,32*11); 
                	        	ap_uint<18> A18_u12 = local_A18(17+32*12,32*12); 
                	        	ap_uint<18> A18_u13 = local_A18(17+32*13,32*13); 
                	        	ap_uint<18> A18_u14 = local_A18(17+32*14,32*14); 
                	        	ap_uint<18> A18_u15 = local_A18(17+32*15,32*15); 
					ap_uint<512> local_x18_temp = local_x18[j];
                        		ap_uint<18> x18_u0 = local_x18_temp(17+32*0,32*0); 
                        		ap_uint<18> x18_u1 = local_x18_temp(17+32*1,32*1); 
                        		ap_uint<18> x18_u2 = local_x18_temp(17+32*2,32*2); 
                        		ap_uint<18> x18_u3 = local_x18_temp(17+32*3,32*3); 
                        		ap_uint<18> x18_u4 = local_x18_temp(17+32*4,32*4); 
                        		ap_uint<18> x18_u5 = local_x18_temp(17+32*5,32*5); 
                        		ap_uint<18> x18_u6 = local_x18_temp(17+32*6,32*6); 
                        		ap_uint<18> x18_u7 = local_x18_temp(17+32*7,32*7); 
                        		ap_uint<18> x18_u8 = local_x18_temp(17+32*8,32*8); 
                        		ap_uint<18> x18_u9 = local_x18_temp(17+32*9,32*9); 
                        		ap_uint<18> x18_u10 = local_x18_temp(17+32*10,32*10); 
                        		ap_uint<18> x18_u11 = local_x18_temp(17+32*11,32*11); 
                        		ap_uint<18> x18_u12 = local_x18_temp(17+32*12,32*12); 
                        		ap_uint<18> x18_u13 = local_x18_temp(17+32*13,32*13); 
                        		ap_uint<18> x18_u14 = local_x18_temp(17+32*14,32*14); 
                        		ap_uint<18> x18_u15 = local_x18_temp(17+32*15,32*15); 
					ap_uint<512> local_A19 = fifo_A19.read();
                	        	ap_uint<18> A19_u0 = local_A19(17+32*0,32*0); 
                	        	ap_uint<18> A19_u1 = local_A19(17+32*1,32*1); 
                	        	ap_uint<18> A19_u2 = local_A19(17+32*2,32*2); 
                	        	ap_uint<18> A19_u3 = local_A19(17+32*3,32*3); 
                	        	ap_uint<18> A19_u4 = local_A19(17+32*4,32*4); 
                	        	ap_uint<18> A19_u5 = local_A19(17+32*5,32*5); 
                	        	ap_uint<18> A19_u6 = local_A19(17+32*6,32*6); 
                	        	ap_uint<18> A19_u7 = local_A19(17+32*7,32*7); 
                	        	ap_uint<18> A19_u8 = local_A19(17+32*8,32*8); 
                	        	ap_uint<18> A19_u9 = local_A19(17+32*9,32*9); 
                	        	ap_uint<18> A19_u10 = local_A19(17+32*10,32*10); 
                	        	ap_uint<18> A19_u11 = local_A19(17+32*11,32*11); 
                	        	ap_uint<18> A19_u12 = local_A19(17+32*12,32*12); 
                	        	ap_uint<18> A19_u13 = local_A19(17+32*13,32*13); 
                	        	ap_uint<18> A19_u14 = local_A19(17+32*14,32*14); 
                	        	ap_uint<18> A19_u15 = local_A19(17+32*15,32*15); 
					ap_uint<512> local_x19_temp = local_x19[j];
                        		ap_uint<18> x19_u0 = local_x19_temp(17+32*0,32*0); 
                        		ap_uint<18> x19_u1 = local_x19_temp(17+32*1,32*1); 
                        		ap_uint<18> x19_u2 = local_x19_temp(17+32*2,32*2); 
                        		ap_uint<18> x19_u3 = local_x19_temp(17+32*3,32*3); 
                        		ap_uint<18> x19_u4 = local_x19_temp(17+32*4,32*4); 
                        		ap_uint<18> x19_u5 = local_x19_temp(17+32*5,32*5); 
                        		ap_uint<18> x19_u6 = local_x19_temp(17+32*6,32*6); 
                        		ap_uint<18> x19_u7 = local_x19_temp(17+32*7,32*7); 
                        		ap_uint<18> x19_u8 = local_x19_temp(17+32*8,32*8); 
                        		ap_uint<18> x19_u9 = local_x19_temp(17+32*9,32*9); 
                        		ap_uint<18> x19_u10 = local_x19_temp(17+32*10,32*10); 
                        		ap_uint<18> x19_u11 = local_x19_temp(17+32*11,32*11); 
                        		ap_uint<18> x19_u12 = local_x19_temp(17+32*12,32*12); 
                        		ap_uint<18> x19_u13 = local_x19_temp(17+32*13,32*13); 
                        		ap_uint<18> x19_u14 = local_x19_temp(17+32*14,32*14); 
                        		ap_uint<18> x19_u15 = local_x19_temp(17+32*15,32*15); 
					ap_uint<512> local_A20 = fifo_A20.read();
                	        	ap_uint<18> A20_u0 = local_A20(17+32*0,32*0); 
                	        	ap_uint<18> A20_u1 = local_A20(17+32*1,32*1); 
                	        	ap_uint<18> A20_u2 = local_A20(17+32*2,32*2); 
                	        	ap_uint<18> A20_u3 = local_A20(17+32*3,32*3); 
                	        	ap_uint<18> A20_u4 = local_A20(17+32*4,32*4); 
                	        	ap_uint<18> A20_u5 = local_A20(17+32*5,32*5); 
                	        	ap_uint<18> A20_u6 = local_A20(17+32*6,32*6); 
                	        	ap_uint<18> A20_u7 = local_A20(17+32*7,32*7); 
                	        	ap_uint<18> A20_u8 = local_A20(17+32*8,32*8); 
                	        	ap_uint<18> A20_u9 = local_A20(17+32*9,32*9); 
                	        	ap_uint<18> A20_u10 = local_A20(17+32*10,32*10); 
                	        	ap_uint<18> A20_u11 = local_A20(17+32*11,32*11); 
                	        	ap_uint<18> A20_u12 = local_A20(17+32*12,32*12); 
                	        	ap_uint<18> A20_u13 = local_A20(17+32*13,32*13); 
                	        	ap_uint<18> A20_u14 = local_A20(17+32*14,32*14); 
                	        	ap_uint<18> A20_u15 = local_A20(17+32*15,32*15); 
					ap_uint<512> local_x20_temp = local_x20[j];
                        		ap_uint<18> x20_u0 = local_x20_temp(17+32*0,32*0); 
                        		ap_uint<18> x20_u1 = local_x20_temp(17+32*1,32*1); 
                        		ap_uint<18> x20_u2 = local_x20_temp(17+32*2,32*2); 
                        		ap_uint<18> x20_u3 = local_x20_temp(17+32*3,32*3); 
                        		ap_uint<18> x20_u4 = local_x20_temp(17+32*4,32*4); 
                        		ap_uint<18> x20_u5 = local_x20_temp(17+32*5,32*5); 
                        		ap_uint<18> x20_u6 = local_x20_temp(17+32*6,32*6); 
                        		ap_uint<18> x20_u7 = local_x20_temp(17+32*7,32*7); 
                        		ap_uint<18> x20_u8 = local_x20_temp(17+32*8,32*8); 
                        		ap_uint<18> x20_u9 = local_x20_temp(17+32*9,32*9); 
                        		ap_uint<18> x20_u10 = local_x20_temp(17+32*10,32*10); 
                        		ap_uint<18> x20_u11 = local_x20_temp(17+32*11,32*11); 
                        		ap_uint<18> x20_u12 = local_x20_temp(17+32*12,32*12); 
                        		ap_uint<18> x20_u13 = local_x20_temp(17+32*13,32*13); 
                        		ap_uint<18> x20_u14 = local_x20_temp(17+32*14,32*14); 
                        		ap_uint<18> x20_u15 = local_x20_temp(17+32*15,32*15); 
					ap_uint<512> local_A21 = fifo_A21.read();
                	        	ap_uint<18> A21_u0 = local_A21(17+32*0,32*0); 
                	        	ap_uint<18> A21_u1 = local_A21(17+32*1,32*1); 
                	        	ap_uint<18> A21_u2 = local_A21(17+32*2,32*2); 
                	        	ap_uint<18> A21_u3 = local_A21(17+32*3,32*3); 
                	        	ap_uint<18> A21_u4 = local_A21(17+32*4,32*4); 
                	        	ap_uint<18> A21_u5 = local_A21(17+32*5,32*5); 
                	        	ap_uint<18> A21_u6 = local_A21(17+32*6,32*6); 
                	        	ap_uint<18> A21_u7 = local_A21(17+32*7,32*7); 
                	        	ap_uint<18> A21_u8 = local_A21(17+32*8,32*8); 
                	        	ap_uint<18> A21_u9 = local_A21(17+32*9,32*9); 
                	        	ap_uint<18> A21_u10 = local_A21(17+32*10,32*10); 
                	        	ap_uint<18> A21_u11 = local_A21(17+32*11,32*11); 
                	        	ap_uint<18> A21_u12 = local_A21(17+32*12,32*12); 
                	        	ap_uint<18> A21_u13 = local_A21(17+32*13,32*13); 
                	        	ap_uint<18> A21_u14 = local_A21(17+32*14,32*14); 
                	        	ap_uint<18> A21_u15 = local_A21(17+32*15,32*15); 
					ap_uint<512> local_x21_temp = local_x21[j];
                        		ap_uint<18> x21_u0 = local_x21_temp(17+32*0,32*0); 
                        		ap_uint<18> x21_u1 = local_x21_temp(17+32*1,32*1); 
                        		ap_uint<18> x21_u2 = local_x21_temp(17+32*2,32*2); 
                        		ap_uint<18> x21_u3 = local_x21_temp(17+32*3,32*3); 
                        		ap_uint<18> x21_u4 = local_x21_temp(17+32*4,32*4); 
                        		ap_uint<18> x21_u5 = local_x21_temp(17+32*5,32*5); 
                        		ap_uint<18> x21_u6 = local_x21_temp(17+32*6,32*6); 
                        		ap_uint<18> x21_u7 = local_x21_temp(17+32*7,32*7); 
                        		ap_uint<18> x21_u8 = local_x21_temp(17+32*8,32*8); 
                        		ap_uint<18> x21_u9 = local_x21_temp(17+32*9,32*9); 
                        		ap_uint<18> x21_u10 = local_x21_temp(17+32*10,32*10); 
                        		ap_uint<18> x21_u11 = local_x21_temp(17+32*11,32*11); 
                        		ap_uint<18> x21_u12 = local_x21_temp(17+32*12,32*12); 
                        		ap_uint<18> x21_u13 = local_x21_temp(17+32*13,32*13); 
                        		ap_uint<18> x21_u14 = local_x21_temp(17+32*14,32*14); 
                        		ap_uint<18> x21_u15 = local_x21_temp(17+32*15,32*15); 
					ap_uint<512> local_A22 = fifo_A22.read();
                	        	ap_uint<18> A22_u0 = local_A22(17+32*0,32*0); 
                	        	ap_uint<18> A22_u1 = local_A22(17+32*1,32*1); 
                	        	ap_uint<18> A22_u2 = local_A22(17+32*2,32*2); 
                	        	ap_uint<18> A22_u3 = local_A22(17+32*3,32*3); 
                	        	ap_uint<18> A22_u4 = local_A22(17+32*4,32*4); 
                	        	ap_uint<18> A22_u5 = local_A22(17+32*5,32*5); 
                	        	ap_uint<18> A22_u6 = local_A22(17+32*6,32*6); 
                	        	ap_uint<18> A22_u7 = local_A22(17+32*7,32*7); 
                	        	ap_uint<18> A22_u8 = local_A22(17+32*8,32*8); 
                	        	ap_uint<18> A22_u9 = local_A22(17+32*9,32*9); 
                	        	ap_uint<18> A22_u10 = local_A22(17+32*10,32*10); 
                	        	ap_uint<18> A22_u11 = local_A22(17+32*11,32*11); 
                	        	ap_uint<18> A22_u12 = local_A22(17+32*12,32*12); 
                	        	ap_uint<18> A22_u13 = local_A22(17+32*13,32*13); 
                	        	ap_uint<18> A22_u14 = local_A22(17+32*14,32*14); 
                	        	ap_uint<18> A22_u15 = local_A22(17+32*15,32*15); 
					ap_uint<512> local_x22_temp = local_x22[j];
                        		ap_uint<18> x22_u0 = local_x22_temp(17+32*0,32*0); 
                        		ap_uint<18> x22_u1 = local_x22_temp(17+32*1,32*1); 
                        		ap_uint<18> x22_u2 = local_x22_temp(17+32*2,32*2); 
                        		ap_uint<18> x22_u3 = local_x22_temp(17+32*3,32*3); 
                        		ap_uint<18> x22_u4 = local_x22_temp(17+32*4,32*4); 
                        		ap_uint<18> x22_u5 = local_x22_temp(17+32*5,32*5); 
                        		ap_uint<18> x22_u6 = local_x22_temp(17+32*6,32*6); 
                        		ap_uint<18> x22_u7 = local_x22_temp(17+32*7,32*7); 
                        		ap_uint<18> x22_u8 = local_x22_temp(17+32*8,32*8); 
                        		ap_uint<18> x22_u9 = local_x22_temp(17+32*9,32*9); 
                        		ap_uint<18> x22_u10 = local_x22_temp(17+32*10,32*10); 
                        		ap_uint<18> x22_u11 = local_x22_temp(17+32*11,32*11); 
                        		ap_uint<18> x22_u12 = local_x22_temp(17+32*12,32*12); 
                        		ap_uint<18> x22_u13 = local_x22_temp(17+32*13,32*13); 
                        		ap_uint<18> x22_u14 = local_x22_temp(17+32*14,32*14); 
                        		ap_uint<18> x22_u15 = local_x22_temp(17+32*15,32*15); 
					ap_uint<512> local_A23 = fifo_A23.read();
                	        	ap_uint<18> A23_u0 = local_A23(17+32*0,32*0); 
                	        	ap_uint<18> A23_u1 = local_A23(17+32*1,32*1); 
                	        	ap_uint<18> A23_u2 = local_A23(17+32*2,32*2); 
                	        	ap_uint<18> A23_u3 = local_A23(17+32*3,32*3); 
                	        	ap_uint<18> A23_u4 = local_A23(17+32*4,32*4); 
                	        	ap_uint<18> A23_u5 = local_A23(17+32*5,32*5); 
                	        	ap_uint<18> A23_u6 = local_A23(17+32*6,32*6); 
                	        	ap_uint<18> A23_u7 = local_A23(17+32*7,32*7); 
                	        	ap_uint<18> A23_u8 = local_A23(17+32*8,32*8); 
                	        	ap_uint<18> A23_u9 = local_A23(17+32*9,32*9); 
                	        	ap_uint<18> A23_u10 = local_A23(17+32*10,32*10); 
                	        	ap_uint<18> A23_u11 = local_A23(17+32*11,32*11); 
                	        	ap_uint<18> A23_u12 = local_A23(17+32*12,32*12); 
                	        	ap_uint<18> A23_u13 = local_A23(17+32*13,32*13); 
                	        	ap_uint<18> A23_u14 = local_A23(17+32*14,32*14); 
                	        	ap_uint<18> A23_u15 = local_A23(17+32*15,32*15); 
					ap_uint<512> local_x23_temp = local_x23[j];
                        		ap_uint<18> x23_u0 = local_x23_temp(17+32*0,32*0); 
                        		ap_uint<18> x23_u1 = local_x23_temp(17+32*1,32*1); 
                        		ap_uint<18> x23_u2 = local_x23_temp(17+32*2,32*2); 
                        		ap_uint<18> x23_u3 = local_x23_temp(17+32*3,32*3); 
                        		ap_uint<18> x23_u4 = local_x23_temp(17+32*4,32*4); 
                        		ap_uint<18> x23_u5 = local_x23_temp(17+32*5,32*5); 
                        		ap_uint<18> x23_u6 = local_x23_temp(17+32*6,32*6); 
                        		ap_uint<18> x23_u7 = local_x23_temp(17+32*7,32*7); 
                        		ap_uint<18> x23_u8 = local_x23_temp(17+32*8,32*8); 
                        		ap_uint<18> x23_u9 = local_x23_temp(17+32*9,32*9); 
                        		ap_uint<18> x23_u10 = local_x23_temp(17+32*10,32*10); 
                        		ap_uint<18> x23_u11 = local_x23_temp(17+32*11,32*11); 
                        		ap_uint<18> x23_u12 = local_x23_temp(17+32*12,32*12); 
                        		ap_uint<18> x23_u13 = local_x23_temp(17+32*13,32*13); 
                        		ap_uint<18> x23_u14 = local_x23_temp(17+32*14,32*14); 
                        		ap_uint<18> x23_u15 = local_x23_temp(17+32*15,32*15); 
	                                acc_y0 += 0
						+ (ap_uint<32>) A0_u0 * (ap_uint<32>) x0_u0
						+ (ap_uint<32>) A0_u1 * (ap_uint<32>) x0_u1
						+ (ap_uint<32>) A0_u2 * (ap_uint<32>) x0_u2
						+ (ap_uint<32>) A0_u3 * (ap_uint<32>) x0_u3
						+ (ap_uint<32>) A0_u4 * (ap_uint<32>) x0_u4
						+ (ap_uint<32>) A0_u5 * (ap_uint<32>) x0_u5
						+ (ap_uint<32>) A0_u6 * (ap_uint<32>) x0_u6
						+ (ap_uint<32>) A0_u7 * (ap_uint<32>) x0_u7
						+ (ap_uint<32>) A0_u8 * (ap_uint<32>) x0_u8
						+ (ap_uint<32>) A0_u9 * (ap_uint<32>) x0_u9
						+ (ap_uint<32>) A0_u10 * (ap_uint<32>) x0_u10
						+ (ap_uint<32>) A0_u11 * (ap_uint<32>) x0_u11
						+ (ap_uint<32>) A0_u12 * (ap_uint<32>) x0_u12
						+ (ap_uint<32>) A0_u13 * (ap_uint<32>) x0_u13
						+ (ap_uint<32>) A0_u14 * (ap_uint<32>) x0_u14
						+ (ap_uint<32>) A0_u15 * (ap_uint<32>) x0_u15
						;
	                                acc_y1 += 0
						+ (ap_uint<32>) A1_u0 * (ap_uint<32>) x1_u0
						+ (ap_uint<32>) A1_u1 * (ap_uint<32>) x1_u1
						+ (ap_uint<32>) A1_u2 * (ap_uint<32>) x1_u2
						+ (ap_uint<32>) A1_u3 * (ap_uint<32>) x1_u3
						+ (ap_uint<32>) A1_u4 * (ap_uint<32>) x1_u4
						+ (ap_uint<32>) A1_u5 * (ap_uint<32>) x1_u5
						+ (ap_uint<32>) A1_u6 * (ap_uint<32>) x1_u6
						+ (ap_uint<32>) A1_u7 * (ap_uint<32>) x1_u7
						+ (ap_uint<32>) A1_u8 * (ap_uint<32>) x1_u8
						+ (ap_uint<32>) A1_u9 * (ap_uint<32>) x1_u9
						+ (ap_uint<32>) A1_u10 * (ap_uint<32>) x1_u10
						+ (ap_uint<32>) A1_u11 * (ap_uint<32>) x1_u11
						+ (ap_uint<32>) A1_u12 * (ap_uint<32>) x1_u12
						+ (ap_uint<32>) A1_u13 * (ap_uint<32>) x1_u13
						+ (ap_uint<32>) A1_u14 * (ap_uint<32>) x1_u14
						+ (ap_uint<32>) A1_u15 * (ap_uint<32>) x1_u15
						;
	                                acc_y2 += 0
						+ (ap_uint<32>) A2_u0 * (ap_uint<32>) x2_u0
						+ (ap_uint<32>) A2_u1 * (ap_uint<32>) x2_u1
						+ (ap_uint<32>) A2_u2 * (ap_uint<32>) x2_u2
						+ (ap_uint<32>) A2_u3 * (ap_uint<32>) x2_u3
						+ (ap_uint<32>) A2_u4 * (ap_uint<32>) x2_u4
						+ (ap_uint<32>) A2_u5 * (ap_uint<32>) x2_u5
						+ (ap_uint<32>) A2_u6 * (ap_uint<32>) x2_u6
						+ (ap_uint<32>) A2_u7 * (ap_uint<32>) x2_u7
						+ (ap_uint<32>) A2_u8 * (ap_uint<32>) x2_u8
						+ (ap_uint<32>) A2_u9 * (ap_uint<32>) x2_u9
						+ (ap_uint<32>) A2_u10 * (ap_uint<32>) x2_u10
						+ (ap_uint<32>) A2_u11 * (ap_uint<32>) x2_u11
						+ (ap_uint<32>) A2_u12 * (ap_uint<32>) x2_u12
						+ (ap_uint<32>) A2_u13 * (ap_uint<32>) x2_u13
						+ (ap_uint<32>) A2_u14 * (ap_uint<32>) x2_u14
						+ (ap_uint<32>) A2_u15 * (ap_uint<32>) x2_u15
						;
	                                acc_y3 += 0
						+ (ap_uint<32>) A3_u0 * (ap_uint<32>) x3_u0
						+ (ap_uint<32>) A3_u1 * (ap_uint<32>) x3_u1
						+ (ap_uint<32>) A3_u2 * (ap_uint<32>) x3_u2
						+ (ap_uint<32>) A3_u3 * (ap_uint<32>) x3_u3
						+ (ap_uint<32>) A3_u4 * (ap_uint<32>) x3_u4
						+ (ap_uint<32>) A3_u5 * (ap_uint<32>) x3_u5
						+ (ap_uint<32>) A3_u6 * (ap_uint<32>) x3_u6
						+ (ap_uint<32>) A3_u7 * (ap_uint<32>) x3_u7
						+ (ap_uint<32>) A3_u8 * (ap_uint<32>) x3_u8
						+ (ap_uint<32>) A3_u9 * (ap_uint<32>) x3_u9
						+ (ap_uint<32>) A3_u10 * (ap_uint<32>) x3_u10
						+ (ap_uint<32>) A3_u11 * (ap_uint<32>) x3_u11
						+ (ap_uint<32>) A3_u12 * (ap_uint<32>) x3_u12
						+ (ap_uint<32>) A3_u13 * (ap_uint<32>) x3_u13
						+ (ap_uint<32>) A3_u14 * (ap_uint<32>) x3_u14
						+ (ap_uint<32>) A3_u15 * (ap_uint<32>) x3_u15
						;
	                                acc_y4 += 0
						+ (ap_uint<32>) A4_u0 * (ap_uint<32>) x4_u0
						+ (ap_uint<32>) A4_u1 * (ap_uint<32>) x4_u1
						+ (ap_uint<32>) A4_u2 * (ap_uint<32>) x4_u2
						+ (ap_uint<32>) A4_u3 * (ap_uint<32>) x4_u3
						+ (ap_uint<32>) A4_u4 * (ap_uint<32>) x4_u4
						+ (ap_uint<32>) A4_u5 * (ap_uint<32>) x4_u5
						+ (ap_uint<32>) A4_u6 * (ap_uint<32>) x4_u6
						+ (ap_uint<32>) A4_u7 * (ap_uint<32>) x4_u7
						+ (ap_uint<32>) A4_u8 * (ap_uint<32>) x4_u8
						+ (ap_uint<32>) A4_u9 * (ap_uint<32>) x4_u9
						+ (ap_uint<32>) A4_u10 * (ap_uint<32>) x4_u10
						+ (ap_uint<32>) A4_u11 * (ap_uint<32>) x4_u11
						+ (ap_uint<32>) A4_u12 * (ap_uint<32>) x4_u12
						+ (ap_uint<32>) A4_u13 * (ap_uint<32>) x4_u13
						+ (ap_uint<32>) A4_u14 * (ap_uint<32>) x4_u14
						+ (ap_uint<32>) A4_u15 * (ap_uint<32>) x4_u15
						;
	                                acc_y5 += 0
						+ (ap_uint<32>) A5_u0 * (ap_uint<32>) x5_u0
						+ (ap_uint<32>) A5_u1 * (ap_uint<32>) x5_u1
						+ (ap_uint<32>) A5_u2 * (ap_uint<32>) x5_u2
						+ (ap_uint<32>) A5_u3 * (ap_uint<32>) x5_u3
						+ (ap_uint<32>) A5_u4 * (ap_uint<32>) x5_u4
						+ (ap_uint<32>) A5_u5 * (ap_uint<32>) x5_u5
						+ (ap_uint<32>) A5_u6 * (ap_uint<32>) x5_u6
						+ (ap_uint<32>) A5_u7 * (ap_uint<32>) x5_u7
						+ (ap_uint<32>) A5_u8 * (ap_uint<32>) x5_u8
						+ (ap_uint<32>) A5_u9 * (ap_uint<32>) x5_u9
						+ (ap_uint<32>) A5_u10 * (ap_uint<32>) x5_u10
						+ (ap_uint<32>) A5_u11 * (ap_uint<32>) x5_u11
						+ (ap_uint<32>) A5_u12 * (ap_uint<32>) x5_u12
						+ (ap_uint<32>) A5_u13 * (ap_uint<32>) x5_u13
						+ (ap_uint<32>) A5_u14 * (ap_uint<32>) x5_u14
						+ (ap_uint<32>) A5_u15 * (ap_uint<32>) x5_u15
						;
	                                acc_y6 += 0
						+ (ap_uint<32>) A6_u0 * (ap_uint<32>) x6_u0
						+ (ap_uint<32>) A6_u1 * (ap_uint<32>) x6_u1
						+ (ap_uint<32>) A6_u2 * (ap_uint<32>) x6_u2
						+ (ap_uint<32>) A6_u3 * (ap_uint<32>) x6_u3
						+ (ap_uint<32>) A6_u4 * (ap_uint<32>) x6_u4
						+ (ap_uint<32>) A6_u5 * (ap_uint<32>) x6_u5
						+ (ap_uint<32>) A6_u6 * (ap_uint<32>) x6_u6
						+ (ap_uint<32>) A6_u7 * (ap_uint<32>) x6_u7
						+ (ap_uint<32>) A6_u8 * (ap_uint<32>) x6_u8
						+ (ap_uint<32>) A6_u9 * (ap_uint<32>) x6_u9
						+ (ap_uint<32>) A6_u10 * (ap_uint<32>) x6_u10
						+ (ap_uint<32>) A6_u11 * (ap_uint<32>) x6_u11
						+ (ap_uint<32>) A6_u12 * (ap_uint<32>) x6_u12
						+ (ap_uint<32>) A6_u13 * (ap_uint<32>) x6_u13
						+ (ap_uint<32>) A6_u14 * (ap_uint<32>) x6_u14
						+ (ap_uint<32>) A6_u15 * (ap_uint<32>) x6_u15
						;
	                                acc_y7 += 0
						+ (ap_uint<32>) A7_u0 * (ap_uint<32>) x7_u0
						+ (ap_uint<32>) A7_u1 * (ap_uint<32>) x7_u1
						+ (ap_uint<32>) A7_u2 * (ap_uint<32>) x7_u2
						+ (ap_uint<32>) A7_u3 * (ap_uint<32>) x7_u3
						+ (ap_uint<32>) A7_u4 * (ap_uint<32>) x7_u4
						+ (ap_uint<32>) A7_u5 * (ap_uint<32>) x7_u5
						+ (ap_uint<32>) A7_u6 * (ap_uint<32>) x7_u6
						+ (ap_uint<32>) A7_u7 * (ap_uint<32>) x7_u7
						+ (ap_uint<32>) A7_u8 * (ap_uint<32>) x7_u8
						+ (ap_uint<32>) A7_u9 * (ap_uint<32>) x7_u9
						+ (ap_uint<32>) A7_u10 * (ap_uint<32>) x7_u10
						+ (ap_uint<32>) A7_u11 * (ap_uint<32>) x7_u11
						+ (ap_uint<32>) A7_u12 * (ap_uint<32>) x7_u12
						+ (ap_uint<32>) A7_u13 * (ap_uint<32>) x7_u13
						+ (ap_uint<32>) A7_u14 * (ap_uint<32>) x7_u14
						+ (ap_uint<32>) A7_u15 * (ap_uint<32>) x7_u15
						;
	                                acc_y8 += 0
						+ (ap_uint<32>) A8_u0 * (ap_uint<32>) x8_u0
						+ (ap_uint<32>) A8_u1 * (ap_uint<32>) x8_u1
						+ (ap_uint<32>) A8_u2 * (ap_uint<32>) x8_u2
						+ (ap_uint<32>) A8_u3 * (ap_uint<32>) x8_u3
						+ (ap_uint<32>) A8_u4 * (ap_uint<32>) x8_u4
						+ (ap_uint<32>) A8_u5 * (ap_uint<32>) x8_u5
						+ (ap_uint<32>) A8_u6 * (ap_uint<32>) x8_u6
						+ (ap_uint<32>) A8_u7 * (ap_uint<32>) x8_u7
						+ (ap_uint<32>) A8_u8 * (ap_uint<32>) x8_u8
						+ (ap_uint<32>) A8_u9 * (ap_uint<32>) x8_u9
						+ (ap_uint<32>) A8_u10 * (ap_uint<32>) x8_u10
						+ (ap_uint<32>) A8_u11 * (ap_uint<32>) x8_u11
						+ (ap_uint<32>) A8_u12 * (ap_uint<32>) x8_u12
						+ (ap_uint<32>) A8_u13 * (ap_uint<32>) x8_u13
						+ (ap_uint<32>) A8_u14 * (ap_uint<32>) x8_u14
						+ (ap_uint<32>) A8_u15 * (ap_uint<32>) x8_u15
						;
	                                acc_y9 += 0
						+ (ap_uint<32>) A9_u0 * (ap_uint<32>) x9_u0
						+ (ap_uint<32>) A9_u1 * (ap_uint<32>) x9_u1
						+ (ap_uint<32>) A9_u2 * (ap_uint<32>) x9_u2
						+ (ap_uint<32>) A9_u3 * (ap_uint<32>) x9_u3
						+ (ap_uint<32>) A9_u4 * (ap_uint<32>) x9_u4
						+ (ap_uint<32>) A9_u5 * (ap_uint<32>) x9_u5
						+ (ap_uint<32>) A9_u6 * (ap_uint<32>) x9_u6
						+ (ap_uint<32>) A9_u7 * (ap_uint<32>) x9_u7
						+ (ap_uint<32>) A9_u8 * (ap_uint<32>) x9_u8
						+ (ap_uint<32>) A9_u9 * (ap_uint<32>) x9_u9
						+ (ap_uint<32>) A9_u10 * (ap_uint<32>) x9_u10
						+ (ap_uint<32>) A9_u11 * (ap_uint<32>) x9_u11
						+ (ap_uint<32>) A9_u12 * (ap_uint<32>) x9_u12
						+ (ap_uint<32>) A9_u13 * (ap_uint<32>) x9_u13
						+ (ap_uint<32>) A9_u14 * (ap_uint<32>) x9_u14
						+ (ap_uint<32>) A9_u15 * (ap_uint<32>) x9_u15
						;
	                                acc_y10 += 0
						+ (ap_uint<32>) A10_u0 * (ap_uint<32>) x10_u0
						+ (ap_uint<32>) A10_u1 * (ap_uint<32>) x10_u1
						+ (ap_uint<32>) A10_u2 * (ap_uint<32>) x10_u2
						+ (ap_uint<32>) A10_u3 * (ap_uint<32>) x10_u3
						+ (ap_uint<32>) A10_u4 * (ap_uint<32>) x10_u4
						+ (ap_uint<32>) A10_u5 * (ap_uint<32>) x10_u5
						+ (ap_uint<32>) A10_u6 * (ap_uint<32>) x10_u6
						+ (ap_uint<32>) A10_u7 * (ap_uint<32>) x10_u7
						+ (ap_uint<32>) A10_u8 * (ap_uint<32>) x10_u8
						+ (ap_uint<32>) A10_u9 * (ap_uint<32>) x10_u9
						+ (ap_uint<32>) A10_u10 * (ap_uint<32>) x10_u10
						+ (ap_uint<32>) A10_u11 * (ap_uint<32>) x10_u11
						+ (ap_uint<32>) A10_u12 * (ap_uint<32>) x10_u12
						+ (ap_uint<32>) A10_u13 * (ap_uint<32>) x10_u13
						+ (ap_uint<32>) A10_u14 * (ap_uint<32>) x10_u14
						+ (ap_uint<32>) A10_u15 * (ap_uint<32>) x10_u15
						;
	                                acc_y11 += 0
						+ (ap_uint<32>) A11_u0 * (ap_uint<32>) x11_u0
						+ (ap_uint<32>) A11_u1 * (ap_uint<32>) x11_u1
						+ (ap_uint<32>) A11_u2 * (ap_uint<32>) x11_u2
						+ (ap_uint<32>) A11_u3 * (ap_uint<32>) x11_u3
						+ (ap_uint<32>) A11_u4 * (ap_uint<32>) x11_u4
						+ (ap_uint<32>) A11_u5 * (ap_uint<32>) x11_u5
						+ (ap_uint<32>) A11_u6 * (ap_uint<32>) x11_u6
						+ (ap_uint<32>) A11_u7 * (ap_uint<32>) x11_u7
						+ (ap_uint<32>) A11_u8 * (ap_uint<32>) x11_u8
						+ (ap_uint<32>) A11_u9 * (ap_uint<32>) x11_u9
						+ (ap_uint<32>) A11_u10 * (ap_uint<32>) x11_u10
						+ (ap_uint<32>) A11_u11 * (ap_uint<32>) x11_u11
						+ (ap_uint<32>) A11_u12 * (ap_uint<32>) x11_u12
						+ (ap_uint<32>) A11_u13 * (ap_uint<32>) x11_u13
						+ (ap_uint<32>) A11_u14 * (ap_uint<32>) x11_u14
						+ (ap_uint<32>) A11_u15 * (ap_uint<32>) x11_u15
						;
	                                acc_y12 += 0
						+ (ap_uint<32>) A12_u0 * (ap_uint<32>) x12_u0
						+ (ap_uint<32>) A12_u1 * (ap_uint<32>) x12_u1
						+ (ap_uint<32>) A12_u2 * (ap_uint<32>) x12_u2
						+ (ap_uint<32>) A12_u3 * (ap_uint<32>) x12_u3
						+ (ap_uint<32>) A12_u4 * (ap_uint<32>) x12_u4
						+ (ap_uint<32>) A12_u5 * (ap_uint<32>) x12_u5
						+ (ap_uint<32>) A12_u6 * (ap_uint<32>) x12_u6
						+ (ap_uint<32>) A12_u7 * (ap_uint<32>) x12_u7
						+ (ap_uint<32>) A12_u8 * (ap_uint<32>) x12_u8
						+ (ap_uint<32>) A12_u9 * (ap_uint<32>) x12_u9
						+ (ap_uint<32>) A12_u10 * (ap_uint<32>) x12_u10
						+ (ap_uint<32>) A12_u11 * (ap_uint<32>) x12_u11
						+ (ap_uint<32>) A12_u12 * (ap_uint<32>) x12_u12
						+ (ap_uint<32>) A12_u13 * (ap_uint<32>) x12_u13
						+ (ap_uint<32>) A12_u14 * (ap_uint<32>) x12_u14
						+ (ap_uint<32>) A12_u15 * (ap_uint<32>) x12_u15
						;
	                                acc_y13 += 0
						+ (ap_uint<32>) A13_u0 * (ap_uint<32>) x13_u0
						+ (ap_uint<32>) A13_u1 * (ap_uint<32>) x13_u1
						+ (ap_uint<32>) A13_u2 * (ap_uint<32>) x13_u2
						+ (ap_uint<32>) A13_u3 * (ap_uint<32>) x13_u3
						+ (ap_uint<32>) A13_u4 * (ap_uint<32>) x13_u4
						+ (ap_uint<32>) A13_u5 * (ap_uint<32>) x13_u5
						+ (ap_uint<32>) A13_u6 * (ap_uint<32>) x13_u6
						+ (ap_uint<32>) A13_u7 * (ap_uint<32>) x13_u7
						+ (ap_uint<32>) A13_u8 * (ap_uint<32>) x13_u8
						+ (ap_uint<32>) A13_u9 * (ap_uint<32>) x13_u9
						+ (ap_uint<32>) A13_u10 * (ap_uint<32>) x13_u10
						+ (ap_uint<32>) A13_u11 * (ap_uint<32>) x13_u11
						+ (ap_uint<32>) A13_u12 * (ap_uint<32>) x13_u12
						+ (ap_uint<32>) A13_u13 * (ap_uint<32>) x13_u13
						+ (ap_uint<32>) A13_u14 * (ap_uint<32>) x13_u14
						+ (ap_uint<32>) A13_u15 * (ap_uint<32>) x13_u15
						;
	                                acc_y14 += 0
						+ (ap_uint<32>) A14_u0 * (ap_uint<32>) x14_u0
						+ (ap_uint<32>) A14_u1 * (ap_uint<32>) x14_u1
						+ (ap_uint<32>) A14_u2 * (ap_uint<32>) x14_u2
						+ (ap_uint<32>) A14_u3 * (ap_uint<32>) x14_u3
						+ (ap_uint<32>) A14_u4 * (ap_uint<32>) x14_u4
						+ (ap_uint<32>) A14_u5 * (ap_uint<32>) x14_u5
						+ (ap_uint<32>) A14_u6 * (ap_uint<32>) x14_u6
						+ (ap_uint<32>) A14_u7 * (ap_uint<32>) x14_u7
						+ (ap_uint<32>) A14_u8 * (ap_uint<32>) x14_u8
						+ (ap_uint<32>) A14_u9 * (ap_uint<32>) x14_u9
						+ (ap_uint<32>) A14_u10 * (ap_uint<32>) x14_u10
						+ (ap_uint<32>) A14_u11 * (ap_uint<32>) x14_u11
						+ (ap_uint<32>) A14_u12 * (ap_uint<32>) x14_u12
						+ (ap_uint<32>) A14_u13 * (ap_uint<32>) x14_u13
						+ (ap_uint<32>) A14_u14 * (ap_uint<32>) x14_u14
						+ (ap_uint<32>) A14_u15 * (ap_uint<32>) x14_u15
						;
	                                acc_y15 += 0
						+ (ap_uint<32>) A15_u0 * (ap_uint<32>) x15_u0
						+ (ap_uint<32>) A15_u1 * (ap_uint<32>) x15_u1
						+ (ap_uint<32>) A15_u2 * (ap_uint<32>) x15_u2
						+ (ap_uint<32>) A15_u3 * (ap_uint<32>) x15_u3
						+ (ap_uint<32>) A15_u4 * (ap_uint<32>) x15_u4
						+ (ap_uint<32>) A15_u5 * (ap_uint<32>) x15_u5
						+ (ap_uint<32>) A15_u6 * (ap_uint<32>) x15_u6
						+ (ap_uint<32>) A15_u7 * (ap_uint<32>) x15_u7
						+ (ap_uint<32>) A15_u8 * (ap_uint<32>) x15_u8
						+ (ap_uint<32>) A15_u9 * (ap_uint<32>) x15_u9
						+ (ap_uint<32>) A15_u10 * (ap_uint<32>) x15_u10
						+ (ap_uint<32>) A15_u11 * (ap_uint<32>) x15_u11
						+ (ap_uint<32>) A15_u12 * (ap_uint<32>) x15_u12
						+ (ap_uint<32>) A15_u13 * (ap_uint<32>) x15_u13
						+ (ap_uint<32>) A15_u14 * (ap_uint<32>) x15_u14
						+ (ap_uint<32>) A15_u15 * (ap_uint<32>) x15_u15
						;
	                                acc_y16 += 0
						+ (ap_uint<32>) A16_u0 * (ap_uint<32>) x16_u0
						+ (ap_uint<32>) A16_u1 * (ap_uint<32>) x16_u1
						+ (ap_uint<32>) A16_u2 * (ap_uint<32>) x16_u2
						+ (ap_uint<32>) A16_u3 * (ap_uint<32>) x16_u3
						+ (ap_uint<32>) A16_u4 * (ap_uint<32>) x16_u4
						+ (ap_uint<32>) A16_u5 * (ap_uint<32>) x16_u5
						+ (ap_uint<32>) A16_u6 * (ap_uint<32>) x16_u6
						+ (ap_uint<32>) A16_u7 * (ap_uint<32>) x16_u7
						+ (ap_uint<32>) A16_u8 * (ap_uint<32>) x16_u8
						+ (ap_uint<32>) A16_u9 * (ap_uint<32>) x16_u9
						+ (ap_uint<32>) A16_u10 * (ap_uint<32>) x16_u10
						+ (ap_uint<32>) A16_u11 * (ap_uint<32>) x16_u11
						+ (ap_uint<32>) A16_u12 * (ap_uint<32>) x16_u12
						+ (ap_uint<32>) A16_u13 * (ap_uint<32>) x16_u13
						+ (ap_uint<32>) A16_u14 * (ap_uint<32>) x16_u14
						+ (ap_uint<32>) A16_u15 * (ap_uint<32>) x16_u15
						;
	                                acc_y17 += 0
						+ (ap_uint<32>) A17_u0 * (ap_uint<32>) x17_u0
						+ (ap_uint<32>) A17_u1 * (ap_uint<32>) x17_u1
						+ (ap_uint<32>) A17_u2 * (ap_uint<32>) x17_u2
						+ (ap_uint<32>) A17_u3 * (ap_uint<32>) x17_u3
						+ (ap_uint<32>) A17_u4 * (ap_uint<32>) x17_u4
						+ (ap_uint<32>) A17_u5 * (ap_uint<32>) x17_u5
						+ (ap_uint<32>) A17_u6 * (ap_uint<32>) x17_u6
						+ (ap_uint<32>) A17_u7 * (ap_uint<32>) x17_u7
						+ (ap_uint<32>) A17_u8 * (ap_uint<32>) x17_u8
						+ (ap_uint<32>) A17_u9 * (ap_uint<32>) x17_u9
						+ (ap_uint<32>) A17_u10 * (ap_uint<32>) x17_u10
						+ (ap_uint<32>) A17_u11 * (ap_uint<32>) x17_u11
						+ (ap_uint<32>) A17_u12 * (ap_uint<32>) x17_u12
						+ (ap_uint<32>) A17_u13 * (ap_uint<32>) x17_u13
						+ (ap_uint<32>) A17_u14 * (ap_uint<32>) x17_u14
						+ (ap_uint<32>) A17_u15 * (ap_uint<32>) x17_u15
						;
	                                acc_y18 += 0
						+ (ap_uint<32>) A18_u0 * (ap_uint<32>) x18_u0
						+ (ap_uint<32>) A18_u1 * (ap_uint<32>) x18_u1
						+ (ap_uint<32>) A18_u2 * (ap_uint<32>) x18_u2
						+ (ap_uint<32>) A18_u3 * (ap_uint<32>) x18_u3
						+ (ap_uint<32>) A18_u4 * (ap_uint<32>) x18_u4
						+ (ap_uint<32>) A18_u5 * (ap_uint<32>) x18_u5
						+ (ap_uint<32>) A18_u6 * (ap_uint<32>) x18_u6
						+ (ap_uint<32>) A18_u7 * (ap_uint<32>) x18_u7
						+ (ap_uint<32>) A18_u8 * (ap_uint<32>) x18_u8
						+ (ap_uint<32>) A18_u9 * (ap_uint<32>) x18_u9
						+ (ap_uint<32>) A18_u10 * (ap_uint<32>) x18_u10
						+ (ap_uint<32>) A18_u11 * (ap_uint<32>) x18_u11
						+ (ap_uint<32>) A18_u12 * (ap_uint<32>) x18_u12
						+ (ap_uint<32>) A18_u13 * (ap_uint<32>) x18_u13
						+ (ap_uint<32>) A18_u14 * (ap_uint<32>) x18_u14
						+ (ap_uint<32>) A18_u15 * (ap_uint<32>) x18_u15
						;
	                                acc_y19 += 0
						+ (ap_uint<32>) A19_u0 * (ap_uint<32>) x19_u0
						+ (ap_uint<32>) A19_u1 * (ap_uint<32>) x19_u1
						+ (ap_uint<32>) A19_u2 * (ap_uint<32>) x19_u2
						+ (ap_uint<32>) A19_u3 * (ap_uint<32>) x19_u3
						+ (ap_uint<32>) A19_u4 * (ap_uint<32>) x19_u4
						+ (ap_uint<32>) A19_u5 * (ap_uint<32>) x19_u5
						+ (ap_uint<32>) A19_u6 * (ap_uint<32>) x19_u6
						+ (ap_uint<32>) A19_u7 * (ap_uint<32>) x19_u7
						+ (ap_uint<32>) A19_u8 * (ap_uint<32>) x19_u8
						+ (ap_uint<32>) A19_u9 * (ap_uint<32>) x19_u9
						+ (ap_uint<32>) A19_u10 * (ap_uint<32>) x19_u10
						+ (ap_uint<32>) A19_u11 * (ap_uint<32>) x19_u11
						+ (ap_uint<32>) A19_u12 * (ap_uint<32>) x19_u12
						+ (ap_uint<32>) A19_u13 * (ap_uint<32>) x19_u13
						+ (ap_uint<32>) A19_u14 * (ap_uint<32>) x19_u14
						+ (ap_uint<32>) A19_u15 * (ap_uint<32>) x19_u15
						;
	                                acc_y20 += 0
						+ (ap_uint<32>) A20_u0 * (ap_uint<32>) x20_u0
						+ (ap_uint<32>) A20_u1 * (ap_uint<32>) x20_u1
						+ (ap_uint<32>) A20_u2 * (ap_uint<32>) x20_u2
						+ (ap_uint<32>) A20_u3 * (ap_uint<32>) x20_u3
						+ (ap_uint<32>) A20_u4 * (ap_uint<32>) x20_u4
						+ (ap_uint<32>) A20_u5 * (ap_uint<32>) x20_u5
						+ (ap_uint<32>) A20_u6 * (ap_uint<32>) x20_u6
						+ (ap_uint<32>) A20_u7 * (ap_uint<32>) x20_u7
						+ (ap_uint<32>) A20_u8 * (ap_uint<32>) x20_u8
						+ (ap_uint<32>) A20_u9 * (ap_uint<32>) x20_u9
						+ (ap_uint<32>) A20_u10 * (ap_uint<32>) x20_u10
						+ (ap_uint<32>) A20_u11 * (ap_uint<32>) x20_u11
						+ (ap_uint<32>) A20_u12 * (ap_uint<32>) x20_u12
						+ (ap_uint<32>) A20_u13 * (ap_uint<32>) x20_u13
						+ (ap_uint<32>) A20_u14 * (ap_uint<32>) x20_u14
						+ (ap_uint<32>) A20_u15 * (ap_uint<32>) x20_u15
						;
	                                acc_y21 += 0
						+ (ap_uint<32>) A21_u0 * (ap_uint<32>) x21_u0
						+ (ap_uint<32>) A21_u1 * (ap_uint<32>) x21_u1
						+ (ap_uint<32>) A21_u2 * (ap_uint<32>) x21_u2
						+ (ap_uint<32>) A21_u3 * (ap_uint<32>) x21_u3
						+ (ap_uint<32>) A21_u4 * (ap_uint<32>) x21_u4
						+ (ap_uint<32>) A21_u5 * (ap_uint<32>) x21_u5
						+ (ap_uint<32>) A21_u6 * (ap_uint<32>) x21_u6
						+ (ap_uint<32>) A21_u7 * (ap_uint<32>) x21_u7
						+ (ap_uint<32>) A21_u8 * (ap_uint<32>) x21_u8
						+ (ap_uint<32>) A21_u9 * (ap_uint<32>) x21_u9
						+ (ap_uint<32>) A21_u10 * (ap_uint<32>) x21_u10
						+ (ap_uint<32>) A21_u11 * (ap_uint<32>) x21_u11
						+ (ap_uint<32>) A21_u12 * (ap_uint<32>) x21_u12
						+ (ap_uint<32>) A21_u13 * (ap_uint<32>) x21_u13
						+ (ap_uint<32>) A21_u14 * (ap_uint<32>) x21_u14
						+ (ap_uint<32>) A21_u15 * (ap_uint<32>) x21_u15
						;
	                                acc_y22 += 0
						+ (ap_uint<32>) A22_u0 * (ap_uint<32>) x22_u0
						+ (ap_uint<32>) A22_u1 * (ap_uint<32>) x22_u1
						+ (ap_uint<32>) A22_u2 * (ap_uint<32>) x22_u2
						+ (ap_uint<32>) A22_u3 * (ap_uint<32>) x22_u3
						+ (ap_uint<32>) A22_u4 * (ap_uint<32>) x22_u4
						+ (ap_uint<32>) A22_u5 * (ap_uint<32>) x22_u5
						+ (ap_uint<32>) A22_u6 * (ap_uint<32>) x22_u6
						+ (ap_uint<32>) A22_u7 * (ap_uint<32>) x22_u7
						+ (ap_uint<32>) A22_u8 * (ap_uint<32>) x22_u8
						+ (ap_uint<32>) A22_u9 * (ap_uint<32>) x22_u9
						+ (ap_uint<32>) A22_u10 * (ap_uint<32>) x22_u10
						+ (ap_uint<32>) A22_u11 * (ap_uint<32>) x22_u11
						+ (ap_uint<32>) A22_u12 * (ap_uint<32>) x22_u12
						+ (ap_uint<32>) A22_u13 * (ap_uint<32>) x22_u13
						+ (ap_uint<32>) A22_u14 * (ap_uint<32>) x22_u14
						+ (ap_uint<32>) A22_u15 * (ap_uint<32>) x22_u15
						;
	                                acc_y23 += 0
						+ (ap_uint<32>) A23_u0 * (ap_uint<32>) x23_u0
						+ (ap_uint<32>) A23_u1 * (ap_uint<32>) x23_u1
						+ (ap_uint<32>) A23_u2 * (ap_uint<32>) x23_u2
						+ (ap_uint<32>) A23_u3 * (ap_uint<32>) x23_u3
						+ (ap_uint<32>) A23_u4 * (ap_uint<32>) x23_u4
						+ (ap_uint<32>) A23_u5 * (ap_uint<32>) x23_u5
						+ (ap_uint<32>) A23_u6 * (ap_uint<32>) x23_u6
						+ (ap_uint<32>) A23_u7 * (ap_uint<32>) x23_u7
						+ (ap_uint<32>) A23_u8 * (ap_uint<32>) x23_u8
						+ (ap_uint<32>) A23_u9 * (ap_uint<32>) x23_u9
						+ (ap_uint<32>) A23_u10 * (ap_uint<32>) x23_u10
						+ (ap_uint<32>) A23_u11 * (ap_uint<32>) x23_u11
						+ (ap_uint<32>) A23_u12 * (ap_uint<32>) x23_u12
						+ (ap_uint<32>) A23_u13 * (ap_uint<32>) x23_u13
						+ (ap_uint<32>) A23_u14 * (ap_uint<32>) x23_u14
						+ (ap_uint<32>) A23_u15 * (ap_uint<32>) x23_u15
						;
                        	}
				switch(i1){
					case 0 : 
						y512_0(31+32*0,32*0) = acc_y0;
						y512_1(31+32*0,32*0) = acc_y1;
						y512_2(31+32*0,32*0) = acc_y2;
						y512_3(31+32*0,32*0) = acc_y3;
						y512_4(31+32*0,32*0) = acc_y4;
						y512_5(31+32*0,32*0) = acc_y5;
						y512_6(31+32*0,32*0) = acc_y6;
						y512_7(31+32*0,32*0) = acc_y7;
						y512_8(31+32*0,32*0) = acc_y8;
						y512_9(31+32*0,32*0) = acc_y9;
						y512_10(31+32*0,32*0) = acc_y10;
						y512_11(31+32*0,32*0) = acc_y11;
						y512_12(31+32*0,32*0) = acc_y12;
						y512_13(31+32*0,32*0) = acc_y13;
						y512_14(31+32*0,32*0) = acc_y14;
						y512_15(31+32*0,32*0) = acc_y15;
						y512_16(31+32*0,32*0) = acc_y16;
						y512_17(31+32*0,32*0) = acc_y17;
						y512_18(31+32*0,32*0) = acc_y18;
						y512_19(31+32*0,32*0) = acc_y19;
						y512_20(31+32*0,32*0) = acc_y20;
						y512_21(31+32*0,32*0) = acc_y21;
						y512_22(31+32*0,32*0) = acc_y22;
						y512_23(31+32*0,32*0) = acc_y23;
						break;
					case 1 : 
						y512_0(31+32*1,32*1) = acc_y0;
						y512_1(31+32*1,32*1) = acc_y1;
						y512_2(31+32*1,32*1) = acc_y2;
						y512_3(31+32*1,32*1) = acc_y3;
						y512_4(31+32*1,32*1) = acc_y4;
						y512_5(31+32*1,32*1) = acc_y5;
						y512_6(31+32*1,32*1) = acc_y6;
						y512_7(31+32*1,32*1) = acc_y7;
						y512_8(31+32*1,32*1) = acc_y8;
						y512_9(31+32*1,32*1) = acc_y9;
						y512_10(31+32*1,32*1) = acc_y10;
						y512_11(31+32*1,32*1) = acc_y11;
						y512_12(31+32*1,32*1) = acc_y12;
						y512_13(31+32*1,32*1) = acc_y13;
						y512_14(31+32*1,32*1) = acc_y14;
						y512_15(31+32*1,32*1) = acc_y15;
						y512_16(31+32*1,32*1) = acc_y16;
						y512_17(31+32*1,32*1) = acc_y17;
						y512_18(31+32*1,32*1) = acc_y18;
						y512_19(31+32*1,32*1) = acc_y19;
						y512_20(31+32*1,32*1) = acc_y20;
						y512_21(31+32*1,32*1) = acc_y21;
						y512_22(31+32*1,32*1) = acc_y22;
						y512_23(31+32*1,32*1) = acc_y23;
						break;
					case 2 : 
						y512_0(31+32*2,32*2) = acc_y0;
						y512_1(31+32*2,32*2) = acc_y1;
						y512_2(31+32*2,32*2) = acc_y2;
						y512_3(31+32*2,32*2) = acc_y3;
						y512_4(31+32*2,32*2) = acc_y4;
						y512_5(31+32*2,32*2) = acc_y5;
						y512_6(31+32*2,32*2) = acc_y6;
						y512_7(31+32*2,32*2) = acc_y7;
						y512_8(31+32*2,32*2) = acc_y8;
						y512_9(31+32*2,32*2) = acc_y9;
						y512_10(31+32*2,32*2) = acc_y10;
						y512_11(31+32*2,32*2) = acc_y11;
						y512_12(31+32*2,32*2) = acc_y12;
						y512_13(31+32*2,32*2) = acc_y13;
						y512_14(31+32*2,32*2) = acc_y14;
						y512_15(31+32*2,32*2) = acc_y15;
						y512_16(31+32*2,32*2) = acc_y16;
						y512_17(31+32*2,32*2) = acc_y17;
						y512_18(31+32*2,32*2) = acc_y18;
						y512_19(31+32*2,32*2) = acc_y19;
						y512_20(31+32*2,32*2) = acc_y20;
						y512_21(31+32*2,32*2) = acc_y21;
						y512_22(31+32*2,32*2) = acc_y22;
						y512_23(31+32*2,32*2) = acc_y23;
						break;
					case 3 : 
						y512_0(31+32*3,32*3) = acc_y0;
						y512_1(31+32*3,32*3) = acc_y1;
						y512_2(31+32*3,32*3) = acc_y2;
						y512_3(31+32*3,32*3) = acc_y3;
						y512_4(31+32*3,32*3) = acc_y4;
						y512_5(31+32*3,32*3) = acc_y5;
						y512_6(31+32*3,32*3) = acc_y6;
						y512_7(31+32*3,32*3) = acc_y7;
						y512_8(31+32*3,32*3) = acc_y8;
						y512_9(31+32*3,32*3) = acc_y9;
						y512_10(31+32*3,32*3) = acc_y10;
						y512_11(31+32*3,32*3) = acc_y11;
						y512_12(31+32*3,32*3) = acc_y12;
						y512_13(31+32*3,32*3) = acc_y13;
						y512_14(31+32*3,32*3) = acc_y14;
						y512_15(31+32*3,32*3) = acc_y15;
						y512_16(31+32*3,32*3) = acc_y16;
						y512_17(31+32*3,32*3) = acc_y17;
						y512_18(31+32*3,32*3) = acc_y18;
						y512_19(31+32*3,32*3) = acc_y19;
						y512_20(31+32*3,32*3) = acc_y20;
						y512_21(31+32*3,32*3) = acc_y21;
						y512_22(31+32*3,32*3) = acc_y22;
						y512_23(31+32*3,32*3) = acc_y23;
						break;
					case 4 : 
						y512_0(31+32*4,32*4) = acc_y0;
						y512_1(31+32*4,32*4) = acc_y1;
						y512_2(31+32*4,32*4) = acc_y2;
						y512_3(31+32*4,32*4) = acc_y3;
						y512_4(31+32*4,32*4) = acc_y4;
						y512_5(31+32*4,32*4) = acc_y5;
						y512_6(31+32*4,32*4) = acc_y6;
						y512_7(31+32*4,32*4) = acc_y7;
						y512_8(31+32*4,32*4) = acc_y8;
						y512_9(31+32*4,32*4) = acc_y9;
						y512_10(31+32*4,32*4) = acc_y10;
						y512_11(31+32*4,32*4) = acc_y11;
						y512_12(31+32*4,32*4) = acc_y12;
						y512_13(31+32*4,32*4) = acc_y13;
						y512_14(31+32*4,32*4) = acc_y14;
						y512_15(31+32*4,32*4) = acc_y15;
						y512_16(31+32*4,32*4) = acc_y16;
						y512_17(31+32*4,32*4) = acc_y17;
						y512_18(31+32*4,32*4) = acc_y18;
						y512_19(31+32*4,32*4) = acc_y19;
						y512_20(31+32*4,32*4) = acc_y20;
						y512_21(31+32*4,32*4) = acc_y21;
						y512_22(31+32*4,32*4) = acc_y22;
						y512_23(31+32*4,32*4) = acc_y23;
						break;
					case 5 : 
						y512_0(31+32*5,32*5) = acc_y0;
						y512_1(31+32*5,32*5) = acc_y1;
						y512_2(31+32*5,32*5) = acc_y2;
						y512_3(31+32*5,32*5) = acc_y3;
						y512_4(31+32*5,32*5) = acc_y4;
						y512_5(31+32*5,32*5) = acc_y5;
						y512_6(31+32*5,32*5) = acc_y6;
						y512_7(31+32*5,32*5) = acc_y7;
						y512_8(31+32*5,32*5) = acc_y8;
						y512_9(31+32*5,32*5) = acc_y9;
						y512_10(31+32*5,32*5) = acc_y10;
						y512_11(31+32*5,32*5) = acc_y11;
						y512_12(31+32*5,32*5) = acc_y12;
						y512_13(31+32*5,32*5) = acc_y13;
						y512_14(31+32*5,32*5) = acc_y14;
						y512_15(31+32*5,32*5) = acc_y15;
						y512_16(31+32*5,32*5) = acc_y16;
						y512_17(31+32*5,32*5) = acc_y17;
						y512_18(31+32*5,32*5) = acc_y18;
						y512_19(31+32*5,32*5) = acc_y19;
						y512_20(31+32*5,32*5) = acc_y20;
						y512_21(31+32*5,32*5) = acc_y21;
						y512_22(31+32*5,32*5) = acc_y22;
						y512_23(31+32*5,32*5) = acc_y23;
						break;
					case 6 : 
						y512_0(31+32*6,32*6) = acc_y0;
						y512_1(31+32*6,32*6) = acc_y1;
						y512_2(31+32*6,32*6) = acc_y2;
						y512_3(31+32*6,32*6) = acc_y3;
						y512_4(31+32*6,32*6) = acc_y4;
						y512_5(31+32*6,32*6) = acc_y5;
						y512_6(31+32*6,32*6) = acc_y6;
						y512_7(31+32*6,32*6) = acc_y7;
						y512_8(31+32*6,32*6) = acc_y8;
						y512_9(31+32*6,32*6) = acc_y9;
						y512_10(31+32*6,32*6) = acc_y10;
						y512_11(31+32*6,32*6) = acc_y11;
						y512_12(31+32*6,32*6) = acc_y12;
						y512_13(31+32*6,32*6) = acc_y13;
						y512_14(31+32*6,32*6) = acc_y14;
						y512_15(31+32*6,32*6) = acc_y15;
						y512_16(31+32*6,32*6) = acc_y16;
						y512_17(31+32*6,32*6) = acc_y17;
						y512_18(31+32*6,32*6) = acc_y18;
						y512_19(31+32*6,32*6) = acc_y19;
						y512_20(31+32*6,32*6) = acc_y20;
						y512_21(31+32*6,32*6) = acc_y21;
						y512_22(31+32*6,32*6) = acc_y22;
						y512_23(31+32*6,32*6) = acc_y23;
						break;
					case 7 : 
						y512_0(31+32*7,32*7) = acc_y0;
						y512_1(31+32*7,32*7) = acc_y1;
						y512_2(31+32*7,32*7) = acc_y2;
						y512_3(31+32*7,32*7) = acc_y3;
						y512_4(31+32*7,32*7) = acc_y4;
						y512_5(31+32*7,32*7) = acc_y5;
						y512_6(31+32*7,32*7) = acc_y6;
						y512_7(31+32*7,32*7) = acc_y7;
						y512_8(31+32*7,32*7) = acc_y8;
						y512_9(31+32*7,32*7) = acc_y9;
						y512_10(31+32*7,32*7) = acc_y10;
						y512_11(31+32*7,32*7) = acc_y11;
						y512_12(31+32*7,32*7) = acc_y12;
						y512_13(31+32*7,32*7) = acc_y13;
						y512_14(31+32*7,32*7) = acc_y14;
						y512_15(31+32*7,32*7) = acc_y15;
						y512_16(31+32*7,32*7) = acc_y16;
						y512_17(31+32*7,32*7) = acc_y17;
						y512_18(31+32*7,32*7) = acc_y18;
						y512_19(31+32*7,32*7) = acc_y19;
						y512_20(31+32*7,32*7) = acc_y20;
						y512_21(31+32*7,32*7) = acc_y21;
						y512_22(31+32*7,32*7) = acc_y22;
						y512_23(31+32*7,32*7) = acc_y23;
						break;
					case 8 : 
						y512_0(31+32*8,32*8) = acc_y0;
						y512_1(31+32*8,32*8) = acc_y1;
						y512_2(31+32*8,32*8) = acc_y2;
						y512_3(31+32*8,32*8) = acc_y3;
						y512_4(31+32*8,32*8) = acc_y4;
						y512_5(31+32*8,32*8) = acc_y5;
						y512_6(31+32*8,32*8) = acc_y6;
						y512_7(31+32*8,32*8) = acc_y7;
						y512_8(31+32*8,32*8) = acc_y8;
						y512_9(31+32*8,32*8) = acc_y9;
						y512_10(31+32*8,32*8) = acc_y10;
						y512_11(31+32*8,32*8) = acc_y11;
						y512_12(31+32*8,32*8) = acc_y12;
						y512_13(31+32*8,32*8) = acc_y13;
						y512_14(31+32*8,32*8) = acc_y14;
						y512_15(31+32*8,32*8) = acc_y15;
						y512_16(31+32*8,32*8) = acc_y16;
						y512_17(31+32*8,32*8) = acc_y17;
						y512_18(31+32*8,32*8) = acc_y18;
						y512_19(31+32*8,32*8) = acc_y19;
						y512_20(31+32*8,32*8) = acc_y20;
						y512_21(31+32*8,32*8) = acc_y21;
						y512_22(31+32*8,32*8) = acc_y22;
						y512_23(31+32*8,32*8) = acc_y23;
						break;
					case 9 : 
						y512_0(31+32*9,32*9) = acc_y0;
						y512_1(31+32*9,32*9) = acc_y1;
						y512_2(31+32*9,32*9) = acc_y2;
						y512_3(31+32*9,32*9) = acc_y3;
						y512_4(31+32*9,32*9) = acc_y4;
						y512_5(31+32*9,32*9) = acc_y5;
						y512_6(31+32*9,32*9) = acc_y6;
						y512_7(31+32*9,32*9) = acc_y7;
						y512_8(31+32*9,32*9) = acc_y8;
						y512_9(31+32*9,32*9) = acc_y9;
						y512_10(31+32*9,32*9) = acc_y10;
						y512_11(31+32*9,32*9) = acc_y11;
						y512_12(31+32*9,32*9) = acc_y12;
						y512_13(31+32*9,32*9) = acc_y13;
						y512_14(31+32*9,32*9) = acc_y14;
						y512_15(31+32*9,32*9) = acc_y15;
						y512_16(31+32*9,32*9) = acc_y16;
						y512_17(31+32*9,32*9) = acc_y17;
						y512_18(31+32*9,32*9) = acc_y18;
						y512_19(31+32*9,32*9) = acc_y19;
						y512_20(31+32*9,32*9) = acc_y20;
						y512_21(31+32*9,32*9) = acc_y21;
						y512_22(31+32*9,32*9) = acc_y22;
						y512_23(31+32*9,32*9) = acc_y23;
						break;
					case 10 : 
						y512_0(31+32*10,32*10) = acc_y0;
						y512_1(31+32*10,32*10) = acc_y1;
						y512_2(31+32*10,32*10) = acc_y2;
						y512_3(31+32*10,32*10) = acc_y3;
						y512_4(31+32*10,32*10) = acc_y4;
						y512_5(31+32*10,32*10) = acc_y5;
						y512_6(31+32*10,32*10) = acc_y6;
						y512_7(31+32*10,32*10) = acc_y7;
						y512_8(31+32*10,32*10) = acc_y8;
						y512_9(31+32*10,32*10) = acc_y9;
						y512_10(31+32*10,32*10) = acc_y10;
						y512_11(31+32*10,32*10) = acc_y11;
						y512_12(31+32*10,32*10) = acc_y12;
						y512_13(31+32*10,32*10) = acc_y13;
						y512_14(31+32*10,32*10) = acc_y14;
						y512_15(31+32*10,32*10) = acc_y15;
						y512_16(31+32*10,32*10) = acc_y16;
						y512_17(31+32*10,32*10) = acc_y17;
						y512_18(31+32*10,32*10) = acc_y18;
						y512_19(31+32*10,32*10) = acc_y19;
						y512_20(31+32*10,32*10) = acc_y20;
						y512_21(31+32*10,32*10) = acc_y21;
						y512_22(31+32*10,32*10) = acc_y22;
						y512_23(31+32*10,32*10) = acc_y23;
						break;
					case 11 : 
						y512_0(31+32*11,32*11) = acc_y0;
						y512_1(31+32*11,32*11) = acc_y1;
						y512_2(31+32*11,32*11) = acc_y2;
						y512_3(31+32*11,32*11) = acc_y3;
						y512_4(31+32*11,32*11) = acc_y4;
						y512_5(31+32*11,32*11) = acc_y5;
						y512_6(31+32*11,32*11) = acc_y6;
						y512_7(31+32*11,32*11) = acc_y7;
						y512_8(31+32*11,32*11) = acc_y8;
						y512_9(31+32*11,32*11) = acc_y9;
						y512_10(31+32*11,32*11) = acc_y10;
						y512_11(31+32*11,32*11) = acc_y11;
						y512_12(31+32*11,32*11) = acc_y12;
						y512_13(31+32*11,32*11) = acc_y13;
						y512_14(31+32*11,32*11) = acc_y14;
						y512_15(31+32*11,32*11) = acc_y15;
						y512_16(31+32*11,32*11) = acc_y16;
						y512_17(31+32*11,32*11) = acc_y17;
						y512_18(31+32*11,32*11) = acc_y18;
						y512_19(31+32*11,32*11) = acc_y19;
						y512_20(31+32*11,32*11) = acc_y20;
						y512_21(31+32*11,32*11) = acc_y21;
						y512_22(31+32*11,32*11) = acc_y22;
						y512_23(31+32*11,32*11) = acc_y23;
						break;
					case 12 : 
						y512_0(31+32*12,32*12) = acc_y0;
						y512_1(31+32*12,32*12) = acc_y1;
						y512_2(31+32*12,32*12) = acc_y2;
						y512_3(31+32*12,32*12) = acc_y3;
						y512_4(31+32*12,32*12) = acc_y4;
						y512_5(31+32*12,32*12) = acc_y5;
						y512_6(31+32*12,32*12) = acc_y6;
						y512_7(31+32*12,32*12) = acc_y7;
						y512_8(31+32*12,32*12) = acc_y8;
						y512_9(31+32*12,32*12) = acc_y9;
						y512_10(31+32*12,32*12) = acc_y10;
						y512_11(31+32*12,32*12) = acc_y11;
						y512_12(31+32*12,32*12) = acc_y12;
						y512_13(31+32*12,32*12) = acc_y13;
						y512_14(31+32*12,32*12) = acc_y14;
						y512_15(31+32*12,32*12) = acc_y15;
						y512_16(31+32*12,32*12) = acc_y16;
						y512_17(31+32*12,32*12) = acc_y17;
						y512_18(31+32*12,32*12) = acc_y18;
						y512_19(31+32*12,32*12) = acc_y19;
						y512_20(31+32*12,32*12) = acc_y20;
						y512_21(31+32*12,32*12) = acc_y21;
						y512_22(31+32*12,32*12) = acc_y22;
						y512_23(31+32*12,32*12) = acc_y23;
						break;
					case 13 : 
						y512_0(31+32*13,32*13) = acc_y0;
						y512_1(31+32*13,32*13) = acc_y1;
						y512_2(31+32*13,32*13) = acc_y2;
						y512_3(31+32*13,32*13) = acc_y3;
						y512_4(31+32*13,32*13) = acc_y4;
						y512_5(31+32*13,32*13) = acc_y5;
						y512_6(31+32*13,32*13) = acc_y6;
						y512_7(31+32*13,32*13) = acc_y7;
						y512_8(31+32*13,32*13) = acc_y8;
						y512_9(31+32*13,32*13) = acc_y9;
						y512_10(31+32*13,32*13) = acc_y10;
						y512_11(31+32*13,32*13) = acc_y11;
						y512_12(31+32*13,32*13) = acc_y12;
						y512_13(31+32*13,32*13) = acc_y13;
						y512_14(31+32*13,32*13) = acc_y14;
						y512_15(31+32*13,32*13) = acc_y15;
						y512_16(31+32*13,32*13) = acc_y16;
						y512_17(31+32*13,32*13) = acc_y17;
						y512_18(31+32*13,32*13) = acc_y18;
						y512_19(31+32*13,32*13) = acc_y19;
						y512_20(31+32*13,32*13) = acc_y20;
						y512_21(31+32*13,32*13) = acc_y21;
						y512_22(31+32*13,32*13) = acc_y22;
						y512_23(31+32*13,32*13) = acc_y23;
						break;
					case 14 : 
						y512_0(31+32*14,32*14) = acc_y0;
						y512_1(31+32*14,32*14) = acc_y1;
						y512_2(31+32*14,32*14) = acc_y2;
						y512_3(31+32*14,32*14) = acc_y3;
						y512_4(31+32*14,32*14) = acc_y4;
						y512_5(31+32*14,32*14) = acc_y5;
						y512_6(31+32*14,32*14) = acc_y6;
						y512_7(31+32*14,32*14) = acc_y7;
						y512_8(31+32*14,32*14) = acc_y8;
						y512_9(31+32*14,32*14) = acc_y9;
						y512_10(31+32*14,32*14) = acc_y10;
						y512_11(31+32*14,32*14) = acc_y11;
						y512_12(31+32*14,32*14) = acc_y12;
						y512_13(31+32*14,32*14) = acc_y13;
						y512_14(31+32*14,32*14) = acc_y14;
						y512_15(31+32*14,32*14) = acc_y15;
						y512_16(31+32*14,32*14) = acc_y16;
						y512_17(31+32*14,32*14) = acc_y17;
						y512_18(31+32*14,32*14) = acc_y18;
						y512_19(31+32*14,32*14) = acc_y19;
						y512_20(31+32*14,32*14) = acc_y20;
						y512_21(31+32*14,32*14) = acc_y21;
						y512_22(31+32*14,32*14) = acc_y22;
						y512_23(31+32*14,32*14) = acc_y23;
						break;
					case 15 : 
						y512_0(31+32*15,32*15) = acc_y0;
						y512_1(31+32*15,32*15) = acc_y1;
						y512_2(31+32*15,32*15) = acc_y2;
						y512_3(31+32*15,32*15) = acc_y3;
						y512_4(31+32*15,32*15) = acc_y4;
						y512_5(31+32*15,32*15) = acc_y5;
						y512_6(31+32*15,32*15) = acc_y6;
						y512_7(31+32*15,32*15) = acc_y7;
						y512_8(31+32*15,32*15) = acc_y8;
						y512_9(31+32*15,32*15) = acc_y9;
						y512_10(31+32*15,32*15) = acc_y10;
						y512_11(31+32*15,32*15) = acc_y11;
						y512_12(31+32*15,32*15) = acc_y12;
						y512_13(31+32*15,32*15) = acc_y13;
						y512_14(31+32*15,32*15) = acc_y14;
						y512_15(31+32*15,32*15) = acc_y15;
						y512_16(31+32*15,32*15) = acc_y16;
						y512_17(31+32*15,32*15) = acc_y17;
						y512_18(31+32*15,32*15) = acc_y18;
						y512_19(31+32*15,32*15) = acc_y19;
						y512_20(31+32*15,32*15) = acc_y20;
						y512_21(31+32*15,32*15) = acc_y21;
						y512_22(31+32*15,32*15) = acc_y22;
						y512_23(31+32*15,32*15) = acc_y23;
						break;
				}
        	        }

			fifo_y.write(y512_0);
			fifo_y.write(y512_1);
			fifo_y.write(y512_2);
			fifo_y.write(y512_3);
			fifo_y.write(y512_4);
			fifo_y.write(y512_5);
			fifo_y.write(y512_6);
			fifo_y.write(y512_7);
			fifo_y.write(y512_8);
			fifo_y.write(y512_9);
			fifo_y.write(y512_10);
			fifo_y.write(y512_11);
			fifo_y.write(y512_12);
			fifo_y.write(y512_13);
			fifo_y.write(y512_14);
			fifo_y.write(y512_15);
			fifo_y.write(y512_16);
			fifo_y.write(y512_17);
			fifo_y.write(y512_18);
			fifo_y.write(y512_19);
			fifo_y.write(y512_20);
			fifo_y.write(y512_21);
			fifo_y.write(y512_22);
			fifo_y.write(y512_23);
		}
        }
}

void x_read(
  const ap_uint<512> *x,
  hls::stream<ap_uint<512> >& fifo_x, 
  int matrix_size
)
{
        for(int i = 0 ; i < matrix_size/16 ; i++ ){
#pragma HLS pipeline
		ap_uint<512> x_temp = HLS_REG(HLS_REG(x[i]));
		fifo_x.write(x_temp);
	}
}

void y_write(
  ap_uint<512>  *y,
  hls::stream<ap_uint<512> >& fifo_y, 
  int matrix_size,
  int repeat_num
)
{
	for(int r = 0 ; r < repeat_num ; r++){
#pragma HLS loop_flatten off
	        for(int i = 0 ; i < matrix_size/24/16 ; i++ ){
			for (int ch = 0; ch < 24; ch++){
#pragma HLS pipeline
				ap_uint<512>  y_temp = fifo_y.read();
				y[ch*matrix_size/24/16+i] = HLS_REG(HLS_REG(y_temp));
			}
		}
	}
}

#ifndef HLS
extern "C" {
#endif

void vadd(
  const ap_uint<512> *A0, 
  const ap_uint<512> *A1, 
  const ap_uint<512> *A2, 
  const ap_uint<512> *A3, 
  const ap_uint<512> *A4, 
  const ap_uint<512> *A5, 
  const ap_uint<512> *A6, 
  const ap_uint<512> *A7, 
  const ap_uint<512> *A8, 
  const ap_uint<512> *A9, 
  const ap_uint<512> *A10, 
  const ap_uint<512> *A11, 
  const ap_uint<512> *A12, 
  const ap_uint<512> *A13, 
  const ap_uint<512> *A14, 
  const ap_uint<512> *A15, 
  const ap_uint<512> *A16, 
  const ap_uint<512> *A17, 
  const ap_uint<512> *A18, 
  const ap_uint<512> *A19, 
  const ap_uint<512> *A20, 
  const ap_uint<512> *A21, 
  const ap_uint<512> *A22, 
  const ap_uint<512> *A23, 
  const ap_uint<512> *x,
  ap_uint<512>  *y,
  int matrix_size,
  int repeat_num
) {
// Here Vitis kernel contains one s_axilite interface which will be used by host application to configure the kernel.
// Here bundle control is defined which is s_axilite interface and associated with all the arguments (in1, in2, out_r and data_num),
// control interface must also be associated with "return".
// All the global memory access arguments must be associated to one m_axi(AXI Master Interface). Here all three arguments(in1, in2, out_r) are
// associated to bundle gmem which means that a AXI master interface named "gmem" will be created in Kernel and all these variables will be
// accessing global memory through this interface.
// Multiple interfaces can also be created based on the requirements. For example when multiple memory accessing arguments need access to
// global memory simultaneously, user can create multiple master interfaces and can connect to different arguments.

#pragma HLS INTERFACE m_axi port = A0 offset = slave bundle = hbm0  
#pragma HLS INTERFACE m_axi port = A1 offset = slave bundle = hbm1  
#pragma HLS INTERFACE m_axi port = A2 offset = slave bundle = hbm2  
#pragma HLS INTERFACE m_axi port = A3 offset = slave bundle = hbm3  
#pragma HLS INTERFACE m_axi port = A4 offset = slave bundle = hbm4  
#pragma HLS INTERFACE m_axi port = A5 offset = slave bundle = hbm5  
#pragma HLS INTERFACE m_axi port = A6 offset = slave bundle = hbm6  
#pragma HLS INTERFACE m_axi port = A7 offset = slave bundle = hbm7  
#pragma HLS INTERFACE m_axi port = A8 offset = slave bundle = hbm8  
#pragma HLS INTERFACE m_axi port = A9 offset = slave bundle = hbm9  
#pragma HLS INTERFACE m_axi port = A10 offset = slave bundle = hbm10  
#pragma HLS INTERFACE m_axi port = A11 offset = slave bundle = hbm11  
#pragma HLS INTERFACE m_axi port = A12 offset = slave bundle = hbm12  
#pragma HLS INTERFACE m_axi port = A13 offset = slave bundle = hbm13  
#pragma HLS INTERFACE m_axi port = A14 offset = slave bundle = hbm14  
#pragma HLS INTERFACE m_axi port = A15 offset = slave bundle = hbm15  
#pragma HLS INTERFACE m_axi port = A16 offset = slave bundle = hbm16  
#pragma HLS INTERFACE m_axi port = A17 offset = slave bundle = hbm17  
#pragma HLS INTERFACE m_axi port = A18 offset = slave bundle = hbm18  
#pragma HLS INTERFACE m_axi port = A19 offset = slave bundle = hbm19  
#pragma HLS INTERFACE m_axi port = A20 offset = slave bundle = hbm20  
#pragma HLS INTERFACE m_axi port = A21 offset = slave bundle = hbm21  
#pragma HLS INTERFACE m_axi port = A22 offset = slave bundle = hbm22  
#pragma HLS INTERFACE m_axi port = A23 offset = slave bundle = hbm23  

#pragma HLS INTERFACE m_axi port = x offset = slave bundle = hbm_xy 
#pragma HLS INTERFACE m_axi port = y offset = slave bundle = hbm_xy

#pragma HLS INTERFACE s_axilite port = matrix_size bundle = control
#pragma HLS INTERFACE s_axilite port = repeat_num bundle = control
#pragma HLS INTERFACE s_axilite port = return bundle = control

#pragma HLS dataflow

  hls::stream<ap_uint<512> > fifo_A0 ;   
  hls::stream<ap_uint<512> > fifo_A1 ;   
  hls::stream<ap_uint<512> > fifo_A2 ;   
  hls::stream<ap_uint<512> > fifo_A3 ;   
  hls::stream<ap_uint<512> > fifo_A4 ;   
  hls::stream<ap_uint<512> > fifo_A5 ;   
  hls::stream<ap_uint<512> > fifo_A6 ;   
  hls::stream<ap_uint<512> > fifo_A7 ;   
  hls::stream<ap_uint<512> > fifo_A8 ;   
  hls::stream<ap_uint<512> > fifo_A9 ;   
  hls::stream<ap_uint<512> > fifo_A10 ;   
  hls::stream<ap_uint<512> > fifo_A11 ;   
  hls::stream<ap_uint<512> > fifo_A12 ;   
  hls::stream<ap_uint<512> > fifo_A13 ;   
  hls::stream<ap_uint<512> > fifo_A14 ;   
  hls::stream<ap_uint<512> > fifo_A15 ;   
  hls::stream<ap_uint<512> > fifo_A16 ;   
  hls::stream<ap_uint<512> > fifo_A17 ;   
  hls::stream<ap_uint<512> > fifo_A18 ;   
  hls::stream<ap_uint<512> > fifo_A19 ;   
  hls::stream<ap_uint<512> > fifo_A20 ;   
  hls::stream<ap_uint<512> > fifo_A21 ;   
  hls::stream<ap_uint<512> > fifo_A22 ;   
  hls::stream<ap_uint<512> > fifo_A23 ;   
  hls::stream<ap_uint<512> > fifo_x;   
  hls::stream<ap_uint<512> > fifo_y; 


#pragma HLS STREAM variable=fifo_A0  depth=2 dim=1
#pragma HLS STREAM variable=fifo_A1  depth=2 dim=1
#pragma HLS STREAM variable=fifo_A2  depth=2 dim=1
#pragma HLS STREAM variable=fifo_A3  depth=2 dim=1
#pragma HLS STREAM variable=fifo_A4  depth=2 dim=1
#pragma HLS STREAM variable=fifo_A5  depth=2 dim=1
#pragma HLS STREAM variable=fifo_A6  depth=2 dim=1
#pragma HLS STREAM variable=fifo_A7  depth=2 dim=1
#pragma HLS STREAM variable=fifo_A8  depth=2 dim=1
#pragma HLS STREAM variable=fifo_A9  depth=2 dim=1
#pragma HLS STREAM variable=fifo_A10  depth=2 dim=1
#pragma HLS STREAM variable=fifo_A11  depth=2 dim=1
#pragma HLS STREAM variable=fifo_A12  depth=2 dim=1
#pragma HLS STREAM variable=fifo_A13  depth=2 dim=1
#pragma HLS STREAM variable=fifo_A14  depth=2 dim=1
#pragma HLS STREAM variable=fifo_A15  depth=2 dim=1
#pragma HLS STREAM variable=fifo_A16  depth=2 dim=1
#pragma HLS STREAM variable=fifo_A17  depth=2 dim=1
#pragma HLS STREAM variable=fifo_A18  depth=2 dim=1
#pragma HLS STREAM variable=fifo_A19  depth=2 dim=1
#pragma HLS STREAM variable=fifo_A20  depth=2 dim=1
#pragma HLS STREAM variable=fifo_A21  depth=2 dim=1
#pragma HLS STREAM variable=fifo_A22  depth=2 dim=1
#pragma HLS STREAM variable=fifo_A23  depth=2 dim=1
#pragma HLS RESOURCE variable=fifo_A0 core=FIFO_SRL
#pragma HLS RESOURCE variable=fifo_A1 core=FIFO_SRL
#pragma HLS RESOURCE variable=fifo_A2 core=FIFO_SRL
#pragma HLS RESOURCE variable=fifo_A3 core=FIFO_SRL
#pragma HLS RESOURCE variable=fifo_A4 core=FIFO_SRL
#pragma HLS RESOURCE variable=fifo_A5 core=FIFO_SRL
#pragma HLS RESOURCE variable=fifo_A6 core=FIFO_SRL
#pragma HLS RESOURCE variable=fifo_A7 core=FIFO_SRL
#pragma HLS RESOURCE variable=fifo_A8 core=FIFO_SRL
#pragma HLS RESOURCE variable=fifo_A9 core=FIFO_SRL
#pragma HLS RESOURCE variable=fifo_A10 core=FIFO_SRL
#pragma HLS RESOURCE variable=fifo_A11 core=FIFO_SRL
#pragma HLS RESOURCE variable=fifo_A12 core=FIFO_SRL
#pragma HLS RESOURCE variable=fifo_A13 core=FIFO_SRL
#pragma HLS RESOURCE variable=fifo_A14 core=FIFO_SRL
#pragma HLS RESOURCE variable=fifo_A15 core=FIFO_SRL
#pragma HLS RESOURCE variable=fifo_A16 core=FIFO_SRL
#pragma HLS RESOURCE variable=fifo_A17 core=FIFO_SRL
#pragma HLS RESOURCE variable=fifo_A18 core=FIFO_SRL
#pragma HLS RESOURCE variable=fifo_A19 core=FIFO_SRL
#pragma HLS RESOURCE variable=fifo_A20 core=FIFO_SRL
#pragma HLS RESOURCE variable=fifo_A21 core=FIFO_SRL
#pragma HLS RESOURCE variable=fifo_A22 core=FIFO_SRL
#pragma HLS RESOURCE variable=fifo_A23 core=FIFO_SRL

#pragma HLS STREAM variable=fifo_x depth=2 dim=1
#pragma HLS RESOURCE variable=fifo_x core=FIFO_SRL
#pragma HLS STREAM variable=fifo_y  depth=24 dim=1
#pragma HLS RESOURCE variable=fifo_y core=FIFO_SRL

  x_read(
    x,
    fifo_x, 
    matrix_size
  );

  readA(
    A0, fifo_A0,
    matrix_size,
    repeat_num
  );
  readA(
    A1, fifo_A1,
    matrix_size,
    repeat_num
  );
  readA(
    A2, fifo_A2,
    matrix_size,
    repeat_num
  );
  readA(
    A3, fifo_A3,
    matrix_size,
    repeat_num
  );
  readA(
    A4, fifo_A4,
    matrix_size,
    repeat_num
  );
  readA(
    A5, fifo_A5,
    matrix_size,
    repeat_num
  );
  readA(
    A6, fifo_A6,
    matrix_size,
    repeat_num
  );
  readA(
    A7, fifo_A7,
    matrix_size,
    repeat_num
  );
  readA(
    A8, fifo_A8,
    matrix_size,
    repeat_num
  );
  readA(
    A9, fifo_A9,
    matrix_size,
    repeat_num
  );
  readA(
    A10, fifo_A10,
    matrix_size,
    repeat_num
  );
  readA(
    A11, fifo_A11,
    matrix_size,
    repeat_num
  );
  readA(
    A12, fifo_A12,
    matrix_size,
    repeat_num
  );
  readA(
    A13, fifo_A13,
    matrix_size,
    repeat_num
  );
  readA(
    A14, fifo_A14,
    matrix_size,
    repeat_num
  );
  readA(
    A15, fifo_A15,
    matrix_size,
    repeat_num
  );
  readA(
    A16, fifo_A16,
    matrix_size,
    repeat_num
  );
  readA(
    A17, fifo_A17,
    matrix_size,
    repeat_num
  );
  readA(
    A18, fifo_A18,
    matrix_size,
    repeat_num
  );
  readA(
    A19, fifo_A19,
    matrix_size,
    repeat_num
  );
  readA(
    A20, fifo_A20,
    matrix_size,
    repeat_num
  );
  readA(
    A21, fifo_A21,
    matrix_size,
    repeat_num
  );
  readA(
    A22, fifo_A22,
    matrix_size,
    repeat_num
  );
  readA(
    A23, fifo_A23,
    matrix_size,
    repeat_num
  );

  mv(
    fifo_A0, 
    fifo_A1, 
    fifo_A2, 
    fifo_A3, 
    fifo_A4, 
    fifo_A5, 
    fifo_A6, 
    fifo_A7, 
    fifo_A8, 
    fifo_A9, 
    fifo_A10, 
    fifo_A11, 
    fifo_A12, 
    fifo_A13, 
    fifo_A14, 
    fifo_A15, 
    fifo_A16, 
    fifo_A17, 
    fifo_A18, 
    fifo_A19, 
    fifo_A20, 
    fifo_A21, 
    fifo_A22, 
    fifo_A23, 
    fifo_x, 
    fifo_y,
    matrix_size,
    repeat_num
  );

  y_write( 
    y,
    fifo_y, 
    matrix_size,
    repeat_num
  );

}
#ifndef HLS
} // end of extern C
#endif
