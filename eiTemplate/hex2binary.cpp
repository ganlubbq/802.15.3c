//函数描述：十六进制转四位二进制
//参数描述：hex-十六进制序列；binary-输出的二进制比特；nhex-转换个数；
//#include<iostream>
#include"genParam.h"
#include "stdafx.h"

using namespace std;

void hex2binary(int hex[], vector<int> &binary, int nhex)
{
	for(int i = 0; i < nhex; i++)
	{
		/*binary[4*i] = (hex[i]/2/2/2)%2;
		binary[4*i+1] = (hex[i]/2/2)%2;
		binary[4*i+2] = (hex[i]/2)%2;
		binary[4*i+3] = hex[i]%2;*/
		binary.push_back((hex[i]/2/2/2)%2);
		binary.push_back((hex[i]/2/2)%2);
		binary.push_back((hex[i]/2)%2);
		binary.push_back(hex[i]%2);
	}
}