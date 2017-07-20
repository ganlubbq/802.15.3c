//����˵����SC-PHYģʽ��SSID����α�������
//����˵����ssid-����α��������������λ�������У�prbs-���ɵ�α������У�Nbits-��Ҫ������������ı�����

//#include<iostream>
#include"genParam.h"
#include "stdafx.h"

using namespace std;

void scrambler_gen_prbs(int ssid[], vector<int> &prbs, int Nbits)
{
	vector<int> prbs_temp (Nbits + 15);//���������ʼ����
	for(int i = 0; i < 4; i++)
		prbs_temp[3-i] = ssid[i];
	int prbs_inif[11] = {1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1};
	for(int i = 0; i < 11; i++)
		prbs_temp[4+i] = prbs_inif[i];
	for(int i = 0; i < Nbits; i++)
	{
		int x = prbs_temp[i];
		int y = prbs_temp[i+1];
		int z = x ^ y;
		prbs_temp[i+15] = z;
		//prbs[i] = prbs_temp[i+15];
		prbs.push_back(prbs_temp[i+15]);
	}
}