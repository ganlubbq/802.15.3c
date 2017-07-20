//参数说明：codebits:需要进过调制的bit序列;Nbits:比特序列的比特数
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