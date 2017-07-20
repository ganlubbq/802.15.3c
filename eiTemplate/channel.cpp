//802.15.3c信道程序，主程序tg3c_tsv_eval_r7
#include "channel.h"
#include "stdafx.h"
using namespace std;

template <class T>
void ClearVector(vector<T>& vt) 
{
	vector <T> vtTemp; 
	vtTemp.swap(vt);
}

double round(double data)
{
	//	int data_int = (double) floor((double) data);
	//	int data_fo = data - floor(data);
	if (data - floor(data) > 0.5)
	{
		data = floor(data) + 1;
	}
	else
	{
		data = floor(data);
	}
	return data;
}

int cmp(const pair<int, double> &x,const pair<int, double> &y)
{
	return x.second < y.second;
}
 
void sortMapbyValue(map<int, double> &t_map,vector< pair<int, double> > &t_vec)
{
	for(map<int, double>::iterator iter = t_map.begin();iter != t_map.end(); iter ++)
	{
		t_vec.push_back(make_pair(iter->first,iter->second));
	}
	sort(t_vec.begin(),t_vec.end(),cmp);
}

double randn()
{
    double u = ((double) rand() / (RAND_MAX)) * 2 - 1;
    double v = ((double) rand() / (RAND_MAX)) * 2 - 1;
    double r = u * u + v * v;
    if (r == 0 || r > 1)
        return randn();
    double c = sqrt(-2 * log(r) / r);
	double y = u * c;
    return y;
}

double rand1()
{
	int i;
	double temp;
	temp = (double)rand()/( RAND_MAX + 1 );
	return temp;
}

double gaussrand()
{
	static double V1, V2, S;
	static int phase = 0;
	double X = 0;

	if (phase == 0) {
		do {
			double U1 = (double)rand() / RAND_MAX;
			double U2 = (double)rand() / RAND_MAX;

			V1 = 2 * U1 - 1;
			V2 = 2 * U2 - 1;
			S = V1 * V1 + V2 * V2;
		} while (S >= 1 || S == 0);

		X = V1 * sqrt(-2 * log(S) / S);
	}
	else
		X = V2 * sqrt(-2 * log(S) / S);

	phase = 1 - phase;

	return X;
}

void MaxandMin(double *a, int l, int r, double& maxValue, double& minValue)
{
    if(l == r)    // l与r之间只有一个元素
    {
        maxValue = a[l] ;
        minValue = a[l] ;
        return ;
    }
    if(l + 1 == r) // l与r之间只有两个元素
    {
        if(a[l] >= a[r])
        {
            maxValue = a[l] ;
            minValue = a[r] ;
        }
        else
        {
            maxValue = a[r] ;
            minValue = a[l] ;
        }
        return ;
    }
    int m = (l + r) / 2 ; // 求中点
    double lmax ; // 左半部份最大值
    double lmin ; // 左半部份最小值
    MaxandMin(a, l, m, lmax, lmin) ;        // 递归计算左半部份
    double rmax ; // 右半部份最大值
    double rmin ; // 右半部份最小值
    MaxandMin(a, m + 1, r, rmax, rmin) ;    // 递归计算右半部份
    maxValue = max(lmax, rmax) ; // 总的最大值
    minValue = min(lmin, rmin) ; // 总的最小值
}

void MaxandMin_vec(vector <double> &a, int l, int r, double& maxValue, double& minValue)
{
    if(l == r)    // l与r之间只有一个元素
    {
        maxValue = a[l] ;
        minValue = a[l] ;
        return ;
    }
    if(l + 1 == r) // l与r之间只有两个元素
    {
        if(a[l] >= a[r])
        {
            maxValue = a[l] ;
            minValue = a[r] ;
        }
        else
        {
            maxValue = a[r] ;
            minValue = a[l] ;
        }
        return ;
    }
    int m = (l + r) / 2 ; // 求中点
    double lmax ; // 左半部份最大值
    double lmin ; // 左半部份最小值
    MaxandMin_vec(a, l, m, lmax, lmin) ;        // 递归计算左半部份
    double rmax ; // 右半部份最大值
    double rmin ; // 右半部份最小值
    MaxandMin_vec(a, m + 1, r, rmax, rmin) ;    // 递归计算右半部份
    maxValue = max(lmax, rmax) ; // 总的最大值
    minValue = min(lmin, rmin) ; // 总的最小值
}

int nextpow2(int n)
{
	int n_log = abs(n);
	double f_log;

	int p_log = 0;
	if (n > (double)pow((double)2, p_log))
	{
		p_log++;
	}
	else
	{
		p_log = p_log - 1;
	}
	f_log = n_log / (double)pow((double)2, p_log);

	if (f_log == 0.5)
	{
		p_log = p_log - 1;
	}
	return p_log;
}

double tsv_laplacernd(double a)
{
	double tsv_laplacernd_output;
    double U1 = rand1();
    double U2 = rand1();
    tsv_laplacernd_output = (2 * (U1 >= 0.5) - 1) * (a / (double) sqrt((double)2)) * log(U2);
    return tsv_laplacernd_output;
}

double angle(complex <double> (&h)[4], int size, double p[4])
{
	for (int i = 0; i<4; i++)
	{
		double real_part = real(h[i]);
		double imag_part = imag(h[i]);
		p[i] = atan2(imag_part, real_part);
		//return p[i];
	}
	return p[4];
}

double angle1(complex <double> h)
{
		double p = 0;
        double real_part = real(h);
        double imag_part = imag(h);
        p = atan2(imag_part, real_part);
        return p;
}

double tsv_poissrnd(int lamda)
{
	//double rand_num = 0.0;
	int tsv_poissrnd_output = 0;
	//srand((unsigned)time(NULL));
	//rand_num = rand() / ((double)RAND_MAX * 3);
	double ar = (double)exp((double)lamda)*rand1();
	if (ar <= 1)
	{
		tsv_poissrnd_output = 0;
	}
	else
	{
		tsv_poissrnd_output = 1;
	}

	while (tsv_poissrnd_output == 1)
	{
		while (ar > 1)
		{
			ar = ar * rand1();
			if (ar <= 1)
			{
				break;
			}
			else
			{
				tsv_poissrnd_output = tsv_poissrnd_output + 1;
			}
		}
		return tsv_poissrnd_output;
	}

}

