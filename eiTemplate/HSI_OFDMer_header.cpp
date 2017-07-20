//����������HSI macheader OFDM����ģ�飬512��fft��ѭ��ǰ׺����128�������������ز�336��
//����������OFDMin-������ţ�OFDMout-������ţ�nums-������Ÿ�����

#include"genParam.h"
#include "stdafx.h"

using namespace std;

void HSI_OFDMer_header(vector<complex<double> > &OFDMin, vector<complex<double> > &OFDMout, int ti)
{
	int nums_in = OFDMin.size();
	const int Nstuff = ceil(nums_in / 336.0) * 336 - nums_in;;
	for (int i = 0; i < Nstuff; ++i)
		OFDMin.push_back(complex<double>(0.0,0.0));//�����
	int nums = Nstuff + nums_in;//����ķ��Ÿ���
	int fft_size = 512;
	const int Nofdm = nums / 336;//ofdm������
	/***********************��Ƶӳ��******************************************/
	int index_temp[512] = {0};//������λ��
	vector<complex<double> > data_temp_00 (336, complex<double>(0,0));//����ԭʼ����
	vector<complex<double> > data_temp_01 (512, complex<double>(0,0));//�����������
	for (int i = 0; i < 512; i++)
		index_temp[i] = 0;//�������Ϣ��λ����1����֮��0
	int index_null[141] = {0};
	for (int i = 0; i < 71; i++)
		index_null[i] = i;
	for (int i = 0; i < 70; i++)
		index_null[71 + i] = 442 + i;//��Ƶ���ز�λ��
	complex<double> sub_null[141];
	for (int i = 0; i < 141; i++)
		sub_null[i] = complex<double> (0,0);//��Ƶ���ز���Ϣ
	int index_dc[3] = {0};
	for (int i = 0; i < 3; i++)
		index_dc[i] = 255 + i;//ֱ�����ز�λ��
	complex<double> sub_dc[3];
	for (int i = 0; i < 3; i++)
		sub_dc[i] = complex<double> (1,0);//ֱ���ز���Ϣ
	int index_pilot[16] = {0};
	for (int i = 0; i < 8; i++)
	{
		index_pilot[i] = 90 + 22 * i;
		index_pilot[i + 8] = 268 + 22 * i;
	}//��Ƶ���ز�λ��
	complex<double> sub_pilot_01[16] = {complex<double> (+1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),+1/sqrt(2.0)),
		complex<double> (+1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),+1/sqrt(2.0))};//��Ƶ���ز���Ϣ�������ԣ�
	complex<double> sub_pilot_00[16] = {complex<double> (-1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),-1/sqrt(2.0)),
		complex<double> (-1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),-1/sqrt(2.0))};//��Ƶ���ز���Ϣ�������ԣ�
	int ssid[4] = {0,0,0,0};
	vector<int> prbs;
	scrambler_gen_prbs(ssid, prbs, Nofdm);//����α������о�����Ƶ����
	int index_guard[16] = {0};
	for (int i = 0; i < 8; i++)
	{
		index_guard[i] = 71 + i;
		index_guard[i + 8] = 434 + i;
	}//�������ز�λ��
	vector<complex<double> > sub_guard(16, complex<double>(0,0));//�������ز���Ϣ
	for (int i = 0; i < Nofdm; i++)
	{
		for (int j = 0; j < 336; j++)//ȡ��ԭʼ����
			data_temp_00[j] = OFDMin[j + i * 336];
		for (int j = 0; j < 141; j++)//�����Ƶ
		{
			index_temp[index_null[j]] = 1;
			data_temp_01[index_null[j]] = sub_null[j];
		}
		for (int j = 0; j < 3; j++)//���ֱ��
		{
			index_temp[index_dc[j]] = 1;
			data_temp_01[index_dc[j]] = sub_dc[j];
		}
		for (int j = 0; j < 16; j++)//��䵼Ƶ
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
		for (int j = 0; j < 16; j++)//��䱣��
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
		for (int j = 0; j < 512; j++)//ʣ��λ����������
		{
			if (index_temp[j] == 0)
			{
				data_temp_01[j] = data_temp_00[data_index];
				data_index++;
			}
		}
		if (ti == 1)
			HSI_toneinter(data_temp_01);//�ز���֯
		IFFT(data_temp_01, fft_size);//IFFT�任
		for (int j = 0; j < 128; j++)//ѭ��ǰ׺128
			//OFDMout[j + 640 * i] = data_temp_01[j];
			OFDMout.push_back(data_temp_01[j] * sqrt(512.0));// * sqrt(512.0)
		for (int j = 0; j < 512; j++)
			//OFDMout[j + 128 + 640 * i] = data_temp_01[j];
			OFDMout.push_back(data_temp_01[j] * sqrt(512.0));// * sqrt(512.0)
	}
}