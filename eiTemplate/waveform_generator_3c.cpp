#include "genParam.h"
#include "stdafx.h"

using namespace std;

void waveform_generator_3c(vector<int> &macheader, vector<int> &macbody, vector<complex<double>> &dataout, Protocol_param_3C &param_3c)
{
	if (param_3c.Sig_mode == SC)
	{
		genSC(macbody, macheader, dataout, param_3c.SC_p);
	}
	else if (param_3c.Sig_mode == HSI)
	{
		genHSI(macbody, macheader, dataout, param_3c.HSI_p);
	}
	else if (param_3c.Sig_mode == AV)
	{
		if (param_3c.AV_p.transRateType == 0)
			genAV(macbody, macheader, dataout, param_3c.AV_p);
		else 
			genAV_LRP(macbody, macheader, dataout, param_3c.AV_p);
	}
	else 
	{
		exit(EXIT_FAILURE);
	}
}

int gen_lmh_3c(Protocol_param_3C& params_3c)
{
	if (params_3c.Sig_mode == SC)
		return params_3c.SC_p.L_mh;
	else if (params_3c.Sig_mode == HSI)
		return params_3c.HSI_p.L_mh;
	else if (params_3c.Sig_mode == AV)
		return params_3c.AV_p.L_mh;
	else
		exit(EXIT_FAILURE);
}

int gen_lmb_3c(Protocol_param_3C& params_3c)
{
	if (params_3c.Sig_mode == SC)
		return params_3c.SC_p.L_mb;
	else if (params_3c.Sig_mode == HSI)
		return params_3c.HSI_p.L_mb;
	else if (params_3c.Sig_mode == AV)
		return params_3c.AV_p.L_mb;
	else
		exit(EXIT_FAILURE);
}