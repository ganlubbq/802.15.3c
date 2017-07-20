//����������AV-PHY�������ģ��
//���������codebits-������أ�bits_conved-������������
//        rate-��������(0:1/3; 1:1/2; 2:4/7; 3:2/3; 4:4/5) ��//Nbits-���������
#include"genParam.h"
#include "stdafx.h"

using namespace std;

void conencoder(vector<int> &codebits, vector<int> &bits_out, int rate)
{
	int Nbits = codebits.size();
	vector<int> X_temp (Nbits, 0);
	vector<int> Y_temp (Nbits, 0);
	vector<int> Z_temp (Nbits, 0);
	int reg_temp[6] = {0};//��ʼ��6λ������ȫ��
	for (int i = 0; i < Nbits; i++)
	{

		X_temp[i] = codebits[i] ^ reg_temp[1] ^ reg_temp[2] ^ reg_temp[4] ^ reg_temp[5];//���ɶ���ʽ133o
		Y_temp[i] = codebits[i] ^ reg_temp[0] ^ reg_temp[1] ^ reg_temp[2] ^ reg_temp[3] ^ reg_temp[5];//���ɶ���ʽ171o
		Z_temp[i] = codebits[i] ^ reg_temp[0] ^ reg_temp[1] ^ reg_temp[3] ^ reg_temp[5];//���ɶ���ʽ165o
		for(int j = 5; j > 0; j--)
			reg_temp[j] = reg_temp[j - 1]; 
		reg_temp[0] = codebits[i];//���üĴ���
	}//�õ��������ԭʼ���
	switch (rate)
	{
	case 0:
		{
			for (int i = 0; i < Nbits; i++)
			{
				bits_out.push_back(X_temp[i]);
				bits_out.push_back(Y_temp[i]);
				bits_out.push_back(Z_temp[i]);
			}//��Э��������Ϣ
			break;
		}
	case 1:
		{
			for (int i = 0; i < Nbits; i++)
			{
				bits_out.push_back(X_temp[i]);
				bits_out.push_back(Y_temp[i]);
			}//��Э��������Ϣ
			break;
		}
	case 2:
		{
			int test = Nbits % 4;
			if (test == 0)
			{
				int Nblocks = Nbits / 4;
				for (int i = 0; i < Nblocks; i++)
				{
					bits_out.push_back(X_temp[4 * i + 0]);
					bits_out.push_back(Y_temp[4 * i + 0]);
					bits_out.push_back(X_temp[4 * i + 1]);
					bits_out.push_back(X_temp[4 * i + 2]);
					bits_out.push_back(Y_temp[4 * i + 2]);
					bits_out.push_back(X_temp[4 * i + 3]);
					bits_out.push_back(Y_temp[4 * i + 3]);
				}//��Э��������Ϣ
			}
			else
			{
				cout << "�������������" << endl;
				exit(EXIT_FAILURE);
			}
			break;
		}
	case 3:
		{
			int test = Nbits % 2;
			if (test == 0)
			{
				int Nblocks = Nbits / 4;
				for (int i = 0; i < Nblocks; i++)
				{
					bits_out.push_back(X_temp[2 * i + 0]);
					bits_out.push_back(Y_temp[2 * i + 0]);
					bits_out.push_back(X_temp[2 * i + 1]);
				}//��Э��������Ϣ
			}
			else
			{
				cout << "�������������" << endl;
				exit(EXIT_FAILURE);
			}
			break;
		}
	case 4:
		{
			int test = Nbits % 4;
			if (test == 0)
			{
				int Nblocks = Nbits / 4;
				for (int i = 0; i < Nblocks; i++)
				{
					bits_out.push_back(X_temp[4 * i + 0]);
					bits_out.push_back(Y_temp[4 * i + 0]);
					bits_out.push_back(X_temp[4 * i + 1]);
					bits_out.push_back(X_temp[4 * i + 2]);
					bits_out.push_back(X_temp[4 * i + 3]);
				}//��Э��������Ϣ
			}
			else
			{
				cout << "�������������" << endl;
				exit(EXIT_FAILURE);
			}
			break;
		}
	default:
		{
			cout << "����ѡ�����" << endl;
			exit(EXIT_FAILURE);
			break;
		}
	}
}