#ifndef GENPARAM_H_
#define GENPARAM_H_
#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <stdlib.h>
#include <complex>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <sys/timeb.h>
#include <vector>
#include <fstream>
#define PI  3.1415926


enum Signal_mode_3c
{
	SC  = 0,
	HSI = 1,
	AV  = 2
};
/**************************************��������*********************************************/

struct SC_param
{
	int Nfram;//֡��
	int L_mh;//macheader�ܳ���
	int L_mb;//macbody��Ϣλ����
	int modtype;//���Է�ʽ
	int FECtype;//ǰ����뷽ʽ
	int FECrate;//ǰ������������
	int sp;//��Ƶ����
	int subtype;//�ӿ�ָ�ģʽ
	int Agr;//Aggregation
	int UEP;//UEP
	int MCS;//MCS
	//int L_fram;//ÿ֡����
	int pretype;//preamble type
	int Bt;//beam tracking
	int Llat;//Low-latency
	int L_pw;//Pilot Word Length
	int PCES;//PCES mode
	int Rsv[2];//reserved bits
	int ssid;//SSID
};

struct HSI_param
{
	//int Ndata;//���ݳ���
	//int Nsdata_MB;//Macbody���ų���
	int Nfram;//֡��
	int modtype;//���Է�ʽ
	//int FECtype;//ǰ����뷽ʽ
	int FECrate;//ǰ������������
	int sp;//��Ƶ����
	//int subtype;//�ӿ�ָ�ģʽ
	//int L_mb;//macheader�ܳ���
	int L_mh;//macheader��Ϣλ����
	int L_mb;//ÿ֡����
	int Agr;//Aggregation
	int UEP;//UEP
	int MCS;//MCS
	int pretype;//preamble type
	int Bt;//beam tracking
	int Llat;//Low-latency
	int bits_inter;//bit interleaver
	int PCES;//PCES mode
	int skewed_map;//skewed constellation
	int Rsv[10];//reserved bits
	int ti;//tone_inter
	int ssid;//SSID
};

struct AV_param
{
	int Nframs;//֡��
	int MCS;//MCS
	int transRateType;//�����ٶ�ģʽ
	int rep;//repetition:5,9
	int L_mh;//macheader����
	int L_mb;//macbody����
	int modtype;//���Ʒ�ʽ
	int out_inter;//�⽻֯���
	int UEP;//UEP��ʽ
	int rate_up;//��֧·����
	int rate_low;//��֧·����
	int ti;//tone_inter
	int ssid;//SSID
};

class Protocol_param_3C
{
public:
	Signal_mode_3c Sig_mode;
	int data_source;//����Դģʽ��PN9-0��PN15-1��ALL0-2���û��Զ���-3
	char *filepath_ds;//����Դ·��
	double IQ_gain;	
	double quan_angle_adjust;
	SC_param SC_p;
	HSI_param HSI_p;
	AV_param AV_p;
	Protocol_param_3C() {setDefault();}
		
