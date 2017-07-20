//����������HSI-PHY��Ƶ����
/*����������syms_input-����ķ��ţ�sp_out-��Ƶ�����Nsyms-����ķ��Ÿ�����sp_index-��Ƶ����:1,48-ֻ��CMS0ʹ����Ƶ,
ÿ�߸�����һ�������Ƶ*/

//#include<iostream>
//#include<cstdlib>
//#include<complex>
#include"genParam.h"
#include "stdafx.h"

using namespace std;

void HSI_spreader(vector<complex<double> > &syms_input, vector<complex<double> > &sp_out, int sp_index)
{
	int Nsyms = syms_input.size();
	const int Nsyms_sp = sp_index * Nsyms;//��Ƶ�����������
	switch (sp_index)
	{
	case 1:
		//sp_out = syms_input;
		//break;
		{
			for (int i = 0; i < Nsyms; i++)
				sp_out.push_back(syms_input[i]);
			break;
		}
	case 48:
		{
			int Ngrp = Nsyms / 7;
			complex<double>* spread_temp = new complex<double> [336];
			complex<double>* spread_temp_a = new complex<double> [7];//��Ƶǰ��һ���߸�����
			complex<double>* spread_temp_b = new complex<double> [168];//��Ƶ���һ��ǰ����168������
			complex<double> sp_seq[24] = {complex<double>(+1,0), complex<double>(0,+1), complex<double>(-1,0), complex<double>(0,+1), complex<double>(0,+1), complex<double>(+1,0), 
								          complex<double>(-1,0), complex<double>(0,+1), complex<double>(0,-1), complex<double>(0,+1), complex<double>(-1,0), complex<double>(0,-1), 
								          complex<double>(-1,0), complex<double>(+1,0), complex<double>(+1,0), complex<double>(+1,0), complex<double>(0,+1), complex<double>(0,-1), 
								          complex<double>(-1,0), complex<double>(-1,0), complex<double>(-1,0), complex<double>(0,+1), complex<double>(0,-1), complex<double>(0,+1)};//��Ƶ����
			for (int i = 0; i < Ngrp; i++)
			{
				for (int j = 0; j < 7; j++)
					spread_temp_a[j] = syms_input[7 * i + j];
				for (int j = 0; j < 7; j++)
				{
					for (int k = 0; k < 24; k++)
					/*{
						spread_temp_b[24 * j + k].real = spread_temp_a[j].real * sp_seq[k].real - 
														 spread_temp_a[j].imag * sp_seq[k].imag;
						spread_temp_b[24 * j + k].imag = spread_temp_a[j].real * sp_seq[k].imag - 
														 spread_temp_a[j].imag * sp_seq[k].real;
					}*/
						spread_temp_b[24 * j + k] = spread_temp_a[j] * sp_seq[k];
				}
				for (int j = 0; j < 168; j++)
					{
						spread_temp[j] = spread_temp_b[j];
						spread_temp[335-j] = spread_temp[j];
					}
				for (int j = 0; j < 336; j++)
					//sp_out[336 * Ngrp + j] = spread_temp[j];
					sp_out.push_back(spread_temp[j]);
			}
			delete [] spread_temp;
			delete [] spread_temp_a;
			delete [] spread_temp_b;
			break;
		}
	default:
		cout<<"��Ƶ�����������"<<endl;
		exit(EXIT_FAILURE);
	}
}