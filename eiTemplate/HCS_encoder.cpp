//函数说明：HCS校验程序，原理为CRC16校验，输出16位校验位,生成多项式为G(x)=X16+X12+X5+1
//参数说明：bits_input-输入的比特序列;parity-计算所得的16位校验位；Nbits-输入需要进行校验的比特个数
//#include<iostream>
#include"genParam.h"
#include "stdafx.h"

using namespace std;

void HCS_encoder(vector<int> &bits_input, vector<int> &parity)
{
	int reg_temp[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};//初始化寄存器全1
	for (int i = 0; i < bits_input.size(); i++)
	{
		int c15 = bits_input[i] ^ reg_temp[0];
		int c3 = c15 ^ reg_temp[4];
		int c10 = c15 ^ reg_temp[11];//计算校验位
		for (int j = 0; j < 15; j++)
		{
			reg_temp[j] = reg_temp[j+1];
		}
		reg_temp[15] = c15;
		reg_temp[10] = c10;
		reg_temp[3] = c3;
	}
	for (int i = 0; i < 16; i++)
	{
		//parity[i] = reg_temp[i] ^ 1;
		parity.push_back(reg_temp[i] ^ 1);//输出补码
	}
}