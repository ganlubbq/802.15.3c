//#include <iostream>
#include "genParam.h"
#include "stdafx.h"

using namespace std;
//codeword[]    编码比特
//nZindex[][]   校验矩阵
//paritybits    校验比特
void genLDPCparity(vector<double> &codeword, vector<vector<double> > &nZindex, vector<double> &paritybits)
{
	for (int i = 0; i < nZindex.size(); i++)
	{
		int len = nZindex[i][0];
		int* nz = new int[len];
		int sum  = 0;
		for (int j = 0; j < len; j++)
		{
			nz[j] = nZindex[i][j + 1];	
		}
		for (int m = 0; m < len; m++)
		{
			sum += codeword[nz[m]-1];
		}
		paritybits[i] = sum % 2;
		delete [] nz;
	}
}