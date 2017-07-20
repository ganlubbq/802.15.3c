//����������AV-PHY���ݸ���ģ��for Header
//����������bitsout-����������أ�A/B/C/D-�����a��������
#include"genParam.h"
#include "stdafx.h"
using namespace std;

void AV_multiplexer_Header(vector<int> &bitsout, vector<int> &A, vector<int> &B, vector<int> &C, vector<int> &D)
{
	int Nbits = A.size();
	int Nblocks = Nbits / 12;
	vector<int> mul_temp (48, 0);
	for (int i = 0; i < Nblocks; i++)
	{
		for (int j = 0; j < 6; j++)//ÿ��������������������ظ��ϳ�һ��48bit���ݿ�
		{
			mul_temp[j] = A[12 * i + j * 2];
			mul_temp[6 + j] = B[12 * i + j * 2];
			mul_temp[12 + j] = C[12 * i + j * 2];
			mul_temp[18 + j] = D[12 * i + j * 2];
			mul_temp[24 + j] = A[12 * i + j * 2 + 1];
			mul_temp[30 + j] = B[12 * i + j * 2 + 1];
			mul_temp[36 + j] = C[12 * i + j * 2 + 1];
			mul_temp[42 + j] = D[12 * i + j * 2 + 1];
		}
		AV_inner_interleaver(mul_temp, 0);//�����ݿ���н�֯
		for (int j = 0; j < 48; j++)
			bitsout.push_back(mul_temp[j]);
	}
}