void tsv_ant_gain_r6(int ant_type, double hpbw, vector <double> &fai0, int azimuth, vector <double> &g)
{
	vector <double> fai;
	complex <double> ray_aoa_azi;
	double ray_aoa_azi_angled;

    if (azimuth != 0)
    {
        for (int ray_num = 0; ray_num < fai0.size(); ray_num++)
        {
            complex <double> data_for_exp(0, (fai0[ray_num]+azimuth / 180 * pi));
            //ray_aoa_azi[ray_num] = exp(data_for_exp);
			ray_aoa_azi = exp(data_for_exp);
            ray_aoa_azi_angled = angle1(ray_aoa_azi);
            fai.push_back(ray_aoa_azi_angled / pi * 180);
        }
    }
    else
    {
        fai = fai0;
    }

    switch (ant_type)
    {
    case 1:
        {
            double G0, theta_ml, G_side, g0;
			vector <double> G;
            G0 = 20 * log10(1.6162 / sin(hpbw*pi/180/2));
            theta_ml = 2.6 * hpbw;
            G_side = -0.4111 * log(hpbw) - 10.597;
            for (int i = 0; i < fai.size(); i++)
            {
                G.push_back(G0 - 3.01 * pow(2 * abs(fai[i]) /hpbw, 2));
				if (abs(fai[i]) > theta_ml / 2 )
				{
					G[i] = G_side;
				}
				g0 = G[i] - G0;
				g.push_back(pow(10, g0 / 20));
            }
            break;
        }
    case 2:
        {
            double alfa;
            alfa = 4 * (double)log((double)2) / pow(hpbw*pi/180, 2);
            for (int i = 0; i < fai.size(); i++)
            {
                g.push_back(sqrt(exp(pow(-alfa * abs(fai[i]) / 180 * pi, 2))));
            }
            break;
        }
    default:
        printf("Antenna model error");
        break;
    }
}

void tsv_ant_gain_r6_2(int ant_type, double hpbw, vector <double> &fai0, int azimuth, vector <double> &g, vector <double> &fai)
{
	vector <complex <double> > ray_aoa_azi;
	vector <double> ray_aoa_azi_angled;

    if (azimuth != 0)
    {
        for (int ray_num = 0; ray_num < fai0.size(); ray_num++)
        {
            complex <double> data_for_exp(0, (fai0[ray_num]+azimuth / 180 * pi));
            //ray_aoa_azi[ray_num] = exp(data_for_exp);
			ray_aoa_azi.push_back(exp(data_for_exp));
            ray_aoa_azi_angled.push_back(angle1(ray_aoa_azi[ray_num]));
            fai.push_back(ray_aoa_azi_angled[ray_num] / pi * 180);
        }
    }
    else
    {
        fai = fai0;
    }

    switch (ant_type)
    {
    case 1:
        {
            double G0, theta_ml, G_side;
			vector <double> G,g0;
            G0 = 20 * log10(1.6162 / sin(hpbw*pi/180/2));
            theta_ml = 2.6 * hpbw;
            G_side = -0.4111 * log(hpbw) - 10.597;
            for (int i = 0; i < fai.size(); i++)
            {
                G.push_back(G0 - 3.01 * pow(2 * abs(fai[i]) /hpbw, 2));
				if (abs(fai[i]) > theta_ml / 2 )
				{
					G[i] = G_side;
				}
				g0.push_back(G[i] - G0);
				g.push_back(pow(10, g0[i] / 20));
            }
            break;
        }
    case 2:
        {
            double alfa;
            alfa = 4 * (double)log((double)2) / pow(hpbw*pi/180, 2);
            for (int i = 0; i < fai.size(); i++)
            {
                g.push_back(sqrt(exp(pow(-alfa * abs(fai[i]) / 180 * pi, 2))));
            }
            break;
        }
    default:
        printf("Antenna model error");
        break;
    }
}

void tsv_ant_gain_r7(int ant_type, int hpbw, vector <double> &fai, vector <double> &g)
{
	double theta_ml, G0, alfa, G, g0;
	switch (ant_type)
	{
	case 1:
		theta_ml = 2.6 * hpbw;
		G0 = 20 * log10(1.6162 / sin(hpbw*pi / 180 / 2));
		for (int i = 0; i < fai.size(); i++)
		{
			if (abs(fai[i]) <= theta_ml / 2)
			{
				G = G0 - 3.01 * pow((2 * abs(fai[i]) / hpbw), 2);
			}
			else
			{
				G = -0.4111 * (double) log((double) hpbw) - 10.597;
			}
			g0 = G - G0;
			g.push_back(pow(10, g0 / 20) );
		}
		break;
	case 2:
		alfa = 4 * (double)log((double)2) / pow(hpbw * pi / 180, 2);
		for (int i = 0; i < fai.size(); i++)
		{
			g.push_back(sqrt(exp(-alfa * pow(abs(fai[i] / 180 * pi), 2))));
		}
		break;
	default:
		printf("default");
		break;
	}
}

double tsv_beta_calc_r5(double fc, double muD, int tx_hpbw, int rx_hpbw, int ant_type)
{
	double beta = 0;
	int gamma0 = 1;

	double D0[] = { -0.3 + muD, 0.3 + muD };
	double Ht[] = { 0, 0.3 };
	double Hr[] = { 0, 0.3 };

	double h1_pre = Ht[1] - Ht[0];
	double h2_pre = Hr[1] - Hr[0];
	double h1 = h1_pre * rand1() + Ht[0];
	double h2 = h2_pre * rand1() + Hr[0];
	double D = (D0[1] - D0[0])*rand1() + D0[0];

	double ramda = 3e8 / fc;

	complex <double> tx_p(0, h1);
	complex <double> rx_p(D, h2);
	double rfl_p = D * h1 / (h1 + h2);

	//    complex <double> h_for_angle[3] = {0};
	//    CComplex h_for_angle_0 = rx_p - tx_p;
	//    CComplex h_for_angle_1 = tx_p - rx_p;
	//    CComplex h_for_angle_2 tsv_poissrnd= rfl_p - tx_p;
	//    CComplex h_for_angle_3 = rfl_p - rx_p;
	complex <double> h_for_angle[] = { rx_p - tx_p, tx_p - rx_p, rfl_p - tx_p, rfl_p - rx_p };
	double tp_1[4], tp[4];
	angle(h_for_angle, 4, tp_1);
	for (int i = 0; i<4; i++)
	{
		tp[i] = tp_1[i] / pi * 180;
	}
	//double tp[] = tp_1[] / pi * 180;

	double dr_theta = tp[0];
	double dr_fai = dr_theta;
	double rfl_theta = tp[2];
	double rfl_fai = -rfl_theta;

	/*double gt1 = 0;
	double gt2 = 0;
	double gr1 = 0;
	double gr2 = 0;*/
/*	double gt1 = tsv_ant_gain_r7(ant_type, tx_hpbw, dr_theta);
	double gt2 = tsv_ant_gain_r7(ant_type, tx_hpbw, rfl_theta);

	double gr1 = tsv_ant_gain_r7(ant_type, rx_hpbw, dr_fai);
	double gr2 = tsv_ant_gain_r7(ant_type, rx_hpbw, rfl_fai);*/

	/*double gt1 = 0.9973;
	double gt2 = 0.8982;
	double gr1 = 0.9973;
	double gr2 = 0.8982;
	*/

	//    beta = (muD/D) * abs(gt1*gr1 + gt2*gr2*gamma0 * exp(I*(2*pi/ramda) * (2*h1*h2/D)));

	complex <double> data_for_exp(0, (2 * pi / ramda) * (2 * h1*h2 / D));
//	beta = (muD / D) * abs(gt1*gr1 + gt2*gr2*gamma0 * exp(data_for_exp));

	return beta;
}

