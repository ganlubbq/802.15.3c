/*����˵����AV PHY OFDM���ƣ�ÿ338�����ݷ��ŵ��Ƴ�һ�����ţ���0-78��434-511�����157����Ƶ��
          ��255��256��257�����3��ֱ��������16����Ƶ������ȫ���1*/

#include "genParam.h"
#include "stdafx.h"

using namespace std;

void AV_OFDMer(vector<complex<double> > &symsin, vector<complex<double> > &symsout, int ti)
{
	int nums_in = symsin.size();
	const int Nstuff = ceil(nums_in / 336.0) * 336 - nums_in;//���bits��
	for (int i = 0; i < Nstuff; ++i)
		symsin.push_back(complex<double>(0.0,0.0));//�����
	int Nsyms = Nstuff + nums_in;//����ķ��Ÿ���
	/***********************��Ƶӳ��******************************************/
	int fft_size = 512;
	int Nblocks = Nsyms / 336;//���ݿ����
	int index_null[157] = {0};//��Ƶλ��
	for (int i = 0; i < 79; ++i)
		index_null[i] = i;
	for (int i = 0; i < 78; ++i)
		index_null[79 + i] = 434 + i;
	int index_dc[3] = {255, 256, 257};//ֱ��λ��
	vector<vector<int> > index_pl;//��Ƶλ��
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
		int Nsyms_temp = mod(i, 22);//���ݷ��ű��ѡ������ز���λ��
		int index_temp[512] = {0};//�����Ƶ
		for (int j = 0; j < 157; ++j)
			index_temp[index_null[j]] = 1;
		for (int j = 0; j < 3; ++j)
			index_temp[255 + j] = 1;
		for (int j = 0; j < 16; ++j)//��䵼Ƶ
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
		for (int j = 0; j < 64; ++j)//ѭ��ǰ׺64
			symsout.push_back(syms_temp[j] * sqrt(512.0));
		for (int j = 0; j < 512; ++j)
			symsout.push_back(syms_temp[j] * sqrt(512.0));
	}
}