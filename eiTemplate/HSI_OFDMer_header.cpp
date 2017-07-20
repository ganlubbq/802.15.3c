//函数描述：HSI macheader OFDM调制模块，512点fft，循环前缀长度128，其中数据子载波336个
//函数参数：OFDMin-输入符号；OFDMout-输出符号；nums-输入符号个数；

#include"genParam.h"
#include "stdafx.h"

using namespace std;

void HSI_OFDMer_header(vector<complex<double> > &OFDMin, vector<complex<double> > &OFDMout, int ti)
{
	int nums_in = OFDMin.size();
	const int Nstuff = ceil(nums_in / 336.0) * 336 - nums_in;;
	for (int i = 0; i < Nstuff; ++i)
		OFDMin.push_back(complex<double>(0.0,0.0));//填充零
	int nums = Nstuff + nums_in;//填充后的符号个数
	int fft_size = 512;
	const int Nofdm = nums / 336;//ofdm符号数
	/***********************载频映射******************************************/
	int index_temp[512] = {0};//总序列位置
	vector<complex<double> > data_temp_00 (336, complex<double>(0,0));//保存原始数据
	vector<complex<double> > data_temp_01 (512, complex<double>(0,0));//保存填充数据
	for (int i = 0; i < 512; i++)
		index_temp[i] = 0;//填充了信息的位置置1，反之置0
	int index_null[141] = {0};
	for (int i = 0; i < 71; i++)
		index_null[i] = i;
	for (int i = 0; i < 70; i++)
		index_null[71 + i] = 442 + i;//零频子载波位置
	complex<double> sub_null[141];
	for (int i = 0; i < 141; i++)
		sub_null[i] = complex<double> (0,0);//零频子载波信息
	int index_dc[3] = {0};
	for (int i = 0; i < 3; i++)
		index_dc[i] = 255 + i;//直流子载波位置
	complex<double> sub_dc[3];
	for (int i = 0; i < 3; i++)
		sub_dc[i] = complex<double> (1,0);//直流载波信息
	int index_pilot[16] = {0};
	for (int i = 0; i < 8; i++)
	{
		index_pilot[i] = 90 + 22 * i;
		index_pilot[i + 8] = 268 + 22 * i;
	}//导频子载波位置
	complex<double> sub_pilot_01[16] = {complex<double> (+1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),+1/sqrt(2.0)),
		complex<double> (+1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),+1/sqrt(2.0))};//导频子载波信息（正极性）
	complex<double> sub_pilot_00[16] = {complex<double> (-1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),-1/sqrt(2.0)),
		complex<double> (-1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),-1/sqrt(2.0))};//导频子载波信息（负极性）
	int ssid[4] = {0,0,0,0};
	vector<int> prbs;
	scrambler_gen_prbs(ssid, prbs, Nofdm);//产生伪随机序列决定导频极性
	int index_guard[16] = {0};
	for (int i = 0; i < 8; i++)
	{
		index_guard[i] = 71 + i;
		index_guard[i + 8] = 434 + i;
	}//保护子载波位置
	vector<complex<double> > sub_guard(16, complex<double>(0,0));//保护子载波信息
	for (int i = 0; i < Nofdm; i++)
	{
		for (int j = 0; j < 336; j++)//取得原始数据
			data_temp_00[j] = OFDMin[j + i * 336];
		for (int j = 0; j < 141; j++)//填充零频
		{
			index_temp[index_null[j]] = 1;
			data_temp_01[index_null[j]] = sub_null[j];
		}
		for (int j = 0; j < 3; j++)//填充直流
		{
			index_temp[index_dc[j]] = 1;
			data_temp_01[index_dc[j]] = sub_dc[j];
		}
		for (int j = 0; j < 16; j++)//填充导频
		{
			if (prbs[i] == 1)
			{
				index_temp[index_pilot[j]] = 1;
				data_temp_01[index_pilot[j]] = sub_pilot_01[j];
			}
			else
			{
				index_temp[index_pilot[j]] = 1;
				data_temp_01[index_pilot[j]] = sub_pilot_00[j];
			}
		}
		for (int j = 0; j < 16; j++)//填充保护
		{
			index_temp[index_guard[j]] = 1;
			data_temp_01[index_guard[j]] = sub_guard[j];
		}
		int data_index = 0;
		int count_temp = 0;//
		for (int i = 0; i < 512; ++i)
		{
			if(index_temp[i] == 0)
				count_temp++;
		}
		for (int j = 0; j < 512; j++)//剩余位置填入数据
		{
			if (index_temp[j] == 0)
			{
				data_temp_01[j] = data_temp_00[data_index];
				data_index++;
			}
		}
		if (ti == 1)
			HSI_toneinter(data_temp_01);//载波交织
		IFFT(data_temp_01, fft_size);//IFFT变换
		for (int j = 0; j < 128; j++)//循环前缀128
			//OFDMout[j + 640 * i] = data_temp_01[j];
			OFDMout.push_back(data_temp_01[j] * sqrt(512.0));// * sqrt(512.0)
		for (int j = 0; j < 512; j++)
			//OFDMout[j + 128 + 640 * i] = data_temp_01[j];
			OFDMout.push_back(data_temp_01[j] * sqrt(512.0));// * sqrt(512.0)
	}
}