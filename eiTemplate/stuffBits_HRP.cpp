//SC mode 比特填充

#include "genParam.h"
#include "stdafx.h"

using namespace std;

void stuffBits_HRP(vector<int> &bitsin, AV_param &AV_p)
{
	int NBits = bitsin.size();		//输入比特长度
	int stuff_mod = 0;
	if (AV_p.MCS == 5 || AV_p.MCS == 6)
		stuff_mod = 216 * 32;
	else
		stuff_mod = 216 * 16;
	int L_stuff = ceil(NBits, stuff_mod) * stuff_mod - NBits;	//the length of stuff bits
	for (int i = 0; i < L_stuff; ++i)
		bitsin.push_back(0);
}