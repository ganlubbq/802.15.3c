#include "stdafx.h"
#include "func.h"
double maxCCDFData(double *s,int sizeN)
{
	double num;
	num = s[0];
	for (int i=0;i<sizeN;i++)
	{
		if(num<s[i])
			num = s[i];
	}
	return num;
}
//计算CCDF序列点函数
double sumCCDF(double *acceptPointArray,double *pPointArrayCCDF,int m_RealValuenSize,int ScaleXend,int num_of_space)
{
	//CCDF的过程部分
	double* NUm=new double[num_of_space+1];//大于0的间隔和小于0的部分
	double DataMax;
	//double DataMin;
	double max_ccdf;
	double DataInter;
	double AvgSum=0;
	//计算平均功率
	for (int avgFlg=0;avgFlg<m_RealValuenSize;avgFlg++)
	{
		AvgSum = AvgSum+pPointArrayCCDF[avgFlg];
	}
	AvgSum = AvgSum/m_RealValuenSize;
	//Power/avg.power
	for (int avgFlgE=0;avgFlgE<m_RealValuenSize;avgFlgE++)
	{
		pPointArrayCCDF[avgFlgE]=10*log10(pPointArrayCCDF[avgFlgE]/AvgSum);
	}
	max_ccdf = maxCCDFData(pPointArrayCCDF,m_RealValuenSize);//最大值
	DataInter = (ScaleXend)/(double)num_of_space;           //类似直方图区间长度,设为500个区间

	for (int NM=0;NM<=num_of_space;NM++)
		NUm[NM]=0;//m_ALLNim区间个数，各区间概率值
	for (int SM=0;SM<=num_of_space;SM++)
		acceptPointArray[SM]=0;           //初始化累积概率数组

	//for(int m=0;m<=num_of_space;m++)
	//{
	//	for (int i=0;i<m_RealValuenSize;i++)
	//	{
	//		if((long)(pPointArrayCCDF[i]*10000000000)>=(long)((-5+m*DataInter)*10000000000))
	//			NUm[m]+=1.0;
	//	}
	//}

	for (int i=0;i<m_RealValuenSize;i++)
	{
		if((long)(pPointArrayCCDF[i]*10000000000)<0)
		{
			NUm[0]++;
		}
		for (int j=1;j<=num_of_space;j++)
		{
			if ((long)(pPointArrayCCDF[i]*10000000000)>= (long)((DataInter*(double)(j-1))*10000000000) && (long)(pPointArrayCCDF[i]*10000000000)< (long)((DataInter*(double)j)*10000000000))
			{
				// cdf区间端值表示
				NUm[j]++;          //统计落入每个区间的数目
				break;
			}
		}
	}

	acceptPointArray[0]=NUm[0]/m_RealValuenSize;         //小于0的概率
	for (int m=1;m<=num_of_space;m++)
	{
		NUm[m]=NUm[m]/m_RealValuenSize;        //求概率
		acceptPointArray[m]=acceptPointArray[m-1]+NUm[m];//累计概率
	}

	for (int n=0;n<=num_of_space;n++)
	{
		if(acceptPointArray[n]>0.9994)
			acceptPointArray[n]=1;
		acceptPointArray[n]=1-acceptPointArray[n];// cdf->ccdf
	}
	return max_ccdf;   //max_ccdf
}

//比特翻转
void bitrp (vector<complex<double>> &Data_In, int n)
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

//FFT
int FFT(vector<complex<double>> &Data_in, int n)
{
	long N=n,i,p;
	complex<double> temp=(0.0,0.0);
	if( N & (N-1) )
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
	//vector<double> wreal(N/2, 0.0);
	//vector<double> wimag(N/2, 0.0);
    double treal, timag, ureal, uimag, arg;
	long m, k, j, t, index1, index2;

	bitrp (Data_in, N);

	// 计算 1 的前 n / 2 个 n 次方根的共轭复数 W'j = wreal [j] + i * wimag [j] , j = 0, 1, ... , n / 2 - 1
	arg = - 2 * 3.14159 / N;
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
	return N;
}

void FFTShift(vector<complex<double>> &Data_in)
{
	int len=Data_in.size();
	complex<double> temp;
	for(int i=0;i<len/2;i++)
	{
		temp=Data_in[i];
		Data_in[i]=Data_in[i+len/2];
		Data_in[i+len/2]=temp;
	}
}