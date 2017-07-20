#include "genParam.h"
#include "stdafx.h"

using namespace std;

void bitrp_3c(vector<complex<double> > &Data_In, int n)
{
	// 位反转置换 Bit-reversal Permutation
	int i, j, a, b, p;
	complex<double> temp;
	for (i = 1, p = 0; i < n; i *= 2)
	{
		p ++;
	}
	for (i = 0; i < n; i ++)
	{
		a = i;
		b = 0;
		for (j = 0; j < p; j ++)
		{
			b = (b << 1) + (a & 1);    // b = b * 2 + a % 2;
			a >>= 1;        // a = a / 2;
		}
		if ( b > i)
		{
			temp=Data_In[b];
			Data_In[b]=Data_In[i];
			Data_In[i]=temp;
		}
	}
}

void FFT_3c(vector<complex<double> > &Data_in, int n)
{
	int N=n,i,p;
	complex<double> temp=(0.0,0.0);
	if( N& (N-1) )
	{
		for (i = 1, p = 0; i < N; i *= 2)
		{
			p ++;
		}
		N=pow(2.0,p);
	}	                                //不是2的幂
	for(int len=0;len<N-n;len++)
		Data_in.push_back(temp);
	double* wreal=new double[N/2];
	double* wimag=new double[N/2]; 
	double treal, timag, ureal, uimag, arg;
	int m, k, j, t, index1, index2;

	bitrp_3c(Data_in, N);

	// 计算 1 的前 n / 2 个 n 次方根的共轭复数 W'j = wreal [j] + i * wimag [j] , j = 0, 1, ... , n / 2 - 1
	arg = - 2 * PI / N;
	treal = cos (arg);
	timag = sin (arg);
	wreal [0] = 1.0;
	wimag [0] = 0.0;
	for (j = 1; j < N / 2; j ++)
	{
		wreal [j] = wreal [j - 1] * treal - wimag [j - 1] * timag;
		wimag [j] = wreal [j - 1] * timag + wimag [j - 1] * treal;
	}

	for (m = 2; m <= N; m *= 2)
	{
		for (k = 0; k < N; k += m)
		{
			for (j = 0; j < m / 2; j ++)
			{
				index1 = k + j;
				index2 = index1 + m / 2;
				t = N * j / m;    // 旋转因子 w 的实部在 wreal [] 中的下标为 t
				treal = wreal [t] * Data_in[index2].real() - wimag [t] * Data_in[index2].imag();
				timag = wreal [t] * Data_in[index2].imag() + wimag [t] * Data_in[index2].real();
				ureal = Data_in[index1].real();
				uimag = Data_in[index1].imag();
				Data_in[index1].real(ureal + treal);
				Data_in[index1].imag(uimag + timag);
				Data_in[index2].real(ureal - treal);
				Data_in[index2].imag(uimag - timag);
			}
		}
	}
	delete[] wreal;
	delete[] wimag;
}
void IFFT(vector<complex<double> > &Data_in, int n)
{
	int N=n,i,p;
	complex<double> temp=(0.0,0.0);
	if( N& (N-1) )
	{
		for (i = 1, p = 0; i < N; i *= 2)
		{
			p ++;
		}
		N=pow(2.0,p);
	}	                                //不是2的幂
	for(int len=0;len<N-n;len++)
		Data_in.push_back(temp);
	double* wreal=new double[N/2];
	double* wimag=new double[N/2]; 
	double treal, timag, ureal, uimag, arg;
	int m, k, j, t, index1, index2;

	bitrp_3c(Data_in, N);

	// 计算 1 的前 n / 2 个 n 次方根 Wj = wreal [j] + i * wimag [j] , j = 0, 1, ... , n / 2 - 1
	arg = 2 * PI / N;
	treal = cos (arg);
	timag = sin (arg);
	wreal [0] = 1.0;
	wimag [0] = 0.0;
	for (j = 1; j < N / 2; j ++)
	{
		wreal [j] = wreal [j - 1] * treal - wimag [j - 1] * timag;
		wimag [j] = wreal [j - 1] * timag + wimag [j - 1] * treal;
	}

	for (m = 2; m <= N; m *= 2)
	{
		for (k = 0; k < N; k += m)
		{
			for (j = 0; j < m / 2; j ++)
			{
				index1 = k + j;
				index2 = index1 + m / 2;
				t = N * j / m;    // 旋转因子 w 的实部在 wreal [] 中的下标为 t
				treal = wreal [t] * Data_in[index2].real() - wimag [t] * Data_in[index2].imag();
				timag = wreal [t] * Data_in[index2].imag() + wimag [t] * Data_in[index2].real();
				ureal = Data_in[index1].real();
				uimag = Data_in[index1].imag();
				Data_in[index1].real(ureal + treal);
				Data_in[index1].imag(uimag + timag);
				Data_in[index2].real(ureal - treal);
				Data_in[index2].imag(uimag - timag);
			}
		}
	}

	for (j=0; j < N; j ++)
	{
		Data_in[j]/=N;
	}
	delete[] wreal;
	delete[] wimag;
}