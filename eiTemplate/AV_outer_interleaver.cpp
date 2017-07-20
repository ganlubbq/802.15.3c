//函数描述：AV-PHY外交织模块，交织深度为2或4；
//参数描述：codebits-输入比特；Nbits-输入的比特数量；depth-交织深度2或4；

//#include<iostream>
//#include<cstdlib>
#include"genParam.h"
#include "stdafx.h"

using namespace std;

//void AV_outer_interleaver(int* codebits, int Nbits, int depth)
void AV_outer_interleaver(vector<int> &codebits, int depth)
{
	int Nbits = codebits.size();
	switch (depth)
	{
	case 2:
		{
			int* bits_temp = new int [Nbits];
			//for (int i = 0; i < Nbits; i++)
			//	bits_temp[i] = codebits[i];//保存输入比特
			int num_test = Nbits % depth;
			if (num_test == 0)
			{
				const int Row = depth;
				const int Col = Nbits / depth;
				int** inter_temp = new int* [Row];
				for (int i = 0; i < Row; i++)
					inter_temp[i] = new int [Col];//交织矩阵
				for (int i = 0; i < Row; i++)
				{
					for (int j = 0; j < Col; j++)
						inter_temp[i][j] = codebits[i * Col + j];//将数据填充至交织矩阵中
				}
				for (int i = 0; i < Col; i++)
				{
					for (int j = 0; j < Row; j++)
						codebits[i * Row + j] = inter_temp[j][i];//按列输出
				}
				for (int i = 0; i < Row; i++)
					delete [] inter_temp[i];
				delete [] inter_temp;
			}
			else
			{
				cout << "输入比特数量错误！" << endl;
			    exit(EXIT_FAILURE);
			}
			break;
		}
	case 4:
		{
			int* bits_temp = new int [Nbits];
			//for (int i = 0; i < Nbits; i++)
			//	bits_temp[i] = codebits[i];//保存输入比特
			int num_test = Nbits % depth;
			if (num_test == 0)
			{
				const int Row = depth;
				const int Col = Nbits / depth;
				int** inter_temp = new int* [Row];
				for (int i = 0; i < Row; i++)
					inter_temp[i] = new int [Col];//交织矩阵
				for (int i = 0; i < Row; i++)
				{
					for (int j = 0; j < Col; j++)
						inter_temp[i][j] = codebits[i * Col + j];//将数据填充至交织矩阵中
				}
				for (int i = 0; i < Col; i++)
				{
					for (int j = 0; j < Row; j++)
						codebits[i * Row + j] = inter_temp[j][i];//按列输出
				}
				for (int i = 0; i < Row; i++)
					delete [] inter_temp[i];
				delete [] inter_temp;
			}
			else
			{
				cout << "输入比特数量错误！" << endl;
			    exit(EXIT_FAILURE);
			}
			break;
		}
	default:
		{
			cout << "交织模式输入错误！" << endl;
			exit(EXIT_FAILURE);
		}
	}
}