//函数说明：SCS校验程序，原理为CRC8校验，输出8位校验位,生成多项式为G(x)=X8+X2+X1+1
//参数说明：bits_input-输入的比特序列;parity-计算所得的16位校验位；Nbits-输入需要进行校验的比特个数
//#include<iostream>
#include"genParam.h"
#include "stdafx.h"

using namespace std;

void AV_SCS_encoder(vector<int> &bits_input, vector<int> &parity)
{
	int reg_temp[] = {1, 1, 1, 1, 1, 1, 1, 1};//初始化寄存器全1
	for (int i = 0; i < bits_input.size(); i++)
	{
		int c7 = bits_input[i] ^ reg_temp[0];
		int c6 = c7 ^ reg_temp[7];
		int c5 = c7 ^ reg_temp[6];//计算校验位
		for (int j = 0; j < 7; j++)
		{
			reg_temp[j] = reg_temp[j+1];
		}
		reg_temp[7] = c7;
		reg_temp[6] = c6;
		reg_temp[5] = c5;
	}
	for (int i = 0; i < 8; i++)
		parity.push_back(reg_temp[i] ^ 1);//输出补码
}