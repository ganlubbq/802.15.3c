//函数说明：RSencoder中8bits转为255进制的十进制数
#include "genParam.h"
#include "stdafx.h"

using namespace std;

void bi2de_rs(vector<int> &biData, vector<int> &deData) 
{  
	int len = biData.size();
	double a =2;
	for(int j = 0;j<len/8;j++)
	{
		for(int i = 0; i <8; i++)  			
			deData[j]+=biData[j*8+i]*pow(a,(7-i));//改为第一位是最高位
	}
}