	void set_signal_mode(Signal_mode_3c sm)//�����ź�ģʽ����������ʼ��
	{
		switch (sm)
		{
		case SC:
			{
				setDefault();
				Sig_mode = SC;
				break;
			}
		case HSI:
			{
				setDefault();
				Sig_mode = HSI;
				break;
			}
		case AV:
			{
				setDefault();
				Sig_mode = AV;
				break;
			}
		default:
			break;
		}
	}
private:
	void setDefault()//����Ĭ�ϲ���
	{
		Sig_mode = SC;
		data_source = 0;
		filepath_ds = NULL;
		IQ_gain = 0;
		quan_angle_adjust = 0;
		/*****************SC����*********************/
		SC_p.Nfram = 1;
		SC_p.L_mh = 80;
		SC_p.L_mb = 239 * 16;
		SC_p.modtype = 1;
		SC_p.FECtype = 0;
		SC_p.FECrate = 1;
		SC_p.sp = 4;
		SC_p.subtype = 0;
		SC_p.Agr = 1;
		SC_p.UEP = 0;
		SC_p.MCS = 0;
		SC_p.pretype = 1;
		SC_p.Bt = 0;
		SC_p.Llat = 0;
		SC_p.L_pw = 0;
		SC_p.PCES = 1;
		SC_p.ssid = 0;
		for (int i = 0; i < 2; i++)
		{
			SC_p.Rsv[i] = 0;
		}
		/****************HSI����*********************/
		HSI_p.Nfram = 1;
		HSI_p.modtype = 2;
		HSI_p.FECrate = 0;
		HSI_p.sp = 48;
		HSI_p.L_mh = 336;
		HSI_p.L_mb = 336 * 4;
		HSI_p.Agr = 0;
		HSI_p.UEP = 0;
		HSI_p.MCS = 1;
		HSI_p.pretype = 1;
		HSI_p.Bt = 0;
		HSI_p.Llat = 0;
		HSI_p.bits_inter = 1;
		HSI_p.PCES = 0;
		HSI_p.skewed_map = 0;
		for (int i = 0; i < 10; ++i)
			HSI_p.Rsv[i] = 0;
		HSI_p.ti = 0;
		HSI_p.ssid = 0;
		/****************AV����*********************/
		AV_p.Nframs = 1;
		AV_p.MCS = 0;
		AV_p.transRateType = 0;
		AV_p.L_mh = 656;
		AV_p.L_mb = 216 * 32;
		AV_p.modtype = 2;
		AV_p.out_inter = 2;
		AV_p.UEP = 0;
		AV_p.rate_up = 0;
		AV_p.rate_low = 0;
		AV_p.ti = 0;
		AV_p.ssid = 0;
	}
};


/****************************************����ģ��*****************************************/
void hex2binary(int hex[], std::vector<int> &binary, int nhex);
void bits2nums(std::vector<int> &codebits, std::vector<int> &nums, int modtype);
int mod(int a, int b);
int ceil(int a, int b);
void gen_prbs(std::vector<int> &genbits, int Nbits);
void genLDPCGenMatrix(int codeIndex, std::vector<std::vector<double> > &nZindexTable);
void rotateZ(int index, double a[][21]);
void genLDPCparity(std::vector<double> &codeword, std::vector<std::vector<double> > &nZindex, std::vector<double> &paritybits);
void HCS_encoder(std::vector<int> &bits_input, std::vector<int> &parity);
void scrambler_gen_prbs(int ssid[], std::vector<int> &prbs, int Nbits);
void scrambler(std::vector<int> &codebits, int ssid[]);
void bitrp_3c(std::vector<std::complex<double> > &Data_In, int n);
void FFT_3c(std::vector<std::complex<double> > &Data_in, int n);
void IFFT(std::vector<std::complex<double> > &Data_in, int n);
void RS_encoder(std::vector<int> &dataIn, std::vector<int> &data_out, int Rate);
void RS_encoder_shortend(std::vector<int> &dataIn, std::vector<int> &data_out);
void bi2de_rs(std::vector<int> &biData, std::vector<int> &deData); 
void de2bi_rs(std::vector<int> &deData, std::vector<int> &biData);
void conencoder(std::vector<int> &codebits, std::vector<int> &bits_out, int rate);
void waveform_generator_3c(std::vector<int> &macheader, std::vector<int> &macbody, std::vector<std::complex<double>> &dataout, Protocol_param_3C &param_3c);
int gen_lmh_3c(Protocol_param_3C& params_3c);
int gen_lmb_3c(Protocol_param_3C& params_3c);
/***************************************RS����*******************************************/
void generate_gf();
void gen_poly();
void encode_rs();
void de2bi(int deData[],int len,int biData[]);
void bi2de(std::vector<int> &biData, int len, int deData[]);
void tx_rs(std::vector<int> &dataIn, std::vector<int> &data_out, int len, int Rate);
/***************************************************************************************/
/***************************************************************************************/

/**************************************SC-PHYģ��****************************************/

