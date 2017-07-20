//函数描述：AV-PHY数据分流模块
//参数描述：codebits-输入比特；bits_up-输出的upper比特流；bits_low-输出的lower比特流；Nbits-输入的比特数；
//        ueptype-0:EEP模式(注意输入比特数是32的倍数）， 1：UEP模式(注意输入比特数是16的倍数）；2:不进行分流，信息保存在bits_up

//#include<iostream>
//#include<cstdlib>
#include"genParam.h"
#include "stdafx.h"


using namespace std;
void AV_splitter(vector<int> &codebits, vector<int> &bits_up, vector<int> &bits_low, int ueptype)
{
	int Nbits = codebits.size();
	switch (ueptype)
	{
	case 0:
		{
			int test = Nbits % 32;//检验比特数
			if (test == 0)
			{
				const int Nblocks = Nbits / 32;//数据块数目
				int bits_temp[32]; 
				for (int i = 0; i < Nblocks; i++)
				{
					for (int j = 0; j < 32; j++)
						bits_temp[j] = codebits[32 * i + j];
					for (int ii = 0; ii < 4; ii++)
						//bits_low[16 * i + ii] = bits_temp[ii];
						bits_low.push_back(bits_temp[ii]);
					for (int ii = 0; ii < 4; ii++)
						//bits_low[16 * i + 4 + ii] = bits_temp[8 + ii];
						bits_low.push_back(bits_temp[8 + ii]);
					for (int ii = 0; ii < 4; ii++)
						//bits_low[16 * i + 8 + ii] = bits_temp[4 + ii];
						bits_low.push_back(bits_temp[4 + ii]);
					for (int ii = 0; ii < 4; ii++)
						//bits_low[16 * i + 12 + ii] = bits_temp[12 + ii];
						bits_low.push_back(bits_temp[12 + ii]);//填充low分流
					for (int ii = 0; ii < 4; ii++)
						//bits_up[16 * i + ii] = bits_temp[16 + ii];
						bits_up.push_back(bits_temp[16 + ii]);
					for (int ii = 0; ii < 4; ii++)
						//bits_up[16 * i + 4 + ii] = bits_temp[16 + 8 + ii];
						bits_up.push_back(bits_temp[16 + 8 + ii]);
					for (int ii = 0; ii < 4; ii++)
						//bits_up[16 * i + 8 + ii] = bits_temp[16 + 4 + ii];
						bits_up.push_back(bits_temp[16 + 4 + ii]);
					for (int ii = 0; ii < 4; ii++)
						//bits_up[16 * i + 12 + ii] = bits_temp[16 + 12 + ii];
						bits_up.push_back(bits_temp[16 + 12 + ii]);//填充upper分流

				}
			}
			else
			{
				cout << "输入比特数目错误！" << endl;
				exit(EXIT_FAILURE);
			}
			break;
		}
	case 1:
		{
			int test = Nbits % 16;//检验比特数
			if (test == 0)
			{
				const int Nblocks = Nbits / 16;//数据块数目
				int bits_temp[16]; 
				for (int i = 0; i < Nblocks; i++)
				{
					for (int j = 0; j < 16; j++)
						bits_temp[j] = codebits[16 * i + j];
					for (int ii = 0; ii < 4; ii++)
						//bits_low[8 * i + ii] = bits_temp[ii];
						bits_low.push_back(bits_temp[ii]);
					for (int ii = 0; ii < 4; ii++)
						//bits_low[8 * i + 4 + ii] = bits_temp[8 + ii];
						bits_low.push_back(bits_temp[8 + ii]);//填充low分流
					for (int ii = 0; ii < 4; ii++)
						//bits_up[8 * i + ii] = bits_temp[4 + ii];
						bits_up.push_back(bits_temp[4 + ii]);
					for (int ii = 0; ii < 4; ii++)
						//bits_up[8 * i + 4 + ii] = bits_temp[12 + ii];
						bits_up.push_back(bits_temp[12 + ii]);//填充upper分流
				}
			}
			else
			{
				cout << "输入比特数目错误！" << endl;
				exit(EXIT_FAILURE);
			}
			break;
		}
	case 2:
		{
			int test = Nbits % 32;//检验比特数
			if (test == 0)
			{
				const int Nblocks = Nbits / 32;//数据块数目
				int bits_temp[32]; 
				for (int i = 0; i < Nblocks; i++)
				{
					for (int j = 0; j < 32; j++)
						bits_temp[j] = codebits[32 * i + j];
					for (int ii = 0; ii < 4; ii++)
						//bits_low[16 * i + ii] = bits_temp[ii];
						bits_low.push_back(bits_temp[ii]);
					for (int ii = 0; ii < 4; ii++)
						//bits_low[16 * i + 4 + ii] = bits_temp[8 + ii];
						bits_low.push_back(bits_temp[8 + ii]);
					for (int ii = 0; ii < 4; ii++)
						//bits_low[16 * i + 8 + ii] = bits_temp[4 + ii];
						bits_low.push_back(bits_temp[4 + ii]);
					for (int ii = 0; ii < 4; ii++)
						//bits_low[16 * i + 12 + ii] = bits_temp[12 + ii];
						bits_low.push_back(bits_temp[12 + ii]);//填充low分流
					for (int ii = 0; ii < 4; ii++)
						//bits_up[16 * i + ii] = bits_temp[16 + ii];
						bits_up.push_back(bits_temp[16 + ii]);
					for (int ii = 0; ii < 4; ii++)
						//bits_up[16 * i + 4 + ii] = bits_temp[16 + 8 + ii];
						bits_up.push_back(bits_temp[16 + 8 + ii]);
					for (int ii = 0; ii < 4; ii++)
						//bits_up[16 * i + 8 + ii] = bits_temp[16 + 4 + ii];
						bits_up.push_back(bits_temp[16 + 4 + ii]);
					for (int ii = 0; ii < 4; ii++)
						//bits_up[16 * i + 12 + ii] = bits_temp[16 + 12 + ii];
						bits_up.push_back(bits_temp[16 + 12 + ii]);//填充upper分流

				}
			}
			else
			{
				cout << "输入比特数目错误！" << endl;
				exit(EXIT_FAILURE);
			}
			break;
		}
	default:
		{
			cout << "UEP模式输入错误！" << endl;
			exit(EXIT_FAILURE);
			break;
		}
	}
}
