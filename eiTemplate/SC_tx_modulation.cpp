//����������SC-PHYģʽ����ӳ��
//����������codebits-�����������Ӧ�����֣�symbols-����ķ������У� Nbits-����bit��������modtype-����ģʽ��1-pi/2 Bpsk,2-pi/2 Qpsk,3-pi/2 8Psk,4-pi/2 16QAM

//#include<iostream>
//#include<cmath>
//#include<cstdlib>
//#include<complex>
#include"genParam.h"
#include "stdafx.h"

using namespace std;

void SC_tx_modulation(vector<int> &codebits, vector<complex<double> > &symbols, int modtype)
{
	int Nbits = codebits.size();
	int Nnums = Nbits/modtype;
	vector<int> nums;//����ת��Ϊ���֣����ݴ�������ӳ����н���ѡ��
	bits2nums(codebits, nums, modtype);
	int nums_temp;
	switch (modtype)
	{
	case 1: 
		{
		complex<double> mod_temp[2] = {complex<double>(0,-1), complex<double>(0,1)};//ӳ���
		for(int i = 0; i < Nnums; i++)
			symbols.push_back(mod_temp[nums[i]]);
		break;
		}
	case 2:
		{
		complex<double> mod_temp[4] = {complex<double>(0,-1), complex<double>(1,0),
			                           complex<double>(-1,0), complex<double>(0,1)};//ӳ���
		for(int i = 0; i < Nnums; i++)
			symbols.push_back(mod_temp[nums[i]]);
		break;
		}
	case 3:
		{
		complex<double> mod_temp[8] = {complex<double>(-cos(PI/4),-cos(PI/4)), complex<double>(-1,0), complex<double>(0,1), complex<double>(-cos(PI/4),+cos(PI/4)), 
			                           complex<double>(0,-1), complex<double>(+cos(PI/4),-cos(PI/4)), complex<double>(+cos(PI/4),+cos(PI/4)), complex<double>(1,0)};//ӳ���
		for(int i = 0; i < Nnums; i++)
			symbols.push_back(mod_temp[nums[i]]);
		break;
		}
	case 4:
		{
		complex<double> mod_temp[16] = {complex<double>(-3/sqrt(10.0),-3/sqrt(10.0)), complex<double>(-3/sqrt(10.0),-1/sqrt(10.0)), complex<double>(-3/sqrt(10.0),+3/sqrt(10.0)), complex<double>(-3/sqrt(10.0),+1/sqrt(10.0)),
		                                complex<double>(-1/sqrt(10.0),-3/sqrt(10.0)), complex<double>(-1/sqrt(10.0),-1/sqrt(10.0)), complex<double>(-1/sqrt(10.0),+3/sqrt(10.0)), complex<double>(-1/sqrt(10.0),+1/sqrt(10.0)),
		                                complex<double>(+3/sqrt(10.0),-3/sqrt(10.0)), complex<double>(+3/sqrt(10.0),-1/sqrt(10.0)), complex<double>(+3/sqrt(10.0),+3/sqrt(10.0)), complex<double>(+3/sqrt(10.0),+1/sqrt(10.0)),
								        complex<double>(+1/sqrt(10.0),-3/sqrt(10.0)), complex<double>(+1/sqrt(10.0),-1/sqrt(10.0)), complex<double>(+1/sqrt(10.0),+3/sqrt(10.0)), complex<double>(+1/sqrt(10.0),+1/sqrt(10.0))};//ӳ���
		for(int i = 0; i < Nnums; i++)
			symbols.push_back(mod_temp[nums[i]]);
		break;
		}
	default:
		{
			cout<<"����ģʽ�������"<<endl;
		    exit(EXIT_FAILURE);
		}
	}
}