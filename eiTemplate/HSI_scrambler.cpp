//函数描述：HSI-PHY扰码程序；
//输入参数：codebits-进行扰码的比特序列；SSID-四位扰码初始值；NBits-进行扰码的比特数量；
//#include<iostream>
#include"genParam.h"
#include "stdafx.h"

using namespace std;

void HSI_scrambler(vector<int> &codebits, int ssid[])
{
	int Nbits = codebits.size();
	//int* prbs = new int[Nbits];
	vector<int> prbs;
	scrambler_gen_prbs(ssid, prbs, Nbits);
	for(int i = 0; i < Nbits; i++)
		codebits[i] = codebits[i] ^ prbs[i];
}