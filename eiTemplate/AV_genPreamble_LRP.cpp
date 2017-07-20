//函数描述：HSI-PHY(LRP)前导生成模块

#include"genParam.h"
#include "stdafx.h"

using namespace std;

void AV_genPreamble_LRP(vector<complex<double> > &vLRP_Pre)
{
	int temp_ts[37] = {-1,1,1,1,1,1,-1,-1,1,-1,1,-1,-1,-1,1,-1,1,0,0,0,1,-1,1,-1,-1,1,-1,1,1,1,1,1,1,-1,-1,1,1};
	vector<complex<double>> freq_syms (128, complex<double>(0,0));
	for (int i = 0; i < 37; ++i) 
	{
		complex<double> temp_ts(temp_ts[i], 0);
		freq_syms[i + 46] = temp_ts;
	}
	IFFT(freq_syms, 128);
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < freq_syms.size(); ++j)
		{
			vLRP_Pre.push_back(freq_syms[j]);
		}
	}
}