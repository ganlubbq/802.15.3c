//函数说明：HSI交织程序，每四个LDPC编码码字（2688bits）进行交织编码, inter_index: 0-不进行比特交织， 1—进行比特交织
//参数说明：bitsin：输入比特；bitsout：输出比特；bitsnums：比特数

//#include<iostream>
#include"genParam.h"
#include "stdafx.h"

using namespace std;

void HSI_interleaver(vector<int> &bitsin, vector<int> &bitsout, int inter_index)
{
	switch (inter_index)
	{
	case 0:
		{
			for (int i = 0; i < bitsin.size(); ++i)
				bitsout.push_back(bitsin[i]);
			break;
		}
	case 1:
		{
			int bitsnums = bitsin.size();
			int Nblocks = bitsnums / 2688;//交织数据块
			int *inter_temp = new int [2688];
			for (int i = 0; i < Nblocks; i++)
			{
				for (int j = 0; j < 2688; j++)
					inter_temp[j] = bitsin[2688 * i + j];
				for (int j = 0; j < 2688; j++)
				{
					int index_temp = (2688 - 24 + j + 2 * 24 * ((j * 24 - j) % 2688)) % 2688;//交织规则
					//bitsout[2688 * i + j] = inter_temp[index_temp];
					bitsout.push_back(inter_temp[index_temp]);
				}
			}
			delete [] inter_temp;
			break;
		}
	default:
		{
			cout << "参数输入错误" << endl;
			break;
		}
	}
	//int bitsnums = bitsin.size();
	//int Nblocks = bitsnums / 2688;//交织数据块
	//int *inter_temp = new int [2688];
	//for (int i = 0; i < Nblocks; i++)
	//{
	//	for (int j = 0; j < 2688; j++)
	//		inter_temp[j] = bitsin[2688 * i + j];
	//	for (int j = 0; j < 2688; j++)
	//	{
	//		int index_temp = (2688 - 24 + j + 2 * 24 * ((j * 24 - j) % 2688)) % 2688;//交织规则
	//		//bitsout[2688 * i + j] = inter_temp[index_temp];
	//		bitsout.push_back(inter_temp[index_temp]);
	//	}
	//}
	//delete [] inter_temp;
}