void tg3c_tsv_params_r4(int cm_num, double (&parameters)[16])
{
	double ramda = 3e8/fc;
	double a_nlos;

	if(cm_num == 11)	//Experimental data Tx : 360deg, Rx : 15deg

	{
			  parameters[0] = 5;                         
			  parameters[1] = 0;
			  parameters[2] = 0;
			  parameters[3] = -88.7;
			  parameters[4] = 4.34;
			  parameters[5] = 9;
			  parameters[6] = 1/5.24;
			  parameters[7] = 1/0.820;
			  parameters[8] = 4.46;
			  parameters[9] = 6.25;
			  parameters[10] = 6.28;
			  parameters[11] = 13.0;
			  parameters[12] = 49.8;
			  parameters[14] = 360;
			  parameters[15] = 15;
			  parameters[13] = (-20) * log10(4 * pi*parameters[0]/ramda);

	}
    else if (cm_num == 12) // Experimental data Tx : 60deg, Rx : 15deg
	{
			 parameters[0] = 5;
			 parameters[1] = 0;
			 parameters[2] = 0;
			 parameters[3] = -108;
			 parameters[4] = 4.00;
			 parameters[5] = 11;
			 parameters[6] = 1/5.15;
             parameters[7] = 1/1.11;
			 parameters[8] = 8.98;
             parameters[9] = 9.17;
			 parameters[10] = 6.63;
             parameters[11] = 9.83;
			 parameters[12] = 119;
			 parameters[14] = 60;
			 parameters[15] = 15;
			 parameters[13] = -20*log10(4*pi*parameters[0]/ramda);
	}
    else if(cm_num == 13) // Experimental data Tx : 30deg, Rx : 15deg
	{
			 parameters[0] = 5;
			 parameters[1] = 0;
			 parameters[2] = 0;
			 parameters[3] = -111;
			 parameters[4] = 2.73;
			 parameters[5] = 8;
			 parameters[6] = 1/6.94;
             parameters[7] = 1/0.856;
			 parameters[8] = 21.5;
             parameters[9] = 4.35;
			 parameters[10] = 3.71;
             parameters[11] = 7.31;
			 parameters[12] = 46.2;
			 parameters[14] = 30;
			 parameters[15] = 15;
			 parameters[13] = -20*log10(4*pi*parameters[0]/ramda);
	}
    else if (cm_num == 14) //Experimental data Tx : 15deg, Rx : 15deg
	{
			 parameters[0] = 5;
			 parameters[1] = 0;
			 parameters[2] = 0;
			 parameters[3] = -110.7;
			 parameters[4] = 1.06;
			 parameters[5] = 4;
			 parameters[6] = 1/22.2;
             parameters[7] = 1/1.08;
			 parameters[8] = 12.6;
             parameters[9] = 4.98;
			 parameters[10] = 7.34;
             parameters[11] = 6.11;
			 parameters[12] = 107;
			 parameters[14] = 15;
			 parameters[15] = 15;
			 parameters[13] = -20*log10(4*pi*parameters[0]/ramda);
	}
    else if(cm_num == 15)//Experimental data Tx : 360deg, Rx : 15deg (SV model)
	{
			 parameters[0] = 5;
			 parameters[1] = 0;
			 parameters[2] = -1;
			 /*parameters[3] = -20 * log10(4 * pi*parameters[0] / ramda); *///N / A in channel model final reponrt
			 parameters[3] = -20 * log10(20 * pi / ramda); //xiugai
			 parameters[4] = 0;
			 parameters[5] = 4;
			 parameters[6] = 0.21;
             parameters[7] = 0.77;
			 parameters[8] = 4.19;
             parameters[9] = 1.07;
			 parameters[10] = 1.54;
             parameters[11] = 1.26;
			 parameters[12] = 8.32;
			 parameters[14] = 360;
			 parameters[15] = 15;
			 parameters[13] = -20 * log10(4 * pi*parameters[0] / ramda); //N / A in channel model final reponrt
	}
		 //******************* parameters[1] Residential channel model(UM2) ******************
    else if(cm_num == 21) //Experimental data Tx : 360deg, Rx : 15deg
	{
			 parameters[0] = 5;
			 parameters[1] = 1;
			 parameters[2] = -1;
			 parameters[3] = -88.7;
			 parameters[4] = 4.34;
			 parameters[5] = 9;
			 parameters[6] = 1 / 5.24;
             parameters[7] = 1 / 0.820;
			 parameters[8] = 4.46;
             parameters[9] = 6.25;
			 parameters[10] = 6.28;
             parameters[11] = 13.0;
			 parameters[12] = 49.8;
			 parameters[14] = 360;
			 parameters[15] = 15;
			 parameters[13] = -20 * log10(4 * pi*parameters[0] / ramda);
	}
    else if(cm_num == 22) //Experimental data Tx : 60deg, Rx : 15deg
	{
			 parameters[0] = 5;
			 parameters[1] = 1;
			 parameters[2] = -1;
			 parameters[3] = -108;
			 parameters[4] = 4.00;
			 parameters[5] = 11;
			 parameters[6] = 1 / 5.15;
             parameters[7] = 1 / 1.11;
			 parameters[8] = 8.98;
             parameters[9] = 9.17;
			 parameters[10] = 6.63;
              parameters[11] = 9.83;
			 parameters[12] = 119;
			 parameters[14] = 60;
			 parameters[15] = 15;
			 parameters[13] = -20 * log10(4 * pi*parameters[0] / ramda);
	}
    else if(cm_num == 23) //Experimental data Tx : 30deg, Rx : 15deg
	{
			 parameters[0] = 5;
			 parameters[1] = 1;
			 parameters[2] = -1;
			 parameters[3] = -111;
			 parameters[4] = 2.73;
			 parameters[5] = 8;
			 parameters[6] = 1 / 6.94;
             parameters[7] = 1 / 0.856;
			 parameters[8] = 21.5;
             parameters[9] = 4.35;
			 parameters[10] = 3.71;
             parameters[11] = 7.31;
			 parameters[12] = 46.2;
			 parameters[14] = 30;
			 parameters[15] = 15;
			 parameters[13] = -20 * log10(4 * pi*parameters[0] / ramda);
	}
    else if(cm_num == 24) //Experimental data Tx : 15deg, Rx : 15deg
	{
			 parameters[0] = 5;
			 parameters[1] = 1;
			 parameters[2] = -1;
			 parameters[3] = -110.7;
			 parameters[4] = 1.06;
			 parameters[5] = 4;
			 parameters[6] = 1 / 22.2;
             parameters[7] = 1 / 1.08;
			 parameters[8] = 12.6;
             parameters[9] = 4.98;
			 parameters[10] = 7.34;
             parameters[11] = 6.11;
			 parameters[12] = 107;
			 parameters[14] = 15;
			 parameters[15] = 15;
			 parameters[13] = -20 * log10(4 * pi*parameters[0] / ramda);
	}
		 //********************** LOS Office channel model(UM3) *********************
		 //IEEE 802.15 - 06 - 0377 - 02 - 003c
    else if(cm_num == 31) //Experimental data Tx : 30deg, Rx : 30deg
	{
			 parameters[0] = 1;
			 parameters[1] = 0;
			 parameters[2] = 0;
			 parameters[3] = -3.27*parameters[0] - 85.8;
			 parameters[4] = 5.04;
			 parameters[5] = 6;
			 parameters[6] = 1 / 24.6;
             parameters[7] = 1 / 1.03;
			 parameters[8] = 49.8;
             parameters[9] = 45.2;
			 parameters[10] = 6.60;
             parameters[11] = 11.3;
			 parameters[12] = 102;
			 parameters[14] = 30;
			 parameters[15] = 30;
			 parameters[13] = -20 * log10(4 * pi*parameters[0] / ramda);
	}
    else if(cm_num == 32) //Experimental data Tx : 60deg, Rx : 60deg
	{
			 parameters[0] = 1;
			 parameters[1] = 0;
			 parameters[2] = 0;
			 parameters[3] = -90.603;
			 parameters[4] = 2.63;
			 parameters[5] = 5;
			 parameters[6] = 1 / 37.6;
             parameters[7] = 1 / 3.41;
			 parameters[8] = 38.8;
             parameters[9] = 64.9;
			 parameters[10] = 8.04;
             parameters[11] = 7.95;
			 parameters[12] = 66.4;
			 parameters[14] = 60;
			 parameters[15] = 60;
			 parameters[13] = -20 * log10(4 * pi*parameters[0] / ramda);
	}

		 //********************* parameters[1] Office channel model(UM4) *********************
		 //IEEE 802.15 - 06 - 0478 - 01 - 003c
    else if(cm_num == 41) //Experimental data Tx : 360deg, Rx : 15deg
	{
			 parameters[0] = 5;
			 parameters[1] = 1;
			 parameters[2] = 0;
			 parameters[3] = -109;
			 parameters[4] = 4.37;
			 parameters[5] = 5;
			 parameters[6] = 1 / 30.8;
             parameters[7] = 1 / 0.29;
			 parameters[8] = 109.2;
             parameters[9] = 67.9;
			 parameters[10] = 3.24;
             parameters[11] = 5.54;
			 parameters[12] = 60.2;
			 parameters[14] = 360;
			 parameters[15] = 15;
			 a_nlos = 5.56;
			 parameters[13] = -a_nlos - 20 * log10(4 * pi * 1 / ramda) - 10 * 3.35* log10((double)parameters[0]);
	}
    else if(cm_num == 42) //Experimental data Tx : 30deg, Rx : 15deg
	{
			 parameters[0] = 5;
			 parameters[1] = 1;
			 parameters[2] = 0;
			 parameters[3] = -107.2;
			 parameters[4] = 4.43;
			 parameters[5] = 5;
			 parameters[6] = 1 / 35.9;
             parameters[7] = 1 / 1.32;
			 parameters[8] = 134.0;
             parameters[9] = 59.0;
			 parameters[10] = 4.37;
             parameters[11] = 6.66;
			 parameters[12] = 22.2;
			 parameters[14] = 30;
			 parameters[15] = 15;
			 a_nlos = 5.56;
			 parameters[13] = -a_nlos - 20 * log10(4 * pi * 1 / ramda) - 10 * 3.35*log10((double)parameters[0]);
	}
		 //************************ LOS Desktop channel model(CM9) ************************
		 //IEEE 802. 15 - 06 - 0297 - 03 - 003c
    else if(cm_num == 71) //Experimental data Tx : 30deg, Rx : 30deg
	{
			 parameters[0] = 3;
			 parameters[1] = 0;
			 parameters[2] = 1;
			 parameters[3] = 4.44*parameters[0] - 105.4;
			 parameters[4] = 2.53;
			 parameters[5] = 3;
			 parameters[6] = 1 / 27.0;
             parameters[7] = 1 / 1.56;
			 parameters[8] = 21.1;
             parameters[9] = 8.85;
			 parameters[10] = 3.01;
             parameters[11] = 7.69;
			 parameters[12] = 34.6;
			 parameters[14] = 30;
			 parameters[15] = 30;
			 parameters[13] = -20 * log10(4 * pi*parameters[0] / ramda);
	}
    else if(cm_num == 72) //Experimental data Tx : 60deg, Rx : 60deg
	{
			 parameters[0] = 1;
			 parameters[1] = 0;
			 parameters[2] = 1;
			 parameters[3] = 3.46*parameters[0] - 98.4;
			 parameters[4] = 3.97;
			 parameters[5] = 3;
			 parameters[6] = 1 / 21.1;
             parameters[7] = 1 / 2.68;
			 parameters[8] = 22.3;
             parameters[9] = 17.2;
			 parameters[10] = 7.27;
             parameters[11] = 4.42;
			 parameters[12] = 38.1;
			 parameters[14] = 60;
			 parameters[15] = 60;
			 parameters[13] = -20 * log10(4 * pi*parameters[0] / ramda);
	}
    else if(cm_num == 73) //Experimental data Tx : 360deg, Rx : 15deg
	{
			 parameters[0] = 3;
			 parameters[1] = 0;
			 parameters[2] = -1;
			 parameters[3] = -20 * log10(4 * pi*parameters[0] / ramda);
			 parameters[4] = 0;
			 parameters[5] = 14;
			 parameters[6] = 1.72;
             parameters[7] = 3.14;
			 parameters[8] = 4.01;
             parameters[9] = 0.58;
			 parameters[10] = 2.70;
             parameters[11] = 1.90;
			 parameters[12] = 14;
			 parameters[14] = 360;
			 parameters[15] = 15;
			 parameters[13] = -20 * log10(4 * pi*parameters[0] / ramda);
	}
    else if(cm_num == 81) //Experimental data Tx : 30deg, Rx : 30deg
	{
			 parameters[0] = 3;
			 parameters[1] = 1;
			 parameters[2] = -1;
			 parameters[3] = 4.44*parameters[0] - 105.4;
			 parameters[4] = 2.53;
			 parameters[5] = 3;
			 parameters[6] = 1 / 27.0;
             parameters[7] = 1 / 1.56;
			 parameters[8] = 21.1;
             parameters[9] = 8.85;
			 parameters[10] = 3.01;
             parameters[11] = 7.69;
			 parameters[12] = 34.6;
			 parameters[14] = 30;
			 parameters[15] = 30;
			 parameters[13] = -20 * log10(4 * pi*parameters[0] / ramda);
	}
    else if(cm_num == 82) //Experimental data Tx : 60deg, Rx : 60deg
	{
			 parameters[0] = 1;
			 parameters[1] = 1;
			 parameters[2] = -1;
			 parameters[3] = 3.46*parameters[0] - 98.4;
			 parameters[4] = 3.97;
			 parameters[5] = 3;
			 parameters[6] = 1 / 21.1;
             parameters[7] = 1 / 2.68;
			 parameters[8] = 22.3;
             parameters[9] = 17.2;
			 parameters[10] = 7.27;
             parameters[11] = 4.42;
			 parameters[12] = 38.1;
			 parameters[14] = 60;
			 parameters[15] = 60;
			 parameters[13] = -20 * log10(4 * pi*parameters[0] / ramda);
	}

		 //************************ LOS Kiosk channel model(CM9) ************************
		 //IEEE 802. 15 - 07 - 0607 - 00 - 003c
    else if(cm_num == 91) //Measurement environment #1
		//Experimental data Tx : 30deg, Rx : 30deg
	{
			 parameters[0] = 1;
			 parameters[1] = 0;
			 parameters[2] = 0;
			 parameters[3] = -98;
			 parameters[4] = 2.99; //11[dB]
			 parameters[5] = 5;
			 parameters[6] = 1 / 18.3;
             parameters[7] = 1 / 1.09;
			 parameters[8] = 30.2;
             parameters[9] = 36.5;
			 parameters[10] = 2.23;
             parameters[11] = 6.88;
			 parameters[12] = 34.2;
			 parameters[14] = 30;
			 parameters[15] = 30;
			 parameters[13] = -20 * log10(4 * pi*parameters[0] / ramda);
	}
    else if(cm_num == 92) //Measurement environment #2
		//Experimental data Tx : 30deg, Rx : 30deg
	{
			 parameters[0] = 1;
			 parameters[1] = 0;
			 parameters[2] = 0;
			 parameters[3] = -107.8;
			 parameters[4] = 2.08; //9.1[dB]
			 parameters[5] = 7;
			 parameters[6] = 1 / 22.6;
             parameters[7] = 1 / 0.99;
			 parameters[8] = 64.2;
             parameters[9] = 61.1;
			 parameters[10] = 2.66;
             parameters[11] = 4.39;
			 parameters[12] = 45.8;
			 parameters[14] = 30;
			 parameters[15] = 30;
			 parameters[13] = -20 * log10(4 * pi*parameters[0] / ramda);
	}
}

