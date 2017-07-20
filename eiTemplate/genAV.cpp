//函数说明：产生AV-PHY物理层信号,输入：bitsin-输入信息比特；machin-输入mac header；symsout-信号输出；AV_p-设置的参数
#include "genParam.h"
#include "stdafx.h"

using namespace std;

void genAV(vector<int> &bitsin, vector<int> &machin, vector<complex<double> > &symsout, AV_param &AV_p)
{
	int ssid = AV_p.ssid;
	for (int i = 0; i < AV_p.Nframs; ++i)
	{
/*****************************preamble*****************************************************/
		vector<complex<double> > vPream;
		AV_genPreamble_HRP(vPream);
		for (int j = 0; j < vPream.size(); ++j)
			symsout.push_back(vPream[j]);
/*****************************header******************************************************/
		ssid = ssid % 16;
		int temp_ssid = ssid;
		int SSID[4] = {0};
		for (int j = 0; j < 4; j++)//计算SSID
		{
			SSID[3 -j] = temp_ssid % 2;
			temp_ssid = temp_ssid /2;
		}
		vector<int> AV_phyh (22 * 8, 0);
		AV_phyh[1] = 0;
		for (int j = 0; j < 4; ++j)
			AV_phyh[2 + j] = SSID[3 - j];
		vector<int> genHCS_temp;
		vector<int> HCS_parity;
		for (int j = 0; j < AV_phyh.size(); ++j)
			genHCS_temp.push_back(AV_phyh[j]);
		for (int j = 0; j < AV_p.L_mh; ++j)
			genHCS_temp.push_back(machin[j]);
		AV_HCS_encoder(genHCS_temp, HCS_parity);//计算HCS
		for (int j = 0; j < 32; ++j)
			genHCS_temp.push_back(HCS_parity[j]);
		scrambler(genHCS_temp, SSID);//扰码
		vector<int> vRSenc_mh;
		vector<int> vRSh_temp_00;//RS编码码字（56，48）
		vector<int> vRSh_temp_01;//RS编码码字（52，44）
		for (int j = 0; j < 48 * 8; ++j)
			vRSh_temp_00.push_back(genHCS_temp[j]);
		for (int j = 0; j < 44 * 8; ++j)
			vRSh_temp_01.push_back(genHCS_temp[48 * 8 + j]);
		RS_encoder(vRSh_temp_00, vRSenc_mh, 3);
		RS_encoder(vRSh_temp_01, vRSenc_mh, 4);//RS编码
		vector<int> mh_outinter;
		AV_outer_interleaver(vRSenc_mh, 2);//外交织
		vector<int> A_mh;
		vector<int> B_mh;
		vector<int> C_mh;
		vector<int> D_mh;
		AV_conencoder_Header(vRSenc_mh, A_mh, B_mh, C_mh, D_mh);
		vector<int> mh_mux;
		AV_multiplexer_Header(mh_mux, A_mh, B_mh, C_mh, D_mh);

		vector<complex<double> > mh_mod;
		AV_tx_modulation(mh_mux, mh_mod, 2, 0);
		
		int Nstuff_mh = 336 - mh_mod.size() % 336;
		for (int j = 0; j < Nstuff_mh; ++j)
			mh_mod.push_back(complex<double> (0, 0));
		vector<complex<double> > mh_ofdm;
		AV_OFDMer(mh_mod, mh_ofdm, AV_p.ti);
		
		for (int j = 0; j < mh_ofdm.size(); ++j)
			symsout.push_back(mh_ofdm[j]);
/*****************************payload******************************************************/
		stuffBits_HRP(bitsin, AV_p);
		vector<int> split_temp_upper;
		vector<int> split_temp_lower;
		vector<int> bitsin_MSB;
		if (AV_p.MCS == 5 || AV_p.MCS == 6)
		{
			int nByte = bitsin.size() / 8;
			int index = 0;
			for (int i = 0; i < nByte; ++i) 
			{
				for (int j = 0; j < 4; ++j)
					bitsin_MSB.push_back(bitsin[i * 8 + j]);
			}
			AV_splitter(bitsin_MSB, split_temp_upper, split_temp_lower, AV_p.UEP);
		}
		else
			AV_splitter(bitsin, split_temp_upper, split_temp_lower, AV_p.UEP);//分流
		scrambler(split_temp_upper,SSID);
		scrambler(split_temp_lower,SSID);//扰码
		vector<int> rs_temp_upper;
		vector<int> rs_temp_lower;
		AV_RSencoder(split_temp_upper, split_temp_lower, rs_temp_upper, rs_temp_lower, AV_p.out_inter);//RS编码
		vector<int> A_mb;
		vector<int> B_mb;
		vector<int> C_mb;
		vector<int> D_mb;
		vector<int> E_mb;
		vector<int> F_mb;
		vector<int> G_mb;
		vector<int> H_mb;
		AV_conencoder(rs_temp_upper, rs_temp_lower, A_mb, B_mb, C_mb, D_mb, E_mb, F_mb, G_mb, H_mb, AV_p.rate_up, AV_p.rate_low, AV_p.UEP);//卷积编码
		vector<int> mb_mux;
		AV_multiplexer(mb_mux, AV_p.UEP, A_mb, B_mb, C_mb, D_mb, E_mb, F_mb, G_mb,  H_mb);//数据复合
		
		vector<complex<double> > mb_mod;
		AV_tx_modulation(mb_mux, mb_mod, AV_p.modtype, AV_p.UEP);//映射
		
		vector<complex<double> > mb_ofdm;
		AV_OFDMer(mb_mod, mb_ofdm, AV_p.ti);//ofdm调制

		for (int j = 0; j < mb_ofdm.size(); ++j)
			symsout.push_back(mb_ofdm[j]);

	}
}