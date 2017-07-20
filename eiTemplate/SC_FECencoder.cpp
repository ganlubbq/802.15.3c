/*函数描述：SC-PHY前向编码模块，输入：bitsin-编码输入，RS编码输入比特数为239的倍数，LDPC编码输入比特数同样为相应码率的倍数；
bitsout-编码输出；fectype-编码模式选择，0-RS，1-LDPC；rate-码率*/

#include "genParam.h"
#include "stdafx.h"

using namespace std;

void SC_FECencoder(vector<int> &bitsin, vector<int> &bitsout, int fectype, int rate)
{
	int Nbits = bitsin.size();
	switch (fectype)
	{
	case 0:
		{
			rate = 1;
			RS_encoder(bitsin, bitsout, rate);
			break;
		}
	case 1:
		{
			HSI_LDPCencoder(bitsin, bitsout, rate);
			break;
		}
	default:
		{
			cout << "前向编码模式选择错误！！！" << endl;
			exit(EXIT_FAILURE);
			break;
		}
	}
}