void tg3c_tsv_ct_r6(int nlos, int num_channels, int adist, double fc, int los_beta_flg, double L_pl,
	double Lam, double lambda, double Gam, double gamma, double std_ln_1, double std_ln_2, int Lmean,
	double Omega0, double smallk, double sigma_fai, int tx_hpbw, int rx_hpbw, int ant_type, int op_num,
	vector <int> &beta, vector <double> &h, vector <double> &h2, vector <double> &aoa, vector <double> &t, vector <double> &t0, vector <int> &np, vector <int> &cl_idx)
	{
	    double std_L = 1/sqrt(2*Lam);
	    double std_lam = 1/sqrt(2*lambda);
	    double Tc, cl_ang_deg, beta0m, beta0, dK, Tc0;
		int h_len = 1000;

	    for (int k = 1; k <= num_channels; k++)
        {
			int path_ix, L;
			path_ix = 0;
			vector <double> tmp_h, tmp_t, tmp_aoa, tmp_clidx;

            L = max(1, tsv_poissrnd(Lmean));//泊松过程公式

            if(nlos == 0)
            {
                if(los_beta_flg == 1)
                {
                    beta[k-1] = tsv_beta_calc_r5(fc, adist, tx_hpbw, rx_hpbw, ant_type);
                }
                else if(los_beta_flg == 0)
                {
                    beta.push_back(1);
                }
                else if(los_beta_flg == -1)
                {
                    beta.push_back(0);
                }
                if(los_beta_flg != -1)
                {
//                    path_ix = path_ix + 1;
                    path_ix++;
                    tmp_h.push_back(beta[k - 1]);
                    tmp_t.push_back(0);
                    tmp_clidx.push_back(1);
                    tmp_aoa.push_back(0);
                }
            }
            else
            {
                if (los_beta_flg != -1)
                {
                    beta.push_back(1);
                }
                else
                {
                    beta.push_back(0);
                }
            }
            if (nlos == 0 && los_beta_flg == -1)//LOS SV model
            {
                Tc = 0;
                cl_ang_deg = 0;
            }
            else
            {

                Tc = pow((std_L * randn()), 2) + pow((std_L * randn()), 2);
                cl_ang_deg = fabs(360 * rand1() - 180);
            }
            if (nlos == 1 && los_beta_flg == -1)
            {
                t0.push_back(Tc);
            }
            dK = L_pl - Omega0;
            Tc0 = Tc;

            for (int ncluster = 0; ncluster < L; ncluster++)
            {
				//relative arrival time of the first ray is set to be 0 in each cluster
				//每簇中第一条多径的到达时间为0，so 多径的到达时间是相对的。
                double Tr = 0;
                int fray = 1; // flag set to be 1 when it is the first arrival ray
				double Mcluster, Pcluster, Tr_len;
                Mcluster = std_ln_1 * randn();
                Pcluster = (-dK - 10*(Tc - Tc0)/Gam/(double) log((double) 10)) + Mcluster;
                Tr_len = 10*gamma;

                while(Tr < Tr_len)
                {
					double t_val, ray_ang_deg, ray_ang_deg0, ray_aoa_c_angled, aoa_val, Mray, Pray, small_dk, h_val;
					ray_ang_deg0 = 0;
                    t_val = Tc + Tr;
                    if (fray == 1)
                    {
                        ray_ang_deg = cl_ang_deg;
                    }
                    else
                    {
                        //ray_ang_deg0 = 0;
                        //tsv_laplacernd(sigma_fai, ray_ang_deg0);
                        //double ray_ang_deg0 = tsv_laplacernd_output;
                        ray_ang_deg = cl_ang_deg + tsv_laplacernd(sigma_fai);
                    }

                    complex <double> data_for_exp_1 (0, ray_ang_deg/ 180 * pi);
                    complex <double> ray_aoa_c = exp(data_for_exp_1);
                    //double _Complex ray_aoa_c = exp(I*ray_ang_deg/180*pi);

                    ray_aoa_c_angled = angle1(ray_aoa_c);
                    aoa_val = ray_aoa_c_angled/pi*180;
                    Mray = std_ln_2 * randn();

                    if (fray == 1)
                    {
                        Pray = Mray;
                        fray = 0;
                    }
                    else
                    {
                        small_dk = smallk * 10 * log10((double) exp((double) 1));
                        Pray = -10 * Tr / gamma / (double) log((double) 10) - small_dk + Mray;
                    }
                    h_val =pow(10,((Pcluster+Pray)/20));

                    path_ix = path_ix + 1;

					//if (path_ix > h_len)

                    tmp_h.push_back(h_val);
                    tmp_t.push_back(t_val);
                    tmp_clidx.push_back(ncluster + 2);

                    tmp_aoa.push_back(aoa_val);

					//double Tr_plus =  pow(std_lam*gaussrand(), 2) + pow(std_lam*gaussrand(), 2);

                    Tr = Tr + pow(std_lam*randn(), 2) + pow(std_lam*randn(), 2);
                }
                Tc = Tc + pow(std_L*randn(), 2) *3 + pow(std_L*randn(), 2);
                cl_ang_deg = 360 * rand1() - 180;
            }
            np.push_back(path_ix); //path_ix数值偏大

			map<int, double> m_tmp_t;
			vector < pair<int, double>> v_tmp_t;
			vector <double> sort_tmp_t;
			vector <int> sort_ix;
			for (int i = 0; i < tmp_t.size(); i++)
			{
				m_tmp_t.insert(pair<int, double> (i, tmp_t[i]));
			}
			sortMapbyValue(m_tmp_t,v_tmp_t);
			for (int i = 0; i < v_tmp_t.size(); i++)
			{
				sort_tmp_t.push_back(v_tmp_t[i].second);
				sort_ix.push_back(v_tmp_t[i].first);
			}

			for (int i = 0; i < sort_tmp_t.size(); i++)
			{
				t.push_back(sort_tmp_t[i]);
				h.push_back(tmp_h[sort_ix[i]]);
				aoa.push_back(tmp_aoa[sort_ix[i]]);
				cl_idx.push_back(tmp_clidx[sort_ix[i]]);
			}
			/*if (t.size() % 1000 != 0)
			{
				int t_siz = t.size();
				int t_siz_1 = (double)ceil((double) t.size() / 1000) * 1000;
				for (int i = t_siz; i < t_siz_1; i++)
				{
					t.push_back(0);
					h.push_back(0);
					aoa.push_back(0);
					cl_idx.push_back(0);
				}
			}*/
        }

		vector <int> np_sum;
		np_sum.push_back(np[0]);
		for (int i = 1; i < np.size(); i++)
		{
			np_sum.push_back(np[i] + np_sum[i - 1]);
		}
		if (op_num == 2 || op_num == 3)
		{
			vector <double> tGrh, tGrh1;
			if (nlos == 0)
			{
				tsv_ant_gain_r6(ant_type, rx_hpbw, aoa, 0, tGrh);
				//tsv_ant_gain_r7(ant_type, rx_hpbw, aoa, tGrh1);
				for (int i = 0; i < num_channels; i++)
				{
					for (int j = np[i]; j < tGrh.size() / 100; j++)
					{
						tGrh[j * 100 + i] = 0;
					}
				}
				for (int i = 0; i < tGrh.size(); i++)
				{
					h2.push_back(h[i] * tGrh[i]);
				}
			}

			else 
			{
				int ii;
				vector <int> rslv;
				vector <double> aoa_ant_gain, tGrh0, h_tGrh0, h1, h_pow_pre, h_pow, tGrh ,aoa_ant_gain_new;
				for (int i = 0; i < num_channels; i++)
				{
					if (i == 0)
					{
						for (int j = 0; j < np[i]; j++)
						{
							aoa_ant_gain.push_back(aoa[j]);
							h_tGrh0.push_back(h[j]);
						}
					}
					else
					{
						for (int j = np_sum[i - 1]; j < np_sum[i]; j++)
						{
							aoa_ant_gain.push_back(aoa[j]); //基本正常
							h_tGrh0.push_back(h[j]); //h的值偏小
						}
					}

					/*//code block for test
					vector <double> h_tGrh0_sort, aoa_ant_gain_sort;
					h_tGrh0_sort.insert(h_tGrh0_sort.end(), h_tGrh0.begin(), h_tGrh0.end());
					aoa_ant_gain_sort.insert(aoa_ant_gain_sort.end(), aoa_ant_gain.begin(), aoa_ant_gain.end());
					sort(h_tGrh0_sort.begin(), h_tGrh0_sort.end());
					sort(aoa_ant_gain_sort.begin(), aoa_ant_gain_sort.end());
					ClearVector(h_tGrh0_sort);
					ClearVector(aoa_ant_gain_sort);
					//test end*/

					for (int j = 0; j < 360; j++)
					{
						double h_pow_sum = 0;
						ii = j + 1;
						tsv_ant_gain_r6(ant_type, rx_hpbw, aoa_ant_gain, ii, tGrh0);
						for (int ij = 0; ij < tGrh0.size(); ij++)
						{
							h1.push_back(h_tGrh0[i] * tGrh0[i]);
							if (ij == 0)
							{
								h_pow_pre.push_back(h1[ij] * h1[ij]);
							}
							else
							{
								h_pow_pre.push_back(h1[ij] * h1[ij] + h_pow_pre[ij - 1]);
							}
						}
						h_pow.push_back(h_pow_pre.back());
						ClearVector(h_pow_pre);
						ClearVector(h1);
						ClearVector(tGrh0);
					}

					map<int, double> m_h_pow;
					vector < pair<int, double>> v_h_pow;
					vector <double> sort_h_pow, sort_h_ix;
					for (int ix = 0; ix < h_pow.size(); ix++)
					{
						m_h_pow.insert(pair<int, double> (ix, h_pow[ix]));
					}
					sortMapbyValue(m_h_pow,v_h_pow);
					for (int ix = 0; ix < v_h_pow.size(); ix++)
					{
						sort_h_pow.push_back(v_h_pow[ix].second);
						sort_h_ix.push_back(v_h_pow[ix].first);
					}
					double a = sort_h_pow.back(); //最值差很大，不过没用到后面运算中
					int b = sort_h_ix.back();
					ClearVector(h_pow);
					ClearVector(sort_h_pow);
					ClearVector(sort_h_ix);

					tsv_ant_gain_r6_2(ant_type, rx_hpbw, aoa_ant_gain, b+1, tGrh, aoa_ant_gain_new);//tGrh和aoa_ant_gain_new数据OK，

					ClearVector(aoa_ant_gain);

					/*//code block for test
					vector <double> tGrh_test, aoa_ant_gain_new_test;
					aoa_ant_gain_new_test.insert(aoa_ant_gain_new_test.end(), aoa_ant_gain_new.begin(), aoa_ant_gain_new.end());
					tGrh_test.insert(tGrh_test.end(), tGrh.begin(), tGrh.end());
					sort(tGrh_test.begin(), tGrh_test.end());
					sort(aoa_ant_gain_new_test.begin(), aoa_ant_gain_new_test.end());
					ClearVector(aoa_ant_gain_new_test);
					ClearVector(tGrh_test);
					//test end*/

					for (int ij = 0; ij < h_tGrh0.size(); ij++)
					{
						h2.push_back(h_tGrh0[ij] * tGrh[ij]); //因h的缘故，数值普遍偏小
					}
					ClearVector(h_tGrh0);
					ClearVector(tGrh);

					/*//code block for test
					vector <double> h2_test;
					h2_test.insert(h2_test.end(), h2.begin(), h2.end());
					sort(h2_test.begin(), h2_test.end());
					//test end*/

					/*if (i == 0)
					{
						for (int jx = 0; jx < np_sum[i]; jx++)
						{
							//aoa_ant_gain.push_back(aoa[j]);
							aoa[jx] = aoa_ant_gain_new[jx];
						}
					}
					else
					{
						for (int jx = np_sum[i - 1]; jx < np_sum[i]; jx++)
						{
							//aoa_ant_gain.push_back(aoa[j]);
							aoa[jx] = aoa_ant_gain_new[jx];
						}
					}*/
					//vector<double>().swap(aoa_ant_gain_new);
					//aoa_ant_gain.~vector <double>();
				}
			}
		}
	}

