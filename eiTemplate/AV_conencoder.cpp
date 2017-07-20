//����������AV-PHY�������ģ��
//���������bitsin:��������;con_A:���������A��con_B:���������B��con_C:���������C��con_D:���������D��con_E:���������E��con_F:���������F��con_G:���������G��con_H:���������H��
//        rate_up:upper֧·���ʣ�rate_low:lower֧·����;ueptype��0-EEP��1-UEP, 2-MSB_only
#include "genParam.h"
#include "stdafx.h"
using namespace std;

void AV_conencoder(vector<int> &in_upper, vector<int> &in_lower, vector<int> &con_A, vector<int> &con_B, vector<int> &con_C, vector<int> &con_D, vector<int> &con_E, vector<int> &con_F, vector<int> &con_G, vector<int> &con_H, int rate_up, int rate_low,int ueptype)
{
	switch (ueptype)
	{
	case 0:
		{
			int Nbits = in_upper.size() / 4;//ÿ������������ı�����
			vector<int> temp_A (Nbits, 0);
			vector<int> temp_B (Nbits, 0);
			vector<int> temp_C (Nbits, 0);
			vector<int> temp_D (Nbits, 0);
			vector<int> temp_E (Nbits, 0);
			vector<int> temp_F (Nbits, 0);
			vector<int> temp_G (Nbits, 0);
			vector<int> temp_H (Nbits, 0);
			for (int i = 0; i < Nbits; ++i)
			{
				temp_A[i] = in_upper[i];
				temp_B[i] = in_upper[Nbits * 1 + i];
				temp_C[i] = in_upper[Nbits * 2 + i];
				temp_D[i] = in_upper[Nbits * 3 + i];
				temp_E[i] = in_lower[i];
				temp_F[i] = in_lower[Nbits * 1 + i];
				temp_G[i] = in_lower[Nbits * 2 + i];
				temp_H[i] = in_lower[Nbits * 3 + i];
			}
			conencoder(temp_A, con_A, rate_up);
			conencoder(temp_B, con_B, rate_up);
			conencoder(temp_C, con_C, rate_up);
			conencoder(temp_D, con_D, rate_up);
			conencoder(temp_E, con_E, rate_low);
			conencoder(temp_F, con_F, rate_low);
			conencoder(temp_G, con_G, rate_low);
			conencoder(temp_H, con_H, rate_low);
			break;
		}
	case 1:
		{
			int Nbits = in_upper.size() / 4;//ÿ������������ı�����
			vector<int> temp_A (Nbits, 0);
			vector<int> temp_B (Nbits, 0);
			vector<int> temp_C (Nbits, 0);
			vector<int> temp_D (Nbits, 0);
			vector<int> temp_E (Nbits, 0);
			vector<int> temp_F (Nbits, 0);
			vector<int> temp_G (Nbits, 0);
			vector<int> temp_H (Nbits, 0);
			for (int i = 0; i < Nbits; ++i)
			{
				temp_A[i] = in_upper[i];
				temp_B[i] = in_upper[Nbits * 1 + i];
				temp_C[i] = in_upper[Nbits * 2 + i];
				temp_D[i] = in_upper[Nbits * 3 + i];
				temp_E[i] = in_lower[i];
				temp_F[i] = in_lower[Nbits * 1 + i];
				temp_G[i] = in_lower[Nbits * 2 + i];
				temp_H[i] = in_lower[Nbits * 3 + i];
			}
			conencoder(temp_A, con_A, rate_up);
			conencoder(temp_B, con_B, rate_up);
			conencoder(temp_C, con_C, rate_up);
			conencoder(temp_D, con_D, rate_up);
			conencoder(temp_E, con_E, rate_low);
			conencoder(temp_F, con_F, rate_low);
			conencoder(temp_G, con_G, rate_low);
			conencoder(temp_H, con_H, rate_low);
			break;
		}
	case 2:
		{
			int Nbits = in_upper.size() / 4;//ÿ������������ı�����
			vector<int> temp_A (Nbits, 0);
			vector<int> temp_B (Nbits, 0);
			vector<int> temp_C (Nbits, 0);
			vector<int> temp_D (Nbits, 0);
			vector<int> temp_E (Nbits, 0);
			vector<int> temp_F (Nbits, 0);
			vector<int> temp_G (Nbits, 0);
			vector<int> temp_H (Nbits, 0);
			for (int i = 0; i < Nbits; ++i)
			{
				temp_A[i] = in_upper[i];
				temp_B[i] = in_upper[Nbits * 1 + i];
				temp_C[i] = in_upper[Nbits * 2 + i];
				temp_D[i] = in_upper[Nbits * 3 + i];
				temp_E[i] = in_lower[i];
				temp_F[i] = in_lower[Nbits * 1 + i];
				temp_G[i] = in_lower[Nbits * 2 + i];
				temp_H[i] = in_lower[Nbits * 3 + i];
			}
			conencoder(temp_A, con_A, rate_up);
			conencoder(temp_B, con_B, rate_up);
			conencoder(temp_C, con_C, rate_up);
			conencoder(temp_D, con_D, rate_up);
			conencoder(temp_E, con_E, rate_low);
			conencoder(temp_F, con_F, rate_low);
			conencoder(temp_G, con_G, rate_low);
			conencoder(temp_H, con_H, rate_low);
			break;
		}
	default:
		{
			cout << "UEPģʽѡ����󣡣�����" << endl;
			exit(EXIT_FAILURE);
			break;
		}
	}
}