

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
  const ap_uint<512> *src,
  hls::stream<ap_uint<512> >& dst, 
  int repeat_num, int data_num
) {
	for (int r = 0; r < repeat_num; r++) {
#pragma HLS loop_flatten off
		for (int i = 0; i < data_num; i++) {
#pragma HLS pipeline II=1
			ap_uint<512> temp = src[i];
			ap_uint<512> temp_delayed = HLS_REG(HLS_REG(temp));

			dst.write(temp_delayed);
		}
	}

	ap_uint<512> terminate_data = ((ap_uint<512>)1)<<511;
	dst.write(terminate_data);

}

void read_dummy(
  hls::stream<ap_uint<512> >& dst 
) {
	ap_uint<512> terminate_data = ((ap_uint<512>)1)<<511;
	dst.write(terminate_data);
}









void bica_dummy(
  hls::stream<ap_uint<512> >& src 
)
{
	ap_uint<512> read_data;
	read_data = src.read();
}

void bica(
  hls::stream<ap_uint<512> >& dst0, 
  hls::stream<ap_uint<512> >& dst1, 
  hls::stream<ap_uint<512> >& dst2, 
  hls::stream<ap_uint<512> >& dst3, 
  hls::stream<ap_uint<512> >& dst4, 
  hls::stream<ap_uint<512> >& dst5, 
  hls::stream<ap_uint<512> >& dst6, 
  hls::stream<ap_uint<512> >& dst7, 
  hls::stream<ap_uint<512> >& src 
) 
{
	ap_uint<1> terminate = 0;
	ap_uint<6> cnt0 = 0;
	ap_uint<6> cnt1 = 0;
	ap_uint<6> cnt2 = 0;
	ap_uint<6> cnt3 = 0;
	ap_uint<6> cnt4 = 0;
	ap_uint<6> cnt5 = 0;
	ap_uint<6> cnt6 = 0;
	ap_uint<6> cnt7 = 0;
	while(terminate == 0){
#pragma HLS pipeline II=1			
		ap_uint<512> read_data;
	       	bool success = src.read_nb(read_data);
		terminate = read_data(512 - 1,512 - 1);

		ap_uint<512> read_data_delayed = HLS_REG(HLS_REG(read_data));
		if( success == true && read_data_delayed(512 - 1,512 - 1) == 0 ){
			ap_uint<3> write_ch = read_data_delayed(21 - 0 - 1,21 - 3);
			switch(write_ch){
				case 0:
					dst0.write(read_data_delayed);
					cnt0 ++;
					break;
				case 1:
					dst1.write(read_data_delayed);
					cnt1 ++;
					break;
				case 2:
					dst2.write(read_data_delayed);
					cnt2 ++;
					break;
				case 3:
					dst3.write(read_data_delayed);
					cnt3 ++;
					break;
				case 4:
					dst4.write(read_data_delayed);
					cnt4 ++;
					break;
				case 5:
					dst5.write(read_data_delayed);
					cnt5 ++;
					break;
				case 6:
					dst6.write(read_data_delayed);
					cnt6 ++;
					break;
				default:
					dst7.write(read_data_delayed);
					cnt7 ++;
					break;
			}
		}
	}

	ap_uint<512> terminate_data = ((ap_uint<512>)1)<<(512-1); 

	for(int i = cnt0; i < 64; i++ ){
        	dst0.write( terminate_data );
	}
	for(int i = cnt1; i < 64; i++ ){
        	dst1.write( terminate_data );
	}
	for(int i = cnt2; i < 64; i++ ){
        	dst2.write( terminate_data );
	}
	for(int i = cnt3; i < 64; i++ ){
        	dst3.write( terminate_data );
	}
	for(int i = cnt4; i < 64; i++ ){
        	dst4.write( terminate_data );
	}
	for(int i = cnt5; i < 64; i++ ){
        	dst5.write( terminate_data );
	}
	for(int i = cnt6; i < 64; i++ ){
        	dst6.write( terminate_data );
	}
	for(int i = cnt7; i < 64; i++ ){
        	dst7.write( terminate_data );
	}
}

