//����˵����HCSУ�����ԭ��ΪCRC16У�飬���16λУ��λ,���ɶ���ʽΪG(x)=X16+X12+X5+1
//����˵����bits_input-����ı�������;parity-�������õ�16λУ��λ��Nbits-������Ҫ����У��ı��ظ���
//#include<iostream>
#include"genParam.h"
#include "stdafx.h"

using namespace std;

void HCS_encoder(vector<int> &bits_input, vector<int> &parity)
{
	int reg_temp[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};//��ʼ���Ĵ���ȫ1
	for (int i = 0; i < bits_input.size(); i++)
	{
		int c15 = bits_input[i] ^ reg_temp[0];
		int c3 = c15 ^ reg_temp[4];
		int c10 = c15 ^ reg_temp[11];//����У��λ
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
		parity.push_back(reg_temp[i] ^ 1);//�������
	}
}