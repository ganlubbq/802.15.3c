/*函数说明：AV PHY OFDM调制，每338个数据符号调制成一个符号，（0-78，434-511）填充157个零频，
          （255，256，257）填充3个直流，包含16个导频，暂且全填充1*/

#include "genParam.h"
#include "stdafx.h"

using namespace std;

void AV_OFDMer(vector<complex<double> > &symsin, vector<complex<double> > &symsout, int ti)
{
	int nums_in = symsin.size();
	const int Nstuff = ceil(nums_in / 336.0) * 336 - nums_in;//填充bits数
	for (int i = 0; i < Nstuff; ++i)
		symsin.push_back(complex<double>(0.0,0.0));//填充零
	int Nsyms = Nstuff + nums_in;//填充后的符号个数
	/***********************载频映射******************************************/
	int fft_size = 512;
	int Nblocks = Nsyms / 336;//数据块个数
	int index_null[157] = {0};//零频位置
	for (int i = 0; i < 79; ++i)
		index_null[i] = i;
	for (int i = 0; i < 78; ++i)
		index_null[79 + i] = 434 + i;
	int index_dc[3] = {255, 256, 257};//直流位置
	vector<vector<int> > index_pl;//导频位置
	for (int i = 0; i < 22; ++i)
	{
		vector<int> dc_temp;
		int temp_dc = 0;
		int temp_cnt = 0;
		for (int j = 0; j < 16; ++j)
		{
			temp_dc = 79 + mod((3 * i), 22) + temp_cnt * 22;
			if (((temp_dc != 255) && (temp_dc != 256)) && (temp_dc != 257))
				dc_temp.push_back(temp_dc);
			else
				--j;
			++temp_cnt;
		}
		index_pl.push_back(dc_temp);
	}
	for (int i = 0; i < Nblocks; ++i)
	{
		vector<complex<double> > syms_temp (512, complex<double> (0,0));
		int Nsyms_temp = mod(i, 22);//根据符号标号选择填充载波的位置
		int index_temp[512] = {0};//填充零频
		for (int j = 0; j < 157; ++j)
			index_temp[index_null[j]] = 1;
		for (int j = 0; j < 3; ++j)
			index_temp[255 + j] = 1;
		for (int j = 0; j < 16; ++j)//填充导频
		{
			index_temp[index_pl[Nsyms_temp][j]] = 1;
			syms_temp[index_pl[Nsyms_temp][j]] = complex<double> (1, 0);
		}
		int syms_cnt = 0;
		for (int j = 0; j < 512; ++j)
		{
			if (index_temp[j] == 0)
			{
				syms_temp[j] = symsin[i * 336 + syms_cnt];
				++syms_cnt;
			}
		}
		if (ti == 1)
			HSI_toneinter(syms_temp);
		IFFT(syms_temp, fft_size);
		for (int j = 0; j < 64; ++j)//循环前缀64
			symsout.push_back(syms_temp[j] * sqrt(512.0));
		for (int j = 0; j < 512; ++j)
			symsout.push_back(syms_temp[j] * sqrt(512.0));
	}
}