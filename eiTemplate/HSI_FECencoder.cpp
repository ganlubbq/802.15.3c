//HSIǰ�����ģ�飺���뷽ʽLDPC����
//�������룺vbitsin-������أ�vbitsout-������أ�UEP-EEP/UEP��ʽ(0/1)��FECrate-ǰ���������:1/2-0; 5/8-1; 3/4-2; 7/8-3

#include "genParam.h"
#include "stdafx.h"

using namespace std;

void HSI_FECencoder(vector<int> &vbitsin, vector<int> &vbitsout, int UEP, int FECrate)
{
	if (UEP == 0)//EEP
	{
		vector<int> vlower, vupper;
		int Nbits = vbitsin.size();
		int Nblock = Nbits / 16;//ÿ16���ؽ��з���
		for (int i = 0; i < Nblock; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				vupper.push_back(vbitsin[16 * i + j]);
				vlower.push_back(vbitsin[16 * i + 8 + j]);
			}
		}
		vector<int> vfec_up;
		vector<int> vfec_low;
		HSI_LDPCencoder(vupper, vfec_up, FECrate);
		HSI_LDPCencoder(vlower, vfec_low, FECrate);
		for (decltype(vfec_low.size()) i = 0; i < vfec_low.size(); i++)
		{
			vbitsout.push_back(vfec_up[i]);
			vbitsout.push_back(vfec_low[i]);
		}
	}
	else
	{
		switch (FECrate)
		{
		case 0:
			{
				vector<int> vlower, vupper;
				int Nbits = vbitsin.size();
				int Nblock = Nbits / 16;//ÿ16���ؽ��з���
				for (int i = 0; i < Nblock; i++)
				{
					for (int j = 0; j < 8; j++)
					{
						vupper.push_back(vbitsin[16 * i + j]);
						vlower.push_back(vbitsin[16 * i + 8 + j]);
					}
				}
				vector<int> vfec_up;
				vector<int> vfec_low;
				int FECrate_up = 0;
				int FECrate_low = 2;
				HSI_LDPCencoder(vupper, vfec_up, FECrate_up);//��û��LDPC����
				HSI_LDPCencoder(vlower, vfec_low, FECrate_low);
				auto Bmux = vfec_up.size() / 3;
				for (decltype(Bmux) i = 0; i < Bmux; i++)//���ݸ���
				{
					vbitsout.push_back(vfec_up[i * 3 + 0]);
					vbitsout.push_back(vfec_low[i * 2 + 0]);
					vbitsout.push_back(vfec_up[i * 3 + 1]);
					vbitsout.push_back(vfec_low[i * 2 + 1]);
					vbitsout.push_back(vfec_up[i * 3 + 2]);
				}
				break;
			}
		case 2:
			{
				vector<int> vlower, vupper;
				int Nbits = vbitsin.size();
				int Nblock = Nbits / 16;//ÿ16���ؽ��з���
				for (int i = 0; i < Nblock; i++)
				{
					for (int j = 0; j < 8; j++)
					{
						vupper.push_back(vbitsin[16 * i + j]);
						vlower.push_back(vbitsin[16 * i + 8 + j]);
					}
				}
				vector<int> vfec_up;
				vector<int> vfec_low;
				int FECrate_up = 2;
				int FECrate_low = 3;
				HSI_LDPCencoder(vupper, vfec_up, FECrate_up);//��û��LDPC����
				HSI_LDPCencoder(vlower, vfec_low, FECrate_low);
				int Bmux = vfec_up.size() / 7;
				for (int i = 0; i < Bmux; i++)//���ݸ���
				{
					vbitsout.push_back(vfec_up[i * 7 + 0]);
					vbitsout.push_back(vfec_low[i * 6 + 0]);
					vbitsout.push_back(vfec_up[i * 7 + 1]);
					vbitsout.push_back(vfec_low[i * 6 + 1]);
					vbitsout.push_back(vfec_up[i * 7 + 2]);
					vbitsout.push_back(vfec_low[i * 6 + 2]);
					vbitsout.push_back(vfec_up[i * 7 + 3]);
					vbitsout.push_back(vfec_low[i * 6 + 3]);
					vbitsout.push_back(vfec_up[i * 7 + 4]);
					vbitsout.push_back(vfec_low[i * 6 + 4]);
					vbitsout.push_back(vfec_up[i * 7 + 5]);
					vbitsout.push_back(vfec_low[i * 6 + 5]);
					vbitsout.push_back(vfec_up[i * 7 + 6]);
				}
				break;
			}
		default:
			{
				cout << "FECrate������󣡣���" << endl;
			}
		}
	}
}
