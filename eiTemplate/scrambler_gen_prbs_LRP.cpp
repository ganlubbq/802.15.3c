//函数说明：AV-PHY中LRP模式由SSID生成伪随机序列
//参数说明：ssid-生成伪随机序列所需的四位比特序列, ssid顺序为协议中的S3,S2,S1,S0；prbs-生成的伪随机序列；Nbits-需要进行扰码操作的比特数

//#include<iostream>
#include"genParam.h"
#include "stdafx.h"

using namespace std;

void scrambler_gen_prbs_LRP(vector<int> &ssid, vector<int> &prbs, int Nbits)
{
	vector<int> prbs_temp (Nbits + 6);//构造扰码初始序列
    prbs = vector<int>(Nbits, 0);
    prbs_temp[Nbits] = 0;
    prbs_temp[Nbits + 1] = 1;
    prbs_temp[Nbits + 2] = ssid[0];
    prbs_temp[Nbits + 3] = ssid[1];
    prbs_temp[Nbits + 4] = ssid[2];
    prbs_temp[Nbits + 5] = ssid[3];
	for(int i = Nbits; i > 0; --i)
	{
		prbs_temp[i - 1] = prbs_temp[i + 1] ^ prbs_temp[i + 5];
        prbs[i - 1] = prbs_temp[i - 1];
	}
}