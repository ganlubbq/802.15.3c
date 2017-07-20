//函数说明：RS编码，输入dataIn：为码片个数的8倍，输出data_out为空容器；Rate：1（239，255），2（216，224），3（48，56），4（44，52）
#include "genParam.h"
#include "stdafx.h"

using namespace std;

void RS_encoder(vector<int> &dataIn, vector<int> &data_out, int Rate)
{
	int len = dataIn.size();
	int pp_scrs[9] = { 1, 0, 1, 1, 1, 0, 0, 0, 1};// p(x)=1+x^2+x^3+x^4+x^8
	int alpha_to_scrs [256] = {0};
	int index_of_scrs [256] = {0};
	int gg_scrs[17] = {0};
	int recd_scrs [255] = {0};
	int data_scrs [239] = {0};
	int bb_scrs [16] = {0};
	/*******************/
	int i_rs;
	int N;
	int K;
	int T;
	int num;
	int pad;

	switch (Rate)
	{
	case 1:
		{
			N = 255;
			K = 239;
			T = 8;
			break;
		}
		
	case 2:
		{
			N = 224;
			K = 216;
			T = 4;
			break;
		}
	case 3:
		{
			N = 56;
			K = 48;
			T = 4;
			break;
		}
	case 4:
		{
			N = 52;
			K = 44;
			T = 4;
			break;
		}
	default:
		{
			cout<<"Wrong rate_id!"; 
			break;
		}
	}
	/********************generate_gf()*****************************/
	int i_gf, mask ;
	mask = 1 ;
	alpha_to_scrs[8] = 0 ;
	for (i_gf=0; i_gf<8; i_gf++)
	{ alpha_to_scrs[i_gf] = mask ;
	index_of_scrs[alpha_to_scrs[i_gf]] = i_gf ;
	if (pp_scrs[i_gf]!=0)
		alpha_to_scrs[8] ^= mask ;
	mask <<= 1 ;
	}
	index_of_scrs[alpha_to_scrs[8]] = 8 ;
	mask >>= 1 ;
	for (i_gf=9; i_gf<255; i_gf++)
	{ if (alpha_to_scrs[i_gf-1] >= mask)
	alpha_to_scrs[i_gf] = alpha_to_scrs[8] ^ ((alpha_to_scrs[i_gf-1]^mask)<<1) ;
	else alpha_to_scrs[i_gf] = alpha_to_scrs[i_gf-1]<<1 ;
	index_of_scrs[alpha_to_scrs[i_gf]] = i_gf ;
	}
	index_of_scrs[0] = -1;
	/*********************gen_poly()****************************/
	int i_po,j_po;
	gg_scrs[0] = 2 ;    /* primitive element alpha = 2  for GF(2**mm)  */
	gg_scrs[1] = 1 ;    /* g(x) = (X+alpha) initially */
	for (i_po=2; i_po<=16; i_po++)
	{ 
		gg_scrs[i_po] = 1 ;
	    for (j_po=i_po-1; j_po>0; j_po--)
			if (gg_scrs[j_po] != 0)
				gg_scrs[j_po] = gg_scrs[j_po-1]^ alpha_to_scrs[(index_of_scrs[gg_scrs[j_po]]+i_po)%255] ;
			else 
				gg_scrs[j_po] = gg_scrs[j_po-1] ;
		gg_scrs[0] = alpha_to_scrs[(index_of_scrs[gg_scrs[0]]+i_po)%255] ;     /* gg[0] can never be zero */
	}
	/* convert gg[] to index form for quicker encoding */
	for (i_po=0; i_po<=16; i_po++)
		gg_scrs[i_po] = index_of_scrs[gg_scrs[i_po]] ;
	/***********************************************************/
	int len_de = len/8;
	int Nstuff = (len%(8*K)) == 0 ? 0 : (8*K - len%(8*K));	//填充比特0
	for (int i = 0; i < Nstuff; ++i)
		dataIn.push_back(0);
	num = (len+Nstuff)/(8*K);//先假设正好整除
	/*int* deData = new int[len_de];
	for (i=0;i<len_de;i++)
		deData[i]=0;*/
	/*int* deDataOut = new int[N*num];
	for (i=0;i<N*num;i++)
		deDataOut[i]=0;*/
	vector<int> deDataOut(N*num, 0);
	/*int* dataOut = new int[N*num*8];
	for (i=0;i<N*num*8;i++)
		dataOut[i]=0;*/
	vector<int> dataOut(N*num*8, 0);
	pad = 239-K;
	//binary to decimal,按8位切割，转成0~255的十进制数，共num个
	vector<int> deData(dataIn.size()/8, 0);
	bi2de_rs(dataIn, deData) ;//
	for (int j = 0;j<num;j++)
	{
		//data 倒序输入encoder_rs
		for (i_rs=0;i_rs<pad;i_rs++)
			data_scrs[i_rs] = 0; 
		for (i_rs=0;i_rs<K;i_rs++)
			data_scrs[i_rs+pad] = deData[K-1-i_rs];
/************************encode_rs**************************************/
	int i_ec, j_ec;
	int feedback ;
	for (i_ec=0; i_ec<16; i_ec++)
		bb_scrs[i_ec] = 0 ;
	for (i_ec=239-1; i_ec>=0; i_ec--)
	{  
		feedback = index_of_scrs[data_scrs[i_ec]^bb_scrs[15]] ;
		if (feedback != -1)
		{ 
			for (j_ec=15; j_ec>0; j_ec--)
				if (gg_scrs[j_ec] != -1)
					bb_scrs[j_ec] = bb_scrs[j_ec-1]^alpha_to_scrs[(gg_scrs[j_ec]+feedback)%255] ;
				else
					bb_scrs[j_ec] = bb_scrs[j_ec-1] ;
			bb_scrs[0] = alpha_to_scrs[(gg_scrs[0]+feedback)%255] ;
		}
		else
		{ 
			for (j_ec=15; j_ec>0; j_ec--)
				bb_scrs[j_ec] = bb_scrs[j_ec-1] ;
			bb_scrs[0] = 0 ;
		}
	}
/***********************************************************************/

		//for (i_rs=0; i_rs<N-K; i_rs++)
		//	recd_scrs[i_rs+K] = bb_scrs[N-K-1-i_rs];//倒序
		//for (i_rs=0; i_rs<K; i_rs++)
		//	recd_scrs[i_rs] = deData[K-1-i_rs];
		for (i_rs=0; i_rs<N-K; i_rs++)
			recd_scrs[i_rs+K] = bb_scrs[N-K-1-i_rs];//更改顺序
		for (i_rs=0; i_rs<K; i_rs++)
			recd_scrs[i_rs] = deData[i_rs];
		for(i_rs=0;i_rs<N;i_rs++)
			deDataOut[j*N+i_rs]=recd_scrs[i_rs];
	}//end j
	de2bi_rs(deDataOut,dataOut); 
	for (int i = 0; i < N*num*8; ++i)
		data_out.push_back(dataOut[i]);
	/*delete deDataOut;
	delete deData;
	delete dataOut;*/
}