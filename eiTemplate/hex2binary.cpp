//����������ʮ������ת��λ������
//����������hex-ʮ���������У�binary-����Ķ����Ʊ��أ�nhex-ת��������
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