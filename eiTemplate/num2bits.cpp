//����������������ת��Ϊ���ط��ţ�����λΪ���λ
//����������num-��������֣� *bits-�洢���飻 L_bits-Ҫת���ı�����
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