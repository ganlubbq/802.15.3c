//����������HSIģʽOFDM�����ز���֯
//����������symsin-�����һ��OFDM����(512��������

//#include<iostream>
//#include<complex>
#include"genParam.h"
#include "stdafx.h"

using namespace std;

void HSI_toneinter(vector<complex<double> > &symsin)
{
	vector<complex<double> > syms_temp;
	for (int i = 0; i < symsin.size(); i++)
		syms_temp.push_back(symsin[i]);//����symsin
	for (int i = 0; i < 512; i++)
	{
		int bits_temp[9] = {0};
		int seed_temp = i;
		bits_temp[8] = i % 2;
		for (int j = 7; j >= 0; --j)
		{
			seed_temp = seed_temp / 2;
			bits_temp[j] = seed_temp % 2; 
		}//�����ת��Ϊ9λ����������
		int index_temp = 0;
		for (int j = 0; j < 9; j++)
		{
			index_temp += bits_temp[j] * pow(2.0, j);
		}//��֯���򣬷�ת���еõ���֯����ز�λ��
		symsin[i] = syms_temp[index_temp];
	}
}