//����˵����HSI��֯����ÿ�ĸ�LDPC�������֣�2688bits�����н�֯����, inter_index: 0-�����б��ؽ�֯�� 1�����б��ؽ�֯
//����˵����bitsin��������أ�bitsout��������أ�bitsnums��������

//#include<iostream>
#include"genParam.h"
#include "stdafx.h"

using namespace std;

void HSI_interleaver(vector<int> &bitsin, vector<int> &bitsout, int inter_index)
{
	switch (inter_index)
	{
	case 0:
		{
			for (int i = 0; i < bitsin.size(); ++i)
				bitsout.push_back(bitsin[i]);
			break;
		}
	case 1:
		{
			int bitsnums = bitsin.size();
			int Nblocks = bitsnums / 2688;//��֯���ݿ�
			int *inter_temp = new int [2688];
			for (int i = 0; i < Nblocks; i++)
			{
				for (int j = 0; j < 2688; j++)
					inter_temp[j] = bitsin[2688 * i + j];
				for (int j = 0; j < 2688; j++)
				{
					int index_temp = (2688 - 24 + j + 2 * 24 * ((j * 24 - j) % 2688)) % 2688;//��֯����
					//bitsout[2688 * i + j] = inter_temp[index_temp];
					bitsout.push_back(inter_temp[index_temp]);
				}
			}
			delete [] inter_temp;
			break;
		}
	default:
		{
			cout << "�����������" << endl;
			break;
		}
	}
	//int bitsnums = bitsin.size();
	//int Nblocks = bitsnums / 2688;//��֯���ݿ�
	//int *inter_temp = new int [2688];
	//for (int i = 0; i < Nblocks; i++)
	//{
	//	for (int j = 0; j < 2688; j++)
	//		inter_temp[j] = bitsin[2688 * i + j];
	//	for (int j = 0; j < 2688; j++)
	//	{
	//		int index_temp = (2688 - 24 + j + 2 * 24 * ((j * 24 - j) % 2688)) % 2688;//��֯����
	//		//bitsout[2688 * i + j] = inter_temp[index_temp];
	//		bitsout.push_back(inter_temp[index_temp]);
	//	}
	//}
	//delete [] inter_temp;
}