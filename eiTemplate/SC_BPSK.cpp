//����˵����codebits:��Ҫ�������Ƶ�bit����;Nbits:�������еı�����
//#include<iostream>
#include"genParam.h"
#include "stdafx.h"

using namespace std;

void SC_BPSK(vector<int> &codebits)
{
	int Nbits = codebits.size();
	for(int i=0; i<Nbits; i++)
		codebits[i] = codebits[i] * 2 - 1;
}