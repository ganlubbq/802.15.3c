//函数描述：AV-PHY数据复合模块
//函数参数：bitsout-复合输出比特；A/B/C/D/E/F/G/H-输入的8个比特流；N_upper-上半比特流比特数；N_lower-下半比特流比特数；ueptype-0：EEP，1：UEP

#include"genParam.h"
#include "stdafx.h"
using namespace std;

void AV_multiplexer(vector<int> &bitsout, int ueptype, vector<int> &A, vector<int> &B, vector<int> &C, vector<int> &D, vector<int> &E, vector<int> &F, vector<int> &G, vector<int> &H)
{
	switch (ueptype)
	{
	case 0:
		{
			int N_upper = A.size();
			int N_lower = E.size();
			int test = N_upper % 6;
			if ((test == 0) && (N_upper == N_lower))
			{
				int Nblocks = N_upper / 6;
				vector<int> mul_temp (48, 0);
				for (int i = 0; i < Nblocks; i++)
				{
					for (int j = 0; j < 6; j++)//每个卷积编码器的六个比特复合成一个48bit数据块
					{
						mul_temp[j] = A[6 * i + j];
						mul_temp[6 + j] = B[6 * i + j];
						mul_temp[12 + j] = C[6 * i + j];
						mul_temp[18 + j] = D[6 * i + j];
						mul_temp[24 + j] = E[6 * i + j];
						mul_temp[30 + j] = F[6 * i + j];
						mul_temp[36 + j] = G[6 * i + j];
						mul_temp[42 + j] = H[6 * i + j];
					}
					AV_inner_interleaver(mul_temp, ueptype);//对数据块进行交织
					for (int j = 0; j < 48; j++)
						bitsout.push_back(mul_temp[j]);
				}
			}
			else
			{
				cout << "比特数输入错误！" << endl;
			    exit(EXIT_FAILURE);
			}
			break;
		}
	case 1:
		{
			int N_upper = A.size();
			int N_lower = E.size();
			int test_01 = N_upper % 14;
			int test_02 = N_lower % 10;
			if ((test_01 == 0) && (test_02 == 0))
			{
				int Nblocks = N_upper / 14;
				vector<int> mul_temp (96, 0);
				for (int i = 0; i < Nblocks; i++)
				{
					for (int j = 0; j < 14; j++)//八个卷积编码器的比特复合成一个96bit数据块
					{
						mul_temp[j] = A[14 * i + j];
						mul_temp[14 + j] = B[14 * i + j];
						mul_temp[28 + j] = C[14 * i + j];
						mul_temp[42 + j] = D[14 * i + j];
					}
					for (int j = 0; j < 10; j++)
					{
						mul_temp[56 + j] = E[10 * i + j];
						mul_temp[66 + j] = F[10 * i + j];
						mul_temp[76 + j] = G[10 * i + j];
						mul_temp[86 + j] = H[10 * i + j];
					}
					AV_inner_interleaver(mul_temp, ueptype);//对数据块进行交织
					for (int j = 0; j < 96; j++)
						//bitsout[96 * i + j] = mul_temp[j];
						bitsout.push_back(mul_temp[j]);
				}
			}
			else
			{
				cout << "比特数输入错误！" << endl;
			    exit(EXIT_FAILURE);
			}
			break;
		}
	case 2:
		{
			int N_upper = A.size();
			int N_lower = E.size();
			int test = N_upper % 6;
			if ((test == 0) && (N_upper == N_lower))
			{
				int Nblocks = N_upper / 6;
				vector<int> mul_temp (48, 0);
				for (int i = 0; i < Nblocks; i++)
				{
					for (int j = 0; j < 6; j++)//每个卷积编码器的六个比特复合成一个48bit数据块
					{
						mul_temp[j] = A[6 * i + j];
						mul_temp[6 + j] = B[6 * i + j];
						mul_temp[12 + j] = C[6 * i + j];
						mul_temp[18 + j] = D[6 * i + j];
						mul_temp[24 + j] = E[6 * i + j];
						mul_temp[30 + j] = F[6 * i + j];
						mul_temp[36 + j] = G[6 * i + j];
						mul_temp[42 + j] = H[6 * i + j];
					}
					AV_inner_interleaver(mul_temp, ueptype);//对数据块进行交织
					for (int j = 0; j < 48; j++)
						bitsout.push_back(mul_temp[j]);
				}
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
			cout << "UEP模式输入错误！" << endl;
			exit(EXIT_FAILURE);
			break;
		}
	}
}