void tg3c_sv_cnvrt_ct(vector <complex<double>> &h_ct, vector <double> &t, vector <int> &np, int num_channels, vector <complex<double>> hN, double N)
{
	int min_Nfs, Nfs, np_k, ts;
	double N_min, t_max;
	vector <int> t_Nfs, np_sum, t_Nfs_sum;

	ts = 1;
	min_Nfs = 50;

	double array_max[2] = {1, (double)ceil((double)min_Nfs * ts)};
	MaxandMin(array_max, 0, 1, N, N_min);
	N = (double)pow((double)2, nextpow2(N));
	Nfs	= N / ts;

	vector <double> t_tmp;
	t_tmp.insert(t_tmp.end(), t.begin(), t.end());
	sort(t_tmp.begin(), t_tmp.end());
	t_max = t_tmp.back();
	h_len = 1 + floor(t_max * Nfs);
	for (int k = 0; k < num_channels; k++)
	{
		np_k = np[k];
		if (k == 0)
		{
			np_sum.push_back(np[k]);
			for (int i = 0; i < np_k; i++)
			{
				t_Nfs.push_back(1 + floor(t[i] * Nfs));
			}
		}
		else
		{
			np_sum.push_back(np[k] + np_sum[k - 1]);
			for (int i = np_sum[k - 1]; i < np_sum[k]; i++)
			{
				t_Nfs.push_back(1 + floor(t[i] * Nfs));
			}
		}

		for (int i = 0; i < h_len * num_channels; i++)
		{
			hN.push_back(0);
		}
		/*for (int i = 0; i < t_Nfs.size(); i++)
		{
			hN.push_back(0);
		}*/
		if (k == 0)
		{
			for (int n = 0; n < np_k; n++)
			{
				hN[t_Nfs[n]] = hN[t_Nfs[n]] + h_ct[n];
			}
		}
		else
		{
			for (int n = 0; n < np_k; n++)
			{
				hN[t_Nfs[n] + k * h_len] = hN[t_Nfs[n] + k * h_len] + h_ct[n + np_sum[k - 1]];
			}
		}
	}
}

