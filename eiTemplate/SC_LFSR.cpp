//函数说明：SC-PHY产生扩频所需的伪随机序列
//参数说明：Nbits-所需的伪随机比特数目,prbs-输出的伪随机序列；
//#include<iostream>
#include"genParam.h"
#include "stdafx.h"

using namespace std;

void SC_LFSR(vector<int> &prbs, int Nbits)
{
	//int* prbs_temp= new int[Nbits+15];
	vector<int> prbs_temp ((Nbits + 15), 0);
	int init_bits[15] = {1,1,1,1,1,0,0,0,0,0,0,1,0,1,0} ;//初始序列
	for (int i = 0; i < 15; i++)
		prbs_temp[i] = init_bits[i];
	for (int i = 0; i < Nbits; i++)
	{
		prbs_temp[i+15] = prbs_temp[i] ^ prbs_temp[i+1];
		prbs.push_back(prbs_temp[i+15]);
	}
}