void SC_BPSK(std::vector<int> &codebits);
void SC_tx_modulation(std::vector<int> &codebits, std::vector<std::complex<double> > &symbols, int modtype);
void SC_LFSR(std::vector<int> &prbs, int Nbits);
void SC_spreader(std::vector<int> &bits_input, std::vector<int> &sp_out, int sp_index);
void SC_subbuilder(std::vector<std::complex<double> > &symin, std::vector<std::complex<double>> &symout, int sub_mod);
void SC_PCESinserter(std::vector<std::complex<double> > &symin, std::vector<std::complex<double> > &symout, int PCES_mod, int sub_mod);
void SC_genPreamble(std::vector<std::complex<double> > &vSC_Pre, int Pre_mod);
void SC_FECencoder(std::vector<int> &bitsin, std::vector<int> &bitsout, int fectype, int rate);
void genSC(std::vector<int> &datain, std::vector<int> &macheader, std::vector<std::complex<double> > &dataout, SC_param &SC_p);
void stuffBits_SC(std::vector<int> &bitsin, SC_param &SC_p);

/*****************************************************************************************/

/**************************************HSI-PHYģ��*****************************************/

void HSI_genPreamble(std::vector<std::complex<double> > &vHSI_Pre, int Pre_mod, int ti);
void HSI_tx_modulation(std::vector<int> &codebits, std::vector<std::complex<double> > &symbols, int modtype, int skew);
//void HSI_PCESinserter(std::complex<double>* symin, std::complex<double>* symout, int PCES_mod, int Nsymin, int Nsymout);
void HSI_spreader(std::vector<std::complex<double> > &syms_input, std::vector<std::complex<double> > &sp_out, int sp_index);
void HSI_interleaver(std::vector<int> &bitsin, std::vector<int> &bitsout, int inter_index);
void HSI_toneinter(std::vector<std::complex<double> > &symsin);
void HSI_OFDMer(std::vector<std::complex<double> > &OFDMin, std::vector<std::complex<double> > &OFDMout, int ti);
void HSI_OFDMer_header(std::vector<std::complex<double> > &OFDMin, std::vector<std::complex<double> > &OFDMout, int ti);
void HSI_FECencoder(std::vector<int> &vbitsin, std::vector<int> &vbitsout, int UEP, int FECrate);
void HSI_LDPCencoder(std::vector<int> &bitsin, std::vector<int> &bitsout, int rate);
void genHSI(std::vector<int> &datain, std::vector<int> &macheader, std::vector<std::complex<double> > &dataout, HSI_param &HSI_p);
void stuffBits_HSI(std::vector<int> &bitsin, HSI_param &HSI_p);

/*****************************************************************************************/

