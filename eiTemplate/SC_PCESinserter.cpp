//函数描述：SC PHY信道估计插入模块
/*参数描述：symin：输入的符号；symout：输出的符号；PCES_mod：选择是否插入信道估计，‘0’不插入，‘1’插入；sub_mod：子块分割模式，0、8、64； */

//#include<iostream>
//#include<cmath>
//#include<complex>
#include"genParam.h"
#include "stdafx.h"

using namespace std;

void SC_PCESinserter(vector<complex<double> > &symin, vector<complex<double> > &symout, int PCES_mod, int sub_mod)
{
	if (PCES_mod == 0)
	{
		//Nsymout = Nsymin;
		int Nsymin = symin.size();
		for (int i = 0; i < Nsymin; i++)
			symout.push_back(symin[i]);
	}
	else
	{
		int a_golay_hex_32[32] = {0x0,0x5,0x3,0x6,0x6,0x3,0x5,0x0,0x0,0x5,0xC,0x9,0x6,0x3,0xA,0xF
							     ,0xF,0xA,0xC,0x9,0x9,0xC,0xA,0xF,0x0,0x5,0xC,0x9,0x6,0x3,0xA,0xF};
		int b_golay_hex_32[32] = {0x0,0xA,0x3,0x9,0x6,0xC,0x5,0xF,0x0,0xA,0xC,0x6,0x6,0xC,0xA,0x0
								 ,0xF,0x5,0xC,0x6,0x9,0x3,0xA,0x0,0x0,0xA,0xC,0x6,0x6,0xC,0xA,0x0};
		vector<int> a_golay_binary_128;
		vector<int> b_golay_binary_128;
		vector<int> b_golay_binary_128_N (128, 0);
		hex2binary(a_golay_hex_32, a_golay_binary_128,32);
		hex2binary(b_golay_hex_32, b_golay_binary_128,32);
		for (int i = 0; i < 128; i++)
				b_golay_binary_128_N[i]=floor((2-(b_golay_binary_128[i]*1.0))/2);
		vector<int> a_golay_binary_256 (256, 0);
		for (int i = 0; i < 128; i++)
			a_golay_binary_256[i] = a_golay_binary_128[i];
		for (int i = 0; i < 128; i++)
			a_golay_binary_256[i+128] = b_golay_binary_128[i];
		vector<int> b_golay_binary_256 (256, 0);
		for (int i = 0; i < 128; i++)
			b_golay_binary_256[i] = a_golay_binary_128[i];
		for (int i = 0; i < 128; i++)
			b_golay_binary_256[i + 128] = b_golay_binary_128_N[i];
		vector<int> PCES_bits (1152, 0);//插入的信道估计序列：a256 b256 a256 b256 b128
		for (int i = 0; i < 256; i++)
			PCES_bits[i] = a_golay_binary_256[i];
		for (int i = 0; i < 256; i++)
			PCES_bits[i+256] = b_golay_binary_256[i];
		for (int i = 0; i < 256; i++)
			PCES_bits[i+512] = a_golay_binary_256[i];
		for (int i = 0; i < 256; i++)
			PCES_bits[i+768] = b_golay_binary_256[i];
		for (int i = 0; i < 128; i++)
			PCES_bits[i+1024] = b_golay_binary_128[i];
		//complex<double> PCES_syms = new complex<double>[1152];
		vector<complex<double> > PCES_syms;
		SC_tx_modulation(PCES_bits, PCES_syms, 1);//对插入的导频进行π/2 BPSK调制
		switch (sub_mod)
		{
		case 0:
			{
				int Nsymin = symin.size();
				int Nblocklength = 448 * 64;//每个数据块的长度
				int Nblocks = ceil((Nsymin * 1.0) / (Nblocklength * 1.0));//数据块数目
				if (Nblocks == 1)
				{
					//Nsymout = Nsymin;
					for (int i = 0; i < Nsymin; i++)
						symout.push_back(symin[i]);
				}
				else
				{
					//Nsymout = Nsymin + (Nblocks - 1) * 1152;
					int N_lblock = Nsymin - (Nblocks - 1) * (Nblocklength);//最后一个数据块符号数
					for (int i = 0; i < (Nblocks - 1); i++)
					{
						for (int j = 0; j < Nblocklength; j++)
							symout.push_back(symin[(Nblocklength) * i + j]);
						for (int k = 0; k < 1152; k++)
							symout.push_back(PCES_syms[k]);
					}
					for (int ii = 0; ii < N_lblock; ii++)
						symout.push_back(symin[(Nblocklength) * (Nblocks - 1)]);//填充数据与信道估计插入
				}
				break;
			}
		case 8:
			{
				int Nsymin = symin.size();
				int Nblocklength = 512 * 64 + 8;//每个数据块的长度
				int Nblocks = ceil((Nsymin * 1.0) / (Nblocklength * 1.0));//数据块数目
				if (Nblocks == 1)
				{
					//Nsymout = Nsymin;
					for (int i = 0; i < Nsymin; i++)
						symout.push_back(symin[i]);
				}
				else
				{
					//Nsymout = Nsymin + (Nblocks - 1) * 1152;
					int N_lblock = Nsymin - (Nblocks - 1) * (Nblocklength);//最后一个数据块符号数
					for (int i = 0; i < (Nblocks - 1); i++)
					{
						for (int j = 0; j < Nblocklength; j++)
							symout.push_back(symin[(Nblocklength) * i + j]);
						for (int k = 0; k < 1152; k++)
							symout.push_back(PCES_syms[k]);
					}
					for (int ii = 0; ii < N_lblock; ii++)
						symout.push_back(symin[(Nblocklength) * (Nblocks - 1)]);//填充数据与信道估计插入
				}
				break;
			}
		case 64:
			{
				int Nsymin = symin.size();
				int Nblocklength = 512 * 64 + 64;//每个数据块的长度
				int Nblocks = ceil((Nsymin * 1.0) / (Nblocklength * 1.0));//数据块数目
				if (Nblocks == 1)
				{
					//Nsymout = Nsymin;
					for (int i = 0; i < Nsymin; i++)
						symout.push_back(symin[i]);
				}
				else
				{
					//Nsymout = Nsymin + (Nblocks - 1) * 1152;
					int N_lblock = Nsymin - (Nblocks - 1) * (Nblocklength);//最后一个数据块符号数
					for (int i = 0; i < (Nblocks - 1); i++)
					{
						for (int j = 0; j < Nblocklength; j++)
							symout.push_back(symin[(Nblocklength) * i + j]);
						for (int k = 0; k < 1152; k++)
							symout.push_back(PCES_syms[k]);
					}
					for (int ii = 0; ii < N_lblock; ii++)
						symout.push_back(symin[(Nblocklength) * (Nblocks - 1)]);//填充数据与信道估计插入
				}
				break;
			}
		default:
			{
				cout << "子块分割模式选择错误！！！！" << endl;
				exit(EXIT_FAILURE);
				break;
			}
		}
	}
}