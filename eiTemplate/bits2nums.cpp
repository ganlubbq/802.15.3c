//函数描述：将输入的比特序列转换为数字,用于调制函数；
//输入参数：codebits:输入的比特序列；nums:比特转换成的符号; modtype：调制模式 1-BPSK,2-QPSK,3-8PSK,4-16QAM，6-64QAM；Nbits:输入的比特数量
//#include<iostream>
//#include<cmath>
//#include<cstdlib>
#include"genParam.h"
#include "stdafx.h"

using namespace std;

void bits2nums(vector<int> &codebits, vector<int> &nums, int modtype)
{
	int Nbits = codebits.size();
	int Nnums = Nbits/modtype;//映射符号数目
	double Nnums_mod = fmod(Nbits*1.0,modtype*1.0); 
	if (Nnums_mod == 0)
	{
		switch (modtype)
		{
		case 1 : 
			{
				for(int i = 0; i < Nnums; i++)
					nums.push_back(codebits[i]);
				break;
			}
		case 2 :
			{
				int temp_index[2] = {2, 1};//调制权重
				for (int i = 0; i < Nnums; i++)
				{
					int temp = 0;
					for (int j = 0; j < modtype; j++)
						temp += codebits[modtype * i + j] * temp_index[j];
					nums.push_back(temp);
				}
				break;
			}
		case 3 :
			{
				int temp_index[3] = {4, 2, 1};//调制权重
				for (int i = 0; i < Nnums; i++)
				{
					int temp = 0;
					for (int j = 0; j < modtype; j++)
						temp += codebits[modtype * i + j] * temp_index[j];
					nums.push_back(temp);
				}
				break;
			}
		case 4 :
			{
				int temp_index[4] = {8, 4, 2, 1};//调制权重
				for (int i = 0; i < Nnums; i++)
				{
					int temp = 0;
					for (int j = 0; j < modtype; j++)
						temp += codebits[modtype * i + j] * temp_index[j];
					nums.push_back(temp);
				}
				break;
			}
		case 6:
			{
				int temp_index[6] = {32, 16, 8, 4, 2, 1};//调制权重
				for (int i = 0; i < Nnums; i++)
				{
					int temp = 0;
					for (int j = 0; j < modtype; j++)
						temp += codebits[modtype * i +j] * temp_index[j];
					nums.push_back(temp);
				}
				break;
			}
		default : 
			{
				cout<<"输入的调制模式错误!"<<endl;
				exit(EXIT_FAILURE);
			}
		}
	}
	else
	{
		cout<<"输入的比特序列数目错误"<<endl;
		exit(EXIT_FAILURE);
	}
}