void tg3c_ct2dt(vector <complex <double> > &h_ct, vector <double> &t, vector <complex <double> > &h_dt)
{
/********************************************************************************************
Description:

    function returns channel response due to target sample rate

    ct2dt(vector <complex <double> > &h_ct, vector <double> &t, cfg cfg0, ch ch0, vector <int> &toa_dt, vector <complex <double> > &h_dt)

Inputs:

	cfg         - part of configuration structure defining beamforming related parameters
    h_ct        - continuous time channel impulse response
    t           - continuous time in [ns]
    sample_rate - sample rate in [GHz]

Outputs:

    h_dt - discrete time channel impulse response
********************************************************************************************/
	double N_min = 0;
	double N, Nfs;
	int ts = 1;
	int min_Nfs = 50;
	int siz = h_ct.size();
	vector <int> time_bin;

	double array_max[2] = {1, (double)ceil((double)min_Nfs * ts)};
	MaxandMin(array_max, 0, 1, N, N_min);
	N = (double)pow((double)2, nextpow2(N));
	Nfs	= N / ts;
	int N_num = ceil(siz / Nfs);
	h_dt.resize(N_num);
	for (int ray_ix = 0; ray_ix < siz; ray_ix++)
	{
		time_bin.push_back(round(t[ray_ix] / ts) + 1);
		h_dt[time_bin[ray_ix] - 1] = h_dt[time_bin[ray_ix] - 1] + h_ct[ray_ix];
	}

	vector <double> h_dt_abs;
	double temp, h_dt_norm;
	for (int i = 0; i < h_dt.size(); i++)
	{
		//temp = abs(h_dt[i]);
		temp = pow(h_dt[i].real(), 2) + pow(h_dt[i].imag(), 2);
		if (i == 0)
		{
			h_dt_abs.push_back(temp);
		}
		else if (i > 0)
		{
			h_dt_abs.push_back(pow(h_dt[i].real(), 2) + pow(h_dt[i].imag(), 2) + h_dt_abs[i - 1]);
		}
	}
	h_dt_norm = sqrt(h_dt_abs.back());
	for (int i = 0; i < h_dt.size(); i++)
	{
		h_dt[i] = h_dt[i] / h_dt_norm;
	}
	vector <double> h_dt_test;
	for (int i = 0; i < h_dt.size(); i++)
	{
		if (i == 0)
		{
			h_dt_test.push_back(pow(h_dt[i].real(), 2) + pow(h_dt[i].imag(), 2));
		}
		else
		{
			h_dt_test.push_back(pow(h_dt[i].real(), 2) + pow(h_dt[i].imag(), 2) + h_dt_test[i - 1]);
		}
	}
}

