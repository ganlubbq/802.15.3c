//函数描述：AV-PHY数据复用时所用交织器
//函数参数：codebits-输入的48(EEP),96(UEP)个比特；ueptype-uep模式，0-EEP，1-UEP， 

//#include<iostream>
//#include<cmath>
//#include<cstdlib>
#include"genParam.h"
#include "stdafx.h"
using namespace std;

void AV_inner_interleaver(vector<int> &codebits, int ueptype)
{
	switch (ueptype)
	{
	case 0:
		{
			vector<int> bits_temp;
			for (int i = 0; i < codebits.size(); i++)
				bits_temp.push_back(codebits[i]);//保存输入比特
			for (int i = 0; i < 48; i++)
	        {
				int index =  mod((6 * floor(i * 1.0 / 6) - 5 * mod(i, 6)), 48);//交织规则
			    codebits[index] = bits_temp[i];
	        }
			break;
		}
	case 1:
		{
			vector<int> bits_temp_01;
			vector<int> bits_temp_02;
			vector<int> bits_temp_01_inter (48, 0);
			vector<int> bits_temp_02_inter (48, 0);
			vector<int> bits_temp;
			for (int i = 0; i < codebits.size(); i++)
				bits_temp.push_back(codebits[i]);//保存输入比特
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 7; j++)
					bits_temp_01.push_back(bits_temp[14 * i + j]);
			}
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 5; j++)
					bits_temp_01.push_back(bits_temp[56 + 10 * i + j]);
			}//按协议保存上半48比特
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 7; j++)
					bits_temp_02.push_back(bits_temp[14 + 14 * i + 7 + j]);
			}
			for (int i = 0; i < 7; i++)
				bits_temp_02.push_back(bits_temp[7 + i]);
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 5; j++)
					bits_temp_02.push_back(bits_temp[56 + 10 * (i + 1) + 5 + j]);
			}
			for (int i = 0; i < 5; i++)
				//bits_temp_02[43 + i] = bits_temp[61 + i];
				bits_temp_02.push_back(bits_temp[61 + i]);//按协议填充下半48比特
			for (int i = 0; i < 48; i++)//上半48比特交织
	        {
				int index =  mod((6 * floor(i * 1.0 / 6) - 5 * mod(i, 6)), 48);//交织规则
			    bits_temp_01_inter[index] = bits_temp_01[i];
				bits_temp_02_inter[index] = bits_temp_02[i];
	        }
			for (int i = 0; i < 48; i++)
			{
				codebits[i] = bits_temp_01_inter[i];
				codebits[48 + i] = bits_temp_02_inter[i];
			}
			break;
		}
	case 2:
		{
			vector<int> bits_temp;
			for (int i = 0; i < codebits.size(); i++)
				bits_temp.push_back(codebits[i]);//保存输入比特
			for (int i = 0; i < 48; i++)
			{
				int index =  mod((6 * floor(i * 1.0 / 6) - 5 * mod(i, 6)), 48);//交织规则
				codebits[index] = bits_temp[i];
			}
			break;
		}
	default:
		{
			cout << "UEP模式输入错误!" << endl;
			exit(EXIT_FAILURE);
		}
	}
}