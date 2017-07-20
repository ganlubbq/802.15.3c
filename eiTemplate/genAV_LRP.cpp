//函数说明：产生AV-PHY中LRP物理层信号,输入：bitsin-输入信息比特；machin-输入mac header；symsout-信号输出；AV_p-设置的参数
#include "genParam.h"
#include "stdafx.h"

using namespace std;

void genAV_LRP(vector<int> &bitsin, vector<int> &machin, vector<complex<double> > &symsout, AV_param &AV_p)
{
    vector<complex<double> > preambleTemp;
    AV_genPreamble_LRP(preambleTemp);       //preamble
    for (int i = 0; i < preambleTemp.size(); ++i)
        symsout.push_back(preambleTemp[i]);

    vector<complex<double> > headerTemp;
    AV_genHeader_LRP(headerTemp);           //header
    for (int i = 0; i < headerTemp.size(); ++i)
        symsout.push_back(headerTemp[i]);

    vector<int> HCS_parity;
    HCS_encoder(bitsin, HCS_parity);
    for (int i = 0; i < HCS_parity.size(); ++i)
        bitsin.push_back(HCS_parity[i]);
    if (AV_p.MCS == 1)
    {
        for (int i = 0; i < 10; ++i)
            bitsin.push_back(0);
    }
    vector<int> bits_con;
    conencoder(bitsin, bits_con, AV_p.rate_up);
    vector<complex<double> > syms_mod;
    AV_tx_modulation_LRP(bits_con, syms_mod);
    vector<complex<double> > syms_ofdm;
    AV_OFDMer_LRP(syms_mod, syms_ofdm, AV_p.rep);
    for (int i = 0; i < syms_ofdm.size(); ++i)
        symsout.push_back(syms_ofdm[i]);
}