//����������AV-PHY RS����ģ��
//���������in_upper:��֧·��������;in_lower:��֧·�������룻out_upper:��֧·���������out_lower��֧·���������ueptype:0-EEP,1-UEP,2-MSB only
#include"genParam.h"
#include "stdafx.h"

using namespace std;

void AV_RSencoder(vector<int> &in_upper, vector<int> &in_lower, vector<int> &out_upper, vector<int> &out_lower, int inter_depth)
{
	int Nbits = in_upper.size();
	int Nstuff_rs = 216 - Nbits % 216;
	for (int i = 0; i < Nstuff_rs; ++i)
	{
		in_upper.push_back(0);
		in_lower.push_back(0);
	}
	RS_encoder(in_upper, out_upper, 2);//RS����
	RS_encoder(in_lower, out_lower, 2);
	AV_outer_interleaver(out_upper, inter_depth);//��֯
	AV_outer_interleaver(out_lower, inter_depth);
}