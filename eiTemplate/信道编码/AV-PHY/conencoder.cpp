//函数描述：AV-PHY卷积编码模块
//输入参数：codebits-输入比特；bits_conved-卷积编码输出；
//        rate-编码码率(0:1/3; 1:1/2; 2:4/7; 3:2/3; 4:4/5) ；//Nbits-输入比特数
#include"genParam.h"
#include "stdafx.h"

using namespace std;

void conencoder(vector<int> &codebits, vector<int> &bits_out, int rate)
{
	int Nbits = codebits.size();
	vector<int> X_temp (Nbits, 0);
	vector<int> Y_temp (Nbits, 0);
	vector<int> Z_temp (Nbits, 0);
	int reg_temp[6] = {0};//初始化6位基础器全零
	for (int i = 0; i < Nbits; i++)
	{

		X_temp[i] = codebits[i] ^ reg_temp[1] ^ reg_temp[2] ^ reg_temp[4] ^ reg_temp[5];//生成多项式133o
		Y_temp[i] = codebits[i] ^ reg_temp[0] ^ reg_temp[1] ^ reg_temp[2] ^ reg_temp[3] ^ reg_temp[5];//生成多项式171o
		Z_temp[i] = codebits[i] ^ reg_temp[0] ^ reg_temp[1] ^ reg_temp[3] ^ reg_temp[5];//生成多项式165o
		for(int j = 5; j > 0; j--)
			reg_temp[j] = reg_temp[j - 1]; 
		reg_temp[0] = codebits[i];//重置寄存器
	}//得到卷积编码原始输出
	switch (rate)
	{
	case 0:
		{
			for (int i = 0; i < Nbits; i++)
			{
				bits_out.push_back(X_temp[i]);
				bits_out.push_back(Y_temp[i]);
				bits_out.push_back(Z_temp[i]);
			}//按协议排列信息
			break;
		}
	case 1:
		{
			for (int i = 0; i < Nbits; i++)
			{
				bits_out.push_back(X_temp[i]);
				bits_out.push_back(Y_temp[i]);
			}//按协议排列信息
			break;
		}
	case 2:
		{
			int test = Nbits % 4;
			if (test == 0)
			{
				int Nblocks = Nbits / 4;
				for (int i = 0; i < Nblocks; i++)
				{
					bits_out.push_back(X_temp[4 * i + 0]);
					bits_out.push_back(Y_temp[4 * i + 0]);
					bits_out.push_back(X_temp[4 * i + 1]);
					bits_out.push_back(X_temp[4 * i + 2]);
					bits_out.push_back(Y_temp[4 * i + 2]);
					bits_out.push_back(X_temp[4 * i + 3]);
					bits_out.push_back(Y_temp[4 * i + 3]);
				}//按协议排列信息
			}
			else
			{
				cout << "比特数输入错误！" << endl;
				exit(EXIT_FAILURE);
			}
			break;
		}
	case 3:
		{
			int test = Nbits % 2;
			if (test == 0)
			{
				int Nblocks = Nbits / 4;
				for (int i = 0; i < Nblocks; i++)
				{
					bits_out.push_back(X_temp[2 * i + 0]);
					bits_out.push_back(Y_temp[2 * i + 0]);
					bits_out.push_back(X_temp[2 * i + 1]);
				}//按协议排列信息
			}
			else
			{
				cout << "比特数输入错误！" << endl;
				exit(EXIT_FAILURE);
			}
			break;
		}
	case 4:
		{
			int test = Nbits % 4;
			if (test == 0)
			{
				int Nblocks = Nbits / 4;
				for (int i = 0; i < Nblocks; i++)
				{
					bits_out.push_back(X_temp[4 * i + 0]);
					bits_out.push_back(Y_temp[4 * i + 0]);
					bits_out.push_back(X_temp[4 * i + 1]);
					bits_out.push_back(X_temp[4 * i + 2]);
					bits_out.push_back(X_temp[4 * i + 3]);
				}//按协议排列信息
			}
			else
			{
				cout << "比特数输入错误！" << endl;
				exit(EXIT_FAILURE);
			}
			break;
		}
	default:
		{
			cout << "码率选择错误！" << endl;
			exit(EXIT_FAILURE);
			break;
		}
	}
}