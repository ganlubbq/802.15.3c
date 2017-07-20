/*����������SC-PHYǰ�����ģ�飬���룺bitsin-�������룬RS�������������Ϊ239�ı�����LDPC�������������ͬ��Ϊ��Ӧ���ʵı�����
bitsout-���������fectype-����ģʽѡ��0-RS��1-LDPC��rate-����*/

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
			cout << "ǰ�����ģʽѡ����󣡣���" << endl;
			exit(EXIT_FAILURE);
			break;
		}
	}
}