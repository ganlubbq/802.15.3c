//函数说明：SC-PHY模式由SSID生成伪随机序列
//参数说明：ssid-生成伪随机序列所需的四位比特序列；prbs-生成的伪随机序列；Nbits-需要进行扰码操作的比特数

//#include<iostream>
#include"genParam.h"
#include "stdafx.h"

using namespace std;

void scrambler_gen_prbs(int ssid[], vector<int> &prbs, int Nbits)
{
	vector<int> prbs_temp (Nbits + 15);//构造扰码初始序列
	for(int i = 0; i < 4; i++)
		prbs_temp[3-i] = ssid[i];
	int prbs_inif[11] = {1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1};
	for(int i = 0; i < 11; i++)
		prbs_temp[4+i] = prbs_inif[i];
	for(int i = 0; i < Nbits; i++)
	{
		int x = prbs_temp[i];
		int y = prbs_temp[i+1];
		int z = x ^ y;
		prbs_temp[i+15] = z;
		//prbs[i] = prbs_temp[i+15];
		prbs.push_back(prbs_temp[i+15]);
	}
}