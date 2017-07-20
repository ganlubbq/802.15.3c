//#include <iostream>
#include "genParam.h"
#include "stdafx.h"

using namespace std;

void rotateZ(int index, double a[][21])
{
	double z[21][21] = {0};
	for(int i = 0; i < 21; i++)
	{
		z[i][i] = 1;
	}
	int p[21]={0};
	for(int i = 0; i < 21; i++)
	{
		p[i] = i;
	}
	for(int i = 0; i < 21; i++)
	{
		p[i] = (21 - index + p[i]) % 21;
	}
	for(int i = 0; i < 21; i++ )
	{
		for (int j = 0; j < 21; j++)
		{
			a[j][i] = z[j][int(p[i])]; 
		}
	}
}