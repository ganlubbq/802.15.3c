//函数描述：AV-PHY卷积编码模块
//输入参数：bitsin:编码输入;con_A:卷积编码器A；con_B:卷积编码器B；con_C:卷积编码器C；con_D:卷积编码器D；con_E:卷积编码器E；con_F:卷积编码器F；con_G:卷积编码器G；con_H:卷积编码器H；
//        rate_up:upper支路码率；rate_low:lower支路码率;ueptype：0-EEP，1-UEP, 2-MSB_only
#include "genParam.h"
#include "stdafx.h"
using namespace std;

void AV_conencoder_Header(vector<int> &bitsin, vector<int> &con_A, vector<int> &con_B, vector<int> &con_C, vector<int> &con_D)
{
	int Nbits = bitsin.size() / 4;//每个卷积编码器的比特数
	vector<int> temp_A (Nbits, 0);
	vector<int> temp_B (Nbits, 0);
	vector<int> temp_C (Nbits, 0);
	vector<int> temp_D (Nbits, 0);
	for (int i = 0; i < Nbits; ++i)
	{
		temp_A[i] = bitsin[i];
		temp_B[i] = bitsin[Nbits * 1 + i];
		temp_C[i] = bitsin[Nbits * 2 + i];
		temp_D[i] = bitsin[Nbits * 3 + i];
	}
	conencoder(temp_A, con_A, 0);
	conencoder(temp_B, con_B, 0);
	conencoder(temp_C, con_C, 0);
	conencoder(temp_D, con_D, 0);
}