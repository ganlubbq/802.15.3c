//����������������ı�������ת��Ϊ����,���ڵ��ƺ�����
//���������codebits:����ı������У�nums:����ת���ɵķ���; modtype������ģʽ 1-BPSK,2-QPSK,3-8PSK,4-16QAM��6-64QAM��Nbits:����ı�������
//#include<iostream>
//#include<cmath>
//#include<cstdlib>
#include"genParam.h"
#include "stdafx.h"

using namespace std;

void bits2nums(vector<int> &codebits, vector<int> &nums, int modtype)
{
	int Nbits = codebits.size();
	int Nnums = Nbits/modtype;//ӳ�������Ŀ
	double Nnums_mod = fmod(Nbits*1.0,modtype*1.0); 
	if (Nnums_mod == 0)
	{
		switch (modtype)
		{
		case 1 : 
			{
				for(int i = 0; i < Nnums; i++)
					nums.push_back(codebits[i]);
				break;
			}
		case 2 :
			{
				int temp_index[2] = {2, 1};//����Ȩ��
				for (int i = 0; i < Nnums; i++)
				{
					int temp = 0;
					for (int j = 0; j < modtype; j++)
						temp += codebits[modtype * i + j] * temp_index[j];
					nums.push_back(temp);
				}
				break;
			}
		case 3 :
			{
				int temp_index[3] = {4, 2, 1};//����Ȩ��
				for (int i = 0; i < Nnums; i++)
				{
					int temp = 0;
					for (int j = 0; j < modtype; j++)
						temp += codebits[modtype * i + j] * temp_index[j];
					nums.push_back(temp);
				}
				break;
			}
		case 4 :
			{
				int temp_index[4] = {8, 4, 2, 1};//����Ȩ��
				for (int i = 0; i < Nnums; i++)
				{
					int temp = 0;
					for (int j = 0; j < modtype; j++)
						temp += codebits[modtype * i + j] * temp_index[j];
					nums.push_back(temp);
				}
				break;
			}
		case 6:
			{
				int temp_index[6] = {32, 16, 8, 4, 2, 1};//����Ȩ��
				for (int i = 0; i < Nnums; i++)
				{
					int temp = 0;
					for (int j = 0; j < modtype; j++)
						temp += codebits[modtype * i +j] * temp_index[j];
					nums.push_back(temp);
				}
				break;
			}
		default : 
			{
				cout<<"����ĵ���ģʽ����!"<<endl;
				exit(EXIT_FAILURE);
			}
		}
	}
	else
	{
		cout<<"����ı���������Ŀ����"<<endl;
		exit(EXIT_FAILURE);
	}
}