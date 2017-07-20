//函数描述：SC-PHY扩频函数
//参数描述：bits_input-输入的比特序列；sp_out-扩频输出；nbits-输入的比特个数；sp_index-扩频因子:1,2,4,6,64

//#include<iostream>
//#include<cstdlib>
#include"genParam.h"
#include "stdafx.h"

using namespace std;

void SC_spreader(vector<int> &bits_input, vector<int> &sp_out, int sp_index)
{
	int nbits = bits_input.size();
	int nbits_sp = sp_index * nbits;//扩频输出比特数；
	switch (sp_index)
	{
	case 1:
		for (int i = 0; i < bits_input.size(); ++i)
			sp_out.push_back(bits_input[i]);
		break;
	case 2:
		{
			//int* prbs = new int [nbits_sp];
			vector<int> prbs;
			SC_LFSR(prbs, nbits_sp);//生成扩频所需的伪随机序列
			for (int i = 0; i < nbits; i++)
			{
				for (int j = 0; j < 2; j++)
				//sp_out[2*i+j] = bits_input[i]^prbs[2*i+j];
					sp_out.push_back(bits_input[i]^prbs[2*i+j]);//扩频后填充到序列中
			}
			break;
		}
	case 4:
		{
			//int* prbs = new int [nbits_sp];
			vector<int> prbs;
			SC_LFSR(prbs, nbits_sp);//生成扩频所需的伪随机序列
			for (int i = 0; i < nbits; i++)
			{
				for (int j = 0; j < 4; j++)
					//sp_out[4*i+j] = bits_input[i]^prbs[4*i+j];
					sp_out.push_back(bits_input[i]^prbs[4*i+j]);//扩频后填充到序列中
			}
			break;
		}
	case 6:
		{
			vector<int> prbs;
			SC_LFSR(prbs, nbits_sp);//生成扩频所需的伪随机序列
			for (int i = 0; i < nbits; i++)
			{
				for (int j = 0; j < 6; j++)
					//sp_out[6*i+j] = bits_input[i]^prbs[6*i+j]
					sp_out.push_back(bits_input[i]^prbs[6*i+j]);;//扩频后填充到序列中
			}
			break;
		}
	case 64:
		{
			vector<int> prbs;
			SC_LFSR(prbs, nbits);//生成扩频所需的伪随机序列,根据此序列选择格雷序列a/b进行扩频
			int a_golay_hex[16] = {0x6,0x3,0xA,0xF,0x0,0x5,0xC,0x9,0x6,0x3,0x5,0x0,0x0,0x5,0x3,0x6};
			int b_golay_hex[16] = {0x6,0xC,0xA,0x0,0x0,0xA,0xC,0x6,0x6,0xC,0x5,0xF,0x0,0xA,0x3,0x9};
			//int* a_golay_bit = new int [16*4];
			//int* b_golay_bit = new int [16*4];
			vector<int> a_golay_bit;
			vector<int> b_golay_bit;
			hex2binary(a_golay_hex, a_golay_bit, 16);
			hex2binary(b_golay_hex, b_golay_bit, 16);
			for (int i = 0; i < nbits; i++)
			{
				if (prbs[i] == 1)
				{
					for (int j = 0; j <64; j++)
						//sp_out[64*i+j] = bits_input[i]^a_golay_bit[j];
						sp_out.push_back(bits_input[i] ^ a_golay_bit[j]);
				}
				else
				{
					for (int j = 0; j <64; j++)
						//sp_out[64*i+j] = bits_input[i]^b_golay_bit[j];
						sp_out.push_back(bits_input[i] ^ b_golay_bit[j]);
				}
			}
			break;
		}
	default:
		cout<<"扩频因子输入错误"<<endl;
		exit(EXIT_FAILURE);
		break;
	}
}