/**************************************AV-PHYģ��*****************************************/
void genAV(std::vector<int> &bitsin, std::vector<int> &machin, std::vector<std::complex<double> > &symsout, AV_param &AV_p);
void genAV_LRP(std::vector<int> &bitsin, std::vector<int> &machin, std::vector<std::complex<double> > &symsout, AV_param &AV_p);
void AV_splitter(std::vector<int> &codebits, std::vector<int> &bits_up, std::vector<int> &bits_low, int ueptype);
void AV_RSencoder(std::vector<int> &in_upper, std::vector<int> &in_lower, std::vector<int> &out_upper, std::vector<int> &out_lower, int inter_depth);
void AV_HCS_encoder(std::vector<int> &bits_input, std::vector<int> &parity);
void AV_tx_modulation(std::vector<int> &bitsin, std::vector<std::complex<double> > &symsout, int modtype, int ueptype);
void AV_tx_modulation_LRP(std::vector<int> &bitsin, std::vector<std::complex<double> > &symsout);
void AV_outer_interleaver(std::vector<int> &codebits, int depth);
void AV_inner_interleaver(std::vector<int> &codebits, int ueptype);
void AV_multiplexer(std::vector<int> &bitsout, int ueptype, std::vector<int> &A, std::vector<int> &B, std::vector<int> &C, std::vector<int> &D, std::vector<int> &E, std::vector<int> &F, std::vector<int> &G, std::vector<int> &H);
void AV_OFDMer(std::vector<std::complex<double> > &symsin, std::vector<std::complex<double> > &symsout, int ti);
void AV_OFDMer_LRP(std::vector<std::complex<double> > &symsin, std::vector<std::complex<double> > &symsout, int rep);
void AV_conencoder(std::vector<int> &in_upper, std::vector<int> &in_lower, std::vector<int> &con_A, std::vector<int> &con_B, std::vector<int> &con_C, std::vector<int> &con_D, std::vector<int> &con_E, std::vector<int> &con_F, std::vector<int> &con_G, std::vector<int> &con_H, int rate_up, int rate_low,int ueptype);
void scrambler_gen_prbs_LRP(std::vector<int> &ssid, std::vector<int> &prbs, int Nbits);
void scrambler_LRP(std::vector<int> &codebits, std::vector<int> &ssid, int type);
void AV_genPreamble_HRP(std::vector<std::complex<double> > &vHRP_Pre);
void AV_genPreamble_LRP(std::vector<std::complex<double> > &vLRP_Pre);
void AV_genHeader_LRP(std::vector<std::complex<double> > &symsout);
void AV_SCS_encoder(std::vector<int> &bits_input, std::vector<int> &parity);
void stuffBits_HRP(std::vector<int> &bitsin, AV_param &AV_p);
void AV_conencoder_Header(std::vector<int> &bitsin, std::vector<int> &con_A, std::vector<int> &con_B, std::vector<int> &con_C, std::vector<int> &con_D);
void AV_multiplexer_Header(std::vector<int> &bitsout, std::vector<int> &A, std::vector<int> &B, std::vector<int> &C, std::vector<int> &D);
/*****************************************************************************************/

/***********************************����Դ*************************************************/
/*******************************************************************
 *  �ļ�����: SignalSource.h
 *  ��Ҫ����: 
 *    ������������ 4 ����Դ(PN9 PN15 ȫ0 ���ļ���),
 *    ��������,�����vector<int>���͵�Դ,����׼�ĸ�ʽӦ�����BYTEԴ
 *   
 *  ��������: 2016.06.21
 *  ����: xingxin
 *  ˵��: ������������Դ�����д,��ԭ���������߼��������ʽ�����Ż�
 ******************************************************************/

/** 
 *  ��������: ����ѡȡ��ģʽ�����ݳ��ȵ���Ϣ������Դ
 *  @param mode ����ģʽѡ��(0:PN9 1:PN15 2:All0 3:�ļ���ȡ)
 *  @param length ���ݳ���(01����λ��)
 *  @param seed ���������
 *  @param filename ������ɾ���·����ʶ���ļ�·��,�ļ��Ƽ�ʹ��ASCII��ʽ����,���ⲻ��Ҫ�Ķ�ȡ�鷳
 *   
 *  @return src ����vector<int>������Դ
 */  
std::vector<int> GenerateSource(int mode=0,int length=64, int seed=10, const char* filename=NULL);

/** 
 *  ��������: ����PN9��Դ
 *  @param length ���ݳ���(01����λ��)
 *  @param seed ���������
 *   
 *  @return src ����vector<int>������Դ
 */  
std::vector<int> PN9(int length = 64, int seed = 10);

/** 
 *  ��������: ����PN15��Դ
 *  @param length ���ݳ���(01����λ��)
 *  @param seed ���������
 *   
 *  @return src ����vector<int>������Դ
 */  
std::vector<int> PN15(int length = 64, int seed = 10);

/** 
 *  ��������: ����ȫ0��Դ
 *  @param length ���ݳ���(01����λ��)
 *   
 *  @return src ����vector<int>������Դ
 */  
std::vector<int> All0(int length = 64);

/** 
 *  ��������: ���ɴ��ļ���ȡ����Դ
 *  @param length ���ݳ���(01����λ��)
 *  @param filename ������ɾ���·����ʶ���ļ�·��,�ļ��Ƽ�ʹ��ASCII��ʽ����,���ⲻ��Ҫ�Ķ�ȡ�鷳
 *   
 *  @return src ����vector<int>������Դ
 */  
std::vector<int> FromFile(int length=64, const char* filename=NULL);


#endif
