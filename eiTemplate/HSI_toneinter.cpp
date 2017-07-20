//函数描述：HSI模式OFDM调制载波交织
//参数描述：symsin-输入的一个OFDM符号(512个复数）

//#include<iostream>
//#include<complex>
#include"genParam.h"
#include "stdafx.h"

using namespace std;

void HSI_toneinter(vector<complex<double> > &symsin)
{
	vector<complex<double> > syms_temp;
	for (int i = 0; i < symsin.size(); i++)
		syms_temp.push_back(symsin[i]);//保存symsin
	for (int i = 0; i < 512; i++)
	{
		int bits_temp[9] = {0};
		int seed_temp = i;
		bits_temp[8] = i % 2;
		for (int j = 7; j >= 0; --j)
		{
			seed_temp = seed_temp / 2;
			bits_temp[j] = seed_temp % 2; 
		}//将序号转化为9位二进制序列
		int index_temp = 0;
		for (int j = 0; j < 9; j++)
		{
			index_temp += bits_temp[j] * pow(2.0, j);
		}//交织规则，反转序列得到交织后的载波位置
		symsin[i] = syms_temp[index_temp];
	}
}