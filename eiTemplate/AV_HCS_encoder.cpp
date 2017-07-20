//����˵����HCSУ�����ԭ��ΪCRC32У�飬���32λУ��λ,���ɶ���ʽΪG(x)=X32+X26+X23+X22+X16+X12+X11+X10+X8+X7+X5+X4+X2+X+1
//����˵����bits_input-����ı�������;parity-�������õ�32λУ��λ
//#include<iostream>
#include "genParam.h"
#include "stdafx.h"
using namespace std;

void AV_HCS_encoder(vector<int> &bits_input, vector<int> &parity)
{
	int reg_temp[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};//��ʼ���Ĵ���ȫ1
	for (int i = 0; i < bits_input.size(); i++)
	{
		int c31 = bits_input[i] ^ reg_temp[0];
		int c5 = c31 ^ reg_temp[6];
		int c8 = c31 ^ reg_temp[9];
		int c9 = c31 ^ reg_temp[10];
		int c15 = c31 ^ reg_temp[16];
		int c19 = c31 ^ reg_temp[20];
		int c20 = c31 ^ reg_temp[21];
		int c21 = c31 ^ reg_temp[22];
		int c23 = c31 ^ reg_temp[24];
		int c24 = c31 ^ reg_temp[25];
		int c26 = c31 ^ reg_temp[27];
		int c27 = c31 ^ reg_temp[28];
		int c29 = c31 ^ reg_temp[30];
		int c30 = c31 ^ reg_temp[31];//����У��λ
		for (int j = 0; j < 31; j++)
		{
			reg_temp[j] = reg_temp[j+1];
		}
		reg_temp[31] = c31;
		reg_temp[30] = c30;
		reg_temp[29] = c29;
		reg_temp[27] = c27;
		reg_temp[26] = c26;
		reg_temp[24] = c24;
		reg_temp[23] = c23;
		reg_temp[21] = c21;
		reg_temp[20] = c20;
		reg_temp[19] = c19;
		reg_temp[15] = c15;
		reg_temp[9] = c9;
		reg_temp[8] = c8;
		reg_temp[5] = c5;
	}
	for (int i = 0; i < 32; i++)
	{
		parity.push_back(reg_temp[i] ^ 1);//�������
	}
}