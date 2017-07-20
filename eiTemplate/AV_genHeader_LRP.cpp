//函数说明：产生AV-PHY中LRP中的macheader
#include "genParam.h"
#include "stdafx.h"

using namespace std;

void AV_genHeader_LRP(vector<complex<double> > &symsout)
{
    vector<int> databits;
    databits.push_back(0);
    databits.push_back(0);
    databits.push_back(1);
    databits.push_back(1);
    databits.push_back(1);
    databits.push_back(1);
    databits.push_back(1);
    vector<int> parity;
    AV_SCS_encoder(databits, parity);   //计算SCS
    for (int i = 0; i < parity.size(); ++i)
        databits.push_back(parity[i]);
    vector<int> bitsCon;
    conencoder(databits, bitsCon, 1);   //卷积编码
    vector<complex<double> > bitsMod;   //modulation
    AV_tx_modulation_LRP(bitsCon, bitsMod);
    AV_OFDMer_LRP(bitsMod, symsout, 9);
}