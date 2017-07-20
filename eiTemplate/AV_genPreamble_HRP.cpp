//函数描述：HSI-PHY(HRP)前导生成模块

#include"genParam.h"
#include "stdafx.h"

using namespace std;

void AV_genPreamble_HRP(vector<complex<double> > &vHRP_Pre)
{
	ifstream inHRP;
	inHRP.open("HRP_preamble_IQ.txt");
	double temp_I;
	double temp_Q;
	for (int i = 0; i < 4608; ++i)
	{
		inHRP >> temp_I >> temp_Q;
		vHRP_Pre.push_back(complex<double>(temp_I, temp_Q));
	}
}