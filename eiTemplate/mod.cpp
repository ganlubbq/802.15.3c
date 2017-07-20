//函数描述：mod函数，与%功能不同，mod(a, b)若为负数则先将a加b的最小整数倍为正后再做运算；
//函数参数：a，b输入，输出整数；
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
			//int nums = (int)(ceil(abs(a) * 1.0 / b));//最小倍数
			//int temp2 = nums * b + a;//最小整数；
			return (((int)ceil(abs(a) * 1.0 / b)) * b + a) % b;
		}
	}
	else
	{
		cout << "第二个变量应该大于零" << endl;
		exit(EXIT_FAILURE);
	}
}