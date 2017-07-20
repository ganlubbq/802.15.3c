//����������HSI-PHYģʽ����ӳ��
//����������codebits-�����������Ӧ�����֣�symbols-����ķ������У� Nbits-����bit��������modtype-����ģʽ��2-QPSK,4-16QAM,6-64QAM��skew��0-��ʹ��skew��1-ʹ��skew��

//#include<iostream>
//#include<cmath>
//#include<cstdlib>
//#include<complex>
#include"genParam.h"
#include "stdafx.h"

using namespace std;

void HSI_tx_modulation(vector<int> &codebits, vector<complex<double> > &symbols, int modtype, int skew)
{
	if (skew == 0)
	{
		int Nbits = codebits.size();
		int Nnums = Nbits/modtype;
		const double D = 1;//unskew mode
		//int *nums = new int [Nnums]
		vector<int> nums;
		bits2nums(codebits, nums, modtype);//����ת��Ϊ���֣����ݴ�������ӳ����н���ѡ��
		switch (modtype)
		{
		case 2: 
			{
			complex<double> mod_temp[4] = {complex<double>(-D, -1), complex<double>(+D, -1), 
										   complex<double>(-D, +1), complex<double>(+D, +1)};//ӳ���
			double nor_factor = 1/sqrt(1 + D * D);//��һ��ϵ��
			for (int i = 0; i < 4; i++)
				mod_temp[i] = mod_temp[i] * nor_factor;//��һ��
			for(int i = 0; i < Nnums; i++)
				//symbols[i] = mod_temp[nums[i]];
				symbols.push_back(mod_temp[nums[i]]);
			break;
			}
		case 4:
			{
			complex<double> mod_temp[16] = {complex<double>((-3) * D, -3), complex<double>((-3) * D, -1), complex<double>((-3) * D, +3), complex<double>((-3) * D, +1), 
			                                complex<double>((-1) * D, -3), complex<double>((-1) * D, -1), complex<double>((-1) * D, +3), complex<double>((-1) * D, +1), 
			                                complex<double>((+3) * D, -3), complex<double>((+3) * D, -1), complex<double>((+3) * D, +3), complex<double>((+3) * D, +1), 
			                                complex<double>((+1) * D, -3), complex<double>((+1) * D, -1), complex<double>((+1) * D, +3), complex<double>((+1) * D, +1)};//ӳ���
			double nor_factor = 1/sqrt(5 * (1 + D * D));//��һ��ϵ��
			for (int i = 0; i < 16; i++)
				mod_temp[i] = mod_temp[i] * nor_factor;//��һ��
			for(int i = 0; i < Nnums; i++)
				//symbols[i] = mod_temp[nums[i]];
				symbols.push_back(mod_temp[nums[i]]);
			break;
			}
		case 6:
			{
			complex<double> mod_temp[64] = {complex<double>((-7) * D, -7), complex<double>((-7) * D, -5), complex<double>((-7) * D, -1), complex<double>((-7) * D, -3), complex<double>((-7) * D, +7), complex<double>((-7) * D, +5), complex<double>((-7) * D, +1), complex<double>((-7) * D, +3), 
			                                complex<double>((-5) * D, -7), complex<double>((-5) * D, -5), complex<double>((-5) * D, -1), complex<double>((-5) * D, -3), complex<double>((-5) * D, +7), complex<double>((-5) * D, +5), complex<double>((-5) * D, +1), complex<double>((-5) * D, +3), 
			                                complex<double>((-1) * D, -7), complex<double>((-1) * D, -5), complex<double>((-1) * D, -1), complex<double>((-1) * D, -3), complex<double>((-1) * D, +7), complex<double>((-1) * D, +5), complex<double>((-1) * D, +1), complex<double>((-1) * D, +3),  
			                                complex<double>((-3) * D, -7), complex<double>((-3) * D, -5), complex<double>((-3) * D, -1), complex<double>((-3) * D, -3), complex<double>((-3) * D, +7), complex<double>((-3) * D, +5), complex<double>((-3) * D, +1), complex<double>((-3) * D, +3), 
									        complex<double>((+7) * D, -7), complex<double>((+7) * D, -5), complex<double>((+7) * D, -1), complex<double>((+7) * D, -3), complex<double>((+7) * D, +7), complex<double>((+7) * D, +5), complex<double>((+7) * D, +1), complex<double>((+7) * D, +3), 
									        complex<double>((+5) * D, -7), complex<double>((+5) * D, -5), complex<double>((+5) * D, -1), complex<double>((+5) * D, -3), complex<double>((+5) * D, +7), complex<double>((+5) * D, +5), complex<double>((+5) * D, +1), complex<double>((+5) * D, +3), 
									        complex<double>((+1) * D, -7), complex<double>((+1) * D, -5), complex<double>((+1) * D, -1), complex<double>((+1) * D, -3), complex<double>((+1) * D, +7), complex<double>((+1) * D, +5), complex<double>((+1) * D, +1), complex<double>((+1) * D, +3), 
									        complex<double>((+3) * D, -7), complex<double>((+3) * D, -5), complex<double>((+3) * D, -1), complex<double>((+3) * D, -3), complex<double>((+3) * D, +7), complex<double>((+3) * D, +5), complex<double>((+3) * D, +1), complex<double>((+3) * D, +3)};//ӳ���
			double nor_factor = 1 / sqrt(21 * (1 + D * D));//��һ��ϵ��
			for (int i = 0; i < 64; i++)
				mod_temp[i] = mod_temp[i] * nor_factor;//��һ��
			for(int i = 0; i < Nnums; i++)
				//symbols[i] = mod_temp[nums[i]];
				symbols.push_back(mod_temp[nums[i]]);
			break;
			}
		default:
			cout<<"����ģʽ�������"<<endl;
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		int Nbits = codebits.size();
		int Nnums = Nbits / modtype;
		const double D = 1.25;//unskew mode
		//int* nums = new int [Nnums];
		vector<int> nums;
		bits2nums(codebits, nums, modtype);//����ת��Ϊ���֣����ݴ�������ӳ����н���ѡ��
		switch (modtype)
		{
		case 2: 
			{
			complex<double> mod_temp[4] = {complex<double>(-D, -1), complex<double>(+D, -1), 
										   complex<double>(-D, +1), complex<double>(+D, +1)};//ӳ���
			double nor_factor = 1 / sqrt(1 + D * D);//��һ��ϵ��
			for (int i = 0; i < 4; i++)
				mod_temp[i] = mod_temp[i] * nor_factor;//��һ��
			for(int i = 0; i < Nnums; i++)
				//symbols[i] = mod_temp[nums[i]];
				symbols.push_back(mod_temp[nums[i]]);
			break;
			}
		case 4:
			{
			complex<double> mod_temp[16] = {complex<double>((-3) * D, -3), complex<double>((-3) * D, -1), complex<double>((-3) * D, +3), complex<double>((-3) * D, +1), 
			                                complex<double>((-1) * D, -3), complex<double>((-1) * D, -1), complex<double>((-1) * D, +3), complex<double>((-1) * D, +1), 
			                                complex<double>((+3) * D, -3), complex<double>((+3) * D, -1), complex<double>((+3) * D, +3), complex<double>((+3) * D, +1), 
			                                complex<double>((+1) * D, -3), complex<double>((+1) * D, -1), complex<double>((+1) * D, +3), complex<double>((+1) * D, +1)};//ӳ���
			double nor_factor = 1 / sqrt(5 * (1 + D * D));//��һ��ϵ��
			for (int i = 0; i < 16; i++)
				mod_temp[i] = mod_temp[i] * nor_factor;//��һ��
			for(int i = 0; i < Nnums; i++)
				//symbols[i] = mod_temp[nums[i]];
				symbols.push_back(mod_temp[nums[i]]);
			break;
			}
		case 6:
			{
			complex<double> mod_temp[64] = {complex<double>((-7) * D, -7), complex<double>((-7) * D, -5), complex<double>((-7) * D, -1), complex<double>((-7) * D, -3), complex<double>((-7) * D, +7), complex<double>((-7) * D, +5), complex<double>((-7) * D, +1), complex<double>((-7) * D, +3), 
			                                complex<double>((-5) * D, -7), complex<double>((-5) * D, -5), complex<double>((-5) * D, -1), complex<double>((-5) * D, -3), complex<double>((-5) * D, +7), complex<double>((-5) * D, +5), complex<double>((-5) * D, +1), complex<double>((-5) * D, +3), 
			                                complex<double>((-1) * D, -7), complex<double>((-1) * D, -5), complex<double>((-1) * D, -1), complex<double>((-1) * D, -3), complex<double>((-1) * D, +7), complex<double>((-1) * D, +5), complex<double>((-1) * D, +1), complex<double>((-1) * D, +3),  
			                                complex<double>((-3) * D, -7), complex<double>((-3) * D, -5), complex<double>((-3) * D, -1), complex<double>((-3) * D, -3), complex<double>((-3) * D, +7), complex<double>((-3) * D, +5), complex<double>((-3) * D, +1), complex<double>((-3) * D, +3), 
									        complex<double>((+7) * D, -7), complex<double>((+7) * D, -5), complex<double>((+7) * D, -1), complex<double>((+7) * D, -3), complex<double>((+7) * D, +7), complex<double>((+7) * D, +5), complex<double>((+7) * D, +1), complex<double>((+7) * D, +3), 
									        complex<double>((+5) * D, -7), complex<double>((+5) * D, -5), complex<double>((+5) * D, -1), complex<double>((+5) * D, -3), complex<double>((+5) * D, +7), complex<double>((+5) * D, +5), complex<double>((+5) * D, +1), complex<double>((+5) * D, +3), 
									        complex<double>((+1) * D, -7), complex<double>((+1) * D, -5), complex<double>((+1) * D, -1), complex<double>((+1) * D, -3), complex<double>((+1) * D, +7), complex<double>((+1) * D, +5), complex<double>((+1) * D, +1), complex<double>((+1) * D, +3), 
									        complex<double>((+3) * D, -7), complex<double>((+3) * D, -5), complex<double>((+3) * D, -1), complex<double>((+3) * D, -3), complex<double>((+3) * D, +7), complex<double>((+3) * D, +5), complex<double>((+3) * D, +1), complex<double>((+3) * D, +3)};//ӳ���
			double nor_factor = 1 / sqrt(21 * (1 + D * D));//��һ��ϵ��
			for (int i = 0; i < 64; i++)
				mod_temp[i] = mod_temp[i] * nor_factor;//��һ��
			for(int i = 0; i < Nnums; i++)
				//symbols[i] = mod_temp[nums[i]];
				symbols.push_back(mod_temp[nums[i]]);
			break;
			}
		default:
			cout<<"����ģʽ�������"<<endl;
			exit(EXIT_FAILURE);
		}
	}
}