void convolution(vector <complex <double> > &p_Data, vector <complex <double> > &p_Filter, vector <complex <double> > &p_Output, int data_Long, int filter_Long, int output_Long)
{
/********************************************************************************************
      函数名：convolution
	  函数功能：对输入向量进行滤波卷积
	  函数参数：double *p_Data  ---指向输入向量指针
				double *p_filter ---指向滤波器向量指针
	            double*p_output ---指向输出向量指针
                int data_Long	---输入向量长度
				int filter_Long  ---滤波器长度
				int output_Long ---输出向量长度

      程序默认data_Long > filter_Long
	  函数返回值：无
********************************************************************************************/
	p_Filter.resize(filter_Long);
	p_Output.resize(output_Long);
	double temp = 0;
	//code block for test
	vector <complex <double>> data_test, filter_test;
	vector <double> data_test_i, data_test_q, filter_test_i, filter_test_q;
	data_test.insert(data_test.begin(), p_Data.begin(), p_Data.end());
	filter_test.insert(filter_test.begin(), p_Filter.begin(), p_Filter.end());
	for (int i = 0; i < data_test.size(); i++)
	{
		data_test_i.push_back(data_test[i].real());
		data_test_q.push_back(data_test[i].imag());
	}
	for (int i = 0; i < filter_test.size(); i++)
	{
		filter_test_i.push_back(filter_test[i].real());
		filter_test_q.push_back(filter_test[i].imag());
	}
	sort(data_test_i.begin(), data_test_i.end());
	sort(data_test_q.begin(), data_test_q.end());
	sort(filter_test_i.begin(), filter_test_i.end());
	sort(filter_test_q.begin(), filter_test_q.end());
	//test end

	for (int i = 0; i < filter_Long; i++)
	{
		for (int j = 0; j <= i; j++)
			p_Output[i] = p_Output[i] + p_Data[j] * p_Filter[i - j];
	}
	for (int i = filter_Long; i < data_Long; i++)
	{
		for (int j = 0; j <filter_Long; j++)
			p_Output[i] = p_Output[i] + p_Data[i - j] * p_Filter[j];
	}
	for (int i = data_Long; i < data_Long + filter_Long - 1; i++)
	{
		for (int j = i - data_Long + 1; j < filter_Long; j++)
			p_Output[i] = p_Output[i] + p_Data[i - j] * p_Filter[j];
	}

	//code block for test
	vector <complex <double>> output_test;
	vector <double> output_test_i, output_test_q;
	output_test.insert(output_test.begin(), p_Output.begin(), p_Output.end());
	for (int i = 0; i < output_test.size(); i++)
	{
		output_test_i.push_back(output_test[i].real());
		output_test_q.push_back(output_test[i].imag());
	}
	sort(output_test_i.begin(), output_test_i.end());
	sort(output_test_q.begin(), output_test_q.end());
	//test end
}

