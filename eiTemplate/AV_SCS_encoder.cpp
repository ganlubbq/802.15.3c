//����˵����SCSУ�����ԭ��ΪCRC8У�飬���8λУ��λ,���ɶ���ʽΪG(x)=X8+X2+X1+1
//����˵����bits_input-����ı�������;parity-�������õ�16λУ��λ��Nbits-������Ҫ����У��ı��ظ���
//#include<iostream>
#include"genParam.h"
#include "stdafx.h"

using namespace std;

void AV_SCS_encoder(vector<int> &bits_input, vector<int> &parity)
{
	int reg_temp[] = {1, 1, 1, 1, 1, 1, 1, 1};//��ʼ���Ĵ���ȫ1
	for (int i = 0; i < bits_input.size(); i++)
	{
		int c7 = bits_input[i] ^ reg_temp[0];
		int c6 = c7 ^ reg_temp[7];
		int c5 = c7 ^ reg_temp[6];//����У��λ
		for (int j = 0; j < 7; j++)
		{
			reg_temp[j] = reg_temp[j+1];
		}
		reg_temp[7] = c7;
		reg_temp[6] = c6;
		reg_temp[5] = c5;
	}
	for (int i = 0; i < 8; i++)
		parity.push_back(reg_temp[i] ^ 1);//�������
}