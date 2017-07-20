//函数说明：AV PHY 中LRP模式OFDM调制

#include "genParam.h"
#include "stdafx.h"

using namespace std;

void AV_OFDMer_LRP(vector<complex<double> > &symsin, vector<complex<double> > &symsout, int rep)
{
	int pilot_index[4] = {50, 58, 70, 78};
	complex<double> pilot[4] = {complex<double>(1 ,0), complex<double>(-1 ,0), complex<double>(-1 ,0), complex<double>(1 ,0)};
	int dc_index[3] = {63, 64, 65};
	complex<double> dc[3] = {complex<double>(1 ,0), complex<double>(1 ,0), complex<double>(1 ,0)};
	int data_index[30] = {46,47,48,49,51,52,53,54,55,56,57,59,60,61,62,66,67,68,69,71,72,73,74,75,76,77,79,80,81,82};
	int nBlock = symsin.size() / 30;
	for (int i = 0; i < nBlock; ++i)
	{
		vector<complex<double>> ifft_temp (128, complex<double>(0,0));
		for (int j = 0; j < 4; ++j)
			ifft_temp[pilot_index[j]] = pilot[j];
		for (int j = 0; j < 3; ++j)
			ifft_temp[dc_index[j]] = dc[j];
		for (int j = 0; j < 30; ++j)
			ifft_temp[data_index[j]] = symsin[i * 30 + j];
		IFFT(ifft_temp, 128);
		for (int j = 0; j < rep; ++j)
		{
			for (int jj = 0; jj < ifft_temp.size(); ++jj)
				symsout.push_back(ifft_temp[jj]);
		}
	}
}