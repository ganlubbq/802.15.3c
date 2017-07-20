//SC 模式生成信号
//datain:输入的二进制符号， macheader:输入的mac信息， dataout：输出的复数， SC_p:设定的参数

#include "genParam.h"
#include "stdafx.h"

using namespace std;

void genSC(vector<int> &datain, vector<int> &macheader, vector<complex<double> > &dataout, SC_param &SC_p)
{
	int ssid = SC_p.ssid;
	for(int i = 0; i < SC_p.Nfram; i++)
	{
		int Lpreb;
		switch (SC_p.pretype)
		{
		case 0:
			Lpreb = 8320;
		case 1:
			Lpreb = 3456;
		case 2:
			Lpreb = 3456;
		}
		vector<complex<double> > SC_preb;
		SC_genPreamble(SC_preb, SC_p.pretype);
		for (int j = 0; j < SC_preb.size(); j++)
			dataout.push_back(SC_preb[j]);//填充Preamble
/******************************构造macheader*******************************/
		vector<int> PH (40, 0);//PHY信息位，共40比特
		ssid = ssid % 16;
		int temp_ssid = ssid;
		int SSID[] = {0, 0, 0, 0};
		for (int j = 0; j < 4; j++)//计算SSID
		{
			SSID[3 -j] = temp_ssid % 2;
			temp_ssid = temp_ssid /2;
		}
		for (int j = 0; j < 4;j++)
			PH[j] = SSID[j];//插入SSID
		PH[4] = SC_p.Agr;//插入aggragation
		PH[5] = SC_p.UEP;//插入UEP
		int temp_mcs = SC_p.MCS;
		for (int j = 0; j < 5; j++)//插入MCS信息
		{
			PH[10 - j] = temp_mcs % 2;
			temp_mcs = temp_mcs / 2;
		}
		int temp_Lfram = SC_p.L_mb / 8;
		for (int j = 0; j < 20; j++)//插入Frame Length，20bits
		{
			PH[30 - j] = temp_Lfram % 2;
			temp_Lfram = temp_Lfram / 2;
		}
		PH[31] = 0;
		PH[32] = SC_p.pretype;//插入Preamble type
		PH[33] = SC_p.Bt;//插入Beam tracking
		PH[34] = SC_p.Llat;//插入Low-latency Mode
		int temp_pw = SC_p.L_pw;
		for (int j = 0; j < 2; j++)//插入2bits pilot word
		{
			PH[36 - j] = temp_mcs % 2;
			temp_pw = temp_pw / 2;
		}
		PH[37] = SC_p.PCES;//插入PCES
		for (int j = 0; j < 2; j++)
			PH[38 + j] = SC_p.Rsv[j];//插入reserved bits
		vector<int> temp_HCS;//存储16位HCS校验位
		vector<int> gen_HCS;
		for (int j = 0; j < PH.size(); ++j)
			gen_HCS.push_back(PH[j]);
		for (int j = 0; j < macheader.size(); j++)
			gen_HCS.push_back(macheader[j]);
		HCS_encoder(gen_HCS, temp_HCS);//计算HCS
		vector<int> temp_scram_mh;//macheader进行扰码
		for (int j = 0; j < macheader.size(); j++)
			temp_scram_mh.push_back(macheader[j]);
		for (int j = 0; j < temp_HCS.size(); j++)
			temp_scram_mh.push_back(temp_HCS[j]);
		scrambler(temp_scram_mh, SSID);//对macheader+HCS进行扰码
		int Nstuff_MH = 239 * 8 - temp_scram_mh.size() - PH.size();//填充比特数
		vector<int> RSbits_MH (239 * 8, 0);//RS输入
		vector<int> genRS_MH;//RS输出
		for (int j = 0; j < PH.size(); ++j)
			RSbits_MH[j] = PH[j];
		for (int j = 0; j < temp_scram_mh.size(); ++j)
			RSbits_MH[PH.size() + j] = temp_scram_mh[j];
		for (int j = 0; j < Nstuff_MH; j++)
			RSbits_MH[temp_scram_mh.size() + PH.size() + j] = 0;
		RS_encoder(RSbits_MH, genRS_MH, 1);
		int Nbdata_MH = PH.size() + temp_scram_mh.size() + 128;//macheader比特数
		vector<int> databits_MH;//添加RS编码后的macheader
		for (int j = 0; j < PH.size() + temp_scram_mh.size(); ++j)
			databits_MH.push_back(genRS_MH[j]);
		for (int j = 0; j < 128; j++)
			databits_MH.push_back(genRS_MH[239 * 8 + j]);

		vector<int> databits_MH_sp;
		SC_spreader(databits_MH, databits_MH_sp, 64);//扩频

		vector<complex<double> > vdatabits_MH_mod;
		SC_tx_modulation(databits_MH_sp, vdatabits_MH_mod, 1);

		for (int j = 0; j < vdatabits_MH_mod.size(); ++j)
			dataout.push_back(vdatabits_MH_mod[j]);//插入macheader
/************************macbody**********************************************/
		stuffBits_SC(datain, SC_p);	//填充比特

		scrambler(datain, SSID);//扰码

		vector<int> PLdata_FEC;
		SC_FECencoder(datain, PLdata_FEC, SC_p.FECtype, SC_p.FECrate);//前向编码

		vector<int> PLdata_sp;
		SC_spreader(PLdata_FEC, PLdata_sp, SC_p.sp);//扩频

		vector<complex<double> > vPLdata_mod;
		SC_tx_modulation(PLdata_sp, vPLdata_mod, SC_p.modtype);//调制映射

		vector<complex<double> > vSub_temp;
		SC_subbuilder(vPLdata_mod, vSub_temp, SC_p.subtype);//子块分割

		vector<complex<double> > vPCES_temp;
	    SC_PCESinserter(vSub_temp, vPCES_temp, SC_p.PCES, SC_p.subtype);

		for (int j = 0; j < vPCES_temp.size(); j++)
			dataout.push_back(vPCES_temp[j]);

		ssid++;//SSID每帧加一
	}
}