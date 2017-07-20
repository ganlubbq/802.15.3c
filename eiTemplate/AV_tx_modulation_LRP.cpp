//函数描述：AV-PHY中LRP模式调制程序
//函数参数：bitsin-输入比特；symsout-输出符号；Nbits-输入的比特数；modtype-调制类型：1-BPSK，2-QPSK，4-16QAM；ueptype-UEP类型：0-EEP，1-UEP

#include"genParam.h"
#include "stdafx.h"


using namespace std;
void AV_tx_modulation_LRP(vector<int> &bitsin, vector<complex<double> > &symsout)
{
	vector<complex<double> > vMap;
    vMap.push_back(complex<double> (-1, 0));
    vMap.push_back(complex<double> ( 1, 0));
    for (int i = 0; i < bitsin.size(); ++i)
        symsout.push_back(vMap[bitsin[i]]);
}