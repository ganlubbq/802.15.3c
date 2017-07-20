//����������SC-PHY��Ƶ����
//����������bits_input-����ı������У�sp_out-��Ƶ�����nbits-����ı��ظ�����sp_index-��Ƶ����:1,2,4,6,64

//#include<iostream>
//#include<cstdlib>
#include"genParam.h"
#include "stdafx.h"

using namespace std;

void SC_spreader(vector<int> &bits_input, vector<int> &sp_out, int sp_index)
{
	int nbits = bits_input.size();
	int nbits_sp = sp_index * nbits;//��Ƶ�����������
	switch (sp_index)
	{
	case 1:
		for (int i = 0; i < bits_input.size(); ++i)
			sp_out.push_back(bits_input[i]);
		break;
	case 2:
		{
			//int* prbs = new int [nbits_sp];
			vector<int> prbs;
			SC_LFSR(prbs, nbits_sp);//������Ƶ�����α�������
			for (int i = 0; i < nbits; i++)
			{
				for (int j = 0; j < 2; j++)
				//sp_out[2*i+j] = bits_input[i]^prbs[2*i+j];
					sp_out.push_back(bits_input[i]^prbs[2*i+j]);//��Ƶ����䵽������
			}
			break;
		}
	case 4:
		{
			//int* prbs = new int [nbits_sp];
			vector<int> prbs;
			SC_LFSR(prbs, nbits_sp);//������Ƶ�����α�������
			for (int i = 0; i < nbits; i++)
			{
				for (int j = 0; j < 4; j++)
					//sp_out[4*i+j] = bits_input[i]^prbs[4*i+j];
					sp_out.push_back(bits_input[i]^prbs[4*i+j]);//��Ƶ����䵽������
			}
			break;
		}
	case 6:
		{
			vector<int> prbs;
			SC_LFSR(prbs, nbits_sp);//������Ƶ�����α�������
			for (int i = 0; i < nbits; i++)
			{
				for (int j = 0; j < 6; j++)
					//sp_out[6*i+j] = bits_input[i]^prbs[6*i+j]
					sp_out.push_back(bits_input[i]^prbs[6*i+j]);;//��Ƶ����䵽������
			}
			break;
		}
	case 64:
		{
			vector<int> prbs;
			SC_LFSR(prbs, nbits);//������Ƶ�����α�������,���ݴ�����ѡ���������a/b������Ƶ
			int a_golay_hex[16] = {0x6,0x3,0xA,0xF,0x0,0x5,0xC,0x9,0x6,0x3,0x5,0x0,0x0,0x5,0x3,0x6};
			int b_golay_hex[16] = {0x6,0xC,0xA,0x0,0x0,0xA,0xC,0x6,0x6,0xC,0x5,0xF,0x0,0xA,0x3,0x9};
			//int* a_golay_bit = new int [16*4];
			//int* b_golay_bit = new int [16*4];
			vector<int> a_golay_bit;
			vector<int> b_golay_bit;
			hex2binary(a_golay_hex, a_golay_bit, 16);
			hex2binary(b_golay_hex, b_golay_bit, 16);
			for (int i = 0; i < nbits; i++)
			{
				if (prbs[i] == 1)
				{
					for (int j = 0; j <64; j++)
						//sp_out[64*i+j] = bits_input[i]^a_golay_bit[j];
						sp_out.push_back(bits_input[i] ^ a_golay_bit[j]);
				}
				else
				{
					for (int j = 0; j <64; j++)
						//sp_out[64*i+j] = bits_input[i]^b_golay_bit[j];
						sp_out.push_back(bits_input[i] ^ b_golay_bit[j]);
				}
			}
			break;
		}
	default:
		cout<<"��Ƶ�����������"<<endl;
		exit(EXIT_FAILURE);
		break;
	}
}