//函数描述：bitsin-编码输入；bitsout-编码输出；rate-码率：0-1/2(336,672),1-5/8(420,672),2-3/4(504,672),3-7/8(588,672), 4-14/15(1344,1440)
#include "genParam.h"
#include "stdafx.h"

using namespace std;

void HSI_LDPCencoder(vector<int> &bitsin, vector<int> &bitsout, int rate)
{
	vector<vector<double> > zMatrix;
	genLDPCGenMatrix(rate, zMatrix);//生成校验矩阵
	int Nparity = zMatrix.size();//校验位个数
	int Ndata = 0;//信息位个数
	if (rate != 4)
		Ndata = 672 - Nparity;
	else
		Ndata = 1344;
	int Nblock = bitsin.size() / Ndata;
	vector<double> parity (Nparity, 0);
	for (int ii = 0; ii < Nblock; ++ii)
	{
		vector<double> temp_gen;
		for (int iii = 0; iii < Ndata; ++iii)
		{
			temp_gen.push_back(bitsin[Ndata * ii + iii]);
			bitsout.push_back(bitsin[Ndata * ii + iii]);
		}
		genLDPCparity(temp_gen, zMatrix, parity);
		for (int iii = 0; iii < Nparity; ++iii)
		{
			//int int_temp = parity[iii];
			bitsout.push_back(parity[iii]);
		}
	}
}