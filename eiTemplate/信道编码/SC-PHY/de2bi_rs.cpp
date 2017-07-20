//函数说明：RSencoder中255进制的十进制数转为bits
#include "genParam.h"
#include "stdafx.h"

using namespace std;

void de2bi_rs(vector<int> &deData, vector<int> &biData)
{
	int len = deData.size();
	for(int j = 0;j<len;j++)
	{
		int de_temp = deData[j];
		for(int i = 7; i >= 0; i--)  
		{  
			/*if(deData[j] & (1 << i))  		
				biData[j*8+i]=1;		
			else  
				biData[j*8+i]=0;*/
			biData[j * 8 + i] = de_temp % 2;//改为与化为十进制时的顺序相同
			de_temp = de_temp / 2;
		}
	} 
}