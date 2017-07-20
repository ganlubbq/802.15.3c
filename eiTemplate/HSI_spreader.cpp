//函数描述：HSI-PHY扩频函数
/*参数描述：syms_input-输入的符号；sp_out-扩频输出；Nsyms-输入的符号个数；sp_index-扩频因子:1,48-只有CMS0使用扩频,
每七个符号一组进行扩频*/

//#include<iostream>
//#include<cstdlib>
//#include<complex>
#include"genParam.h"
#include "stdafx.h"

using namespace std;

void HSI_spreader(vector<complex<double> > &syms_input, vector<complex<double> > &sp_out, int sp_index)
{
	int Nsyms = syms_input.size();
	const int Nsyms_sp = sp_index * Nsyms;//扩频输出比特数；
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
			complex<double>* spread_temp_a = new complex<double> [7];//扩频前的一组七个符号
			complex<double>* spread_temp_b = new complex<double> [168];//扩频后的一组前半组168个符号
			complex<double> sp_seq[24] = {complex<double>(+1,0), complex<double>(0,+1), complex<double>(-1,0), complex<double>(0,+1), complex<double>(0,+1), complex<double>(+1,0), 
								          complex<double>(-1,0), complex<double>(0,+1), complex<double>(0,-1), complex<double>(0,+1), complex<double>(-1,0), complex<double>(0,-1), 
								          complex<double>(-1,0), complex<double>(+1,0), complex<double>(+1,0), complex<double>(+1,0), complex<double>(0,+1), complex<double>(0,-1), 
								          complex<double>(-1,0), complex<double>(-1,0), complex<double>(-1,0), complex<double>(0,+1), complex<double>(0,-1), complex<double>(0,+1)};//扩频序列
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
		cout<<"扩频因子输入错误"<<endl;
		exit(EXIT_FAILURE);
	}
}