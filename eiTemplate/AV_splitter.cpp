//����������AV-PHY���ݷ���ģ��
//����������codebits-������أ�bits_up-�����upper��������bits_low-�����lower��������Nbits-����ı�������
//        ueptype-0:EEPģʽ(ע�������������32�ı������� 1��UEPģʽ(ע�������������16�ı�������2:�����з�������Ϣ������bits_up

//#include<iostream>
//#include<cstdlib>
#include"genParam.h"
#include "stdafx.h"


using namespace std;
void AV_splitter(vector<int> &codebits, vector<int> &bits_up, vector<int> &bits_low, int ueptype)
{
	int Nbits = codebits.size();
	switch (ueptype)
	{
	case 0:
		{
			int test = Nbits % 32;//���������
			if (test == 0)
			{
				const int Nblocks = Nbits / 32;//���ݿ���Ŀ
				int bits_temp[32]; 
				for (int i = 0; i < Nblocks; i++)
				{
					for (int j = 0; j < 32; j++)
						bits_temp[j] = codebits[32 * i + j];
					for (int ii = 0; ii < 4; ii++)
						//bits_low[16 * i + ii] = bits_temp[ii];
						bits_low.push_back(bits_temp[ii]);
					for (int ii = 0; ii < 4; ii++)
						//bits_low[16 * i + 4 + ii] = bits_temp[8 + ii];
						bits_low.push_back(bits_temp[8 + ii]);
					for (int ii = 0; ii < 4; ii++)
						//bits_low[16 * i + 8 + ii] = bits_temp[4 + ii];
						bits_low.push_back(bits_temp[4 + ii]);
					for (int ii = 0; ii < 4; ii++)
						//bits_low[16 * i + 12 + ii] = bits_temp[12 + ii];
						bits_low.push_back(bits_temp[12 + ii]);//���low����
					for (int ii = 0; ii < 4; ii++)
						//bits_up[16 * i + ii] = bits_temp[16 + ii];
						bits_up.push_back(bits_temp[16 + ii]);
					for (int ii = 0; ii < 4; ii++)
						//bits_up[16 * i + 4 + ii] = bits_temp[16 + 8 + ii];
						bits_up.push_back(bits_temp[16 + 8 + ii]);
					for (int ii = 0; ii < 4; ii++)
						//bits_up[16 * i + 8 + ii] = bits_temp[16 + 4 + ii];
						bits_up.push_back(bits_temp[16 + 4 + ii]);
					for (int ii = 0; ii < 4; ii++)
						//bits_up[16 * i + 12 + ii] = bits_temp[16 + 12 + ii];
						bits_up.push_back(bits_temp[16 + 12 + ii]);//���upper����

				}
			}
			else
			{
				cout << "���������Ŀ����" << endl;
				exit(EXIT_FAILURE);
			}
			break;
		}
	case 1:
		{
			int test = Nbits % 16;//���������
			if (test == 0)
			{
				const int Nblocks = Nbits / 16;//���ݿ���Ŀ
				int bits_temp[16]; 
				for (int i = 0; i < Nblocks; i++)
				{
					for (int j = 0; j < 16; j++)
						bits_temp[j] = codebits[16 * i + j];
					for (int ii = 0; ii < 4; ii++)
						//bits_low[8 * i + ii] = bits_temp[ii];
						bits_low.push_back(bits_temp[ii]);
					for (int ii = 0; ii < 4; ii++)
						//bits_low[8 * i + 4 + ii] = bits_temp[8 + ii];
						bits_low.push_back(bits_temp[8 + ii]);//���low����
					for (int ii = 0; ii < 4; ii++)
						//bits_up[8 * i + ii] = bits_temp[4 + ii];
						bits_up.push_back(bits_temp[4 + ii]);
					for (int ii = 0; ii < 4; ii++)
						//bits_up[8 * i + 4 + ii] = bits_temp[12 + ii];
						bits_up.push_back(bits_temp[12 + ii]);//���upper����
				}
			}
			else
			{
				cout << "���������Ŀ����" << endl;
				exit(EXIT_FAILURE);
			}
			break;
		}
	case 2:
		{
			int test = Nbits % 32;//���������
			if (test == 0)
			{
				const int Nblocks = Nbits / 32;//���ݿ���Ŀ
				int bits_temp[32]; 
				for (int i = 0; i < Nblocks; i++)
				{
					for (int j = 0; j < 32; j++)
						bits_temp[j] = codebits[32 * i + j];
					for (int ii = 0; ii < 4; ii++)
						//bits_low[16 * i + ii] = bits_temp[ii];
						bits_low.push_back(bits_temp[ii]);
					for (int ii = 0; ii < 4; ii++)
						//bits_low[16 * i + 4 + ii] = bits_temp[8 + ii];
						bits_low.push_back(bits_temp[8 + ii]);
					for (int ii = 0; ii < 4; ii++)
						//bits_low[16 * i + 8 + ii] = bits_temp[4 + ii];
						bits_low.push_back(bits_temp[4 + ii]);
					for (int ii = 0; ii < 4; ii++)
						//bits_low[16 * i + 12 + ii] = bits_temp[12 + ii];
						bits_low.push_back(bits_temp[12 + ii]);//���low����
					for (int ii = 0; ii < 4; ii++)
						//bits_up[16 * i + ii] = bits_temp[16 + ii];
						bits_up.push_back(bits_temp[16 + ii]);
					for (int ii = 0; ii < 4; ii++)
						//bits_up[16 * i + 4 + ii] = bits_temp[16 + 8 + ii];
						bits_up.push_back(bits_temp[16 + 8 + ii]);
					for (int ii = 0; ii < 4; ii++)
						//bits_up[16 * i + 8 + ii] = bits_temp[16 + 4 + ii];
						bits_up.push_back(bits_temp[16 + 4 + ii]);
					for (int ii = 0; ii < 4; ii++)
						//bits_up[16 * i + 12 + ii] = bits_temp[16 + 12 + ii];
						bits_up.push_back(bits_temp[16 + 12 + ii]);//���upper����

				}
			}
			else
			{
				cout << "���������Ŀ����" << endl;
				exit(EXIT_FAILURE);
			}
			break;
		}
	default:
		{
			cout << "UEPģʽ�������" << endl;
			exit(EXIT_FAILURE);
			break;
		}
	}
}
