//����˵����RSencoder��255���Ƶ�ʮ������תΪbits
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
			biData[j * 8 + i] = de_temp % 2;//��Ϊ�뻯Ϊʮ����ʱ��˳����ͬ
			de_temp = de_temp / 2;
		}
	} 
}