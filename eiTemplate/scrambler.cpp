//����������SC-PHY�������
//���������codebits-��������ı������У�SSID-��λ�����ʼֵ��NBits-��������ı���������
//#include<iostream>
#include"genParam.h"
#include "stdafx.h"

using namespace std;

void scrambler(vector<int> &codebits, int ssid[])
{
	int Nbits = codebits.size();
	vector<int> prbs;
	scrambler_gen_prbs(ssid, prbs, Nbits);
	for(int i = 0; i < Nbits; i++)
		codebits[i] = codebits[i] ^ prbs[i];
}