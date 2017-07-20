//函数描述：AV-PHY中LRP扰码程序；
//输入参数：codebits-进行扰码的比特序列；SSID-四位扰码初始值；
//#include<iostream>
#include"genParam.h"
#include "stdafx.h"

using namespace std;

void scrambler_LRP(vector<int> &codebits, vector<int> &ssid, int type)
{
	switch (type)
	{
	case 0:
		break;
	case 1:
		{
			int Nbits = codebits.size();
			vector<int> prbs;
			scrambler_gen_prbs_LRP(ssid, prbs, Nbits);
			for(int i = 0; i < Nbits; i++)
				codebits[i] = codebits[i] ^ prbs[i];
			break;
		}
	default:
		break;
	}
}