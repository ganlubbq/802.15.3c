//����������mod��������%���ܲ�ͬ��mod(a, b)��Ϊ�������Ƚ�a��b����С������Ϊ�����������㣻
//����������a��b���룬���������
//#include<iostream>
//#include<cmath>
//#include<cstdlib>
#include"genParam.h"
#include "stdafx.h"

using namespace std;
int mod(int a, int b)
{
	if (b > 0)
	{
		if (a >= 0)
			return a % b;
		else
		{
			//int nums = (int)(ceil(abs(a) * 1.0 / b));//��С����
			//int temp2 = nums * b + a;//��С������
			return (((int)ceil(abs(a) * 1.0 / b)) * b + a) % b;
		}
	}
	else
	{
		cout << "�ڶ�������Ӧ�ô�����" << endl;
		exit(EXIT_FAILURE);
	}
}