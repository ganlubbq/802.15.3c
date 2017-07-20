//HSI ģʽ�����ź�
//datain:����Ķ����Ʒ��ţ� dataout������ĸ����� SC_p:�趨�Ĳ���


#include "genParam.h"
#include "stdafx.h"


using namespace std;

void genHSI(vector<int> &datain, vector<int> &macheader, vector<complex<double> > &dataout, HSI_param &HSI_p)
{
	int ssid = HSI_p.ssid;
	
	for (int i = 0; i < HSI_p.Nfram; i++)
	{
		int Lpreb;
		switch (HSI_p.pretype)
		{
		case 0:
			Lpreb = 8320;
		case 1:
			Lpreb = 3456;
		case 2:
			Lpreb = 3456;
		}

		vector<complex<double>> HSI_preb;
		HSI_genPreamble(HSI_preb, HSI_p.pretype, HSI_p.ti);

		for (int j = 0; j < HSI_preb.size(); j++)
			dataout.push_back(HSI_preb[j]);//���Preamble
/******************************����macheader*******************************/
		vector<int> vMacheader;//
		vector<int> PHYheader (48, 0);//��48λPHYheader
		ssid = ssid % 16;
		int temp_ssid = ssid;
		int SSID[4] = {0};
		for (int j = 0; j < 4; j++)//����SSID
		{
			SSID[3 -j] = temp_ssid % 2;
			temp_ssid = temp_ssid / 2;
		}
		for (int j = 0; j < 4;j++)
			PHYheader[j] = SSID[j];//����SSID
		PHYheader[4] = HSI_p.Agr;//����Aggregation
		PHYheader[5] = HSI_p.UEP;//����UEP
		int temp_MCS = HSI_p.MCS;
		for (int j = 0; j < 4; j++)//����5bits MCS
		{
			PHYheader[10 - j] = temp_MCS % 2;
			temp_MCS = temp_MCS / 2;
		}
		int temp_Lfram = HSI_p.L_mb;
		for (int j = 0; j < 20; j++)//����20bits frame length
		{
			PHYheader[30 - j] = temp_Lfram % 2;
			temp_Lfram = temp_Lfram / 2;
		}
		PHYheader[31] = 0;
		PHYheader[32] = HSI_p.pretype;//����Preamble type
		PHYheader[33] = HSI_p.Bt;//����Beam tracking
		PHYheader[34] = HSI_p.Llat;//����Low-latency mode
		PHYheader[35] = HSI_p.bits_inter;//����Bit interleaver
		PHYheader[36] = HSI_p.PCES;//����PCES mode
		PHYheader[37] = HSI_p.skewed_map;//����Skewed constellation
		for (int j = 0; j < 10; j++)//����Reserved bits
			PHYheader[38 + j] = HSI_p.Rsv[j];
		int index_header = 48 + HSI_p.L_mh;
	    vector<int> gen_HSI;
		for (int j = 0; j < 48; j++)
			gen_HSI.push_back(PHYheader[j]);
		for (int j = 0; j < HSI_p.L_mh; j++)
			gen_HSI.push_back(macheader[j]);
		vector<int> pHCS;
		HCS_encoder(gen_HSI, pHCS);//����HSI
		vector<int> gen_scram;
		for (int j = 0; j < HSI_p.L_mh; j++)
			gen_scram.push_back(macheader[j]);
		for (int j = 0; j < 16; j++)
			gen_scram.push_back(pHCS[j]);
		scrambler(gen_scram, SSID);//����
		vector<int> gen_fech_in;
		vector<int> gen_fech_out;
		for (int j = 0; j < 48; j++)
			gen_fech_in.push_back(PHYheader[j]);
		for (decltype(gen_scram.size()) j = 0; j < gen_scram.size(); j++)
			gen_fech_in.push_back(gen_scram[j]);

		HSI_LDPCencoder(gen_fech_in, gen_fech_out, 0);//ǰ����룬����1/2

		vector<complex<double> > gen_map_h;
		HSI_tx_modulation(gen_fech_out, gen_map_h, 2, 0);//QPSK����

		vector<complex<double> > gen_OFDM_h;
		HSI_OFDMer_header(gen_map_h, gen_OFDM_h, HSI_p.ti);//OFDM

		for (int j = 0; j < gen_OFDM_h.size(); j++)
			dataout.push_back(gen_OFDM_h[j]);
/************************macbody**********************************************/
		vector<int> temp_payload;
		for (int j = 0; j < HSI_p.L_mb; j++)
			temp_payload.push_back(datain[j]);

		stuffBits_HSI(temp_payload, HSI_p);

		scrambler(temp_payload, SSID);

		vector<int> temp_pl_fec;
		HSI_FECencoder(temp_payload,temp_pl_fec,HSI_p.UEP,HSI_p.FECrate);//ǰ�����

		vector<int> temp_pl_inter;
		HSI_interleaver(temp_pl_fec, temp_pl_inter, HSI_p.bits_inter);

		vector<complex<double> > temp_pl_map;
		HSI_tx_modulation(temp_pl_inter, temp_pl_map, HSI_p.modtype, HSI_p.skewed_map);

		vector<complex<double> > temp_pl_sp;
		HSI_spreader(temp_pl_map, temp_pl_sp, HSI_p.sp);

		vector<complex<double> > temp_pl_ofdm;
		HSI_OFDMer(temp_pl_sp, temp_pl_ofdm, HSI_p.ti);

		//*******************��FFT�������ƺ���ȥ��***************************/
		int left_sz = ceil((65535 - dataout.size()) / 576.0) * 576;
		left_sz = left_sz < temp_pl_ofdm.size() ? left_sz : temp_pl_ofdm.size();
		//***************************************************************/
		for (int j = 0; j < left_sz; j++)
			dataout.push_back(temp_pl_ofdm[j]);
		///****************************test*********************************/
		//for (int i  = 0; i < temp_pl_sp.size(); ++i)
		//	dataout.push_back(temp_pl_sp[i]);
	}
}