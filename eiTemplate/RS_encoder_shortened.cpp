//函数说明：RS编码，输入dataIn：为码片个数的8倍，而且其个数小于239*8; 输出data_out为空容器；
#include "genParam.h"
#include "stdafx.h"

using namespace std;

void RS_encoder_shortend(vector<int> &dataIn, vector<int> &data_out)
{
	int stuffbits_num = 239 * 8 - dataIn.size();
	vector<int> rs_in_temp(dataIn);
	vector<int> rs_out_temp;
	for (int i = 0; i < stuffbits_num; ++i)
		rs_in_temp.push_back(0);
	RS_encoder(rs_in_temp, rs_out_temp, 1);
	for (int i = 0; i < dataIn.size(); ++i)
		data_out.push_back(rs_out_temp[i]);
	for (int i = 0; i < 128; ++i)
		data_out.push_back(rs_out_temp[239 * 8 + i]);
}