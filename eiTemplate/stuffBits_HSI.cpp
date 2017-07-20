//HSI mode 比特填充

#include "genParam.h"
#include "stdafx.h"

using namespace std;

void stuffBits_HSI(vector<int> &bitsin, HSI_param &HSI_p)
{
	int NBits = bitsin.size();		//输入比特长度
	int preStuff = ceil(NBits, 8) * 8 - NBits;
	NBits = NBits + preStuff;
	for (int i = 0; i < preStuff; ++i)	//保证是8的倍数
		bitsin.push_back(0);
	int Lcode_MSB = 0;					//前向编码码字长度
	int Ldata_MSB = 0;					//码字信息位长度
	int Lcode_LSB = 0;					//前向编码码字长度
	int Ldata_LSB = 0;					//码字信息位长度
	int L_MUX = 0;
	switch (HSI_p.MCS) 
	{
	case 0:
		{
			Lcode_MSB = 672;
			Ldata_MSB = 336;
			Lcode_LSB = 672;
			Ldata_LSB = 336;
			L_MUX = 336;
			break;
		}
	case 1:
		{
			Lcode_MSB = 672;
			Ldata_MSB = 336;
			Lcode_LSB = 672;
			Ldata_LSB = 336;
			L_MUX = 336;
			break;
		}
	case 2:
		{
			Lcode_MSB = 672;
			Ldata_MSB = 504;
			Lcode_LSB = 672;
			Ldata_LSB = 504;
			L_MUX = 504;
			break;
		}
	case 3:
		{
			Lcode_MSB = 672;
			Ldata_MSB = 588;
			Lcode_LSB = 672;
			Ldata_LSB = 588;
			L_MUX = 588;
			break;
		}
	case 4:
		{
			Lcode_MSB = 672;
			Ldata_MSB = 336;
			Lcode_LSB = 672;
			Ldata_LSB = 336;
			L_MUX = 336;
			break;
		}
	case 5:
		{
			Lcode_MSB = 672;
			Ldata_MSB = 504;
			Lcode_LSB = 672;
			Ldata_LSB = 504;
			L_MUX = 504;
			break;
		}
	case 6:
		{
			Lcode_MSB = 672;
			Ldata_MSB = 588;
			Lcode_LSB = 672;
			Ldata_LSB = 588;
			L_MUX = 588;
			break;
		}
	case 7:
		{
			Lcode_MSB = 672;
			Ldata_MSB = 420;
			Lcode_LSB = 672;
			Ldata_LSB = 420;
			L_MUX = 420 * 3;
			break;
		}
	case 8:
		{
			Lcode_MSB = 672;
			Ldata_MSB = 336;
			Lcode_LSB = 672;
			Ldata_LSB = 504;
			L_MUX = 1008 * 4;
			break;
		}
	case 9:
		{
			Lcode_MSB = 672;
			Ldata_MSB = 504;
			Lcode_LSB = 672;
			Ldata_LSB = 588;
			L_MUX = 3528 * 4;
			break;
		}
	case 10:
		{
			Lcode_MSB = 672;
			Ldata_MSB = 336;
			Lcode_LSB = 672;
			Ldata_LSB = 504;
			L_MUX = 1008 * 4;
			break;
		}
	case 11:
		{
			Lcode_MSB = 672;
			Ldata_MSB = 504;
			Lcode_LSB = 672;
			Ldata_LSB = 588;
			L_MUX = 3528 * 4;
			break;
		}
	default:
		break;
	}
	int stuff_FEC = (ceil((NBits / 2), L_MUX) * L_MUX - NBits / 2) * 2; //stuff bits for FECencode
	NBits = NBits + stuff_FEC;
	for (int i = 0; i < stuff_FEC; ++i)
		bitsin.push_back(0);
}