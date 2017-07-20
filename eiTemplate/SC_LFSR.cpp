//����˵����SC-PHY������Ƶ�����α�������
//����˵����Nbits-�����α���������Ŀ,prbs-�����α������У�
//#include<iostream>
#include"genParam.h"
#include "stdafx.h"

using namespace std;

void SC_LFSR(vector<int> &prbs, int Nbits)
{
	//int* prbs_temp= new int[Nbits+15];
	vector<int> prbs_temp ((Nbits + 15), 0);
	int init_bits[15] = {1,1,1,1,1,0,0,0,0,0,0,1,0,1,0} ;//��ʼ����
	for (int i = 0; i < 15; i++)
		prbs_temp[i] = init_bits[i];
	for (int i = 0; i < Nbits; i++)
	{
		prbs_temp[i+15] = prbs_temp[i] ^ prbs_temp[i+1];
		prbs.push_back(prbs_temp[i+15]);
	}
}