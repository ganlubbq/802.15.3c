//����������AV-PHY��LRP�������
//���������codebits-��������ı������У�SSID-��λ�����ʼֵ��
//#include<iostream>
#include"genParam.h"
#include "stdafx.h"

using namespace std;

void scrambler_LRP(vector<int> &codebits, vector<int> &ssid, int type)
{
	switch (type)
	{
	case 0:
		break;
	case 1:
		{
			int Nbits = codebits.size();
			vector<int> prbs;
			scrambler_gen_prbs_LRP(ssid, prbs, Nbits);
			for(int i = 0; i < Nbits; i++)
				codebits[i] = codebits[i] ^ prbs[i];
			break;
		}
	default:
		break;
	}
}