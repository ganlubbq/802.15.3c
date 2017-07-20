//����������AV-PHY�������ģ��
//���������bitsin:��������;con_A:���������A��con_B:���������B��con_C:���������C��con_D:���������D��con_E:���������E��con_F:���������F��con_G:���������G��con_H:���������H��
//        rate_up:upper֧·���ʣ�rate_low:lower֧·����;ueptype��0-EEP��1-UEP, 2-MSB_only
#include "genParam.h"
#include "stdafx.h"
using namespace std;

void AV_conencoder_Header(vector<int> &bitsin, vector<int> &con_A, vector<int> &con_B, vector<int> &con_C, vector<int> &con_D)
{
	int Nbits = bitsin.size() / 4;//ÿ������������ı�����
	vector<int> temp_A (Nbits, 0);
	vector<int> temp_B (Nbits, 0);
	vector<int> temp_C (Nbits, 0);
	vector<int> temp_D (Nbits, 0);
	for (int i = 0; i < Nbits; ++i)
	{
		temp_A[i] = bitsin[i];
		temp_B[i] = bitsin[Nbits * 1 + i];
		temp_C[i] = bitsin[Nbits * 2 + i];
		temp_D[i] = bitsin[Nbits * 3 + i];
	}
	conencoder(temp_A, con_A, 0);
	conencoder(temp_B, con_B, 0);
	conencoder(temp_C, con_C, 0);
	conencoder(temp_D, con_D, 0);
}