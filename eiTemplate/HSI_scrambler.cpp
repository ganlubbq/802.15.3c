//����������HSI-PHY�������
//���������codebits-��������ı������У�SSID-��λ�����ʼֵ��NBits-��������ı���������
//#include<iostream>
#include"genParam.h"
#include "stdafx.h"

using namespace std;

void HSI_scrambler(vector<int> &codebits, int ssid[])
{
	int Nbits = codebits.size();
	//int* prbs = new int[Nbits];
	vector<int> prbs;
	scrambler_gen_prbs(ssid, prbs, Nbits);
	for(int i = 0; i < Nbits; i++)
		codebits[i] = codebits[i] ^ prbs[i];
}