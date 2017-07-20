//����������AV-PHY�⽻֯ģ�飬��֯���Ϊ2��4��
//����������codebits-������أ�Nbits-����ı���������depth-��֯���2��4��

//#include<iostream>
//#include<cstdlib>
#include"genParam.h"
#include "stdafx.h"

using namespace std;

//void AV_outer_interleaver(int* codebits, int Nbits, int depth)
void AV_outer_interleaver(vector<int> &codebits, int depth)
{
	int Nbits = codebits.size();
	switch (depth)
	{
	case 2:
		{
			int* bits_temp = new int [Nbits];
			//for (int i = 0; i < Nbits; i++)
			//	bits_temp[i] = codebits[i];//�����������
			int num_test = Nbits % depth;
			if (num_test == 0)
			{
				const int Row = depth;
				const int Col = Nbits / depth;
				int** inter_temp = new int* [Row];
				for (int i = 0; i < Row; i++)
					inter_temp[i] = new int [Col];//��֯����
				for (int i = 0; i < Row; i++)
				{
					for (int j = 0; j < Col; j++)
						inter_temp[i][j] = codebits[i * Col + j];//�������������֯������
				}
				for (int i = 0; i < Col; i++)
				{
					for (int j = 0; j < Row; j++)
						codebits[i * Row + j] = inter_temp[j][i];//�������
				}
				for (int i = 0; i < Row; i++)
					delete [] inter_temp[i];
				delete [] inter_temp;
			}
			else
			{
				cout << "���������������" << endl;
			    exit(EXIT_FAILURE);
			}
			break;
		}
	case 4:
		{
			int* bits_temp = new int [Nbits];
			//for (int i = 0; i < Nbits; i++)
			//	bits_temp[i] = codebits[i];//�����������
			int num_test = Nbits % depth;
			if (num_test == 0)
			{
				const int Row = depth;
				const int Col = Nbits / depth;
				int** inter_temp = new int* [Row];
				for (int i = 0; i < Row; i++)
					inter_temp[i] = new int [Col];//��֯����
				for (int i = 0; i < Row; i++)
				{
					for (int j = 0; j < Col; j++)
						inter_temp[i][j] = codebits[i * Col + j];//�������������֯������
				}
				for (int i = 0; i < Col; i++)
				{
					for (int j = 0; j < Row; j++)
						codebits[i * Row + j] = inter_temp[j][i];//�������
				}
				for (int i = 0; i < Row; i++)
					delete [] inter_temp[i];
				delete [] inter_temp;
			}
			else
			{
				cout << "���������������" << endl;
			    exit(EXIT_FAILURE);
			}
			break;
		}
	default:
		{
			cout << "��֯ģʽ�������" << endl;
			exit(EXIT_FAILURE);
		}
	}
}