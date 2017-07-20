//函数描述：将数字转换为比特符号，最左位为最高位
//参数描述：num-输入的数字； *bits-存储数组； L_bits-要转化的比特数
#include "genParam.h"
#include "stdafx.h"

using namespace std;

void num2bits(int num, int *bits, int L_bits)
{
	int temp = num;
	for (int i = 0; i < L_bits; i++)
	{
		bits[L_bits - 1 -i] = temp % 2;
		temp = temp /2;
	}
}