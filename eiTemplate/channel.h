#ifndef CHANNEL_H_
#define CHANNEL_H_

#include "stdafx.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
//#include <mex.h>
#include <time.h>
#include <complex>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <string>


#define max(a,b) (((a) > (b)) ? (a) : (b))

/* Input Arguments */

#define nlos_IN prhs[0]cr_chan_conv
#define num_channels_IN prhs[1]
#define adist_IN prhs[2]
#define fc_IN prhs[3]
#define los_beta_flg_IN prhs[4]
#define L_pl_IN prhs[5]
#define Lam_IN prhs[6]
#define lambda_IN prhs[7]
#define Gam_IN prhs[8]
#define gamma_IN prhs[9]
#define std_ln_1_IN prhs[10]
#define std_ln_2_IN prhs[11]
#define Lmean_IN prhs[12]
#define Omega0_IN prhs[13]
#define smallk_IN prhs[14]
#define sigma_fai_IN prhs[15]
#define tx_hpbw_IN prhs[16]
#define rx_hpbw_IN prhs[17]
#define ant_type_IN prhs[18]
#define op_num_IN prhs[19]

/* Output Arguments */

#define beta_OUT plhs[0]
#define h_OUT plhs[1]
#define h2_OUT plhs[2]
#define aoa_OUT plhs[3]
#define t_OUT plhs[4]
#define t0_OUT plhs[5]
#define np_OUT plhs[6]
#define cl_idx_OUT plhs[7]


//%----------------------------------------------------------------------------------
//%
//% Description :
//% This function M-file generates sets of AOA, TOA, and power of rays in continuous
//% time on the basis of TSV model
//% IEEE802.15.4a distribution code was modified by
//% H. Harada, R. Funada, H. Sawada, Y. Shoji, and S. Kato
//%----------------------------------------------------------------------------------
//% Modified point from r6: a function that antenna automatically searches the direction
//% receiving maximum power
//
//function [beta,h,h2,aoa,t,t0,np,cl_idx] = tg3c_tsv_ct_r6(...
//	nlos, num_channels,...								% Channel params
//	adist, fc, los_beta_flg, L_pl,...					% T-S-V model params
//	Lam, lambda, Gam, gamma, std_ln_1, std_ln_2, ...	% SV model params
//	Lmean, Omega0, smallk, sigma_fai,...
//	tx_hpbw, rx_hpbw, ant_type,...						% Antenna model params used in simulation
//	op_num)
//
//% Arguments:
//% nlos				: Flag of NLOS environment
//% num_channels		: Number of channel realizations
//% Lam				: Cluster arrival rate (clusters per nsec)
//% lambda			: Ray arrival rate (rays per nsec)
//% Gam				: Cluster decay factor (time constant, nsec)
//% gamma				: Ray decay factor (time constant, nsec)
//% std_ln_1			: Standard deviation of log-normal variable for cluster fading
//% std_ln_2			: Standard deviation of log-normal variable for ray fading
//% Lmean				: Average number of arrival clusters
//
//% Parameters added for making TG3c channel model
//% fc				: Carrier frequency [GHz]
//% los_beta_flg		: Flag used for beta calculation
//% L_pl				: Path loss regarding LOS component
//% Omega0			: Cluster power level
//% smallk			: Small Rician effect
//% sigma_fai			: Cluster arrival angle spread in deg
//% tx_hpbw			: TX half-power angle in deg
//% rx_hpbw			: RX half-power angle in deg
//% ant_type			: Antenna model used in simulation
//%	1: Simple Gaussian distribution
//%	2: Reference antenna model
//% op_num			: Option index
//
//% Output values:
//%	h		: Impulse responses in continuous time
//%	h2		: Impulse responses after antenna gain convolution in continuous time
//%	t		: TOAs of h
//%	t0		: Arrival time of the first ray of the first SV cluster
//%	np		: Number of paths in clusters including LOS component
//% Output values added for makRAND_MAX   ing TG3c channel model
//%	beta	: Amplitude of the LOS component
//%	aoa		: AOAs of rays in clusters including LOS component in continuous time
static int h_len = 1000;
static int ngrow = 1000;
static int gamma0 = 1;
static double pi = 3.1416;
static long long int fc = 60000000000;
static int num_channels = 100;
//int tsv_poissrnd(int lamda);
struct LessDereference
{
	template <class T>
	bool operator()(const T * lhs, const T * rhs) const {
		return *lhs < *rhs;
	}
};

class Protocol_param_channel
{
public:
	int chanel_switch;//信道开关
	int cm_num;
	double fc;
	Protocol_param_channel() {setDefault();}
private:
	void setDefault()
	{
		chanel_switch = 0;
		cm_num = 21;
		fc = 6e10;
	}
};

template <class T>
void ClearVector(std::vector<T>& vt);
double round(double data);
int cmp(const std::pair<int, double> &x,const std::pair<int, double> &y);
void sortMapbyValue(std::map<int, double> &t_map,std::vector< std::pair<int, double> > &t_vec);
double randn();
double rand1();
double gaussrand();
void MaxandMin(double *a, int l, int r, double& maxValue, double& minValue);
void MaxandMin_vec(std::vector <double> &a, int l, int r, double& maxValue, double& minValue);
int nextpow2(int n);
double tsv_laplacernd(double a);
double angle(std::complex <double> (&h)[4], int size, double p[4]);
double angle1(std::complex <double> h);
double tsv_poissrnd(int lamda);
void tsv_ant_gain_r6(int ant_type, double hpbw, std::vector <double> &fai0, int azimuth, std::vector <double> &g);
void tsv_ant_gain_r6_2(int ant_type, double hpbw, std::vector <double> &fai0, int azimuth, std::vector <double> &g, std::vector <double> &fai);
void tsv_ant_gain_r7(int ant_type, int hpbw, std::vector <double> &fai, std::vector <double> &g);
double tsv_beta_calc_r5(double fc, double muD, int tx_hpbw, int rx_hpbw, int ant_type);
void tg3c_tsv_params_r4(int cm_num, double (&parameters)[16]);
void tg3c_tsv_ct_r6(int nlos, int num_channels, int adist, double fc, int los_beta_flg, double L_pl,
	double Lam, double lambda, double Gam, double gamma, double std_ln_1, double std_ln_2, int Lmean,
	double Omega0, double smallk, double sigma_fai, int tx_hpbw, int rx_hpbw, int ant_type, int op_num,
	std::vector <int> &beta, std::vector <double> &h, std::vector <double> &h2, std::vector <double> &aoa, std::vector <double> &t, std::vector <double> &t0, std::vector <int> &np, std::vector <int> &cl_idx);
void tg3c_sv_cnvrt_ct(std::vector <std::complex<double>> &h_ct, std::vector <double> &t, std::vector <int> &np, int num_channels, std::vector <std::complex<double>> hN, double N);
void tg3c_ct2dt(std::vector <std::complex <double> > &h_ct, std::vector <double> &t, std::vector <std::complex <double> > &h_dt);
void convolution(std::vector <std::complex <double> > &p_Data, std::vector <std::complex <double> > &p_Filter, std::vector <std::complex <double> > &p_Output, int data_Long, int filter_Long, int output_Long);
void add_noise(std::vector <std::complex <double> > &in_data, int c, std::vector <std::complex <double> > &out_data);
void tg3c_tsv_eval_r7(int cm_num, double fc, std::vector <std::complex<double>> &data_in, std::vector <std::complex<double>> &data_out);

#endif