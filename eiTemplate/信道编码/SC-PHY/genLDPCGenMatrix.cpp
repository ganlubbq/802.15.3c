//#include <iostream>
//#include <vector>
#include "genParam.h"
#include "stdafx.h"

using namespace std;
//codeIndex码率选择
void genLDPCGenMatrix(int codeIndex, vector<vector<double> > &nZindexTable)
{
	int N,D,r,c,k;
	int Max = 0;
	ifstream inf; //假设数据保存在c:\da.txt文件中
	switch (codeIndex)
	{
	case 0:
		{
			N = 1;   D = 2; r = 16; c = 32; Max = 194;
			inf.open("codeIndex0.txt");
			break;
		}
	case 1:
		{		
			N = 5;   D = 8; r = 12; c = 32; Max = 59;
			inf.open("codeIndex1.txt");	
			break;
		}	
	case 2:
		{
			N = 3;   D = 4; r = 8; c = 32; Max = 91;
			inf.open("codeIndex2.txt");	
			break;
		}	
	case 3:
		{
			N = 7;  D = 8; r = 4; c = 32; Max = 139;
			inf.open("codeIndex3.txt");
			break;
		}
	case 4:
		{
			N = 14; D = 15; Max = 129;
			inf.open("codeIndex4.txt");
			break;
		}
	default:
		std::cout<<"Invalid Code Index"<<std::endl;
		break;
	}
	if (codeIndex != 4)
		k = r * 21;
	else
		k = 96;
	nZindexTable.resize(k,vector<double>(Max,0));
	for (int i =0;i < k;i++ )
	{
		for (int j =0;j < Max;j++)
		{
			inf>>nZindexTable[i][j];
		}
	}
	inf.close(); //读取完毕后,关闭文件
}