void add_noise(vector <complex <double> > &in_data, int c, vector <complex <double> > &out_data)
{
	int r = 1;
	vector <complex <double> > noise;

	for (int i = 0; i < c; i++)
	{
		noise.push_back(complex <double> (gaussrand(), gaussrand()));
		out_data.push_back(in_data[i] + noise[i]);
	}

	//code block for test
	vector <double> out_data_i, out_data_q;
	for (int i = 0; i < out_data.size(); i++)
	{
		out_data_i.push_back(out_data[i].real());
		out_data_q.push_back(out_data[i].imag());
	}
	sort(out_data_i.begin(), out_data_i.end());
	sort(out_data_q.begin(), out_data_q.end());
}

void tg3c_tsv_eval_r7(int cm_num, double fc, vector <complex<double>> &data_in, vector <complex<double>> &data_out)
{
	double cl_idx[] = { 0 };
	double parameters[16];
	tg3c_tsv_params_r4(cm_num, parameters);

	int adist, nlos, los_beta_flg, Lmean, tx_hpbw, rx_hpbw, rx_hpbw0;
	double Omega0, smallk, Lam, lamda, Gam, gamma, std_ln_1, std_ln_2, sigma_fai, L_pl;

	adist        = parameters[0];      //收发天线距离
    nlos         = parameters[1];      //是否为NLOS环境
	los_beta_flg = parameters[2];      //
	Omega0		 = parameters[3];      //簇的功率
    smallk		 = parameters[4];      //小k，莱斯因子
    Lmean		 = parameters[5];      //到达簇的平均数
    Lam			 = parameters[6];      //簇的到达率
    lamda		 = parameters[7];      //径的到达率
	Gam			 = parameters[8];      //簇的时延（ns）
	gamma		 = parameters[9];      //径的时延（ns）
	std_ln_1	 = parameters[10];     //簇衰减的标准差
	std_ln_2	 = parameters[11];     //径衰减的标准差
	sigma_fai	 = parameters[12];	   //簇的到达角（deg）
	tx_hpbw		 = parameters[14];     //发射天线半功率角
	rx_hpbw		 = parameters[15] * 2; //接收天线半功率角
	rx_hpbw0     = parameters[15];
	L_pl		 = parameters[13];     //路损

	int ant_type = 1;
	int op_num = 2;
	int num_channels = 1;
	vector <double> h_ct, h2_ct, aoa_ct, t_ct, t0;
	vector <int> beta, np, idx;
	double N;
	vector <complex<double>> h2, hN, h;

 	tg3c_tsv_ct_r6(nlos, num_channels, adist, fc, los_beta_flg, L_pl, Lam, lamda, Gam, gamma, std_ln_1, std_ln_2, Lmean, Omega0, smallk, sigma_fai, tx_hpbw, rx_hpbw, ant_type, op_num, beta, h_ct, h2_ct, aoa_ct, t_ct, t0, np, idx);

	if (nlos == 0)
	{
		for (int i = 0; i < np[0]; i++)
		{
			h2.push_back(complex <double> (h2_ct[i], rand1()));
		} 
		for (int i = np[0]; i < h2_ct.size(); i++)
		{
			h2.push_back(complex <double> (rand1(), rand1()) * h2_ct[i]);
		}
	}
	 else	
	{
		for (int i = 0; i < h2_ct.size(); i++)
		{
			h2.push_back(complex <double> (rand1(), rand1()) * h2_ct[i]);
		}
	}

	tg3c_ct2dt(h2, t_ct, hN);

	int sleep_num = 7749;
	
	int NumOfTaps = hN.size();

	vector <complex <double> > imp_res_data, data_out_channel;
	for (int i = 0; i < NumOfTaps; i++)
	{
		imp_res_data.push_back(hN[i]);

	}
	vector <double> imp_res_data_test;
	for (int i = 0; i < imp_res_data.size(); i++)
	{
		double imp_res_test;
		imp_res_test = pow(imp_res_data[i].real(), 2) + pow(imp_res_data[i].imag(), 2);
		if (i == 0)
		{
			imp_res_data_test.push_back(imp_res_test);
		}
		else
		{
			imp_res_data_test.push_back(imp_res_test + imp_res_data_test[i-1]);
		}
	}

	convolution(data_in, imp_res_data, data_out_channel, data_in.size(), NumOfTaps, data_in.size() + NumOfTaps - 1);
	data_out.insert(data_out.begin(), data_out_channel.begin(), data_out_channel.end());

	//code block for test
	vector <complex <float>> data_out_real, data_out_imag;
	for (int i = 0; i < data_out.size(); i++)
	{
		data_out_real.push_back(data_out[i].real());
		data_out_imag.push_back(data_out[i].imag());
	}
	//sort(data_out_imag.begin(), data_out_imag.end());
	//test end

	//add_noise(data_out_channel, data_in.size(), data_out);
}