void write(
  hls::stream<ap_uint<512> >& src0, 
  hls::stream<ap_uint<512> >& src1, 
  hls::stream<ap_uint<512> >& src2, 
  hls::stream<ap_uint<512> >& src3, 
  hls::stream<ap_uint<512> >& src4, 
  hls::stream<ap_uint<512> >& src5, 
  hls::stream<ap_uint<512> >& src6, 
  hls::stream<ap_uint<512> >& src7, 
  ap_uint<512> *dst0, 
  ap_uint<512> *dst1, 
  ap_uint<512> *dst2, 
  ap_uint<512> *dst3, 
  ap_uint<512> *dst4, 
  ap_uint<512> *dst5, 
  ap_uint<512> *dst6, 
  ap_uint<512> *dst7, 
  int zero
) 
{
	ap_uint<1> terminate0 = 0;
	ap_uint<18> offset0 = 0;
	ap_uint<1> terminate1 = 0;
	ap_uint<18> offset1 = 0;
	ap_uint<1> terminate2 = 0;
	ap_uint<18> offset2 = 0;
	ap_uint<1> terminate3 = 0;
	ap_uint<18> offset3 = 0;
	ap_uint<1> terminate4 = 0;
	ap_uint<18> offset4 = 0;
	ap_uint<1> terminate5 = 0;
	ap_uint<18> offset5 = 0;
	ap_uint<1> terminate6 = 0;
	ap_uint<18> offset6 = 0;
	ap_uint<1> terminate7 = 0;
	ap_uint<18> offset7 = 0;
	while(
		terminate0 == 0 ||
		terminate1 == 0 ||
		terminate2 == 0 ||
		terminate3 == 0 ||
		terminate4 == 0 ||
		terminate5 == 0 ||
		terminate6 == 0 ||
		terminate7 == 0 ||
		0
	){
		if( terminate0 == 0 ){
			for (int i = 0; i < 64; i++) {
#pragma HLS pipeline II=1
				ap_uint<512> temp = src0.read();
				ap_uint<512> temp_delayed = HLS_REG(HLS_REG(temp));
       		         	if( temp_delayed(512-1,512-1) == true ){
					terminate0 = true;
				}
				dst0[offset0+i] = temp_delayed;
			}
			offset0 += 64;
		}
		if( terminate1 == 0 ){
			for (int i = 0; i < 64; i++) {
#pragma HLS pipeline II=1
				ap_uint<512> temp = src1.read();
				ap_uint<512> temp_delayed = HLS_REG(HLS_REG(temp));
       		         	if( temp_delayed(512-1,512-1) == true ){
					terminate1 = true;
				}
				dst1[offset1+i] = temp_delayed;
			}
			offset1 += 64;
		}
		if( terminate2 == 0 ){
			for (int i = 0; i < 64; i++) {
#pragma HLS pipeline II=1
				ap_uint<512> temp = src2.read();
				ap_uint<512> temp_delayed = HLS_REG(HLS_REG(temp));
       		         	if( temp_delayed(512-1,512-1) == true ){
					terminate2 = true;
				}
				dst2[offset2+i] = temp_delayed;
			}
			offset2 += 64;
		}
		if( terminate3 == 0 ){
			for (int i = 0; i < 64; i++) {
#pragma HLS pipeline II=1
				ap_uint<512> temp = src3.read();
				ap_uint<512> temp_delayed = HLS_REG(HLS_REG(temp));
       		         	if( temp_delayed(512-1,512-1) == true ){
					terminate3 = true;
				}
				dst3[offset3+i] = temp_delayed;
			}
			offset3 += 64;
		}
		if( terminate4 == 0 ){
			for (int i = 0; i < 64; i++) {
#pragma HLS pipeline II=1
				ap_uint<512> temp = src4.read();
				ap_uint<512> temp_delayed = HLS_REG(HLS_REG(temp));
       		         	if( temp_delayed(512-1,512-1) == true ){
					terminate4 = true;
				}
				dst4[offset4+i] = temp_delayed;
			}
			offset4 += 64;
		}
		if( terminate5 == 0 ){
			for (int i = 0; i < 64; i++) {
#pragma HLS pipeline II=1
				ap_uint<512> temp = src5.read();
				ap_uint<512> temp_delayed = HLS_REG(HLS_REG(temp));
       		         	if( temp_delayed(512-1,512-1) == true ){
					terminate5 = true;
				}
				dst5[offset5+i] = temp_delayed;
			}
			offset5 += 64;
		}
		if( terminate6 == 0 ){
			for (int i = 0; i < 64; i++) {
#pragma HLS pipeline II=1
				ap_uint<512> temp = src6.read();
				ap_uint<512> temp_delayed = HLS_REG(HLS_REG(temp));
       		         	if( temp_delayed(512-1,512-1) == true ){
					terminate6 = true;
				}
				dst6[offset6+i] = temp_delayed;
			}
			offset6 += 64;
		}
		if( terminate7 == 0 ){
			for (int i = 0; i < 64; i++) {
#pragma HLS pipeline II=1
				ap_uint<512> temp = src7.read();
				ap_uint<512> temp_delayed = HLS_REG(HLS_REG(temp));
       		         	if( temp_delayed(512-1,512-1) == true ){
					terminate7 = true;
				}
				dst7[offset7+i] = temp_delayed;
			}
			offset7 += 64;
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
  int data_num 
) {

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
#pragma HLS INTERFACE s_axilite port = return bundle = control

#pragma HLS dataflow

        hls::stream<ap_uint<512> > key_ch0_stage0;
        hls::stream<ap_uint<512> > key_ch0_stage0_0;
        hls::stream<ap_uint<512> > key_ch0_stage0_1;
#pragma HLS STREAM variable=key_ch0_stage0    depth=16 dim=1
#pragma HLS STREAM variable=key_ch0_stage0_0  depth=16 dim=1
#pragma HLS STREAM variable=key_ch0_stage0_1  depth=16 dim=1
#pragma HLS RESOURCE variable=key_ch0_stage0   core=FIFO_SRL
#pragma HLS RESOURCE variable=key_ch0_stage0_0 core=FIFO_SRL
#pragma HLS RESOURCE variable=key_ch0_stage0_1 core=FIFO_SRL
        hls::stream<ap_uint<512> > key_ch1_stage0;
        hls::stream<ap_uint<512> > key_ch1_stage0_0;
        hls::stream<ap_uint<512> > key_ch1_stage0_1;
#pragma HLS STREAM variable=key_ch1_stage0    depth=16 dim=1
#pragma HLS STREAM variable=key_ch1_stage0_0  depth=16 dim=1
#pragma HLS STREAM variable=key_ch1_stage0_1  depth=16 dim=1
#pragma HLS RESOURCE variable=key_ch1_stage0   core=FIFO_SRL
#pragma HLS RESOURCE variable=key_ch1_stage0_0 core=FIFO_SRL
#pragma HLS RESOURCE variable=key_ch1_stage0_1 core=FIFO_SRL
        hls::stream<ap_uint<512> > key_ch2_stage0;
        hls::stream<ap_uint<512> > key_ch2_stage0_0;
        hls::stream<ap_uint<512> > key_ch2_stage0_1;
#pragma HLS STREAM variable=key_ch2_stage0    depth=16 dim=1
#pragma HLS STREAM variable=key_ch2_stage0_0  depth=16 dim=1
#pragma HLS STREAM variable=key_ch2_stage0_1  depth=16 dim=1
#pragma HLS RESOURCE variable=key_ch2_stage0   core=FIFO_SRL
#pragma HLS RESOURCE variable=key_ch2_stage0_0 core=FIFO_SRL
#pragma HLS RESOURCE variable=key_ch2_stage0_1 core=FIFO_SRL
        hls::stream<ap_uint<512> > key_ch3_stage0;
        hls::stream<ap_uint<512> > key_ch3_stage0_0;
        hls::stream<ap_uint<512> > key_ch3_stage0_1;
#pragma HLS STREAM variable=key_ch3_stage0    depth=16 dim=1
#pragma HLS STREAM variable=key_ch3_stage0_0  depth=16 dim=1
#pragma HLS STREAM variable=key_ch3_stage0_1  depth=16 dim=1
#pragma HLS RESOURCE variable=key_ch3_stage0   core=FIFO_SRL
#pragma HLS RESOURCE variable=key_ch3_stage0_0 core=FIFO_SRL
#pragma HLS RESOURCE variable=key_ch3_stage0_1 core=FIFO_SRL
        hls::stream<ap_uint<512> > key_ch4_stage0;
        hls::stream<ap_uint<512> > key_ch4_stage0_0;
        hls::stream<ap_uint<512> > key_ch4_stage0_1;
#pragma HLS STREAM variable=key_ch4_stage0    depth=16 dim=1
#pragma HLS STREAM variable=key_ch4_stage0_0  depth=16 dim=1
#pragma HLS STREAM variable=key_ch4_stage0_1  depth=16 dim=1
#pragma HLS RESOURCE variable=key_ch4_stage0   core=FIFO_SRL
#pragma HLS RESOURCE variable=key_ch4_stage0_0 core=FIFO_SRL
#pragma HLS RESOURCE variable=key_ch4_stage0_1 core=FIFO_SRL
        hls::stream<ap_uint<512> > key_ch5_stage0;
        hls::stream<ap_uint<512> > key_ch5_stage0_0;
        hls::stream<ap_uint<512> > key_ch5_stage0_1;
#pragma HLS STREAM variable=key_ch5_stage0    depth=16 dim=1
#pragma HLS STREAM variable=key_ch5_stage0_0  depth=16 dim=1
#pragma HLS STREAM variable=key_ch5_stage0_1  depth=16 dim=1
#pragma HLS RESOURCE variable=key_ch5_stage0   core=FIFO_SRL
#pragma HLS RESOURCE variable=key_ch5_stage0_0 core=FIFO_SRL
#pragma HLS RESOURCE variable=key_ch5_stage0_1 core=FIFO_SRL
        hls::stream<ap_uint<512> > key_ch6_stage0;
        hls::stream<ap_uint<512> > key_ch6_stage0_0;
        hls::stream<ap_uint<512> > key_ch6_stage0_1;
#pragma HLS STREAM variable=key_ch6_stage0    depth=16 dim=1
#pragma HLS STREAM variable=key_ch6_stage0_0  depth=16 dim=1
#pragma HLS STREAM variable=key_ch6_stage0_1  depth=16 dim=1
#pragma HLS RESOURCE variable=key_ch6_stage0   core=FIFO_SRL
#pragma HLS RESOURCE variable=key_ch6_stage0_0 core=FIFO_SRL
#pragma HLS RESOURCE variable=key_ch6_stage0_1 core=FIFO_SRL
        hls::stream<ap_uint<512> > key_ch7_stage0;
        hls::stream<ap_uint<512> > key_ch7_stage0_0;
        hls::stream<ap_uint<512> > key_ch7_stage0_1;
#pragma HLS STREAM variable=key_ch7_stage0    depth=16 dim=1
#pragma HLS STREAM variable=key_ch7_stage0_0  depth=16 dim=1
#pragma HLS STREAM variable=key_ch7_stage0_1  depth=16 dim=1
#pragma HLS RESOURCE variable=key_ch7_stage0   core=FIFO_SRL
#pragma HLS RESOURCE variable=key_ch7_stage0_0 core=FIFO_SRL
#pragma HLS RESOURCE variable=key_ch7_stage0_1 core=FIFO_SRL

	read(in0,
		key_ch0_stage0,
		repeat_num, data_num);
	read(in1,
		key_ch1_stage0,
		repeat_num, data_num);
	read(in2,
		key_ch2_stage0,
		repeat_num, data_num);
	read(in3,
		key_ch3_stage0,
		repeat_num, data_num);
	read(in4,
		key_ch4_stage0,
		repeat_num, data_num);
	read(in5,
		key_ch5_stage0,
		repeat_num, data_num);
	read(in6,
		key_ch6_stage0,
		repeat_num, data_num);
	read(in7,
		key_ch7_stage0,
		repeat_num, data_num);




	hls::stream<ap_uint<512> > axi_data_fifo0_0;   
	hls::stream<ap_uint<512> > axi_data_fifo0_1;   
	hls::stream<ap_uint<512> > axi_data_fifo0_2;   
	hls::stream<ap_uint<512> > axi_data_fifo0_3;   
	hls::stream<ap_uint<512> > axi_data_fifo0_4;   
	hls::stream<ap_uint<512> > axi_data_fifo0_5;   
	hls::stream<ap_uint<512> > axi_data_fifo0_6;   
	hls::stream<ap_uint<512> > axi_data_fifo0_7;   
	hls::stream<ap_uint<512> > axi_data_fifo1_0;   
	hls::stream<ap_uint<512> > axi_data_fifo1_1;   
	hls::stream<ap_uint<512> > axi_data_fifo1_2;   
	hls::stream<ap_uint<512> > axi_data_fifo1_3;   
	hls::stream<ap_uint<512> > axi_data_fifo1_4;   
	hls::stream<ap_uint<512> > axi_data_fifo1_5;   
	hls::stream<ap_uint<512> > axi_data_fifo1_6;   
	hls::stream<ap_uint<512> > axi_data_fifo1_7;   
	hls::stream<ap_uint<512> > axi_data_fifo2_0;   
	hls::stream<ap_uint<512> > axi_data_fifo2_1;   
	hls::stream<ap_uint<512> > axi_data_fifo2_2;   
	hls::stream<ap_uint<512> > axi_data_fifo2_3;   
	hls::stream<ap_uint<512> > axi_data_fifo2_4;   
	hls::stream<ap_uint<512> > axi_data_fifo2_5;   
	hls::stream<ap_uint<512> > axi_data_fifo2_6;   
	hls::stream<ap_uint<512> > axi_data_fifo2_7;   
	hls::stream<ap_uint<512> > axi_data_fifo3_0;   
	hls::stream<ap_uint<512> > axi_data_fifo3_1;   
	hls::stream<ap_uint<512> > axi_data_fifo3_2;   
	hls::stream<ap_uint<512> > axi_data_fifo3_3;   
	hls::stream<ap_uint<512> > axi_data_fifo3_4;   
	hls::stream<ap_uint<512> > axi_data_fifo3_5;   
	hls::stream<ap_uint<512> > axi_data_fifo3_6;   
	hls::stream<ap_uint<512> > axi_data_fifo3_7;   
	hls::stream<ap_uint<512> > axi_data_fifo4_0;   
	hls::stream<ap_uint<512> > axi_data_fifo4_1;   
	hls::stream<ap_uint<512> > axi_data_fifo4_2;   
	hls::stream<ap_uint<512> > axi_data_fifo4_3;   
	hls::stream<ap_uint<512> > axi_data_fifo4_4;   
	hls::stream<ap_uint<512> > axi_data_fifo4_5;   
	hls::stream<ap_uint<512> > axi_data_fifo4_6;   
	hls::stream<ap_uint<512> > axi_data_fifo4_7;   
	hls::stream<ap_uint<512> > axi_data_fifo5_0;   
	hls::stream<ap_uint<512> > axi_data_fifo5_1;   
	hls::stream<ap_uint<512> > axi_data_fifo5_2;   
	hls::stream<ap_uint<512> > axi_data_fifo5_3;   
	hls::stream<ap_uint<512> > axi_data_fifo5_4;   
	hls::stream<ap_uint<512> > axi_data_fifo5_5;   
	hls::stream<ap_uint<512> > axi_data_fifo5_6;   
	hls::stream<ap_uint<512> > axi_data_fifo5_7;   
	hls::stream<ap_uint<512> > axi_data_fifo6_0;   
	hls::stream<ap_uint<512> > axi_data_fifo6_1;   
	hls::stream<ap_uint<512> > axi_data_fifo6_2;   
	hls::stream<ap_uint<512> > axi_data_fifo6_3;   
	hls::stream<ap_uint<512> > axi_data_fifo6_4;   
	hls::stream<ap_uint<512> > axi_data_fifo6_5;   
	hls::stream<ap_uint<512> > axi_data_fifo6_6;   
	hls::stream<ap_uint<512> > axi_data_fifo6_7;   
	hls::stream<ap_uint<512> > axi_data_fifo7_0;   
	hls::stream<ap_uint<512> > axi_data_fifo7_1;   
	hls::stream<ap_uint<512> > axi_data_fifo7_2;   
	hls::stream<ap_uint<512> > axi_data_fifo7_3;   
	hls::stream<ap_uint<512> > axi_data_fifo7_4;   
	hls::stream<ap_uint<512> > axi_data_fifo7_5;   
	hls::stream<ap_uint<512> > axi_data_fifo7_6;   
	hls::stream<ap_uint<512> > axi_data_fifo7_7;   

#pragma HLS STREAM variable=axi_data_fifo0_0 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo0_1 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo0_2 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo0_3 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo0_4 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo0_5 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo0_6 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo0_7 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo1_0 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo1_1 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo1_2 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo1_3 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo1_4 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo1_5 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo1_6 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo1_7 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo2_0 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo2_1 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo2_2 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo2_3 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo2_4 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo2_5 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo2_6 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo2_7 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo3_0 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo3_1 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo3_2 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo3_3 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo3_4 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo3_5 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo3_6 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo3_7 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo4_0 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo4_1 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo4_2 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo4_3 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo4_4 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo4_5 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo4_6 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo4_7 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo5_0 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo5_1 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo5_2 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo5_3 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo5_4 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo5_5 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo5_6 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo5_7 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo6_0 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo6_1 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo6_2 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo6_3 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo6_4 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo6_5 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo6_6 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo6_7 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo7_0 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo7_1 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo7_2 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo7_3 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo7_4 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo7_5 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo7_6 depth=512 dim=1
#pragma HLS STREAM variable=axi_data_fifo7_7 depth=512 dim=1
#pragma HLS RESOURCE variable=axi_data_fifo0_0 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo0_1 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo0_2 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo0_3 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo0_4 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo0_5 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo0_6 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo0_7 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo1_0 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo1_1 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo1_2 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo1_3 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo1_4 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo1_5 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo1_6 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo1_7 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo2_0 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo2_1 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo2_2 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo2_3 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo2_4 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo2_5 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo2_6 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo2_7 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo3_0 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo3_1 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo3_2 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo3_3 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo3_4 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo3_5 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo3_6 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo3_7 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo4_0 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo4_1 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo4_2 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo4_3 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo4_4 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo4_5 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo4_6 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo4_7 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo5_0 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo5_1 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo5_2 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo5_3 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo5_4 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo5_5 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo5_6 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo5_7 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo6_0 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo6_1 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo6_2 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo6_3 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo6_4 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo6_5 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo6_6 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo6_7 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo7_0 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo7_1 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo7_2 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo7_3 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo7_4 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo7_5 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo7_6 core=FIFO_BRAM
#pragma HLS RESOURCE variable=axi_data_fifo7_7 core=FIFO_BRAM

  bica(
	axi_data_fifo0_0, 
	axi_data_fifo0_1, 
	axi_data_fifo0_2, 
	axi_data_fifo0_3, 
	axi_data_fifo0_4, 
	axi_data_fifo0_5, 
	axi_data_fifo0_6, 
	axi_data_fifo0_7, 
	key_ch0_stage0);
  bica(
	axi_data_fifo1_0, 
	axi_data_fifo1_1, 
	axi_data_fifo1_2, 
	axi_data_fifo1_3, 
	axi_data_fifo1_4, 
	axi_data_fifo1_5, 
	axi_data_fifo1_6, 
	axi_data_fifo1_7, 
	key_ch1_stage0);
  bica(
	axi_data_fifo2_0, 
	axi_data_fifo2_1, 
	axi_data_fifo2_2, 
	axi_data_fifo2_3, 
	axi_data_fifo2_4, 
	axi_data_fifo2_5, 
	axi_data_fifo2_6, 
	axi_data_fifo2_7, 
	key_ch2_stage0);
  bica(
	axi_data_fifo3_0, 
	axi_data_fifo3_1, 
	axi_data_fifo3_2, 
	axi_data_fifo3_3, 
	axi_data_fifo3_4, 
	axi_data_fifo3_5, 
	axi_data_fifo3_6, 
	axi_data_fifo3_7, 
	key_ch3_stage0);
  bica(
	axi_data_fifo4_0, 
	axi_data_fifo4_1, 
	axi_data_fifo4_2, 
	axi_data_fifo4_3, 
	axi_data_fifo4_4, 
	axi_data_fifo4_5, 
	axi_data_fifo4_6, 
	axi_data_fifo4_7, 
	key_ch4_stage0);
  bica(
	axi_data_fifo5_0, 
	axi_data_fifo5_1, 
	axi_data_fifo5_2, 
	axi_data_fifo5_3, 
	axi_data_fifo5_4, 
	axi_data_fifo5_5, 
	axi_data_fifo5_6, 
	axi_data_fifo5_7, 
	key_ch5_stage0);
  bica(
	axi_data_fifo6_0, 
	axi_data_fifo6_1, 
	axi_data_fifo6_2, 
	axi_data_fifo6_3, 
	axi_data_fifo6_4, 
	axi_data_fifo6_5, 
	axi_data_fifo6_6, 
	axi_data_fifo6_7, 
	key_ch6_stage0);
  bica(
	axi_data_fifo7_0, 
	axi_data_fifo7_1, 
	axi_data_fifo7_2, 
	axi_data_fifo7_3, 
	axi_data_fifo7_4, 
	axi_data_fifo7_5, 
	axi_data_fifo7_6, 
	axi_data_fifo7_7, 
	key_ch7_stage0);

  write(
	axi_data_fifo0_0, 
	axi_data_fifo0_1, 
	axi_data_fifo0_2, 
	axi_data_fifo0_3, 
	axi_data_fifo0_4, 
	axi_data_fifo0_5, 
	axi_data_fifo0_6, 
	axi_data_fifo0_7, 
	out0_0, 
	out0_1, 
	out0_2, 
	out0_3, 
	out0_4, 
	out0_5, 
	out0_6, 
	out0_7, 
	0);
  write(
	axi_data_fifo1_0, 
	axi_data_fifo1_1, 
	axi_data_fifo1_2, 
	axi_data_fifo1_3, 
	axi_data_fifo1_4, 
	axi_data_fifo1_5, 
	axi_data_fifo1_6, 
	axi_data_fifo1_7, 
	out1_0, 
	out1_1, 
	out1_2, 
	out1_3, 
	out1_4, 
	out1_5, 
	out1_6, 
	out1_7, 
	0);
  write(
	axi_data_fifo2_0, 
	axi_data_fifo2_1, 
	axi_data_fifo2_2, 
	axi_data_fifo2_3, 
	axi_data_fifo2_4, 
	axi_data_fifo2_5, 
	axi_data_fifo2_6, 
	axi_data_fifo2_7, 
	out2_0, 
	out2_1, 
	out2_2, 
	out2_3, 
	out2_4, 
	out2_5, 
	out2_6, 
	out2_7, 
	0);
  write(
	axi_data_fifo3_0, 
	axi_data_fifo3_1, 
	axi_data_fifo3_2, 
	axi_data_fifo3_3, 
	axi_data_fifo3_4, 
	axi_data_fifo3_5, 
	axi_data_fifo3_6, 
	axi_data_fifo3_7, 
	out3_0, 
	out3_1, 
	out3_2, 
	out3_3, 
	out3_4, 
	out3_5, 
	out3_6, 
	out3_7, 
	0);
  write(
	axi_data_fifo4_0, 
	axi_data_fifo4_1, 
	axi_data_fifo4_2, 
	axi_data_fifo4_3, 
	axi_data_fifo4_4, 
	axi_data_fifo4_5, 
	axi_data_fifo4_6, 
	axi_data_fifo4_7, 
	out4_0, 
	out4_1, 
	out4_2, 
	out4_3, 
	out4_4, 
	out4_5, 
	out4_6, 
	out4_7, 
	0);
  write(
	axi_data_fifo5_0, 
	axi_data_fifo5_1, 
	axi_data_fifo5_2, 
	axi_data_fifo5_3, 
	axi_data_fifo5_4, 
	axi_data_fifo5_5, 
	axi_data_fifo5_6, 
	axi_data_fifo5_7, 
	out5_0, 
	out5_1, 
	out5_2, 
	out5_3, 
	out5_4, 
	out5_5, 
	out5_6, 
	out5_7, 
	0);
  write(
	axi_data_fifo6_0, 
	axi_data_fifo6_1, 
	axi_data_fifo6_2, 
	axi_data_fifo6_3, 
	axi_data_fifo6_4, 
	axi_data_fifo6_5, 
	axi_data_fifo6_6, 
	axi_data_fifo6_7, 
	out6_0, 
	out6_1, 
	out6_2, 
	out6_3, 
	out6_4, 
	out6_5, 
	out6_6, 
	out6_7, 
	0);
  write(
	axi_data_fifo7_0, 
	axi_data_fifo7_1, 
	axi_data_fifo7_2, 
	axi_data_fifo7_3, 
	axi_data_fifo7_4, 
	axi_data_fifo7_5, 
	axi_data_fifo7_6, 
	axi_data_fifo7_7, 
	out7_0, 
	out7_1, 
	out7_2, 
	out7_3, 
	out7_4, 
	out7_5, 
	out7_6, 
	out7_7, 
	0);

}
#ifndef HLS
} // end of extern C
#endif
