//#include"genParam.h"
//#include "stdafx.h"
//using namespace std;
//
///****************************************公共模块*****************************************/
//void hex2binary(int hex[], vector<int> &binary, int nhex)
//{
//	for(int i = 0; i < nhex; i++)
//	{
//		/*binary[4*i] = (hex[i]/2/2/2)%2;
//		binary[4*i+1] = (hex[i]/2/2)%2;
//		binary[4*i+2] = (hex[i]/2)%2;
//		binary[4*i+3] = hex[i]%2;*/
//		binary.push_back((hex[i]/2/2/2)%2);
//		binary.push_back((hex[i]/2/2)%2);
//		binary.push_back((hex[i]/2)%2);
//		binary.push_back(hex[i]%2);
//	}
//}
//
//void bits2nums(vector<int> &codebits, vector<int> &nums, int modtype)
//{
//	int Nbits = codebits.size();
//	int Nnums = Nbits/modtype;//映射符号数目
//	double Nnums_mod = fmod(Nbits*1.0,modtype*1.0); 
//	if (Nnums_mod == 0)
//	{
//		switch (modtype)
//		{
//		case 1 : 
//			{
//				for(int i = 0; i < Nnums; i++)
//					nums.push_back(codebits[i]);
//				break;
//			}
//		case 2 :
//			{
//				int temp_index[2] = {2, 1};//调制权重
//				for (int i = 0; i < Nnums; i++)
//				{
//					int temp = 0;
//					for (int j = 0; j < modtype; j++)
//						temp += codebits[modtype * i + j] * temp_index[j];
//					nums.push_back(temp);
//				}
//				break;
//			}
//		case 3 :
//			{
//				int temp_index[3] = {4, 2, 1};//调制权重
//				for (int i = 0; i < Nnums; i++)
//				{
//					int temp = 0;
//					for (int j = 0; j < modtype; j++)
//						temp += codebits[modtype * i + j] * temp_index[j];
//					nums.push_back(temp);
//				}
//				break;
//			}
//		case 4 :
//			{
//				int temp_index[4] = {8, 4, 2, 1};//调制权重
//				for (int i = 0; i < Nnums; i++)
//				{
//					int temp = 0;
//					for (int j = 0; j < modtype; j++)
//						temp += codebits[modtype * i + j] * temp_index[j];
//					nums.push_back(temp);
//				}
//				break;
//			}
//		case 6:
//			{
//				int temp_index[6] = {32, 16, 8, 4, 2, 1};//调制权重
//				for (int i = 0; i < Nnums; i++)
//				{
//					int temp = 0;
//					for (int j = 0; j < modtype; j++)
//						temp += codebits[modtype * i +j] * temp_index[j];
//					nums.push_back(temp);
//				}
//				break;
//			}
//		default : 
//			{
//				cout<<"输入的调制模式错误!"<<endl;
//				exit(EXIT_FAILURE);
//			}
//		}
//	}
//	else
//	{
//		cout<<"输入的比特序列数目错误"<<endl;
//		exit(EXIT_FAILURE);
//	}
//}
//
//int mod(int a, int b)
//{
//	if (b > 0)
//	{
//		if (a >= 0)
//			return a % b;
//		else
//		{
//			//int nums = (int)(ceil(abs(a) * 1.0 / b));//最小倍数
//			//int temp2 = nums * b + a;//最小整数；
//			return (((int)ceil(abs(a) * 1.0 / b)) * b + a) % b;
//		}
//	}
//	else
//	{
//		cout << "第二个变量应该大于零" << endl;
//		exit(EXIT_FAILURE);
//	}
//}
//
//void gen_prbs(vector<int> &genbits, int Nbits)
//{
//	srand((unsigned)time(0));     
//	for(int i = 0; i < Nbits; i++)          //产生随机数    
//		genbits.push_back(rand() % 2);
//}
//
//void genLDPCGenMatrix(int codeIndex, vector<vector<double> > &nZindexTable)
//{
//	int N,D,r,c;
//	int Max = 0;
//	ifstream inf; //假设数据保存在c:\da.txt文件中
//	switch (codeIndex)
//	{
//	case 0:
//		{
//			N = 1;   D = 2; r = 16; c = 32; Max = 194;
//			inf.open("codeIndex0.txt");
//			break;
//		}
//	case 1:
//		{		
//			N = 5;   D = 8; r = 12; c = 32; Max = 59;
//			inf.open("codeIndex1.txt");	
//			break;
//		}	
//	case 2:
//		{
//			N = 3;   D = 4; r = 8; c = 32; Max = 91;
//			inf.open("codeIndex2.txt");	
//			break;
//		}	
//	case 3:
//		{
//			N = 7;  D = 8; r = 4; c = 32; Max = 139;
//			inf.open("codeIndex3.txt");
//			break;
//		}	
//	default:
//		std::cout<<"Invalid Code Index"<<std::endl;
//		break;
//	}
//	int k = r * 21;
//	nZindexTable.resize(k,vector<double>(Max,0));
//	for (int i =0;i < k;i++ )
//	{
//		for (int j =0;j < Max;j++)
//		{
//			inf>>nZindexTable[i][j];
//		}
//	}
//	inf.close(); //读取完毕后,关闭文件
//}
//
//void rotateZ(int index, double a[][21])
//{
//	double z[21][21] = {0};
//	for(int i = 0; i < 21; i++)
//	{
//		z[i][i] = 1;
//	}
//	int p[21]={0};
//	for(int i = 0; i < 21; i++)
//	{
//		p[i] = i;
//	}
//	for(int i = 0; i < 21; i++)
//	{
//		p[i] = (21 - index + p[i]) % 21;
//	}
//	for(int i = 0; i < 21; i++ )
//	{
//		for (int j = 0; j < 21; j++)
//		{
//			a[j][i] = z[j][int(p[i])]; 
//		}
//	}
//}
//
//void genLDPCparity(vector<double> &codeword, vector<vector<double> > &nZindex, vector<double> &paritybits)
//{
//	for (int i = 0; i < nZindex.size(); i++)
//	{
//		int len = nZindex[i][0];
//		int* nz = new int[len];
//		int sum  = 0;
//		for (int j = 0; j < len; j++)
//		{
//			nz[j] = nZindex[i][j + 1];	
//		}
//		for (int m = 0; m < len; m++)
//		{
//			sum += codeword[nz[m]-1];
//		}
//		paritybits[i] = sum % 2;
//		delete [] nz;
//	}
//}
//
//void HCS_encoder(vector<int> &bits_input, vector<int> &parity)
//{
//	int reg_temp[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};//初始化寄存器全1
//	for (int i = 0; i < bits_input.size(); i++)
//	{
//		int c15 = bits_input[i] ^ reg_temp[0];
//		int c3 = c15 ^ reg_temp[4];
//		int c10 = c15 ^ reg_temp[11];//计算校验位
//		for (int j = 0; j < 15; j++)
//		{
//			reg_temp[j] = reg_temp[j+1];
//		}
//		reg_temp[15] = c15;
//		reg_temp[10] = c10;
//		reg_temp[3] = c3;
//	}
//	for (int i = 0; i < 16; i++)
//	{
//		//parity[i] = reg_temp[i] ^ 1;
//		parity.push_back(reg_temp[i] ^ 1);//输出补码
//	}
//}
//
//void scrambler_gen_prbs(int ssid[], vector<int> &prbs, int Nbits)
//{
//	vector<int> prbs_temp (Nbits + 15);//构造扰码初始序列
//	for(int i = 0; i < 4; i++)
//		prbs_temp[3-i] = ssid[i];
//	int prbs_inif[11] = {1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1};
//	for(int i = 0; i < 11; i++)
//		prbs_temp[4+i] = prbs_inif[i];
//	for(int i = 0; i < Nbits; i++)
//	{
//		int x = prbs_temp[i];
//		int y = prbs_temp[i+1];
//		int z = x ^ y;
//		prbs_temp[i+15] = z;
//		//prbs[i] = prbs_temp[i+15];
//		prbs.push_back(prbs_temp[i+15]);
//	}
//}
//
//void scrambler(vector<int> &codebits, int ssid[])
//{
//	int Nbits = codebits.size();
//	vector<int> prbs;
//	scrambler_gen_prbs(ssid, prbs, Nbits);
//	for(int i = 0; i < Nbits; i++)
//		codebits[i] = codebits[i] ^ prbs[i];
//}
//
//void bitrp_3c(vector<complex<double> > &Data_In, int n)
//{
//	// 位反转置换 Bit-reversal Permutation
//	int i, j, a, b, p;
//	complex<double> temp;
//	for (i = 1, p = 0; i < n; i *= 2)
//	{
//		p ++;
//	}
//	for (i = 0; i < n; i ++)
//	{
//		a = i;
//		b = 0;
//		for (j = 0; j < p; j ++)
//		{
//			b = (b << 1) + (a & 1);    // b = b * 2 + a % 2;
//			a >>= 1;        // a = a / 2;
//		}
//		if ( b > i)
//		{
//			temp=Data_In[b];
//			Data_In[b]=Data_In[i];
//			Data_In[i]=temp;
//		}
//	}
//}
//
//void FFT_3c(vector<complex<double> > &Data_in, int n)
//{
//	int N=n,i,p;
//	complex<double> temp=(0.0,0.0);
//	if( N& (N-1) )
//	{
//		for (i = 1, p = 0; i < N; i *= 2)
//		{
//			p ++;
//		}
//		N=pow(2.0,p);
//	}	                                //不是2的幂
//	for(int len=0;len<N-n;len++)
//		Data_in.push_back(temp);
//	double* wreal=new double[N/2];
//	double* wimag=new double[N/2]; 
//	double treal, timag, ureal, uimag, arg;
//	int m, k, j, t, index1, index2;
//
//	bitrp_3c(Data_in, N);
//
//	// 计算 1 的前 n / 2 个 n 次方根的共轭复数 W'j = wreal [j] + i * wimag [j] , j = 0, 1, ... , n / 2 - 1
//	arg = - 2 * PI / N;
//	treal = cos (arg);
//	timag = sin (arg);
//	wreal [0] = 1.0;
//	wimag [0] = 0.0;
//	for (j = 1; j < N / 2; j ++)
//	{
//		wreal [j] = wreal [j - 1] * treal - wimag [j - 1] * timag;
//		wimag [j] = wreal [j - 1] * timag + wimag [j - 1] * treal;
//	}
//
//	for (m = 2; m <= N; m *= 2)
//	{
//		for (k = 0; k < N; k += m)
//		{
//			for (j = 0; j < m / 2; j ++)
//			{
//				index1 = k + j;
//				index2 = index1 + m / 2;
//				t = N * j / m;    // 旋转因子 w 的实部在 wreal [] 中的下标为 t
//				treal = wreal [t] * Data_in[index2].real() - wimag [t] * Data_in[index2].imag();
//				timag = wreal [t] * Data_in[index2].imag() + wimag [t] * Data_in[index2].real();
//				ureal = Data_in[index1].real();
//				uimag = Data_in[index1].imag();
//				Data_in[index1].real(ureal + treal);
//				Data_in[index1].imag(uimag + timag);
//				Data_in[index2].real(ureal - treal);
//				Data_in[index2].imag(uimag - timag);
//			}
//		}
//	}
//	delete[] wreal;
//	delete[] wimag;
//}
//
//void IFFT(vector<complex<double> > &Data_in, int n)
//{
//	int N=n,i,p;
//	complex<double> temp=(0.0,0.0);
//	if( N& (N-1) )
//	{
//		for (i = 1, p = 0; i < N; i *= 2)
//		{
//			p ++;
//		}
//		N=pow(2.0,p);
//	}	                                //不是2的幂
//	for(int len=0;len<N-n;len++)
//		Data_in.push_back(temp);
//	double* wreal=new double[N/2];
//	double* wimag=new double[N/2]; 
//	double treal, timag, ureal, uimag, arg;
//	int m, k, j, t, index1, index2;
//
//	bitrp_3c(Data_in, N);
//
//	// 计算 1 的前 n / 2 个 n 次方根 Wj = wreal [j] + i * wimag [j] , j = 0, 1, ... , n / 2 - 1
//	arg = 2 * PI / N;
//	treal = cos (arg);
//	timag = sin (arg);
//	wreal [0] = 1.0;
//	wimag [0] = 0.0;
//	for (j = 1; j < N / 2; j ++)
//	{
//		wreal [j] = wreal [j - 1] * treal - wimag [j - 1] * timag;
//		wimag [j] = wreal [j - 1] * timag + wimag [j - 1] * treal;
//	}
//
//	for (m = 2; m <= N; m *= 2)
//	{
//		for (k = 0; k < N; k += m)
//		{
//			for (j = 0; j < m / 2; j ++)
//			{
//				index1 = k + j;
//				index2 = index1 + m / 2;
//				t = N * j / m;    // 旋转因子 w 的实部在 wreal [] 中的下标为 t
//				treal = wreal [t] * Data_in[index2].real() - wimag [t] * Data_in[index2].imag();
//				timag = wreal [t] * Data_in[index2].imag() + wimag [t] * Data_in[index2].real();
//				ureal = Data_in[index1].real();
//				uimag = Data_in[index1].imag();
//				Data_in[index1].real(ureal + treal);
//				Data_in[index1].imag(uimag + timag);
//				Data_in[index2].real(ureal - treal);
//				Data_in[index2].imag(uimag - timag);
//			}
//		}
//	}
//
//	for (j=0; j < N; j ++)
//	{
//		Data_in[j]/=N;
//	}
//	delete[] wreal;
//	delete[] wimag;
//}
//
//void RS_encoder(vector<int> &dataIn, vector<int> &data_out, int Rate)
//{
//	int len = dataIn.size();
//	int pp_scrs[9] = { 1, 0, 1, 1, 1, 0, 0, 0, 1};// p(x)=1+x^2+x^3+x^4+x^8
//	int alpha_to_scrs [256] = {0};
//	int index_of_scrs [256] = {0};
//	int gg_scrs[17] = {0};
//	int recd_scrs [255] = {0};
//	int data_scrs [239] = {0};
//	int bb_scrs [16] = {0};
//	/*******************/
//	int i_rs;
//	int N;
//	int K;
//	int T;
//	int num;
//	int pad;
//
//	switch (Rate)
//	{
//	case 1:
//		{
//			N = 255;
//			K = 239;
//			T = 8;
//			break;
//		}
//		
//	case 2:
//		{
//			N = 224;
//			K = 216;
//			T = 4;
//			break;
//		}
//	case 3:
//		{
//			N = 56;
//			K = 48;
//			T = 4;
//			break;
//		}
//	case 4:
//		{
//			N = 52;
//			K = 44;
//			T = 4;
//			break;
//		}
//	default:
//		{
//			cout<<"Wrong rate_id!"; 
//			break;
//		}
//	}
//	/********************generate_gf()*****************************/
//	int i_gf, mask ;
//	mask = 1 ;
//	alpha_to_scrs[8] = 0 ;
//	for (i_gf=0; i_gf<8; i_gf++)
//	{ alpha_to_scrs[i_gf] = mask ;
//	index_of_scrs[alpha_to_scrs[i_gf]] = i_gf ;
//	if (pp_scrs[i_gf]!=0)
//		alpha_to_scrs[8] ^= mask ;
//	mask <<= 1 ;
//	}
//	index_of_scrs[alpha_to_scrs[8]] = 8 ;
//	mask >>= 1 ;
//	for (i_gf=9; i_gf<255; i_gf++)
//	{ if (alpha_to_scrs[i_gf-1] >= mask)
//	alpha_to_scrs[i_gf] = alpha_to_scrs[8] ^ ((alpha_to_scrs[i_gf-1]^mask)<<1) ;
//	else alpha_to_scrs[i_gf] = alpha_to_scrs[i_gf-1]<<1 ;
//	index_of_scrs[alpha_to_scrs[i_gf]] = i_gf ;
//	}
//	index_of_scrs[0] = -1;
//	/*********************gen_poly()****************************/
//	int i_po,j_po;
//	gg_scrs[0] = 2 ;    /* primitive element alpha = 2  for GF(2**mm)  */
//	gg_scrs[1] = 1 ;    /* g(x) = (X+alpha) initially */
//	for (i_po=2; i_po<=16; i_po++)
//	{ 
//		gg_scrs[i_po] = 1 ;
//	    for (j_po=i_po-1; j_po>0; j_po--)
//			if (gg_scrs[j_po] != 0)
//				gg_scrs[j_po] = gg_scrs[j_po-1]^ alpha_to_scrs[(index_of_scrs[gg_scrs[j_po]]+i_po)%255] ;
//			else 
//				gg_scrs[j_po] = gg_scrs[j_po-1] ;
//		gg_scrs[0] = alpha_to_scrs[(index_of_scrs[gg_scrs[0]]+i_po)%255] ;     /* gg[0] can never be zero */
//	}
//	/* convert gg[] to index form for quicker encoding */
//	for (i_po=0; i_po<=16; i_po++)
//		gg_scrs[i_po] = index_of_scrs[gg_scrs[i_po]] ;
//	/***********************************************************/
//	int len_de = len/8;
//	num = len/(8*K);//先假设正好整除
//	/*int* deData = new int[len_de];
//	for (i=0;i<len_de;i++)
//		deData[i]=0;*/
//	/*int* deDataOut = new int[N*num];
//	for (i=0;i<N*num;i++)
//		deDataOut[i]=0;*/
//	vector<int> deDataOut(N*num, 0);
//	/*int* dataOut = new int[N*num*8];
//	for (i=0;i<N*num*8;i++)
//		dataOut[i]=0;*/
//	vector<int> dataOut(N*num*8, 0);
//	pad = 239-K;
//	//binary to decimal,按8位切割，转成0~255的十进制数，共num个
//	vector<int> deData(dataIn.size()/8, 0);
//	bi2de_rs(dataIn, deData) ;//
//	for (int j = 0;j<num;j++)
//	{
//		//data 倒序输入encoder_rs
//		for (i_rs=0;i_rs<pad;i_rs++)
//			data_scrs[i_rs] = 0; 
//		for (i_rs=0;i_rs<K;i_rs++)
//			data_scrs[i_rs+pad] = deData[K-1-i_rs];
///************************encode_rs**************************************/
//	int i_ec, j_ec;
//	int feedback ;
//	for (i_ec=0; i_ec<16; i_ec++)
//		bb_scrs[i_ec] = 0 ;
//	for (i_ec=239-1; i_ec>=0; i_ec--)
//	{  
//		feedback = index_of_scrs[data_scrs[i_ec]^bb_scrs[15]] ;
//		if (feedback != -1)
//		{ 
//			for (j_ec=15; j_ec>0; j_ec--)
//				if (gg_scrs[j_ec] != -1)
//					bb_scrs[j_ec] = bb_scrs[j_ec-1]^alpha_to_scrs[(gg_scrs[j_ec]+feedback)%255] ;
//				else
//					bb_scrs[j_ec] = bb_scrs[j_ec-1] ;
//			bb_scrs[0] = alpha_to_scrs[(gg_scrs[0]+feedback)%255] ;
//		}
//		else
//		{ 
//			for (j_ec=15; j_ec>0; j_ec--)
//				bb_scrs[j_ec] = bb_scrs[j_ec-1] ;
//			bb_scrs[0] = 0 ;
//		}
//	}
///***********************************************************************/
//
//		//for (i_rs=0; i_rs<N-K; i_rs++)
//		//	recd_scrs[i_rs+K] = bb_scrs[N-K-1-i_rs];//倒序
//		//for (i_rs=0; i_rs<K; i_rs++)
//		//	recd_scrs[i_rs] = deData[K-1-i_rs];
//		for (i_rs=0; i_rs<N-K; i_rs++)
//			recd_scrs[i_rs+K] = bb_scrs[N-K-1-i_rs];//更改顺序
//		for (i_rs=0; i_rs<K; i_rs++)
//			recd_scrs[i_rs] = deData[i_rs];
//		for(i_rs=0;i_rs<N;i_rs++)
//			deDataOut[j*N+i_rs]=recd_scrs[i_rs];
//	}//end j
//	de2bi_rs(deDataOut,dataOut); 
//	for (int i = 0; i < N*num*8; ++i)
//		data_out.push_back(dataOut[i]);
//	/*delete deDataOut;
//	delete deData;
//	delete dataOut;*/
//}
//
//void RS_encoder_shortend(vector<int> &dataIn, vector<int> &data_out)
//{
//	int stuffbits_num = 239 * 8 - dataIn.size();
//	vector<int> rs_in_temp(dataIn);
//	vector<int> rs_out_temp;
//	for (int i = 0; i < stuffbits_num; ++i)
//		rs_in_temp.push_back(0);
//	RS_encoder(rs_in_temp, rs_out_temp, 1);
//	for (int i = 0; i < dataIn.size(); ++i)
//		data_out.push_back(rs_out_temp[i]);
//	for (int i = 0; i < 128; ++i)
//		data_out.push_back(rs_out_temp[239 * 8 + i]);
//}
//
//void bi2de_rs(vector<int> &biData, vector<int> &deData) 
//{  
//	int len = biData.size();
//	double a =2;
//	for(int j = 0;j<len/8;j++)
//	{
//		for(int i = 0; i <8; i++)  			
//			deData[j]+=biData[j*8+i]*pow(a,(7-i));//改为第一位是最高位
//	}
//}
//
//void de2bi_rs(vector<int> &deData, vector<int> &biData)
//{
//	int len = deData.size();
//	for(int j = 0;j<len;j++)
//	{
//		int de_temp = deData[j];
//		for(int i = 7; i >= 0; i--)  
//		{  
//			/*if(deData[j] & (1 << i))  		
//				biData[j*8+i]=1;		
//			else  
//				biData[j*8+i]=0;*/
//			biData[j * 8 + i] = de_temp % 2;//改为与化为十进制时的顺序相同
//			de_temp = de_temp / 2;
//		}
//	} 
//}
//
//void conencoder(vector<int> &codebits, vector<int> &bits_out, int rate)
//{
//	int Nbits = codebits.size();
//	vector<int> X_temp (Nbits, 0);
//	vector<int> Y_temp (Nbits, 0);
//	vector<int> Z_temp (Nbits, 0);
//	int reg_temp[6] = {0};//初始化6位基础器全零
//	for (int i = 0; i < Nbits; i++)
//	{
//
//		X_temp[i] = codebits[i] ^ reg_temp[1] ^ reg_temp[2] ^ reg_temp[4] ^ reg_temp[5];//生成多项式133o
//		Y_temp[i] = codebits[i] ^ reg_temp[0] ^ reg_temp[1] ^ reg_temp[2] ^ reg_temp[3] ^ reg_temp[5];//生成多项式171o
//		Z_temp[i] = codebits[i] ^ reg_temp[0] ^ reg_temp[1] ^ reg_temp[3] ^ reg_temp[5];//生成多项式165o
//		for(int j = 5; j > 0; j--)
//			reg_temp[j] = reg_temp[j - 1]; 
//		reg_temp[0] = codebits[i];//重置寄存器
//	}//得到卷积编码原始输出
//	switch (rate)
//	{
//	case 0:
//		{
//			for (int i = 0; i < Nbits; i++)
//			{
//				bits_out.push_back(X_temp[i]);
//				bits_out.push_back(Y_temp[i]);
//				bits_out.push_back(Z_temp[i]);
//			}//按协议排列信息
//			break;
//		}
//	case 1:
//		{
//			for (int i = 0; i < Nbits; i++)
//			{
//				bits_out.push_back(X_temp[i]);
//				bits_out.push_back(Y_temp[i]);
//			}//按协议排列信息
//			break;
//		}
//	case 2:
//		{
//			int test = Nbits % 4;
//			if (test == 0)
//			{
//				int Nblocks = Nbits / 4;
//				for (int i = 0; i < Nblocks; i++)
//				{
//					bits_out.push_back(X_temp[4 * i + 0]);
//					bits_out.push_back(Y_temp[4 * i + 0]);
//					bits_out.push_back(X_temp[4 * i + 1]);
//					bits_out.push_back(X_temp[4 * i + 2]);
//					bits_out.push_back(Y_temp[4 * i + 2]);
//					bits_out.push_back(X_temp[4 * i + 3]);
//					bits_out.push_back(Y_temp[4 * i + 3]);
//				}//按协议排列信息
//			}
//			else
//			{
//				cout << "比特数输入错误！" << endl;
//				exit(EXIT_FAILURE);
//			}
//			break;
//		}
//	case 3:
//		{
//			int test = Nbits % 2;
//			if (test == 0)
//			{
//				int Nblocks = Nbits / 4;
//				for (int i = 0; i < Nblocks; i++)
//				{
//					bits_out.push_back(X_temp[2 * i + 0]);
//					bits_out.push_back(Y_temp[2 * i + 0]);
//					bits_out.push_back(X_temp[2 * i + 1]);
//				}//按协议排列信息
//			}
//			else
//			{
//				cout << "比特数输入错误！" << endl;
//				exit(EXIT_FAILURE);
//			}
//			break;
//		}
//	case 4:
//		{
//			int test = Nbits % 4;
//			if (test == 0)
//			{
//				int Nblocks = Nbits / 4;
//				for (int i = 0; i < Nblocks; i++)
//				{
//					bits_out.push_back(X_temp[4 * i + 0]);
//					bits_out.push_back(Y_temp[4 * i + 0]);
//					bits_out.push_back(X_temp[4 * i + 1]);
//					bits_out.push_back(X_temp[4 * i + 2]);
//					bits_out.push_back(X_temp[4 * i + 3]);
//				}//按协议排列信息
//			}
//			else
//			{
//				cout << "比特数输入错误！" << endl;
//				exit(EXIT_FAILURE);
//			}
//			break;
//		}
//	default:
//		{
//			cout << "码率选择错误！" << endl;
//			exit(EXIT_FAILURE);
//			break;
//		}
//	}
//}
//
///**************************************SC-PHY模块****************************************/
//
//void SC_BPSK(vector<int> &codebits)
//{
//	int Nbits = codebits.size();
//	for(int i=0; i<Nbits; i++)
//		codebits[i] = codebits[i] * 2 - 1;
//}
//
//void SC_tx_modulation(vector<int> &codebits, vector<complex<double> > &symbols, int modtype)
//{
//	int Nbits = codebits.size();
//	int Nnums = Nbits/modtype;
//	vector<int> nums;//比特转化为数字，根据此数字在映射表中进行选择
//	bits2nums(codebits, nums, modtype);
//	int nums_temp;
//	switch (modtype)
//	{
//	case 1: 
//		{
//			complex<double> mod_temp[2] = {complex<double>(0,-1), complex<double>(0,1)};//映射表
//			for(int i = 0; i < Nnums; i++)
//				symbols.push_back(mod_temp[nums[i]]);
//			break;
//		}
//	case 2:
//		{
//			complex<double> mod_temp[4] = {complex<double>(0,-1), complex<double>(1,0),
//				                           complex<double>(-1,0), complex<double>(0,1)};//映射表
//			for(int i = 0; i < Nnums; i++)
//				symbols.push_back(mod_temp[nums[i]]);
//			break;
//		}
//	case 3:
//		{
//			complex<double> mod_temp[8] = {complex<double>(-cos(PI/4),-cos(PI/4)), complex<double>(-1,0), complex<double>(0,1), complex<double>(-cos(PI/4),+cos(PI/4)), 
//										   complex<double>(0,-1), complex<double>(+cos(PI/4),-cos(PI/4)), complex<double>(+cos(PI/4),+cos(PI/4)), complex<double>(1,0)};//映射表
//			for(int i = 0; i < Nnums; i++)
//				symbols.push_back(mod_temp[nums[i]]);
//			break;
//		}
//	case 4:
//		{
//			complex<double> mod_temp[16] = {complex<double>(-3/sqrt(10.0),-3/sqrt(10.0)), complex<double>(-3/sqrt(10.0),-1/sqrt(10.0)), complex<double>(-3/sqrt(10.0),+3/sqrt(10.0)), complex<double>(-3/sqrt(10.0),+1/sqrt(10.0)),
//				complex<double>(-1/sqrt(10.0),-3/sqrt(10.0)), complex<double>(-1/sqrt(10.0),-1/sqrt(10.0)), complex<double>(-1/sqrt(10.0),+3/sqrt(10.0)), complex<double>(-1/sqrt(10.0),+1/sqrt(10.0)),
//				complex<double>(+3/sqrt(10.0),-3/sqrt(10.0)), complex<double>(+3/sqrt(10.0),-1/sqrt(10.0)), complex<double>(+3/sqrt(10.0),+3/sqrt(10.0)), complex<double>(+3/sqrt(10.0),+1/sqrt(10.0)),
//				complex<double>(+1/sqrt(10.0),-3/sqrt(10.0)), complex<double>(+1/sqrt(10.0),-1/sqrt(10.0)), complex<double>(+1/sqrt(10.0),+3/sqrt(10.0)), complex<double>(+1/sqrt(10.0),+1/sqrt(10.0))};//映射表
//			for(int i = 0; i < Nnums; i++)
//				symbols.push_back(mod_temp[nums[i]]);
//			break;
//		}
//	default:
//		{
//			cout<<"调制模式输入错误！"<<endl;
//			exit(EXIT_FAILURE);
//		}
//	}
//}
//
//void SC_LFSR(vector<int> &prbs, int Nbits)
//{
//	//int* prbs_temp= new int[Nbits+15];
//	vector<int> prbs_temp ((Nbits + 15), 0);
//	int init_bits[15] = {1,1,1,1,1,0,0,0,0,0,0,1,0,1,0} ;//初始序列
//	for (int i = 0; i < 15; i++)
//		prbs_temp[i] = init_bits[i];
//	for (int i = 0; i < Nbits; i++)
//	{
//		prbs_temp[i+15] = prbs_temp[i] ^ prbs_temp[i+1];
//		prbs.push_back(prbs_temp[i+15]);
//	}
//}
//
//void SC_spreader(vector<int> &bits_input, vector<int> &sp_out, int sp_index)
//{
//	int nbits = bits_input.size();
//	int nbits_sp = sp_index * nbits;//扩频输出比特数；
//	switch (sp_index)
//	{
//	case 1:
//		for (int i = 0; i < bits_input.size(); ++i)
//			sp_out.push_back(bits_input[i]);
//		break;
//	case 2:
//		{
//			//int* prbs = new int [nbits_sp];
//			vector<int> prbs;
//			SC_LFSR(prbs, nbits_sp);//生成扩频所需的伪随机序列
//			for (int i = 0; i < nbits; i++)
//			{
//				for (int j = 0; j < 2; j++)
//					//sp_out[2*i+j] = bits_input[i]^prbs[2*i+j];
//					sp_out.push_back(bits_input[i]^prbs[2*i+j]);//扩频后填充到序列中
//			}
//			break;
//		}
//	case 4:
//		{
//			//int* prbs = new int [nbits_sp];
//			vector<int> prbs;
//			SC_LFSR(prbs, nbits_sp);//生成扩频所需的伪随机序列
//			for (int i = 0; i < nbits; i++)
//			{
//				for (int j = 0; j < 4; j++)
//					//sp_out[4*i+j] = bits_input[i]^prbs[4*i+j];
//					sp_out.push_back(bits_input[i]^prbs[4*i+j]);//扩频后填充到序列中
//			}
//			break;
//		}
//	case 6:
//		{
//			vector<int> prbs;
//			SC_LFSR(prbs, nbits_sp);//生成扩频所需的伪随机序列
//			for (int i = 0; i < nbits; i++)
//			{
//				for (int j = 0; j < 6; j++)
//					//sp_out[6*i+j] = bits_input[i]^prbs[6*i+j]
//					sp_out.push_back(bits_input[i]^prbs[6*i+j]);;//扩频后填充到序列中
//			}
//			break;
//		}
//	case 64:
//		{
//			vector<int> prbs;
//			SC_LFSR(prbs, nbits);//生成扩频所需的伪随机序列,根据此序列选择格雷序列a/b进行扩频
//			int a_golay_hex[16] = {0x6,0x3,0xA,0xF,0x0,0x5,0xC,0x9,0x6,0x3,0x5,0x0,0x0,0x5,0x3,0x6};
//			int b_golay_hex[16] = {0x6,0xC,0xA,0x0,0x0,0xA,0xC,0x6,0x6,0xC,0x5,0xF,0x0,0xA,0x3,0x9};
//			//int* a_golay_bit = new int [16*4];
//			//int* b_golay_bit = new int [16*4];
//			vector<int> a_golay_bit;
//			vector<int> b_golay_bit;
//			hex2binary(a_golay_hex, a_golay_bit, 16);
//			hex2binary(b_golay_hex, b_golay_bit, 16);
//			for (int i = 0; i < nbits; i++)
//			{
//				if (prbs[i] == 1)
//				{
//					for (int j = 0; j <64; j++)
//						//sp_out[64*i+j] = bits_input[i]^a_golay_bit[j];
//						sp_out.push_back(bits_input[i] ^ a_golay_bit[j]);
//				}
//				else
//				{
//					for (int j = 0; j <64; j++)
//						//sp_out[64*i+j] = bits_input[i]^b_golay_bit[j];
//						sp_out.push_back(bits_input[i] ^ b_golay_bit[j]);
//				}
//			}
//			break;
//		}
//	default:
//		cout<<"扩频因子输入错误"<<endl;
//		exit(EXIT_FAILURE);
//		break;
//	}
//}
//
//void SC_subbuilder(vector<complex<double> > &symin, vector<complex<double>> &symout, int sub_mod)
//{
//	int Lsymin = symin.size();
//	switch (sub_mod)
//	{
//	case 0:
//		{
//			for (int i=0;i<Lsymin;i++)
//			{
//				symout.push_back(symin[i]);	
//			}
//			break;
//		}
//	case 8:
//		{
//			int a_golay_hex[2]={0xE,0xB};
//			int b_golay_hex[2]={0xD,0x8};
//			vector<int> a_golay_bits;
//			vector<int> b_golay_bits;
//			vector<int> a_golay_bits_N (8, 0);
//			vector<int> b_golay_bits_N (8, 0);
//			vector<complex<double> > a_golay_sym;
//			vector<complex<double> > b_golay_sym;
//			vector<complex<double> > a_golay_sym_N;
//			vector<complex<double> > b_golay_sym_N;
//			hex2binary(a_golay_hex,a_golay_bits,2);
//			hex2binary(b_golay_hex,b_golay_bits,2);//子块前插入的导频
//			for (int i=0;i<8;i++)
//				a_golay_bits_N[i]=floor((2-(a_golay_bits[i]*1.0))/2);
//			for (int i=0;i<8;i++)
//				b_golay_bits_N[i]=floor((2-(b_golay_bits[i]*1.0))/2);//极性相反的格雷序列
//			SC_tx_modulation(a_golay_bits,a_golay_sym,1);
//			SC_tx_modulation(b_golay_bits,b_golay_sym,1);
//			SC_tx_modulation(a_golay_bits_N,a_golay_sym_N,1);
//			SC_tx_modulation(b_golay_bits_N,b_golay_sym_N,1);//插入的导频进行π/2 BPSK调制
//			int Nblocks=ceil(Lsymin*1.0/(448*64));//每个数据块包含64个数据子块，其中每个子块的数据长度为448，导频长度为8
//			if (Nblocks==1)
//			{
//				for (int i=1;i<Lsymin;i++)
//					symout.push_back(symin[i]);
//				//Lsymout=Lsymin;
//			}
//			else
//			{
//				//Lsymout=(Nblocks-1)*(64*64+8)+Lsymin;//输出符号数
//				int Nlfsr=Nblocks-1;
//				int Lblock=64*512+8;//每个数据块长度
//				vector<int> S_lfsr;
//				SC_LFSR(S_lfsr,Nlfsr);
//				int LLblock=Lsymin-(Nblocks-1)*448*64;//最后一个数据块符号数
//				for (int i=0;i<(Nblocks-1);i++)
//				{
//					if ((i%2)==0)
//					{
//						if (S_lfsr[i]==0)//根据线性寄存器输出选择导频极性
//						{
//							for (int j=0;j<512;j++)
//							{
//								for (int k=0;k<8;k++)
//								{
//									symout.push_back(a_golay_sym[k]);
//								}
//								for (int l=0;l<56;l++)
//								{
//									symout.push_back(symin[448*64*i+56*j+l]);
//								}
//							}
//							for (int m=0;m<8;m++)
//							{
//								symout.push_back(a_golay_sym[m]);
//							}
//						}
//						else
//						{
//							for (int j=0;j<512;j++)
//							{
//								for (int k=0;k<8;k++)
//								{
//									symout.push_back(a_golay_sym_N[k]);
//								}
//								for (int l=0;l<56;l++)
//								{
//									symout.push_back(symin[448*64*i+56*j+l]);
//								}
//							}
//							for (int m=0;m<8;m++)
//							{
//								symout.push_back(a_golay_sym_N[m]);
//							}
//						}
//					}
//					else
//					{
//						if (S_lfsr[i]==0)//根据线性寄存器输出选择导频极性
//						{
//							for (int j=0;j<512;j++)
//							{
//								for (int k=0;k<8;k++)
//								{
//									symout.push_back(b_golay_sym[k]);
//								}
//								for (int l=0;l<56;l++)
//								{
//									symout.push_back(symin[448*64*i+56*j+l]);
//								}
//							}
//							for (int m=0;m<8;m++)
//							{
//								symout.push_back(b_golay_sym[m]);
//							}
//						}
//						else
//						{
//							for (int j=0;j<512;j++)
//							{
//								for (int k=0;k<8;k++)
//								{
//									symout.push_back(b_golay_sym_N[k]);
//								}
//								for (int l=0;l<56;l++)
//								{
//									symout.push_back(symin[448*64*i+56*j+l]);
//								}
//							}
//							for (int m=0;m<8;m++)
//							{
//								symout.push_back(b_golay_sym_N[m]);
//							}
//						}
//					}
//				}
//				for (int ii=0;ii<LLblock;ii++)//最后一个数据块不需要插入导频
//				{
//					symout.push_back(symin[(Nblocks-1)*448*64+ii]);
//				}
//			}
//			break;
//		}
//	case 64:
//		{
//			int a_golay_hex[16]={0x6,0x3,0xA,0xF,0x0,0x5,0xC,0x9,0x6,0x3,0x5,0x0,0x0,0x5,0x3,0x6};
//			int b_golay_hex[16]={0x6,0xC,0xA,0x0,0x0,0xA,0xC,0x6,0x6,0xC,0x5,0xF,0x0,0xA,0x3,0x9};
//			vector<int> a_golay_bits;
//			vector<int> b_golay_bits;
//			vector<int> a_golay_bits_N (64, 0);
//			vector<int> b_golay_bits_N (64, 0);
//			vector<complex<double> > a_golay_sym;
//			vector<complex<double> > b_golay_sym;
//			vector<complex<double> > a_golay_sym_N;
//			vector<complex<double> > b_golay_sym_N;
//			hex2binary(a_golay_hex,a_golay_bits,16);
//			hex2binary(b_golay_hex,b_golay_bits,16);//子块前插入的导频
//			for (int i=0;i<64;i++)
//				a_golay_bits_N[i]=floor((2-(a_golay_bits[i]*1.0))/2);
//			for (int i=0;i<64;i++)
//				b_golay_bits_N[i]=floor((2-(b_golay_bits[i]*1.0))/2);//极性相反的格雷序列
//			SC_tx_modulation(a_golay_bits,a_golay_sym,1);
//			SC_tx_modulation(b_golay_bits,b_golay_sym,1);
//			SC_tx_modulation(a_golay_bits_N,a_golay_sym_N,1);
//			SC_tx_modulation(b_golay_bits_N,b_golay_sym_N,1);//插入的导频进行π/2 BPSK调制
//			int Nblocks=ceil(Lsymin*1.0/(448*64));//每个数据块包含64个数据子块，其中每个子块的数据长度为448，导频长度为64
//			if (Nblocks==1)
//			{
//				for (int i=1;i<Lsymin;i++)
//					symout.push_back(symin[i]);
//			}
//			else
//			{
//				int LLblock=Lsymin-(Nblocks-1)*448*64;//最后一个数据块符号数
//				int Nlfsr=Nblocks-1;
//				int Lblock=64*512+64;//每个数据块长度
//				vector<int> S_lfsr;
//				SC_LFSR(S_lfsr,Nlfsr);
//				for (int i=0;i<(Nblocks-1);i++)
//				{
//					if ((i%2)==0)//根据极性选择导频a、b
//					{
//						if (S_lfsr[i]==0)//根据线性寄存器输出选择导频极性
//						{
//							for (int j=0;j<64;j++)
//							{
//								for (int k=0;k<64;k++)
//								{
//									symout.push_back(a_golay_sym[k]);
//								}
//								for (int l=0;l<448;l++)
//								{
//									symout.push_back(symin[448*64*i+448*j+l]);
//								}
//							}
//							for (int m=0;m<64;m++)
//							{
//								symout.push_back(a_golay_sym[m]);
//							}
//						}
//						else
//						{
//							for (int j=0;j<64;j++)
//							{
//								for (int k=0;k<64;k++)
//								{
//									symout.push_back(a_golay_sym_N[k]);
//								}
//								for (int l=0;l<448;l++)
//								{
//									symout.push_back(symin[448*64*i+448*j+l]);
//								}
//							}
//							for (int m=0;m<64;m++)
//							{
//								symout.push_back(a_golay_sym_N[m]);
//							}
//						}
//					}
//					else
//					{
//						if (S_lfsr[i]==0)//根据线性寄存器输出选择导频极性
//						{
//							for (int j=0;j<64;j++)
//							{
//								for (int k=0;k<64;k++)
//								{
//									symout.push_back(b_golay_sym[k]);
//								}
//								for (int l=0;l<448;l++)
//								{
//									symout.push_back(symin[448*64*i+448*j+l]);
//								}
//							}
//							for (int m=0;m<64;m++)
//							{
//								symout.push_back(b_golay_sym[m]);
//							}
//						}
//						else
//						{
//							for (int j=0;j<64;j++)
//							{
//								for (int k=0;k<64;k++)
//								{
//									symout.push_back(b_golay_sym_N[k]);
//								}
//								for (int l=0;l<448;l++)
//								{
//									symout.push_back(symin[448*64*i+448*j+l]);
//								}
//							}
//							for (int m=0;m<64;m++)
//							{
//								symout[Lblock*i+64*512+m]=b_golay_sym_N[m];
//							}
//						}
//					}
//				}
//				for (int ii=0;ii<LLblock;ii++)//最后一个数据块不需要插入导频
//				{
//					symout.push_back(symin[(Nblocks-1)*448*64+ii]);
//				}
//			}
//			break;
//		}
//	default:
//		{
//			cout<<"划分子块输入模式错误"<<endl;
//			exit(EXIT_FAILURE);
//			break;
//		}
//	}
//}
//
//void SC_PCESinserter(vector<complex<double> > &symin, vector<complex<double> > &symout, int PCES_mod, int sub_mod)
//{
//	if (PCES_mod == 0)
//	{
//		//Nsymout = Nsymin;
//		int Nsymin = symin.size();
//		for (int i = 0; i < Nsymin; i++)
//			symout.push_back(symin[i]);
//	}
//	else
//	{
//		int a_golay_hex_32[32] = {0x0,0x5,0x3,0x6,0x6,0x3,0x5,0x0,0x0,0x5,0xC,0x9,0x6,0x3,0xA,0xF
//			,0xF,0xA,0xC,0x9,0x9,0xC,0xA,0xF,0x0,0x5,0xC,0x9,0x6,0x3,0xA,0xF};
//		int b_golay_hex_32[32] = {0x0,0xA,0x3,0x9,0x6,0xC,0x5,0xF,0x0,0xA,0xC,0x6,0x6,0xC,0xA,0x0
//			,0xF,0x5,0xC,0x6,0x9,0x3,0xA,0x0,0x0,0xA,0xC,0x6,0x6,0xC,0xA,0x0};
//		vector<int> a_golay_binary_128;
//		vector<int> b_golay_binary_128;
//		vector<int> b_golay_binary_128_N (128, 0);
//		hex2binary(a_golay_hex_32, a_golay_binary_128,32);
//		hex2binary(b_golay_hex_32, b_golay_binary_128,32);
//		for (int i = 0; i < 128; i++)
//			b_golay_binary_128_N[i]=floor((2-(b_golay_binary_128[i]*1.0))/2);
//		vector<int> a_golay_binary_256 (256, 0);
//		for (int i = 0; i < 128; i++)
//			a_golay_binary_256[i] = a_golay_binary_128[i];
//		for (int i = 0; i < 128; i++)
//			a_golay_binary_256[i+128] = b_golay_binary_128[i];
//		vector<int> b_golay_binary_256 (256, 0);
//		for (int i = 0; i < 128; i++)
//			b_golay_binary_256[i] = a_golay_binary_128[i];
//		for (int i = 0; i < 128; i++)
//			b_golay_binary_256[i + 128] = b_golay_binary_128_N[i];
//		vector<int> PCES_bits (1152, 0);//插入的信道估计序列：a256 b256 a256 b256 b128
//		for (int i = 0; i < 256; i++)
//			PCES_bits[i] = a_golay_binary_256[i];
//		for (int i = 0; i < 256; i++)
//			PCES_bits[i+256] = b_golay_binary_256[i];
//		for (int i = 0; i < 256; i++)
//			PCES_bits[i+512] = a_golay_binary_256[i];
//		for (int i = 0; i < 256; i++)
//			PCES_bits[i+768] = b_golay_binary_256[i];
//		for (int i = 0; i < 128; i++)
//			PCES_bits[i+1024] = b_golay_binary_128[i];
//		//complex<double> PCES_syms = new complex<double>[1152];
//		vector<complex<double> > PCES_syms;
//		SC_tx_modulation(PCES_bits, PCES_syms, 1);//对插入的导频进行π/2 BPSK调制
//		switch (sub_mod)
//		{
//		case 0:
//			{
//				int Nsymin = symin.size();
//				int Nblocklength = 448 * 64;//每个数据块的长度
//				int Nblocks = ceil((Nsymin * 1.0) / (Nblocklength * 1.0));//数据块数目
//				if (Nblocks == 1)
//				{
//					//Nsymout = Nsymin;
//					for (int i = 0; i < Nsymin; i++)
//						symout.push_back(symin[i]);
//				}
//				else
//				{
//					//Nsymout = Nsymin + (Nblocks - 1) * 1152;
//					int N_lblock = Nsymin - (Nblocks - 1) * (Nblocklength);//最后一个数据块符号数
//					for (int i = 0; i < (Nblocks - 1); i++)
//					{
//						for (int j = 0; j < Nblocklength; j++)
//							symout.push_back(symin[(Nblocklength) * i + j]);
//						for (int k = 0; k < 1152; k++)
//							symout.push_back(PCES_syms[k]);
//					}
//					for (int ii = 0; ii < N_lblock; ii++)
//						symout.push_back(symin[(Nblocklength) * (Nblocks - 1)]);//填充数据与信道估计插入
//				}
//				break;
//			}
//		case 8:
//			{
//				int Nsymin = symin.size();
//				int Nblocklength = 512 * 64 + 8;//每个数据块的长度
//				int Nblocks = ceil((Nsymin * 1.0) / (Nblocklength * 1.0));//数据块数目
//				if (Nblocks == 1)
//				{
//					//Nsymout = Nsymin;
//					for (int i = 0; i < Nsymin; i++)
//						symout.push_back(symin[i]);
//				}
//				else
//				{
//					//Nsymout = Nsymin + (Nblocks - 1) * 1152;
//					int N_lblock = Nsymin - (Nblocks - 1) * (Nblocklength);//最后一个数据块符号数
//					for (int i = 0; i < (Nblocks - 1); i++)
//					{
//						for (int j = 0; j < Nblocklength; j++)
//							symout.push_back(symin[(Nblocklength) * i + j]);
//						for (int k = 0; k < 1152; k++)
//							symout.push_back(PCES_syms[k]);
//					}
//					for (int ii = 0; ii < N_lblock; ii++)
//						symout.push_back(symin[(Nblocklength) * (Nblocks - 1)]);//填充数据与信道估计插入
//				}
//				break;
//			}
//		case 64:
//			{
//				int Nsymin = symin.size();
//				int Nblocklength = 512 * 64 + 64;//每个数据块的长度
//				int Nblocks = ceil((Nsymin * 1.0) / (Nblocklength * 1.0));//数据块数目
//				if (Nblocks == 1)
//				{
//					//Nsymout = Nsymin;
//					for (int i = 0; i < Nsymin; i++)
//						symout.push_back(symin[i]);
//				}
//				else
//				{
//					//Nsymout = Nsymin + (Nblocks - 1) * 1152;
//					int N_lblock = Nsymin - (Nblocks - 1) * (Nblocklength);//最后一个数据块符号数
//					for (int i = 0; i < (Nblocks - 1); i++)
//					{
//						for (int j = 0; j < Nblocklength; j++)
//							symout.push_back(symin[(Nblocklength) * i + j]);
//						for (int k = 0; k < 1152; k++)
//							symout.push_back(PCES_syms[k]);
//					}
//					for (int ii = 0; ii < N_lblock; ii++)
//						symout.push_back(symin[(Nblocklength) * (Nblocks - 1)]);//填充数据与信道估计插入
//				}
//				break;
//			}
//		default:
//			{
//				cout << "子块分割模式选择错误！！！！" << endl;
//				exit(EXIT_FAILURE);
//				break;
//			}
//		}
//	}
//}
//
//void SC_genPreamble(vector<complex<double> > &vSC_Pre, int Pre_mod)
//{
//	int a_golay_hex_32[32] = {0x0,0x5,0x3,0x6,0x6,0x3,0x5,0x0,0x0,0x5,0xC,0x9,0x6,0x3,0xA,0xF,
//		0xF,0xA,0xC,0x9,0x9,0xC,0xA,0xF,0x0,0x5,0xC,0x9,0x6,0x3,0xA,0xF};
//	int b_golay_hex_32[32] = {0x0,0xA,0x3,0x9,0x6,0xC,0x5,0xF,0x0,0xA,0xC,0x6,0x6,0xC,0xA,0x0,
//		0xF,0x5,0xC,0x6,0x9,0x3,0xA,0x0,0x0,0xA,0xC,0x6,0x6,0xC,0xA,0x0};
//	vector<int> a_golay_binary_128;
//	hex2binary(a_golay_hex_32, a_golay_binary_128, 32);//a128
//	vector<int> b_golay_binary_128;
//	hex2binary(b_golay_hex_32, b_golay_binary_128, 32);//b128
//	vector<int> a_golay_binary_128_N (128, 0);
//	for (int i = 0; i < 128; i++)
//		a_golay_binary_128_N[i]=floor((2-(a_golay_binary_128[i]*1.0))/2);//a128补码
//	vector<int> b_golay_binary_128_N (128, 0);
//	for (int i = 0; i < 128; i++)
//		b_golay_binary_128_N[i]=floor((2-(b_golay_binary_128[i]*1.0))/2);//b128补码
//	vector<int> a_golay_binary_256;
//	for (int i = 0; i < 128; i++)
//		a_golay_binary_256.push_back(a_golay_binary_128[i]);
//	for (int i = 0; i < 128; i++)
//		a_golay_binary_256.push_back(a_golay_binary_128_N[i]);
//	vector<int> b_golay_binary_256;
//	for (int i = 0; i < 128; i++)
//		b_golay_binary_256.push_back(b_golay_binary_128[i]);
//	for (int i = 0; i < 128; i++)
//		b_golay_binary_256.push_back(b_golay_binary_128_N[i]);//b256
//	switch (Pre_mod)
//	{
//	case 0:
//		{
//			int Lpreb = 48 * 128 + 7 * 128 + (5 * 256);//前导长度
//			vector<int> sync;//前导sync部分
//			for (int i = 0; i < 48; i++)
//			{
//				for (int j = 0; j < 128; j++)
//					sync.push_back(b_golay_binary_128[i]);
//			}
//			vector<int> sfd;//前导sfd部分
//			int seed[7] = {1, -1, 1, 1, -1, -1, -1};
//			for (int i = 0; i < 7; i++)
//			{
//				if (seed[i] == 1)
//				{
//					for (int j = 0; j < 128; j++)
//						sfd.push_back(b_golay_binary_128[j]);
//				}
//				else
//				{
//					for (int j = 0; j < 128; j++)
//						sfd.push_back(b_golay_binary_128_N[j]);
//				}
//			}
//			vector<int> ces;//前导ces部分
//			for (int i = 0; i < 128; i++)
//				ces.push_back(a_golay_binary_128[i]);
//			for (int i = 0; i < 256; i++)
//				ces.push_back(a_golay_binary_256[i]);
//			for (int i = 0; i < 256; i++)
//				ces.push_back(b_golay_binary_256[i]);
//			for (int i = 0; i < 256; i++)
//				ces.push_back(a_golay_binary_256[i]);
//			for (int i = 0; i < 256; i++)
//				ces.push_back(b_golay_binary_256[i]);
//			for (int i = 0; i < 128; i++)
//				ces.push_back(b_golay_binary_128[i]);
//			vector<int> Preamble;//Preamble
//			for (int i = 0; i < sync.size(); i++)
//				Preamble.push_back(sync[i]);
//			for (int i = 0; i < sfd.size(); i++)
//				Preamble.push_back(sfd[i]);
//			for (int i = 0; i < ces.size(); i++)
//				Preamble.push_back(ces[i]);
//			SC_tx_modulation(Preamble, vSC_Pre, 1);//对preamble进行调制
//			break;
//		}
//	case 1:
//		{
//			int Lpreb = 14 * 128 + 4 * 128 + (4 * 256 + 128);//前导长度
//			vector<int> sync;//前导sync部分
//			for (int i = 0; i < 14; i++)
//			{
//				for (int j = 0; j < 128; j++)
//					sync.push_back(a_golay_binary_128[i]);
//			}
//			vector<int> sfd;//前导sfd部分
//			int seed[4] = {1, -1, 1, -1};
//			for (int i = 0; i < 4; i++)
//			{
//				if (seed[i] == 1)
//				{
//					for (int j = 0; j < 128; j++)
//						sfd.push_back(a_golay_binary_128[j]);
//				}
//				else
//				{
//					for (int j = 0; j < 128; j++)
//						sfd.push_back(a_golay_binary_128_N[j]);
//				}
//			}
//			vector<int> ces;//前导ces部分
//			for (int i = 0; i < 256; i++)
//				ces.push_back(a_golay_binary_256[i]);
//			for (int i = 0; i < 256; i++)
//				ces.push_back(b_golay_binary_256[i]);
//			for (int i = 0; i < 256; i++)
//				ces.push_back(a_golay_binary_256[i]);
//			for (int i = 0; i < 256; i++)
//				ces.push_back(b_golay_binary_256[i]);
//			for (int i = 0; i < 128; i++)
//				ces.push_back(b_golay_binary_128[i]);
//			vector<int> Preamble;//Preamble
//			for (int i = 0; i < sync.size(); i++)
//				Preamble.push_back(sync[i]);
//			for (int i = 0; i < sfd.size(); i++)
//				Preamble.push_back(sfd[i]);
//			for (int i = 0; i < ces.size(); i++)
//				Preamble.push_back(ces[i]);
//			SC_tx_modulation(Preamble, vSC_Pre, 1);//对preamble进行调制
//			break;
//		}
//	case 2:
//		{
//			int Lpreb = 14 * 128 + 4 * 128 + (4 * 256 + 128);//前导长度
//			vector<int> sync;//前导sync部分
//			for (int i = 0; i < 14; i++)
//			{
//				for (int j = 0; j < 128; j++)
//					sync.push_back(a_golay_binary_128[i]);
//			}
//			vector<int> sfd;//前导sfd部分
//			int seed[4] = {1, 1, -1, -1};
//			for (int i = 0; i < 4; i++)
//			{
//				if (seed[i] == 1)
//				{
//					for (int j = 0; j < 128; j++)
//						sfd.push_back(a_golay_binary_128[j]);
//				}
//				else
//				{
//					for (int j = 0; j < 128; j++)
//						sfd.push_back(a_golay_binary_128_N[j]);
//				}
//			}
//			vector<int> ces;//前导ces部分
//			for (int i = 0; i < 256; i++)
//				ces.push_back(a_golay_binary_256[i]);
//			for (int i = 0; i < 256; i++)
//				ces.push_back(b_golay_binary_256[i]);
//			for (int i = 0; i < 256; i++)
//				ces.push_back(a_golay_binary_256[i]);
//			for (int i = 0; i < 256; i++)
//				ces.push_back(b_golay_binary_256[i]);
//			for (int i = 0; i < 128; i++)
//				ces.push_back(b_golay_binary_128[i]);
//			vector<int> Preamble;//Preamble
//			for (int i = 0; i < sync.size(); i++)
//				Preamble.push_back(sync[i]);
//			for (int i = 0; i < sfd.size(); i++)
//				Preamble.push_back(sfd[i]);
//			for (int i = 0; i < ces.size(); i++)
//				Preamble.push_back(ces[i]);
//			SC_tx_modulation(Preamble, vSC_Pre, 1);//对preamble进行调制
//			break;
//		}
//	default:
//		{
//			cout << "前导模式错误！！" << endl;
//			break;
//		}
//	}
//}
//
//void SC_FECencoder(vector<int> &bitsin, vector<int> &bitsout, int fectype, int rate)
//{
//	int Nbits = bitsin.size();
//	switch (fectype)
//	{
//	case 0:
//		{
//			rate = 1;
//			RS_encoder(bitsin, bitsout, rate);
//			break;
//		}
//	case 1:
//		{
//			HSI_LDPCencoder(bitsin, bitsout, rate);
//			break;
//		}
//	default:
//		{
//			cout << "前向编码模式选择错误！！！" << endl;
//			exit(EXIT_FAILURE);
//			break;
//		}
//	}
//}
//
//void genSC(vector<int> &datain, vector<int> &macheader, vector<complex<double> > &dataout, SC_param SC_p)
//{
//	int ssid = 0;
//	for(int i = 0; i < SC_p.Nfram; i++)
//	{
//		int Lpreb;
//		switch (SC_p.pretype)
//		{
//		case 0:
//			Lpreb = 8320;
//		case 1:
//			Lpreb = 3456;
//		case 2:
//			Lpreb = 3456;
//		}
//		vector<complex<double> > SC_preb;
//		SC_genPreamble(SC_preb, SC_p.pretype);
//		for (int j = 0; j < SC_preb.size(); j++)
//			dataout.push_back(SC_preb[j]);//填充Preamble
//		/******************************构造macheader*******************************/
//		vector<int> PH (40, 0);//PHY信息位，共40比特
//		ssid = ssid % 16;
//		int temp_ssid = ssid;
//		int SSID[] = {0, 0, 0, 0};
//		for (int j = 0; j < 4; j++)//计算SSID
//		{
//			SSID[3 -j] = temp_ssid % 2;
//			temp_ssid = temp_ssid /2;
//		}
//		for (int j = 0; j < 4;j++)
//			PH[j] = SSID[j];//插入SSID
//		PH[4] = SC_p.Agr;//插入aggragation
//		PH[5] = SC_p.UEP;//插入UEP
//		int temp_mcs = SC_p.MCS;
//		for (int j = 0; j < 5; j++)//插入MCS信息
//		{
//			PH[10 - j] = temp_mcs % 2;
//			temp_mcs = temp_mcs / 2;
//		}
//		int temp_Lfram = SC_p.L_mb;
//		for (int j = 0; j < 20; j++)//插入Frame Length，20bits
//		{
//			PH[30 - j] = temp_Lfram % 2;
//			temp_Lfram = temp_Lfram / 2;
//		}
//		PH[31] = 0;
//		PH[32] = SC_p.pretype;//插入Preamble type
//		PH[33] = SC_p.Bt;//插入Beam tracking
//		PH[34] = SC_p.Llat;//插入Low-latency Mode
//		int temp_pw = SC_p.L_pw;
//		for (int j = 0; j < 2; j++)//插入2bits pilot word
//		{
//			PH[36 - j] = temp_mcs % 2;
//			temp_pw = temp_pw / 2;
//		}
//		PH[37] = SC_p.PCES;//插入PCES
//		for (int j = 0; j < 2; j++)
//			PH[38 + j] = SC_p.Rsv[j];//插入reserved bits
//		vector<int> temp_HCS;//存储16位HCS校验位
//		vector<int> gen_HCS;
//		for (int j = 0; j < PH.size(); ++j)
//			gen_HCS.push_back(PH[j]);
//		for (int j = 0; j < macheader.size(); j++)
//			gen_HCS.push_back(macheader[j]);
//		HCS_encoder(gen_HCS, temp_HCS);//计算HCS
//		vector<int> temp_scram_mh;//macheader进行扰码
//		for (int j = 0; j < macheader.size(); j++)
//			temp_scram_mh.push_back(macheader[j]);
//		for (int j = 0; j < temp_HCS.size(); j++)
//			temp_scram_mh.push_back(temp_HCS[j]);
//		scrambler(temp_scram_mh, SSID);//对macheader+HCS进行扰码
//		//int Nstuff_MH = 239 * 8 - temp_scram_mh.size() - PH.size();//填充比特数
//		//vector<int> RSbits_MH (239 * 8, 0);//RS输入
//		//vector<int> genRS_MH;//RS输出
//		//for (int j = 0; j < PH.size(); ++j)
//		//	RSbits_MH[j] = PH[j];
//		//for (int j = 0; j < temp_scram_mh.size(); ++j)
//		//	RSbits_MH[PH.size() + j] = temp_scram_mh[j];
//		//for (int j = 0; j < Nstuff_MH; j++)
//		//	RSbits_MH[temp_scram_mh.size() + PH.size() + j] = 0;
//		//RS_encoder(RSbits_MH, genRS_MH, 1);
//		vector<int> RSbits_MH;//RS输入
//		vector<int> genRS_MH;//RS输出
//		for (int j = 0; j < PH.size(); ++j)
//			RSbits_MH.push_back(PH[j]);
//		for (int j = 0; j < temp_scram_mh.size(); ++j)
//			RSbits_MH.push_back(temp_scram_mh[j]);
//		RS_encoder_shortend(RSbits_MH, genRS_MH);
//		//int Nbdata_MH = PH.size() + temp_scram_mh.size() + 128;//macheader比特数
//		//vector<int> databits_MH;//添加RS编码后的macheader
//		//for (int j = 0; j < PH.size() + temp_scram_mh.size(); ++j)
//		//	databits_MH.push_back(genRS_MH[j]);
//		//for (int j = 0; j < 128; j++)
//		//	databits_MH.push_back(genRS_MH[239 * 8 + j]);
//		vector<int> databits_MH_sp;
//		SC_spreader(genRS_MH, databits_MH_sp, 64);//扩频
//		vector<complex<double> > vdatabits_MH_mod;
//		SC_tx_modulation(databits_MH_sp, vdatabits_MH_mod, 1);
//		for (int j = 0; j < vdatabits_MH_mod.size(); ++j)
//			dataout.push_back(vdatabits_MH_mod[j]);//插入macheader
//		/************************macbody**********************************************/
//		scrambler(datain, SSID);//扰码
//		vector<int> PLdata_FEC;
//		SC_FECencoder(datain, PLdata_FEC, SC_p.FECtype, SC_p.FECrate);//前向编码
//		vector<int> PLdata_sp;
//		SC_spreader(PLdata_FEC, PLdata_sp, SC_p.sp);//扩频
//		vector<complex<double> > vPLdata_mod;
//		SC_tx_modulation(PLdata_sp, vPLdata_mod, SC_p.modtyoe);//调制映射
//		vector<complex<double> > vSub_temp;
//		SC_subbuilder(vPLdata_mod, vSub_temp, SC_p.subtype);//子块分割
//		vector<complex<double> > vPCES_temp;
//		SC_PCESinserter(vSub_temp, vPCES_temp, SC_p.PCES, SC_p.subtype);
//		for (int j = 0; j < vPCES_temp.size(); j++)
//			dataout.push_back(vPCES_temp[j]);
//		ssid++;//SSID每帧加一
//	}
//}
//
///**************************************HSI-PHY模块*****************************************/
//
//void HSI_genPreamble(vector<complex<double> > &vHSI_Pre, int Pre_mod)
//{
//	int a_golay_hex_32[32] = {0x0,0x5,0x3,0x6,0x6,0x3,0x5,0x0,0x0,0x5,0xC,0x9,0x6,0x3,0xA,0xF,
//		0xF,0xA,0xC,0x9,0x9,0xC,0xA,0xF,0x0,0x5,0xC,0x9,0x6,0x3,0xA,0xF};
//	int b_golay_hex_32[32] = {0x0,0xA,0x3,0x9,0x6,0xC,0x5,0xF,0x0,0xA,0xC,0x6,0x6,0xC,0xA,0x0,
//		0xF,0x5,0xC,0x6,0x9,0x3,0xA,0x0,0x0,0xA,0xC,0x6,0x6,0xC,0xA,0x0};
//	vector<int> a_golay_binary_128;
//	hex2binary(a_golay_hex_32, a_golay_binary_128, 32);//a128
//	vector<int> b_golay_binary_128;
//	hex2binary(b_golay_hex_32, b_golay_binary_128, 32);//b128
//	vector<int> a_golay_binary_128_N (128, 0);
//	for (int i = 0; i < 128; i++)
//		a_golay_binary_128_N[i]=floor((2-(a_golay_binary_128[i]*1.0))/2);//a128补码
//	vector<int> b_golay_binary_128_N (128, 0);
//	for (int i = 0; i < 128; i++)
//		b_golay_binary_128_N[i]=floor((2-(b_golay_binary_128[i]*1.0))/2);//b128补码
//	vector<int> a_golay_binary_256;
//	for (int i = 0; i < 128; i++)
//		a_golay_binary_256.push_back(a_golay_binary_128[i]);
//	for (int i = 0; i < 128; i++)
//		a_golay_binary_256.push_back(a_golay_binary_128_N[i]);
//	vector<int> b_golay_binary_256;
//	for (int i = 0; i < 128; i++)
//		b_golay_binary_256.push_back(b_golay_binary_128[i]);
//	for (int i = 0; i < 128; i++)
//		b_golay_binary_256.push_back(b_golay_binary_128_N[i]);//b256
//	switch (Pre_mod)
//	{
//	case 0:
//		{
//			int Lpreb = 48 * 128 + 7 * 128 + (5 * 256);//前导长度
//			vector<int> sync;//前导sync部分
//			for (int i = 0; i < 48; i++)
//			{
//				for (int j = 0; j < 128; j++)
//					sync.push_back(b_golay_binary_128[i]);
//			}
//			vector<int> sfd;//前导sfd部分
//			int seed[7] = {1, -1, 1, 1, -1, -1, -1};
//			for (int i = 0; i < 7; i++)
//			{
//				if (seed[i] == 1)
//				{
//					for (int j = 0; j < 128; j++)
//						sfd.push_back(b_golay_binary_128[j]);
//				}
//				else
//				{
//					for (int j = 0; j < 128; j++)
//						sfd.push_back(b_golay_binary_128_N[j]);
//				}
//			}
//			vector<int> ces;//前导ces部分
//			for (int i = 0; i < 128; i++)
//				ces.push_back(a_golay_binary_128[i]);
//			for (int i = 0; i < 256; i++)
//				ces.push_back(a_golay_binary_256[i]);
//			for (int i = 0; i < 256; i++)
//				ces.push_back(b_golay_binary_256[i]);
//			for (int i = 0; i < 256; i++)
//				ces.push_back(a_golay_binary_256[i]);
//			for (int i = 0; i < 256; i++)
//				ces.push_back(b_golay_binary_256[i]);
//			for (int i = 0; i < 128; i++)
//				ces.push_back(b_golay_binary_128[i]);
//			vector<int> Preamble;//Preamble
//			for (int i = 0; i < sync.size(); i++)
//				Preamble.push_back(sync[i]);
//			for (int i = 0; i < sfd.size(); i++)
//				Preamble.push_back(sfd[i]);
//			for (int i = 0; i < ces.size(); i++)
//				Preamble.push_back(ces[i]);
//			//SC_tx_modulation(Preamble, vHSI_Pre, 1);//对preamble进行调制
//			vector<complex<double>> Preamble_mod;
//			HSI_tx_modulation(Preamble, Preamble_mod, 2, 0);//对preamble进行调制
//			HSI_OFDMer_header(Preamble_mod, vHSI_Pre);
//			//int Num_ifft = Preamble_mod.size() / 512;
//			//for (int i = 0; i <= Num_ifft; ++i)
//			//{
//			//	if (i != Num_ifft)
//			//	{
//			//		vector<complex<double>> ifft_temp;
//			//		for (int ii = 0; ii < 512; ++ii)
//			//			ifft_temp.push_back(Preamble_mod[i * 512 + ii]);
//			//		IFFT(ifft_temp, 512);
//			//		for (auto ii = ifft_temp.cbegin(); ii != ifft_temp.cend(); ++ii)
//			//			vHSI_Pre.push_back(*ii);
//			//	}
//			//	else
//			//	{
//			//		vector<complex<double>> ifft_temp;
//			//		//int Num_last = (Preamble_mod.size() - 512 * i);
//			//		for (int ii = 512 * i; ii < Preamble_mod.size(); ++ii)
//			//			ifft_temp.push_back(Preamble_mod[ii]);
//			//		IFFT(ifft_temp, ifft_temp.size());
//			//		for (auto ii = ifft_temp.cbegin(); ii != ifft_temp.cend(); ++ii)
//			//			vHSI_Pre.push_back(*ii);
//			//	}
//			//}
//			break;
//		}
//	case 1:
//		{
//			int Lpreb = 14 * 128 + 4 * 128 + (4 * 256 + 128);//前导长度
//			vector<int> sync;//前导sync部分
//			for (int i = 0; i < 14; i++)
//			{
//				for (int j = 0; j < 128; j++)
//					sync.push_back(a_golay_binary_128[j]);
//			}
//			vector<int> sfd;//前导sfd部分
//			int seed[4] = {1, -1, 1, -1};
//			for (int i = 0; i < 4; i++)
//			{
//				if (seed[i] == 1)
//				{
//					for (int j = 0; j < 128; j++)
//						sfd.push_back(a_golay_binary_128[j]);
//				}
//				else
//				{
//					for (int j = 0; j < 128; j++)
//						sfd.push_back(a_golay_binary_128_N[j]);
//				}
//			}
//			vector<int> ces;//前导ces部分
//			for (int i = 0; i < 256; i++)
//				ces.push_back(a_golay_binary_256[i]);
//			for (int i = 0; i < 256; i++)
//				ces.push_back(b_golay_binary_256[i]);
//			for (int i = 0; i < 256; i++)
//				ces.push_back(a_golay_binary_256[i]);
//			for (int i = 0; i < 256; i++)
//				ces.push_back(b_golay_binary_256[i]);
//			for (int i = 0; i < 128; i++)
//				ces.push_back(b_golay_binary_128[i]);
//			vector<int> Preamble;//Preamble
//			for (int i = 0; i < sync.size(); i++)
//				Preamble.push_back(sync[i]);
//			for (int i = 0; i < sfd.size(); i++)
//				Preamble.push_back(sfd[i]);
//			for (int i = 0; i < ces.size(); i++)
//				Preamble.push_back(ces[i]);
//
//			//SC_tx_modulation(Preamble, vHSI_Pre, 1);//对preamble进行调制
//			//HSI_tx_modulation(Preamble, vHSI_Pre, 2, 0);//QPSK调制
//			vector<complex<double>> Preamble_mod;
//			HSI_tx_modulation(Preamble, Preamble_mod, 2, 0);//对preamble进行调制
//			//int Num_ifft = Preamble_mod.size() / 512;
//			HSI_OFDMer_header(Preamble_mod, vHSI_Pre);
//			//for (int i = 0; i <= Num_ifft; ++i)
//			//{
//			//	if (i != Num_ifft)
//			//	{
//			//		vector<complex<double>> ifft_temp;
//			//		for (int ii = 0; ii < 512; ++ii)
//			//			ifft_temp.push_back(Preamble_mod[i * 512 + ii]);
//			//		IFFT(ifft_temp, 512);
//			//		for (auto ii = ifft_temp.cbegin(); ii != ifft_temp.cend(); ++ii)
//			//			vHSI_Pre.push_back(*ii);
//			//	}
//			//	else
//			//	{
//			//		vector<complex<double>> ifft_temp;
//			//		//int Num_last = (Preamble_mod.size() - 512 * i);
//			//		for (int ii = 512 * i; ii < Preamble_mod.size(); ++ii)
//			//			ifft_temp.push_back(Preamble_mod[ii]);
//			//		IFFT(ifft_temp, ifft_temp.size());
//			//		for (auto ii = ifft_temp.cbegin(); ii != ifft_temp.cend(); ++ii)
//			//			vHSI_Pre.push_back(*ii);
//			//	}
//			//}
//			break;
//		}
//	case 2:
//		{
//			int Lpreb = 14 * 128 + 4 * 128 + (4 * 256 + 128);//前导长度
//			vector<int> sync;//前导sync部分
//			for (int i = 0; i < 14; i++)
//			{
//				for (int j = 0; j < 128; j++)
//					sync.push_back(a_golay_binary_128[j]);
//			}
//			vector<int> sfd;//前导sfd部分
//			int seed[4] = {1, 1, -1, -1};
//			for (int i = 0; i < 4; i++)
//			{
//				if (seed[i] == 1)
//				{
//					for (int j = 0; j < 128; j++)
//						sfd.push_back(a_golay_binary_128[j]);
//				}
//				else
//				{
//					for (int j = 0; j < 128; j++)
//						sfd.push_back(a_golay_binary_128_N[j]);
//				}
//			}
//			vector<int> ces;//前导ces部分
//			for (int i = 0; i < 256; i++)
//				ces.push_back(a_golay_binary_256[i]);
//			for (int i = 0; i < 256; i++)
//				ces.push_back(b_golay_binary_256[i]);
//			for (int i = 0; i < 256; i++)
//				ces.push_back(a_golay_binary_256[i]);
//			for (int i = 0; i < 256; i++)
//				ces.push_back(b_golay_binary_256[i]);
//			for (int i = 0; i < 128; i++)
//				ces.push_back(b_golay_binary_128[i]);
//			vector<int> Preamble;//Preamble
//			for (int i = 0; i < sync.size(); i++)
//				Preamble.push_back(sync[i]);
//			for (int i = 0; i < sfd.size(); i++)
//				Preamble.push_back(sfd[i]);
//			for (int i = 0; i < ces.size(); i++)
//				Preamble.push_back(ces[i]);
//			//SC_tx_modulation(Preamble, vHSI_Pre, 1);//对preamble进行调制
//			//HSI_tx_modulation(Preamble, vHSI_Pre, 2, 0);//QPSK调制
//			vector<complex<double>> Preamble_mod;
//			HSI_tx_modulation(Preamble, Preamble_mod, 2, 0);//对preamble进行调制
//			HSI_OFDMer_header(Preamble_mod, vHSI_Pre);
//			//int Num_ifft = Preamble_mod.size() / 512;
//			//for (int i = 0; i <= Num_ifft; ++i)
//			//{
//			//	if (i != Num_ifft)
//			//	{
//			//		vector<complex<double>> ifft_temp;
//			//		for (int ii = 0; ii < 512; ++ii)
//			//			ifft_temp.push_back(Preamble_mod[i * 512 + ii]);
//			//		IFFT(ifft_temp, 512);
//			//		for (auto ii = ifft_temp.cbegin(); ii != ifft_temp.cend(); ++ii)
//			//			vHSI_Pre.push_back(*ii);
//			//	}
//			//	else
//			//	{
//			//		vector<complex<double>> ifft_temp;
//			//		//int Num_last = (Preamble_mod.size() - 512 * i);
//			//		for (int ii = 512 * i; ii < Preamble_mod.size(); ++ii)
//			//			ifft_temp.push_back(Preamble_mod[ii]);
//			//		IFFT(ifft_temp, ifft_temp.size());
//			//		for (auto ii = ifft_temp.cbegin(); ii != ifft_temp.cend(); ++ii)
//			//			vHSI_Pre.push_back(*ii);
//			//	}
//			//}
//			break;
//		}
//	default:
//		{
//			cout << "前导模式错误！！" << endl;
//			break;
//		}
//	}
//}
//
//void HSI_tx_modulation(vector<int> &codebits, vector<complex<double> > &symbols, int modtype, int skew)
//{
//	if (skew == 0)
//	{
//		int Nbits = codebits.size();
//		int Nnums = Nbits/modtype;
//		const double D = 1;//unskew mode
//		//int *nums = new int [Nnums]
//		vector<int> nums;
//		bits2nums(codebits, nums, modtype);//比特转化为数字，根据此数字在映射表中进行选择
//		switch (modtype)
//		{
//		case 2: 
//			{
//				complex<double> mod_temp[4] = {complex<double>(-D, -1), complex<double>(+D, -1), 
//					complex<double>(-D, +1), complex<double>(+D, +1)};//映射表
//				double nor_factor = 1/sqrt(1 + D * D);//归一化系数
//				for (int i = 0; i < 4; i++)
//					mod_temp[i] = mod_temp[i] * nor_factor;//归一化
//				for(int i = 0; i < Nnums; i++)
//					//symbols[i] = mod_temp[nums[i]];
//					symbols.push_back(mod_temp[nums[i]]);
//				break;
//			}
//		case 4:
//			{
//				complex<double> mod_temp[16] = {complex<double>((-3) * D, -3), complex<double>((-3) * D, -1), complex<double>((-3) * D, +3), complex<double>((-3) * D, +1), 
//					complex<double>((-1) * D, -3), complex<double>((-1) * D, -1), complex<double>((-1) * D, +3), complex<double>((-1) * D, +1), 
//					complex<double>((+3) * D, -3), complex<double>((+3) * D, -1), complex<double>((+3) * D, +3), complex<double>((+3) * D, +1), 
//					complex<double>((+1) * D, -3), complex<double>((+1) * D, -1), complex<double>((+1) * D, +3), complex<double>((+1) * D, +1)};//映射表
//				double nor_factor = 1/sqrt(5 * (1 + D * D));//归一化系数
//				for (int i = 0; i < 16; i++)
//					mod_temp[i] = mod_temp[i] * nor_factor;//归一化
//				for(int i = 0; i < Nnums; i++)
//					//symbols[i] = mod_temp[nums[i]];
//					symbols.push_back(mod_temp[nums[i]]);
//				break;
//			}
//		case 6:
//			{
//				complex<double> mod_temp[64] = {complex<double>((-7) * D, -7), complex<double>((-7) * D, -5), complex<double>((-7) * D, -1), complex<double>((-7) * D, -3), complex<double>((-7) * D, +7), complex<double>((-7) * D, +5), complex<double>((-7) * D, +1), complex<double>((-7) * D, +3), 
//					complex<double>((-5) * D, -7), complex<double>((-5) * D, -5), complex<double>((-5) * D, -1), complex<double>((-5) * D, -3), complex<double>((-5) * D, +7), complex<double>((-5) * D, +5), complex<double>((-5) * D, +1), complex<double>((-5) * D, +3), 
//					complex<double>((-1) * D, -7), complex<double>((-1) * D, -5), complex<double>((-1) * D, -1), complex<double>((-1) * D, -3), complex<double>((-1) * D, +7), complex<double>((-1) * D, +5), complex<double>((-1) * D, +1), complex<double>((-1) * D, +3),  
//					complex<double>((-3) * D, -7), complex<double>((-3) * D, -5), complex<double>((-3) * D, -1), complex<double>((-3) * D, -3), complex<double>((-3) * D, +7), complex<double>((-3) * D, +5), complex<double>((-3) * D, +1), complex<double>((-3) * D, +3), 
//					complex<double>((+7) * D, -7), complex<double>((+7) * D, -5), complex<double>((+7) * D, -1), complex<double>((+7) * D, -3), complex<double>((+7) * D, +7), complex<double>((+7) * D, +5), complex<double>((+7) * D, +1), complex<double>((+7) * D, +3), 
//					complex<double>((+5) * D, -7), complex<double>((+5) * D, -5), complex<double>((+5) * D, -1), complex<double>((+5) * D, -3), complex<double>((+5) * D, +7), complex<double>((+5) * D, +5), complex<double>((+5) * D, +1), complex<double>((+5) * D, +3), 
//					complex<double>((+1) * D, -7), complex<double>((+1) * D, -5), complex<double>((+1) * D, -1), complex<double>((+1) * D, -3), complex<double>((+1) * D, +7), complex<double>((+1) * D, +5), complex<double>((+1) * D, +1), complex<double>((+1) * D, +3), 
//					complex<double>((+3) * D, -7), complex<double>((+3) * D, -5), complex<double>((+3) * D, -1), complex<double>((+3) * D, -3), complex<double>((+3) * D, +7), complex<double>((+3) * D, +5), complex<double>((+3) * D, +1), complex<double>((+3) * D, +3)};//映射表
//				double nor_factor = 1 / sqrt(21 * (1 + D * D));//归一化系数
//				for (int i = 0; i < 64; i++)
//					mod_temp[i] = mod_temp[i] * nor_factor;//归一化
//				for(int i = 0; i < Nnums; i++)
//					//symbols[i] = mod_temp[nums[i]];
//					symbols.push_back(mod_temp[nums[i]]);
//				break;
//			}
//		default:
//			cout<<"调制模式输入错误！"<<endl;
//			exit(EXIT_FAILURE);
//		}
//	}
//	else
//	{
//		int Nbits = codebits.size();
//		int Nnums = Nbits / modtype;
//		const double D = 1.25;//unskew mode
//		//int* nums = new int [Nnums];
//		vector<int> nums;
//		bits2nums(codebits, nums, modtype);//比特转化为数字，根据此数字在映射表中进行选择
//		switch (modtype)
//		{
//		case 2: 
//			{
//				complex<double> mod_temp[4] = {complex<double>(-D, -1), complex<double>(+D, -1), 
//					complex<double>(-D, +1), complex<double>(+D, +1)};//映射表
//				double nor_factor = 1 / sqrt(1 + D * D);//归一化系数
//				for (int i = 0; i < 4; i++)
//					mod_temp[i] = mod_temp[i] * nor_factor;//归一化
//				for(int i = 0; i < Nnums; i++)
//					//symbols[i] = mod_temp[nums[i]];
//					symbols.push_back(mod_temp[nums[i]]);
//				break;
//			}
//		case 4:
//			{
//				complex<double> mod_temp[16] = {complex<double>((-3) * D, -3), complex<double>((-3) * D, -1), complex<double>((-3) * D, +3), complex<double>((-3) * D, +1), 
//					complex<double>((-1) * D, -3), complex<double>((-1) * D, -1), complex<double>((-1) * D, +3), complex<double>((-1) * D, +1), 
//					complex<double>((+3) * D, -3), complex<double>((+3) * D, -1), complex<double>((+3) * D, +3), complex<double>((+3) * D, +1), 
//					complex<double>((+1) * D, -3), complex<double>((+1) * D, -1), complex<double>((+1) * D, +3), complex<double>((+1) * D, +1)};//映射表
//				double nor_factor = 1 / sqrt(5 * (1 + D * D));//归一化系数
//				for (int i = 0; i < 16; i++)
//					mod_temp[i] = mod_temp[i] * nor_factor;//归一化
//				for(int i = 0; i < Nnums; i++)
//					//symbols[i] = mod_temp[nums[i]];
//					symbols.push_back(mod_temp[nums[i]]);
//				break;
//			}
//		case 6:
//			{
//				complex<double> mod_temp[64] = {complex<double>((-7) * D, -7), complex<double>((-7) * D, -5), complex<double>((-7) * D, -1), complex<double>((-7) * D, -3), complex<double>((-7) * D, +7), complex<double>((-7) * D, +5), complex<double>((-7) * D, +1), complex<double>((-7) * D, +3), 
//					complex<double>((-5) * D, -7), complex<double>((-5) * D, -5), complex<double>((-5) * D, -1), complex<double>((-5) * D, -3), complex<double>((-5) * D, +7), complex<double>((-5) * D, +5), complex<double>((-5) * D, +1), complex<double>((-5) * D, +3), 
//					complex<double>((-1) * D, -7), complex<double>((-1) * D, -5), complex<double>((-1) * D, -1), complex<double>((-1) * D, -3), complex<double>((-1) * D, +7), complex<double>((-1) * D, +5), complex<double>((-1) * D, +1), complex<double>((-1) * D, +3),  
//					complex<double>((-3) * D, -7), complex<double>((-3) * D, -5), complex<double>((-3) * D, -1), complex<double>((-3) * D, -3), complex<double>((-3) * D, +7), complex<double>((-3) * D, +5), complex<double>((-3) * D, +1), complex<double>((-3) * D, +3), 
//					complex<double>((+7) * D, -7), complex<double>((+7) * D, -5), complex<double>((+7) * D, -1), complex<double>((+7) * D, -3), complex<double>((+7) * D, +7), complex<double>((+7) * D, +5), complex<double>((+7) * D, +1), complex<double>((+7) * D, +3), 
//					complex<double>((+5) * D, -7), complex<double>((+5) * D, -5), complex<double>((+5) * D, -1), complex<double>((+5) * D, -3), complex<double>((+5) * D, +7), complex<double>((+5) * D, +5), complex<double>((+5) * D, +1), complex<double>((+5) * D, +3), 
//					complex<double>((+1) * D, -7), complex<double>((+1) * D, -5), complex<double>((+1) * D, -1), complex<double>((+1) * D, -3), complex<double>((+1) * D, +7), complex<double>((+1) * D, +5), complex<double>((+1) * D, +1), complex<double>((+1) * D, +3), 
//					complex<double>((+3) * D, -7), complex<double>((+3) * D, -5), complex<double>((+3) * D, -1), complex<double>((+3) * D, -3), complex<double>((+3) * D, +7), complex<double>((+3) * D, +5), complex<double>((+3) * D, +1), complex<double>((+3) * D, +3)};//映射表
//				double nor_factor = 1 / sqrt(21 * (1 + D * D));//归一化系数
//				for (int i = 0; i < 64; i++)
//					mod_temp[i] = mod_temp[i] * nor_factor;//归一化
//				for(int i = 0; i < Nnums; i++)
//					//symbols[i] = mod_temp[nums[i]];
//					symbols.push_back(mod_temp[nums[i]]);
//				break;
//			}
//		default:
//			cout<<"调制模式输入错误！"<<endl;
//			exit(EXIT_FAILURE);
//		}
//	}
//}
//
//void HSI_spreader(vector<complex<double> > &syms_input, vector<complex<double> > &sp_out, int sp_index)
//{
//	int Nsyms = syms_input.size();
//	const int Nsyms_sp = sp_index * Nsyms;//扩频输出比特数；
//	switch (sp_index)
//	{
//	case 1:
//		//sp_out = syms_input;
//		//break;
//		{
//			for (int i = 0; i < Nsyms; i++)
//				sp_out.push_back(syms_input[i]);
//			break;
//		}
//	case 48:
//		{
//			int Ngrp = Nsyms / 7;
//			complex<double>* spread_temp = new complex<double> [336];
//			complex<double>* spread_temp_a = new complex<double> [7];//扩频前的一组七个符号
//			complex<double>* spread_temp_b = new complex<double> [168];//扩频后的一组前半组168个符号
//			complex<double> sp_seq[24] = {complex<double>(+1,0), complex<double>(0,+1), complex<double>(-1,0), complex<double>(0,+1), complex<double>(0,+1), complex<double>(+1,0), 
//								          complex<double>(-1,0), complex<double>(0,+1), complex<double>(0,-1), complex<double>(0,+1), complex<double>(-1,0), complex<double>(0,-1), 
//								          complex<double>(-1,0), complex<double>(+1,0), complex<double>(+1,0), complex<double>(+1,0), complex<double>(0,+1), complex<double>(0,-1), 
//								          complex<double>(-1,0), complex<double>(-1,0), complex<double>(-1,0), complex<double>(0,+1), complex<double>(0,-1), complex<double>(0,+1)};//扩频序列
//			for (int i = 0; i < Ngrp; i++)
//			{
//				for (int j = 0; j < 7; j++)
//					spread_temp_a[j] = syms_input[7 * i + j];
//				for (int j = 0; j < 7; j++)
//				{
//					for (int k = 0; k < 24; k++)
//					/*{
//						spread_temp_b[24 * j + k].real = spread_temp_a[j].real * sp_seq[k].real - 
//														 spread_temp_a[j].imag * sp_seq[k].imag;
//						spread_temp_b[24 * j + k].imag = spread_temp_a[j].real * sp_seq[k].imag - 
//														 spread_temp_a[j].imag * sp_seq[k].real;
//					}*/
//						spread_temp_b[24 * j + k] = spread_temp_a[j] * sp_seq[k];
//				}
//				for (int j = 0; j < 168; j++)
//					{
//						spread_temp[j] = spread_temp_b[j];
//						spread_temp[335-j] = spread_temp[j];
//					}
//				for (int j = 0; j < 336; j++)
//					//sp_out[336 * Ngrp + j] = spread_temp[j];
//					sp_out.push_back(spread_temp[j]);
//			}
//			delete [] spread_temp;
//			delete [] spread_temp_a;
//			delete [] spread_temp_b;
//			break;
//		}
//	default:
//		cout<<"扩频因子输入错误"<<endl;
//		exit(EXIT_FAILURE);
//	}
//}
//
//void HSI_interleaver(vector<int> &bitsin, vector<int> &bitsout, int inter_index)
//{
//	switch (inter_index)
//	{
//	case 0:
//		{
//			for (int i = 0; i < bitsin.size(); ++i)
//				bitsout.push_back(bitsin[i]);
//			break;
//		}
//	case 1:
//		{
//			int bitsnums = bitsin.size();
//			int Nblocks = bitsnums / 2688;//交织数据块
//			int *inter_temp = new int [2688];
//			for (int i = 0; i < Nblocks; i++)
//			{
//				for (int j = 0; j < 2688; j++)
//					inter_temp[j] = bitsin[2688 * i + j];
//				for (int j = 0; j < 2688; j++)
//				{
//					int index_temp = (2688 - 24 + j + 2 * 24 * ((j * 24 - j) % 2688)) % 2688;//交织规则
//					//bitsout[2688 * i + j] = inter_temp[index_temp];
//					bitsout.push_back(inter_temp[index_temp]);
//				}
//			}
//			delete [] inter_temp;
//			break;
//		}
//	default:
//		{
//			cout << "参数输入错误" << endl;
//			break;
//		}
//	}
//}
//
//void HSI_toneinter(vector<complex<double> > &symsin)
//{
//	vector<complex<double> > syms_temp;
//	for (int i = 0; i < symsin.size(); i++)
//		syms_temp.push_back(symsin[i]);//保存symsin
//	for (int i = 0; i < 512; i++)
//	{
//		int bits_temp[9] = {0};
//		int seed_temp = i;
//		bits_temp[8] = i % 2;
//		for (int j = 7; j >= 0; --j)
//		{
//			seed_temp = seed_temp / 2;
//			bits_temp[j] = seed_temp % 2; 
//		}//将序号转化为9位二进制序列
//		int index_temp = 0;
//		for (int j = 0; j < 9; j++)
//		{
//			index_temp += bits_temp[j] * pow(2.0, j);
//		}//交织规则，反转序列得到交织后的载波位置
//		symsin[i] = syms_temp[index_temp];
//	}
//}
//
//void HSI_OFDMer(vector<complex<double> > &OFDMin, vector<complex<double> > &OFDMout)
//{
//	int nums_in = OFDMin.size();
//	const int Nstuff = ceil(nums_in / 336.0) * 336 - nums_in;
//	for (int i = 0; i < Nstuff; ++i)
//		OFDMin.push_back(complex<double>(0.0,0.0));//填充零
//	int nums = Nstuff + nums_in;//填充后的符号个数
//	/***********************载频映射******************************************/
//	int fft_size = 512;
//	const int Nofdm = nums / 336;//ofdm符号数
//	int index_temp[512] = {0};//总序列位置
//	vector<complex<double> > data_temp_00 (336, complex<double>(0,0));//保存原始数据
//	vector<complex<double> > data_temp_01 (512, complex<double>(0,0));//保存填充数据
//	for (int i = 0; i < 512; i++)
//		index_temp[i] = 0;//填充了信息的位置置1，反之置0
//	int index_null[141] = {0};
//	for (int i = 0; i < 71; i++)
//		index_null[i] = i;
//	for (int i = 0; i < 70; i++)
//		index_null[71 + i] = 442 + i;//零频子载波位置
//	complex<double> sub_null[141];
//	for (int i = 0; i < 141; i++)
//		sub_null[i] = complex<double> (0,0);//零频子载波信息
//	int index_dc[3] = {0};
//	for (int i = 0; i < 3; i++)
//		index_dc[i] = 255 + i;//直流子载波位置
//	complex<double> sub_dc[3];
//	for (int i = 0; i < 3; i++)
//		sub_dc[i] = complex<double> (1,0);//直流载波信息
//	int index_pilot[16] = {0};
//	for (int i = 0; i < 8; i++)
//	{
//		index_pilot[i] = 90 + 22 * i;
//		index_pilot[i + 8] = 268 + 22 * i;
//	}//导频子载波位置
//	complex<double> sub_pilot_01[16] = {complex<double> (+1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),+1/sqrt(2.0)),
//		complex<double> (+1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),+1/sqrt(2.0))};//导频子载波信息（正极性）
//	complex<double> sub_pilot_00[16] = {complex<double> (-1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),-1/sqrt(2.0)),
//		complex<double> (-1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),-1/sqrt(2.0))};//导频子载波信息（负极性）
//	int ssid[4] = {0,0,0,0};
//	vector<int> prbs;
//	scrambler_gen_prbs(ssid, prbs, Nofdm);//产生伪随机序列决定导频极性
//	int index_guard[16] = {0};
//	for (int i = 0; i < 8; i++)
//	{
//		index_guard[i] = 71 + i;
//		index_guard[i + 8] = 434 + i;
//	}//保护子载波位置
//	vector<complex<double> > sub_guard(16, complex<double>(0,0));//保护子载波信息
//	/********************************OFDM调制*****************************/
//	for (int i = 0; i < Nofdm; i++)
//	{
//		for (int j = 0; j < 336; j++)//取得原始数据
//			data_temp_00[j] = OFDMin[j + i * 336];
//		for (int j = 0; j < 141; j++)//填充零频
//		{
//			index_temp[index_null[j]] = 1;
//			data_temp_01[index_null[j]] = sub_null[j];
//		}
//		for (int j = 0; j < 3; j++)//填充直流
//		{
//			index_temp[index_dc[j]] = 1;
//			data_temp_01[index_dc[j]] = sub_dc[j];
//		}
//		for (int j = 0; j < 16; j++)//填充导频
//		{
//			if (prbs[i] == 1)
//			{
//				index_temp[index_pilot[j]] = 1;
//				data_temp_01[index_pilot[j]] = sub_pilot_01[j];
//			}
//			else
//			{
//				index_temp[index_pilot[j]] = 1;
//				data_temp_01[index_pilot[j]] = sub_pilot_00[j];
//			}
//		}
//		for (int j = 0; j < 16; j++)//填充保护
//		{
//			index_temp[index_guard[j]] = 1;
//			data_temp_01[index_guard[j]] = sub_guard[j];
//		}
//		int data_index = 0;
//		int count_temp = 0;//
//		for (int i = 0; i < 512; ++i)
//		{
//			if(index_temp[i] == 0)
//				count_temp++;
//		}
//		for (int j = 0; j < 512; j++)//剩余位置填入数据
//		{
//			if (index_temp[j] == 0)
//			{
//				data_temp_01[j] = data_temp_00[data_index];
//				data_index++;
//			}
//		}
//		//HSI_toneinter(data_temp_01);//载波交织
//		IFFT(data_temp_01, fft_size);//IFFT变换
//		for (int j = 0; j < 64; j++)//循环前缀64
//			//OFDMout[j + 640 * i] = data_temp_01[j];
//			OFDMout.push_back(data_temp_01[j]);
//		for (int j = 0; j < 512; j++)
//			//OFDMout[j + 128 + 640 * i] = data_temp_01[j];
//			OFDMout.push_back(data_temp_01[j]);
//	}
//}
//
//void HSI_OFDMer_header(vector<complex<double> > &OFDMin, vector<complex<double> > &OFDMout)
//{
//	int nums_in = OFDMin.size();
//	const int Nstuff = ceil(nums_in / 336.0) * 336 - nums_in;
//	for (int i = 0; i < Nstuff; ++i)
//		OFDMin.push_back(complex<double>(0.0,0.0));//填充零
//	int nums = Nstuff + nums_in;//填充后的符号个数
//	int fft_size = 512;
//	const int Nofdm = nums / 336;//ofdm符号数
//	/***********************载频映射******************************************/
//	int index_temp[512] = {0};//总序列位置
//	vector<complex<double> > data_temp_00 (336, complex<double>(0,0));//保存原始数据
//	vector<complex<double> > data_temp_01 (512, complex<double>(0,0));//保存填充数据
//	for (int i = 0; i < 512; i++)
//		index_temp[i] = 0;//填充了信息的位置置1，反之置0
//	int index_null[141] = {0};
//	for (int i = 0; i < 71; i++)
//		index_null[i] = i;
//	for (int i = 0; i < 70; i++)
//		index_null[71 + i] = 442 + i;//零频子载波位置
//	complex<double> sub_null[141];
//	for (int i = 0; i < 141; i++)
//		sub_null[i] = complex<double> (0,0);//零频子载波信息
//	int index_dc[3] = {0};
//	for (int i = 0; i < 3; i++)
//		index_dc[i] = 255 + i;//直流子载波位置
//	complex<double> sub_dc[3];
//	for (int i = 0; i < 3; i++)
//		sub_dc[i] = complex<double> (1,0);//直流载波信息
//	int index_pilot[16] = {0};
//	for (int i = 0; i < 8; i++)
//	{
//		index_pilot[i] = 90 + 22 * i;
//		index_pilot[i + 8] = 268 + 22 * i;
//	}//导频子载波位置
//	complex<double> sub_pilot_01[16] = {complex<double> (+1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),+1/sqrt(2.0)),
//		complex<double> (+1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (+1/sqrt(2.0),+1/sqrt(2.0))};//导频子载波信息（正极性）
//	complex<double> sub_pilot_00[16] = {complex<double> (-1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),-1/sqrt(2.0)),
//		complex<double> (-1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),-1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),+1/sqrt(2.0)), complex<double> (-1/sqrt(2.0),-1/sqrt(2.0))};//导频子载波信息（负极性）
//	int ssid[4] = {0,0,0,0};
//	vector<int> prbs;
//	scrambler_gen_prbs(ssid, prbs, Nofdm);//产生伪随机序列决定导频极性
//	int index_guard[16] = {0};
//	for (int i = 0; i < 8; i++)
//	{
//		index_guard[i] = 71 + i;
//		index_guard[i + 8] = 434 + i;
//	}//保护子载波位置
//	vector<complex<double> > sub_guard(16, complex<double>(0,0));//保护子载波信息
//	for (int i = 0; i < Nofdm; i++)
//	{
//		for (int j = 0; j < 336; j++)//取得原始数据
//			data_temp_00[j] = OFDMin[j + i * 336];
//		for (int j = 0; j < 141; j++)//填充零频
//		{
//			index_temp[index_null[j]] = 1;
//			data_temp_01[index_null[j]] = sub_null[j];
//		}
//		for (int j = 0; j < 3; j++)//填充直流
//		{
//			index_temp[index_dc[j]] = 1;
//			data_temp_01[index_dc[j]] = sub_dc[j];
//		}
//		for (int j = 0; j < 16; j++)//填充导频
//		{
//			if (prbs[i] == 1)
//			{
//				index_temp[index_pilot[j]] = 1;
//				data_temp_01[index_pilot[j]] = sub_pilot_01[j];
//			}
//			else
//			{
//				index_temp[index_pilot[j]] = 1;
//				data_temp_01[index_pilot[j]] = sub_pilot_00[j];
//			}
//		}
//		for (int j = 0; j < 16; j++)//填充保护
//		{
//			index_temp[index_guard[j]] = 1;
//			data_temp_01[index_guard[j]] = sub_guard[j];
//		}
//		int data_index = 0;
//		int count_temp = 0;//
//		for (int i = 0; i < 512; ++i)
//		{
//			if(index_temp[i] == 0)
//				count_temp++;
//		}
//		for (int j = 0; j < 512; j++)//剩余位置填入数据
//		{
//			if (index_temp[j] == 0)
//			{
//				data_temp_01[j] = data_temp_00[data_index];
//				data_index++;
//			}
//		}
//		//HSI_toneinter(data_temp_01);//载波交织
//		IFFT(data_temp_01, fft_size);//IFFT变换
//		for (int j = 0; j < 128; j++)//循环前缀128
//			//OFDMout[j + 640 * i] = data_temp_01[j];
//			OFDMout.push_back(data_temp_01[j]);
//		for (int j = 0; j < 512; j++)
//			//OFDMout[j + 128 + 640 * i] = data_temp_01[j];
//			OFDMout.push_back(data_temp_01[j]);
//	}
//}
//
//void HSI_FECencoder(vector<int> &vbitsin, vector<int> &vbitsout, int UEP, int FECrate)
//{
//	if (UEP == 0)//EEP
//	{
//		vector<int> vlower, vupper;
//		int Nbits = vbitsin.size();
//		int Nblock = Nbits / 16;//每16比特进行分流
//		for (int i = 0; i < Nblock; i++)
//		{
//			for (int j = 0; j < 8; j++)
//			{
//				vupper.push_back(vbitsin[16 * i + j]);
//				vlower.push_back(vbitsin[16 * i + 8 + j]);
//			}
//		}
//		vector<int> vfec_up;
//		vector<int> vfec_low;
//		HSI_LDPCencoder(vupper, vfec_up, FECrate);
//		HSI_LDPCencoder(vlower, vfec_low, FECrate);
//		for (decltype(vfec_low.size()) i = 0; i < vfec_low.size(); i++)
//		{
//			vbitsout.push_back(vfec_up[i]);
//			vbitsout.push_back(vfec_low[i]);
//		}
//	}
//	else
//	{
//		switch (FECrate)
//		{
//		case 0:
//			{
//				vector<int> vlower, vupper;
//				int Nbits = vbitsin.size();
//				int Nblock = Nbits / 16;//每16比特进行分流
//				for (int i = 0; i < Nblock; i++)
//				{
//					for (int j = 0; j < 8; j++)
//					{
//						vupper.push_back(vbitsin[16 * i + j]);
//						vlower.push_back(vbitsin[16 * i + 8 + j]);
//					}
//				}
//				vector<int> vfec_up;
//				vector<int> vfec_low;
//				int FECrate_up = 0;
//				int FECrate_low = 2;
//				HSI_LDPCencoder(vupper, vfec_up, FECrate_up);//还没有LDPC编码
//				HSI_LDPCencoder(vlower, vfec_low, FECrate_low);
//				auto Bmux = vfec_up.size() / 3;
//				for (decltype(Bmux) i = 0; i < Bmux; i++)//数据复合
//				{
//					vbitsout.push_back(vfec_up[i * 3 + 0]);
//					vbitsout.push_back(vfec_low[i * 2 + 0]);
//					vbitsout.push_back(vfec_up[i * 3 + 1]);
//					vbitsout.push_back(vfec_low[i * 2 + 1]);
//					vbitsout.push_back(vfec_up[i * 3 + 2]);
//				}
//				break;
//			}
//		case 2:
//			{
//				vector<int> vlower, vupper;
//				int Nbits = vbitsin.size();
//				int Nblock = Nbits / 16;//每16比特进行分流
//				for (int i = 0; i < Nblock; i++)
//				{
//					for (int j = 0; j < 8; j++)
//					{
//						vupper.push_back(vbitsin[16 * i + j]);
//						vlower.push_back(vbitsin[16 * i + 8 + j]);
//					}
//				}
//				vector<int> vfec_up;
//				vector<int> vfec_low;
//				int FECrate_up = 2;
//				int FECrate_low = 3;
//				HSI_LDPCencoder(vupper, vfec_up, FECrate_up);//还没有LDPC编码
//				HSI_LDPCencoder(vlower, vfec_low, FECrate_low);
//				int Bmux = vfec_up.size() / 7;
//				for (int i = 0; i < Bmux; i++)//数据复合
//				{
//					vbitsout.push_back(vfec_up[i * 7 + 0]);
//					vbitsout.push_back(vfec_low[i * 6 + 0]);
//					vbitsout.push_back(vfec_up[i * 7 + 1]);
//					vbitsout.push_back(vfec_low[i * 6 + 1]);
//					vbitsout.push_back(vfec_up[i * 7 + 2]);
//					vbitsout.push_back(vfec_low[i * 6 + 2]);
//					vbitsout.push_back(vfec_up[i * 7 + 3]);
//					vbitsout.push_back(vfec_low[i * 6 + 3]);
//					vbitsout.push_back(vfec_up[i * 7 + 4]);
//					vbitsout.push_back(vfec_low[i * 6 + 4]);
//					vbitsout.push_back(vfec_up[i * 7 + 5]);
//					vbitsout.push_back(vfec_low[i * 6 + 5]);
//					vbitsout.push_back(vfec_up[i * 7 + 6]);
//				}
//				break;
//			}
//		default:
//			{
//				cout << "FECrate输入错误！！！" << endl;
//			}
//		}
//	}
//}
//
//void HSI_LDPCencoder(vector<int> &bitsin, vector<int> &bitsout, int rate)
//{
//	vector<vector<double> > zMatrix;
//	genLDPCGenMatrix(rate, zMatrix);//生成校验矩阵
//	int Nparity = zMatrix.size();//校验位个数
//	int Ndata = 672 - Nparity;//信息位个数
//	int Nblock = bitsin.size() / Ndata;
//	vector<double> parity (Nparity, 0);
//	for (int ii = 0; ii < Nblock; ++ii)
//	{
//		vector<double> temp_gen;
//		for (int iii = 0; iii < Ndata; ++iii)
//		{
//			temp_gen.push_back(bitsin[Ndata * ii + iii]);
//			bitsout.push_back(bitsin[Ndata * ii + iii]);
//		}
//		genLDPCparity(temp_gen, zMatrix, parity);
//		for (int iii = 0; iii < Nparity; ++iii)
//		{
//			//int int_temp = parity[iii];
//			bitsout.push_back(parity[iii]);
//		}
//	}
//}
//
//void genHSI(vector<int> &datain, vector<int> &macheader, vector<complex<double> > &dataout, HSI_param &HSI_p)
//{
//	int ssid = 0;
//	for (int i = 0; i < HSI_p.Nfram; i++)
//	{
//		int Lpreb;
//		switch (HSI_p.pretype)
//		{
//		case 0:
//			Lpreb = 8320;
//		case 1:
//			Lpreb = 3456;
//		case 2:
//			Lpreb = 3456;
//		}
//		//complex<double> *HSI_preb = new complex<double>[Lpreb];
//		vector<complex<double> > HSI_preb;
//		HSI_genPreamble(HSI_preb, HSI_p.pretype);
//		for (int j = 0; j < HSI_preb.size(); j++)
//			dataout.push_back(HSI_preb[j] * 5.0);//填充Preamble
//		//delete [] HSI_preb;
//		/******************************构造macheader*******************************/
//		vector<int> vMacheader;//
//		//int *PHYheader = new int[48];
//		vector<int> PHYheader (48, 0);//共48位PHYheader
//		ssid = ssid % 16;
//		int temp_ssid = ssid;
//		int SSID[4] = {0};
//		for (int j = 0; j < 4; j++)//计算SSID
//		{
//			SSID[3 -j] = temp_ssid % 2;
//			temp_ssid = temp_ssid /2;
//		}
//		for (int j = 0; j < 4;j++)
//			PHYheader[j] = SSID[j];//插入SSID
//		PHYheader[4] = HSI_p.Agr;//插入Aggregation
//		PHYheader[5] = HSI_p.UEP;//插入UEP
//		int temp_MCS = HSI_p.MCS;
//		for (int j = 0; j < 4; j++)//插入5bits MCS
//		{
//			PHYheader[10 - j] = temp_MCS % 2;
//			temp_MCS = temp_MCS / 2;
//		}
//		int temp_Lfram = HSI_p.L_mb;
//		for (int j = 0; j < 20; j++)//插入20bits frame length
//		{
//			PHYheader[30 - j] = temp_Lfram % 2;
//			temp_Lfram = temp_Lfram / 2;
//		}
//		PHYheader[31] = 0;
//		PHYheader[32] = HSI_p.pretype;//插入Preamble type
//		PHYheader[33] = HSI_p.Bt;//插入Beam tracking
//		PHYheader[34] = HSI_p.Llat;//插入Low-latency mode
//		PHYheader[35] = HSI_p.bits_inter;//插入Bit interleaver
//		PHYheader[36] = HSI_p.PCES;//插入PCES mode
//		PHYheader[37] = HSI_p.skewed_map;//插入Skewed constellation
//		for (int j = 0; j < 10; j++)//插入Reserved bits
//			PHYheader[38 + j] = HSI_p.Rsv[j];
//		int index_header = 48 + HSI_p.L_mh;
//		vector<int> gen_HSI;
//		for (int j = 0; j < 48; j++)
//			gen_HSI.push_back(PHYheader[j]);
//		for (int j = 0; j < HSI_p.L_mh; j++)
//			gen_HSI.push_back(macheader[j]);
//		vector<int> pHCS;
//		HCS_encoder(gen_HSI, pHCS);//计算HSI
//		vector<int> gen_scram;
//		for (int j = 0; j < HSI_p.L_mh; j++)
//			gen_scram.push_back(macheader[j]);
//		for (int j = 0; j < 16; j++)
//			gen_scram.push_back(pHCS[j]);
//		scrambler(gen_scram, SSID);//扰码
//		vector<int> gen_fech_in;
//		vector<int> gen_fech_out;
//		for (int j = 0; j < 48; j++)
//			gen_fech_in.push_back(PHYheader[j]);
//		for (decltype(gen_scram.size()) j = 0; j < gen_scram.size(); j++)
//			gen_fech_in.push_back(gen_scram[j]);
//		HSI_LDPCencoder(gen_fech_in, gen_fech_out, 0);//前向编码，码率1/2
//		vector<complex<double> > gen_map_h;
//		HSI_tx_modulation(gen_fech_out, gen_map_h, 2, 0);//QPSK调制
//		vector<complex<double> > gen_OFDM_h;
//		HSI_OFDMer_header(gen_map_h, gen_OFDM_h);//OFDM
//		for (int j = 0; j < gen_OFDM_h.size(); j++)
//			dataout.push_back(gen_OFDM_h[j]);
//		/************************macbody**********************************************/
//		vector<int> temp_payload;
//		for (int j = 0; j < HSI_p.L_mb; j++)
//			temp_payload.push_back(datain[j]);
//		vector<int> temp_pl_fec;
//		HSI_FECencoder(temp_payload,temp_pl_fec,HSI_p.UEP,HSI_p.FECrate);//前向编码
//		vector<int> temp_pl_inter;
//		HSI_interleaver(temp_pl_fec, temp_pl_inter, HSI_p.bits_inter);
//		vector<complex<double> > temp_pl_map;
//		HSI_tx_modulation(temp_pl_inter, temp_pl_map, HSI_p.modtype, HSI_p.skewed_map);
//		vector<complex<double> > temp_pl_sp;
//		HSI_spreader(temp_pl_map, temp_pl_sp, HSI_p.sp);
//		vector<complex<double> > temp_pl_ofdm;
//		HSI_OFDMer(temp_pl_sp, temp_pl_ofdm);
//		for (int j = 0; j < temp_pl_ofdm.size(); j++)
//			dataout.push_back(temp_pl_ofdm[j]);
//	}
//}
//
///**************************************AV-PHY模块*****************************************/
//void genAV(vector<int> &bitsin, vector<int> &machin, vector<complex<double> > &symsout, AV_param &AV_p)
//{
//	int ssid = 0;
//	for (int i = 0; i < AV_p.Nframs; ++i)
//	{
//		/*****************************preamble*****************************************************/
//		vector<complex<double> > vPream;
//		HSI_genPreamble(vPream, 1);
//		for (int j = 0; j < vPream.size(); ++j)
//			symsout.push_back(vPream[j]);
//		/*****************************header******************************************************/
//		ssid = ssid % 16;
//		int temp_ssid = ssid;
//		int SSID[4] = {0};
//		for (int j = 0; j < 4; j++)//计算SSID
//		{
//			SSID[3 -j] = temp_ssid % 2;
//			temp_ssid = temp_ssid /2;
//		}
//		vector<int> AV_phyh (22 * 8, 0);
//		AV_phyh[1] = 0;
//		for (int j = 0; j < 4; ++j)
//			AV_phyh[2 + j] = SSID[3 - j];
//		vector<int> genHCS_temp;
//		vector<int> HCS_parity;
//		for (int j = 0; j < AV_phyh.size(); ++j)
//			genHCS_temp.push_back(AV_phyh[j]);
//		for (int j = 0; j < AV_p.L_mh; ++j)
//			genHCS_temp.push_back(machin[j]);
//		AV_HCS_encoder(genHCS_temp, HCS_parity);//计算HCS
//		for (int j = 0; j < 32; ++j)
//			genHCS_temp.push_back(HCS_parity[j]);
//		scrambler(genHCS_temp, SSID);//扰码
//		vector<int> vRSenc_mh;
//		vector<int> vRSh_temp_00;//RS编码码字（56，48）
//		vector<int> vRSh_temp_01;//RS编码码字（52，44）
//		for (int j = 0; j < 48 * 8; ++j)
//			vRSh_temp_00.push_back(genHCS_temp[j]);
//		for (int j = 0; j < 44 * 8; ++j)
//			vRSh_temp_01.push_back(genHCS_temp[48 * 8 + j]);
//		RS_encoder(vRSh_temp_00, vRSenc_mh, 3);
//		RS_encoder(vRSh_temp_01, vRSenc_mh, 4);//RS编码
//		vector<int> mh_outinter;
//		AV_outer_interleaver(vRSenc_mh, 2);//外交织
//		vector<int> A_mh;
//		vector<int> B_mh;
//		vector<int> C_mh;
//		vector<int> D_mh;
//		vector<int> E_mh;
//		vector<int> F_mh;
//		vector<int> G_mh;
//		vector<int> H_mh;
//		vector<int> mh_fake;
//		AV_conencoder(vRSenc_mh, mh_fake, A_mh, B_mh, C_mh, D_mh, E_mh, F_mh, G_mh, H_mh, 0, 0, 2);
//		vector<int> mh_mux;
//		AV_multiplexer(mh_mux, 2, A_mh, B_mh, C_mh, D_mh, E_mh, F_mh, G_mh, G_mh);
//		vector<complex<double> > mh_mod;
//		AV_tx_modulation(mh_mux, mh_mod, 2, 0);
//		int Nstuff_mh = 336 - mh_mod.size() % 336;
//		for (int j = 0; j < Nstuff_mh; ++j)
//			mh_mod.push_back(complex<double> (0, 0));
//		vector<complex<double> > mh_ofdm;
//		AV_OFDMer(mh_mod, mh_ofdm);
//		for (int j = 0; j < mh_ofdm.size(); ++j)
//			symsout.push_back(mh_ofdm[j] * 10.0);
//		/*****************************header******************************************************/
//		vector<int> split_temp_upper;
//		vector<int> split_temp_lower;
//		AV_splitter(bitsin, split_temp_upper, split_temp_lower, AV_p.UEP);//分流
//		scrambler(split_temp_upper,SSID);
//		scrambler(split_temp_lower,SSID);//扰码
//		vector<int> rs_temp_upper;
//		vector<int> rs_temp_lower;
//		AV_RSencoder(split_temp_upper, split_temp_lower, rs_temp_upper, rs_temp_lower, AV_p.UEP, AV_p.out_inter);//RS编码
//		vector<int> A_mb;
//		vector<int> B_mb;
//		vector<int> C_mb;
//		vector<int> D_mb;
//		vector<int> E_mb;
//		vector<int> F_mb;
//		vector<int> G_mb;
//		vector<int> H_mb;
//		AV_conencoder(rs_temp_upper, rs_temp_lower, A_mb, B_mb, C_mb, D_mb, E_mb, F_mb, G_mb,  H_mb, AV_p.rate_up, AV_p.rate_low, AV_p.UEP);//卷积编码
//		vector<int> mb_mux;
//		AV_multiplexer(mb_mux, AV_p.UEP, A_mb, B_mb, C_mb, D_mb, E_mb, F_mb, G_mb,  H_mb);//数据复合
//		vector<complex<double> > mb_mod;
//		AV_tx_modulation(mb_mux, mb_mod, AV_p.modtype, AV_p.UEP);//映射
//		vector<complex<double> > mb_ofdm;
//		AV_OFDMer(mb_mod, mb_ofdm);//ofdm调制
//		for (int j = 0; j < mb_ofdm.size(); ++j)
//			symsout.push_back(mb_ofdm[j]* 10.0);
//	}
//}
//
//void AV_splitter(vector<int> &codebits, vector<int> &bits_up, vector<int> &bits_low, int ueptype)
//{
//	int Nbits = codebits.size();
//	switch (ueptype)
//	{
//	case 0:
//		{
//			int test = Nbits % 32;//检验比特数
//			if (test == 0)
//			{
//				const int Nblocks = Nbits / 32;//数据块数目
//				int bits_temp[32]; 
//				for (int i = 0; i < Nblocks; i++)
//				{
//					for (int j = 0; j < 32; j++)
//						bits_temp[j] = codebits[32 * i + j];
//					for (int ii = 0; ii < 4; ii++)
//						//bits_low[16 * i + ii] = bits_temp[ii];
//						bits_low.push_back(bits_temp[ii]);
//					for (int ii = 0; ii < 4; ii++)
//						//bits_low[16 * i + 4 + ii] = bits_temp[8 + ii];
//						bits_low.push_back(bits_temp[8 + ii]);
//					for (int ii = 0; ii < 4; ii++)
//						//bits_low[16 * i + 8 + ii] = bits_temp[4 + ii];
//						bits_low.push_back(bits_temp[4 + ii]);
//					for (int ii = 0; ii < 4; ii++)
//						//bits_low[16 * i + 12 + ii] = bits_temp[12 + ii];
//						bits_low.push_back(bits_temp[12 + ii]);//填充low分流
//					for (int ii = 0; ii < 4; ii++)
//						//bits_up[16 * i + ii] = bits_temp[16 + ii];
//						bits_up.push_back(bits_temp[16 + ii]);
//					for (int ii = 0; ii < 4; ii++)
//						//bits_up[16 * i + 4 + ii] = bits_temp[16 + 8 + ii];
//						bits_up.push_back(bits_temp[16 + 8 + ii]);
//					for (int ii = 0; ii < 4; ii++)
//						//bits_up[16 * i + 8 + ii] = bits_temp[16 + 4 + ii];
//						bits_up.push_back(bits_temp[16 + 4 + ii]);
//					for (int ii = 0; ii < 4; ii++)
//						//bits_up[16 * i + 12 + ii] = bits_temp[16 + 12 + ii];
//						bits_up.push_back(bits_temp[16 + 12 + ii]);//填充upper分流
//
//				}
//			}
//			else
//			{
//				cout << "输入比特数目错误！" << endl;
//				exit(EXIT_FAILURE);
//			}
//			break;
//		}
//	case 1:
//		{
//			int test = Nbits % 16;//检验比特数
//			if (test == 0)
//			{
//				const int Nblocks = Nbits / 16;//数据块数目
//				int bits_temp[16]; 
//				for (int i = 0; i < Nblocks; i++)
//				{
//					for (int j = 0; j < 16; j++)
//						bits_temp[j] = codebits[16 * i + j];
//					for (int ii = 0; ii < 4; ii++)
//						//bits_low[8 * i + ii] = bits_temp[ii];
//						bits_low.push_back(bits_temp[ii]);
//					for (int ii = 0; ii < 4; ii++)
//						//bits_low[8 * i + 4 + ii] = bits_temp[8 + ii];
//						bits_low.push_back(bits_temp[8 + ii]);//填充low分流
//					for (int ii = 0; ii < 4; ii++)
//						//bits_up[8 * i + ii] = bits_temp[4 + ii];
//						bits_up.push_back(bits_temp[4 + ii]);
//					for (int ii = 0; ii < 4; ii++)
//						//bits_up[8 * i + 4 + ii] = bits_temp[12 + ii];
//						bits_up.push_back(bits_temp[12 + ii]);//填充upper分流
//				}
//			}
//			else
//			{
//				cout << "输入比特数目错误！" << endl;
//				exit(EXIT_FAILURE);
//			}
//			break;
//		}
//	case 2:
//		{
//			for (int i = 0; i < codebits.size(); ++i)
//				bits_up.push_back(codebits[i]);
//			break;
//		}
//	default:
//		{
//			cout << "UEP模式输入错误！" << endl;
//			exit(EXIT_FAILURE);
//			break;
//		}
//	}
//}
//
//void AV_RSencoder(vector<int> &in_upper, vector<int> &in_lower, vector<int> &out_upper, vector<int> &out_lower, int ueptype, int inter_depth)
//{
//	if (ueptype != 2)
//	{
//		int Nbits = in_upper.size();
//		int Nstuff_rs = 216 - Nbits % 216;
//		for (int i = 0; i < Nstuff_rs; ++i)
//		{
//			in_upper.push_back(0);
//			in_lower.push_back(0);
//		}
//		RS_encoder(in_upper, out_upper, 2);//RS编码
//		RS_encoder(in_lower, out_lower, 2);
//		AV_outer_interleaver(out_upper, inter_depth);//交织
//		AV_outer_interleaver(out_lower, inter_depth);
//	}
//	else
//	{
//		int Nbits = in_upper.size();
//		int Nstuff_rs = 216 - Nbits % 216;
//		for (int i = 0; i < Nstuff_rs; ++i)
//		{
//			in_upper.push_back(0);
//		}
//		RS_encoder(in_upper, out_upper, 2);//RS编码
//		AV_outer_interleaver(out_upper, inter_depth);//交织
//	}
//}
//
//void AV_HCS_encoder(vector<int> &bits_input, vector<int> &parity)
//{
//	int reg_temp[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};//初始化寄存器全1
//	for (int i = 0; i < bits_input.size(); i++)
//	{
//		int c31 = bits_input[i] ^ reg_temp[0];
//		int c5 = c31 ^ reg_temp[6];
//		int c8 = c31 ^ reg_temp[9];
//		int c9 = c31 ^ reg_temp[10];
//		int c15 = c31 ^ reg_temp[16];
//		int c19 = c31 ^ reg_temp[20];
//		int c20 = c31 ^ reg_temp[21];
//		int c21 = c31 ^ reg_temp[22];
//		int c23 = c31 ^ reg_temp[24];
//		int c24 = c31 ^ reg_temp[25];
//		int c26 = c31 ^ reg_temp[27];
//		int c27 = c31 ^ reg_temp[28];
//		int c29 = c31 ^ reg_temp[30];
//		int c30 = c31 ^ reg_temp[31];//计算校验位
//		for (int j = 0; j < 31; j++)
//		{
//			reg_temp[j] = reg_temp[j+1];
//		}
//		reg_temp[31] = c31;
//		reg_temp[30] = c30;
//		reg_temp[29] = c29;
//		reg_temp[27] = c27;
//		reg_temp[26] = c26;
//		reg_temp[24] = c24;
//		reg_temp[23] = c23;
//		reg_temp[21] = c21;
//		reg_temp[20] = c20;
//		reg_temp[19] = c19;
//		reg_temp[15] = c15;
//		reg_temp[9] = c9;
//		reg_temp[8] = c8;
//		reg_temp[5] = c5;
//	}
//	for (int i = 0; i < 32; i++)
//	{
//		parity.push_back(reg_temp[i] ^ 1);//输出补码
//	}
//}
//
//void AV_tx_modulation(vector<int> &bitsin, vector<complex<double> > &symsout, int modtype, int ueptype)
//{
//	int Nbits = bitsin.size();
//	if (modtype == 1)
//	{
//		complex<double> map_temp[2] = {complex<double> (-1, 0),complex<double> (1, 0)};//映射表
//		int map_index = 0;
//		for (int i = 0; i < Nbits; i++)
//		{
//			map_index = bitsin[i];
//			symsout[i] = map_temp[bitsin[i]];
//		}
//	}
//	else
//	{
//		switch (ueptype)
//		{
//		case 0:
//			{
//				double d1 = 1.0;
//				double d2 = 1.0;
//				switch (modtype)
//				{
//				case 2:
//					{
//						double nor_index = 1 / sqrt(d1 * d1 + d2 * d2);//归一化系数
//						complex<double> map_temp[4] = {complex<double>(-d1, -d2), complex<double>(+d1, -d2), 
//							complex<double>(-d1, +d2), complex<double>(+d1, +d2)};//映射表
//						for (int i = 0; i < 4; i++)
//							map_temp[i] = map_temp[i] * nor_index;
//						int Nsyms = Nbits / modtype;
//						vector<int> nums;
//						//HSI_bits2nums(bitsin, nums, modtype);
//						bits2nums(bitsin, nums, modtype);//比特转换为数字
//						for (int i = 0; i < Nsyms; i++)
//						{
//							int num_temp = nums[i];
//							//symsout[i] = map_temp[num_temp];
//							symsout.push_back(map_temp[num_temp]);
//						}
//						break;
//					}
//				case 4:
//					{
//						double nor_index = 1 / sqrt(5 * (d1 * d1 + d2 * d2));//归一化系数
//						complex<double> map_temp[16] = {complex<double>(-3 * d1, -3 * d2), complex<double>(-3 * d1, -1 * d2), complex<double>(-3 * d1, +3 * d2), complex<double>(-3 * d1, +1 * d2), 
//							complex<double>(-1 * d1, -3 * d2), complex<double>(-1 * d1, -1 * d2), complex<double>(-1 * d1, +3 * d2), complex<double>(-1 * d1, +1 * d2),
//							complex<double>(+3 * d1, -3 * d2), complex<double>(+3 * d1, -1 * d2), complex<double>(+3 * d1, +3 * d2), complex<double>(+3 * d1, +1 * d2), 
//							complex<double>(+1 * d1, -3 * d2), complex<double>(+1 * d1, -1 * d2), complex<double>(+1 * d1, +3 * d2), complex<double>(+1 * d1, +1 * d2)};//映射表
//						for (int i = 0; i < 16; i++)
//							map_temp[i] = map_temp[i] * nor_index;
//						int Nsyms = Nbits / modtype;
//						vector<int> nums;
//						//HSI_bits2nums(bitsin, nums, modtype);
//						bits2nums(bitsin, nums, modtype);//比特转换为数字
//						for (int i = 0; i < Nsyms; i++)
//						{
//							int num_temp = nums[i];
//							symsout.push_back(map_temp[num_temp]);
//						}
//						break;
//					}
//				default:
//					{
//						cout<<"调制模式输入错误！"<<endl;
//						exit(EXIT_FAILURE);
//						break;
//					}
//				}
//				break;
//			}
//		case 1:
//			{
//				double d1 = 1.25;
//				double d2 = 1.0;
//				switch (modtype)
//				{
//				case 2:
//					{
//						double nor_index = 1 / sqrt(d1 * d1 + d2 * d2);//归一化系数
//						complex<double> map_temp[4] = {complex<double>(-d1, -d2), complex<double>(+d1, -d2), 
//							complex<double>(-d1, +d2), complex<double>(+d1, +d2)};//映射表
//						for (int i = 0; i < 4; i++)
//							map_temp[i] = map_temp[i] * nor_index;
//						int Nsyms = Nbits / modtype;
//						vector<int> nums;
//						//HSI_bits2nums(bitsin, nums, modtype);
//						bits2nums(bitsin, nums, modtype);//比特转换为数字
//						for (int i = 0; i < Nsyms; i++)
//						{
//							int num_temp = nums[i];
//							symsout.push_back(map_temp[num_temp]);;
//						}
//						break;
//					}
//				case 4:
//					{
//						double nor_index = 1 / sqrt(5 * (d1 * d1 + d2 * d2));//归一化系数
//						complex<double> map_temp[16] = {complex<double>(-3 * d1, -3 * d2), complex<double>(-3 * d1, -1 * d2), complex<double>(-3 * d1, +3 * d2), complex<double>(-3 * d1, +1 * d2), 
//							complex<double>(-1 * d1, -3 * d2), complex<double>(-1 * d1, -1 * d2), complex<double>(-1 * d1, +3 * d2), complex<double>(-1 * d1, +1 * d2),
//							complex<double>(+3 * d1, -3 * d2), complex<double>(+3 * d1, -1 * d2), complex<double>(+3 * d1, +3 * d2), complex<double>(+3 * d1, +1 * d2), 
//							complex<double>(+1 * d1, -3 * d2), complex<double>(+1 * d1, -1 * d2), complex<double>(+1 * d1, +3 * d2), complex<double>(+1 * d1, +1 * d2)};//映射表
//						for (int i = 0; i < 16; i++)
//							map_temp[i] = map_temp[i] * nor_index;
//						int Nsyms = Nbits / modtype;
//						vector<int> nums;
//						//HSI_bits2nums(bitsin, nums, modtype);
//						bits2nums(bitsin, nums, modtype);//比特转换为数字
//						for (int i = 0; i < Nsyms; i++)
//						{
//							int num_temp = nums[i];
//							symsout.push_back(map_temp[num_temp]);
//						}
//						break;
//					}
//				default:
//					{
//						cout<<"调制模式输入错误！"<<endl;
//						exit(EXIT_FAILURE);
//						break;
//					}
//				}
//				break;
//			}
//		case 2:
//			{
//				double d1 = 1.0;
//				double d2 = 1.0;
//				switch (modtype)
//				{
//				case 2:
//					{
//						double nor_index = 1 / sqrt(d1 * d1 + d2 * d2);//归一化系数
//						complex<double> map_temp[4] = {complex<double>(-d1, -d2), complex<double>(+d1, -d2), 
//							complex<double>(-d1, +d2), complex<double>(+d1, +d2)};//映射表
//						for (int i = 0; i < 4; i++)
//							map_temp[i] = map_temp[i] * nor_index;
//						int Nsyms = Nbits / modtype;
//						vector<int> nums;
//						//HSI_bits2nums(bitsin, nums, modtype);
//						bits2nums(bitsin, nums, modtype);//比特转换为数字
//						for (int i = 0; i < Nsyms; i++)
//						{
//							int num_temp = nums[i];
//							//symsout[i] = map_temp[num_temp];
//							symsout.push_back(map_temp[num_temp]);
//						}
//						break;
//					}
//				case 4:
//					{
//						double nor_index = 1 / sqrt(5 * (d1 * d1 + d2 * d2));//归一化系数
//						complex<double> map_temp[16] = {complex<double>(-3 * d1, -3 * d2), complex<double>(-3 * d1, -1 * d2), complex<double>(-3 * d1, +3 * d2), complex<double>(-3 * d1, +1 * d2), 
//							complex<double>(-1 * d1, -3 * d2), complex<double>(-1 * d1, -1 * d2), complex<double>(-1 * d1, +3 * d2), complex<double>(-1 * d1, +1 * d2),
//							complex<double>(+3 * d1, -3 * d2), complex<double>(+3 * d1, -1 * d2), complex<double>(+3 * d1, +3 * d2), complex<double>(+3 * d1, +1 * d2), 
//							complex<double>(+1 * d1, -3 * d2), complex<double>(+1 * d1, -1 * d2), complex<double>(+1 * d1, +3 * d2), complex<double>(+1 * d1, +1 * d2)};//映射表
//						for (int i = 0; i < 16; i++)
//							map_temp[i] = map_temp[i] * nor_index;
//						int Nsyms = Nbits / modtype;
//						vector<int> nums;
//						//HSI_bits2nums(bitsin, nums, modtype);
//						bits2nums(bitsin, nums, modtype);//比特转换为数字
//						for (int i = 0; i < Nsyms; i++)
//						{
//							int num_temp = nums[i];
//							symsout.push_back(map_temp[num_temp]);
//						}
//						break;
//					}
//				default:
//					{
//						cout<<"调制模式输入错误！"<<endl;
//						exit(EXIT_FAILURE);
//					}
//				}
//				break;
//			}
//		default:
//			{
//				cout<<"UEP模式输入错误！"<<endl;
//				exit(EXIT_FAILURE);
//			}
//		}
//	}
//}
//
//void AV_outer_interleaver(vector<int> &codebits, int depth)
//{
//	int Nbits = codebits.size();
//	switch (depth)
//	{
//	case 2:
//		{
//			int* bits_temp = new int [Nbits];
//			//for (int i = 0; i < Nbits; i++)
//			//	bits_temp[i] = codebits[i];//保存输入比特
//			int num_test = Nbits % depth;
//			if (num_test == 0)
//			{
//				const int Row = depth;
//				const int Col = Nbits / depth;
//				int** inter_temp = new int* [Row];
//				for (int i = 0; i < Row; i++)
//					inter_temp[i] = new int [Col];//交织矩阵
//				for (int i = 0; i < Row; i++)
//				{
//					for (int j = 0; j < Col; j++)
//						inter_temp[i][j] = codebits[i * Col + j];//将数据填充至交织矩阵中
//				}
//				for (int i = 0; i < Col; i++)
//				{
//					for (int j = 0; j < Row; j++)
//						codebits[i * Row + j] = inter_temp[j][i];//按列输出
//				}
//				for (int i = 0; i < Row; i++)
//					delete [] inter_temp[i];
//				delete [] inter_temp;
//			}
//			else
//			{
//				cout << "输入比特数量错误！" << endl;
//				exit(EXIT_FAILURE);
//			}
//			break;
//		}
//	case 4:
//		{
//			int* bits_temp = new int [Nbits];
//			//for (int i = 0; i < Nbits; i++)
//			//	bits_temp[i] = codebits[i];//保存输入比特
//			int num_test = Nbits % depth;
//			if (num_test == 0)
//			{
//				const int Row = depth;
//				const int Col = Nbits / depth;
//				int** inter_temp = new int* [Row];
//				for (int i = 0; i < Row; i++)
//					inter_temp[i] = new int [Col];//交织矩阵
//				for (int i = 0; i < Row; i++)
//				{
//					for (int j = 0; j < Col; j++)
//						inter_temp[i][j] = codebits[i * Col + j];//将数据填充至交织矩阵中
//				}
//				for (int i = 0; i < Col; i++)
//				{
//					for (int j = 0; j < Row; j++)
//						codebits[i * Row + j] = inter_temp[j][i];//按列输出
//				}
//				for (int i = 0; i < Row; i++)
//					delete [] inter_temp[i];
//				delete [] inter_temp;
//			}
//			else
//			{
//				cout << "输入比特数量错误！" << endl;
//				exit(EXIT_FAILURE);
//			}
//			break;
//		}
//	default:
//		{
//			cout << "交织模式输入错误！" << endl;
//			exit(EXIT_FAILURE);
//		}
//	}
//}
//
//void AV_inner_interleaver(vector<int> &codebits, int ueptype)
//{
//	switch (ueptype)
//	{
//	case 0:
//		{
//			vector<int> bits_temp;
//			for (int i = 0; i < codebits.size(); i++)
//				bits_temp.push_back(codebits[i]);//保存输入比特
//			for (int i = 0; i < 48; i++)
//			{
//				int index =  mod((6 * floor(i * 1.0 / 6) - 5 * mod(i, 6)), 48);//交织规则
//				codebits[index] = bits_temp[i];
//			}
//			break;
//		}
//	case 1:
//		{
//			vector<int> bits_temp_01;
//			vector<int> bits_temp_02;
//			vector<int> bits_temp_01_inter (48, 0);
//			vector<int> bits_temp_02_inter (48, 0);
//			vector<int> bits_temp;
//			for (int i = 0; i < codebits.size(); i++)
//				bits_temp.push_back(codebits[i]);//保存输入比特
//			for (int i = 0; i < 4; i++)
//			{
//				for (int j = 0; j < 7; j++)
//					bits_temp_01.push_back(bits_temp[14 * i + j]);
//			}
//			for (int i = 0; i < 4; i++)
//			{
//				for (int j = 0; j < 5; j++)
//					bits_temp_01.push_back(bits_temp[56 + 10 * i + j]);
//			}//按协议保存上半48比特
//			for (int i = 0; i < 3; i++)
//			{
//				for (int j = 0; j < 7; j++)
//					bits_temp_02.push_back(bits_temp[14 + 14 * i + 7 + j]);
//			}
//			for (int i = 0; i < 7; i++)
//				bits_temp_02.push_back(bits_temp[7 + i]);
//			for (int i = 0; i < 3; i++)
//			{
//				for (int j = 0; j < 5; j++)
//					bits_temp_02.push_back(bits_temp[56 + 10 * (i + 1) + 5 + j]);
//			}
//			for (int i = 0; i < 5; i++)
//				//bits_temp_02[43 + i] = bits_temp[61 + i];
//				bits_temp_02.push_back(bits_temp[61 + i]);//按协议填充下半48比特
//			for (int i = 0; i < 48; i++)//上半48比特交织
//			{
//				int index =  mod((6 * floor(i * 1.0 / 6) - 5 * mod(i, 6)), 48);//交织规则
//				bits_temp_01_inter[index] = bits_temp_01[i];
//				bits_temp_02_inter[index] = bits_temp_02[i];
//			}
//			for (int i = 0; i < 48; i++)
//			{
//				codebits[i] = bits_temp_01_inter[i];
//				codebits[48 + i] = bits_temp_02_inter[i];
//			}
//			break;
//		}
//	default:
//		{
//			cout << "UEP模式输入错误!" << endl;
//			exit(EXIT_FAILURE);
//		}
//	}
//}
//
//void AV_multiplexer(vector<int> &bitsout, int ueptype, vector<int> &A, vector<int> &B, vector<int> &C, vector<int> &D, vector<int> &E, vector<int> &F, vector<int> &G, vector<int> &H)
//{
//	switch (ueptype)
//	{
//	case 0:
//		{
//			int N_upper = A.size();
//			int N_lower = E.size();
//			int test = N_upper % 6;
//			if ((test == 0) && (N_upper == N_lower))
//			{
//				int Nblocks = N_upper / 6;
//				vector<int> mul_temp (48, 0);
//				for (int i = 0; i < Nblocks; i++)
//				{
//					for (int j = 0; j < 6; j++)//每个卷积编码器的六个比特复合成一个48bit数据块
//					{
//						mul_temp[j] = A[6 * i + j];
//						mul_temp[6 + j] = B[6 * i + j];
//						mul_temp[12 + j] = C[6 * i + j];
//						mul_temp[18 + j] = D[6 * i + j];
//						mul_temp[24 + j] = E[6 * i + j];
//						mul_temp[30 + j] = F[6 * i + j];
//						mul_temp[36 + j] = G[6 * i + j];
//						mul_temp[42 + j] = H[6 * i + j];
//					}
//					AV_inner_interleaver(mul_temp, ueptype);//对数据块进行交织
//					for (int j = 0; j < 48; j++)
//						bitsout.push_back(mul_temp[j]);
//				}
//			}
//			else
//			{
//				cout << "比特数输入错误！" << endl;
//				exit(EXIT_FAILURE);
//			}
//			break;
//		}
//	case 1:
//		{
//			int N_upper = A.size();
//			int N_lower = E.size();
//			int test_01 = N_upper % 14;
//			int test_02 = N_lower % 10;
//			if ((test_01 == 0) && (test_02 == 0))
//			{
//				int Nblocks = N_upper / 14;
//				vector<int> mul_temp (96, 0);
//				for (int i = 0; i < Nblocks; i++)
//				{
//					for (int j = 0; j < 14; j++)//八个卷积编码器的比特复合成一个96bit数据块
//					{
//						mul_temp[j] = A[14 * i + j];
//						mul_temp[14 + j] = B[14 * i + j];
//						mul_temp[28 + j] = C[14 * i + j];
//						mul_temp[42 + j] = D[14 * i + j];
//					}
//					for (int j = 0; j < 10; j++)
//					{
//						mul_temp[56 + j] = E[10 * i + j];
//						mul_temp[66 + j] = F[10 * i + j];
//						mul_temp[76 + j] = G[10 * i + j];
//						mul_temp[86 + j] = H[10 * i + j];
//					}
//					AV_inner_interleaver(mul_temp, ueptype);//对数据块进行交织
//					for (int j = 0; j < 96; j++)
//						//bitsout[96 * i + j] = mul_temp[j];
//						bitsout.push_back(mul_temp[j]);
//				}
//			}
//			else
//			{
//				cout << "比特数输入错误！" << endl;
//				exit(EXIT_FAILURE);
//			}
//			break;
//		}
//	case 2:
//		{
//			int Nblocks = A.size() / 12;
//			for (int i = 0; i < Nblocks; ++i)
//			{
//				vector<int> inter_temp;
//				for (int j = 0; j < 6; ++j)
//					inter_temp.push_back(A[12 * i + 2 * j + 1]);
//				for (int j = 0; j < 6; ++j)
//					inter_temp.push_back(B[12 * i + 2 * j + 1]);
//				for (int j = 0; j < 6; ++j)
//					inter_temp.push_back(C[12 * i + 2 * j + 1]);
//				for (int j = 0; j < 6; ++j)
//					inter_temp.push_back(D[12 * i + 2 * j + 1]);
//				for (int j = 0; j < 6; ++j)
//					inter_temp.push_back(A[12 * i + 2 * j]);
//				for (int j = 0; j < 6; ++j)
//					inter_temp.push_back(B[12 * i + 2 * j]);
//				for (int j = 0; j < 6; ++j)
//					inter_temp.push_back(C[12 * i + 2 * j]);
//				for (int j = 0; j < 6; ++j)
//					inter_temp.push_back(D[12 * i + 2 * j]);
//				AV_inner_interleaver(inter_temp, 0);//按EEP交织规则交织
//				for (int j = 0; j < 48; ++j)
//					bitsout.push_back(inter_temp[j]);
//			}
//			break;
//		}
//	default:
//		{
//			cout << "UEP模式输入错误！" << endl;
//			exit(EXIT_FAILURE);
//			break;
//		}
//	}
//}
//
//void AV_OFDMer(vector<complex<double> > &symsin, vector<complex<double> > &symsout)
//{
//	int nums_in = symsin.size();
//	const int Nstuff = ceil(nums_in / 336.0) * 336 - nums_in;
//	for (int i = 0; i < Nstuff; ++i)
//		symsin.push_back(complex<double>(0.0,0.0));//填充零
//	int nums = Nstuff + nums_in;//填充后的符号个数
//	int fft_size = 512;
//	int Nsyms = symsin.size();//符号长度
//	int Nblocks = Nsyms / 336;//数据块个数
//	int index_null[157] = {0};//零频位置
//	for (int i = 0; i < 79; ++i)
//		index_null[i] = i;
//	for (int i = 0; i < 78; ++i)
//		index_null[79 + i] = 434 + i;
//	int index_dc[3] = {255, 256, 257};//直流位置
//	vector<vector<int> > index_pl;//导频位置
//	for (int i = 0; i < 22; ++i)
//	{
//		vector<int> dc_temp;
//		int temp_dc = 0;
//		int temp_cnt = 0;
//		for (int j = 0; j < 16; ++j)
//		{
//			temp_dc = 79 + mod((3 * i), 22) + temp_cnt * 22;
//			if (((temp_dc != 255) && (temp_dc != 256)) && (temp_dc != 257))
//				dc_temp.push_back(temp_dc);
//			else
//				--j;
//			++temp_cnt;
//		}
//		index_pl.push_back(dc_temp);
//	}
//	for (int i = 0; i < Nblocks; ++i)
//	{
//		vector<complex<double> > syms_temp (512, complex<double> (0,0));
//		int Nsyms_temp = mod(i, 22);//根据符号标号选择填充载波的位置
//		int index_temp[512] = {0};//填充零频
//		for (int j = 0; j < 157; ++j)
//			index_temp[index_null[j]] = 1;
//		for (int j = 0; j < 3; ++j)
//			index_temp[255 + j] = 1;
//		for (int j = 0; j < 16; ++j)//填充导频
//		{
//			index_temp[index_pl[Nsyms_temp][j]] = 1;
//			syms_temp[index_pl[Nsyms_temp][j]] = complex<double> (1, 0);
//		}
//		int syms_cnt = 0;
//		for (int j = 0; j < 512; ++j)
//		{
//			if (index_temp[j] == 0)
//			{
//				syms_temp[j] = symsin[i * 336 + syms_cnt];
//				++syms_cnt;
//			}
//		}
//		HSI_toneinter(syms_temp);
//		IFFT(syms_temp, fft_size);
//		for (int j = 0; j < 64; ++j)//循环前缀64
//			symsout.push_back(syms_temp[j] * sqrt(512.0));
//		for (int j = 0; j < 512; ++j)
//			symsout.push_back(syms_temp[j] * sqrt(512.0));
//	}
//}
//
//void AV_conencoder(vector<int> &in_upper, vector<int> &in_lower, vector<int> &con_A, vector<int> &con_B, vector<int> &con_C, vector<int> &con_D, vector<int> &con_E, vector<int> &con_F, vector<int> &con_G, vector<int> &con_H, int rate_up, int rate_low,int ueptype)
//{
//	switch (ueptype)
//	{
//	case 0:
//		{
//			int Nbits = in_upper.size() / 4;//每个卷积编码器的比特数
//			vector<int> temp_A (Nbits, 0);
//			vector<int> temp_B (Nbits, 0);
//			vector<int> temp_C (Nbits, 0);
//			vector<int> temp_D (Nbits, 0);
//			vector<int> temp_E (Nbits, 0);
//			vector<int> temp_F (Nbits, 0);
//			vector<int> temp_G (Nbits, 0);
//			vector<int> temp_H (Nbits, 0);
//			for (int i = 0; i < Nbits; ++i)
//			{
//				temp_A[i] = in_upper[i];
//				temp_B[i] = in_upper[Nbits * 1 + i];
//				temp_C[i] = in_upper[Nbits * 2 + i];
//				temp_D[i] = in_upper[Nbits * 3 + i];
//				temp_E[i] = in_upper[i];
//				temp_F[i] = in_lower[Nbits * 1 + i];
//				temp_G[i] = in_lower[Nbits * 2 + i];
//				temp_H[i] = in_lower[Nbits * 3 + i];
//			}
//			conencoder(temp_A, con_A, rate_up);
//			conencoder(temp_B, con_B, rate_up);
//			conencoder(temp_C, con_C, rate_up);
//			conencoder(temp_D, con_D, rate_up);
//			conencoder(temp_E, con_E, rate_low);
//			conencoder(temp_F, con_F, rate_low);
//			conencoder(temp_G, con_G, rate_low);
//			conencoder(temp_H, con_H, rate_low);
//			break;
//		}
//	case 1:
//		{
//			int Nbits = in_upper.size() / 4;//每个卷积编码器的比特数
//			vector<int> temp_A (Nbits, 0);
//			vector<int> temp_B (Nbits, 0);
//			vector<int> temp_C (Nbits, 0);
//			vector<int> temp_D (Nbits, 0);
//			vector<int> temp_E (Nbits, 0);
//			vector<int> temp_F (Nbits, 0);
//			vector<int> temp_G (Nbits, 0);
//			vector<int> temp_H (Nbits, 0);
//			for (int i = 0; i < Nbits; ++i)
//			{
//				temp_A[i] = in_upper[i];
//				temp_B[i] = in_upper[Nbits * 1 + i];
//				temp_C[i] = in_upper[Nbits * 2 + i];
//				temp_D[i] = in_upper[Nbits * 3 + i];
//				temp_E[i] = in_upper[i];
//				temp_F[i] = in_lower[Nbits * 1 + i];
//				temp_G[i] = in_lower[Nbits * 2 + i];
//				temp_H[i] = in_lower[Nbits * 3 + i];
//			}
//			conencoder(temp_A, con_A, rate_up);
//			conencoder(temp_B, con_B, rate_up);
//			conencoder(temp_C, con_C, rate_up);
//			conencoder(temp_D, con_D, rate_up);
//			conencoder(temp_E, con_E, rate_low);
//			conencoder(temp_F, con_F, rate_low);
//			conencoder(temp_G, con_G, rate_low);
//			conencoder(temp_H, con_H, rate_low);
//			break;
//		}
//	case 2:
//		{
//			int Nbits = in_upper.size() / 4;//每个卷积编码器的比特数
//			vector<int> temp_A (Nbits, 0);
//			vector<int> temp_B (Nbits, 0);
//			vector<int> temp_C (Nbits, 0);
//			vector<int> temp_D (Nbits, 0);
//			for (int i = 0; i < Nbits; ++i)
//			{
//				temp_A[i] = in_upper[i];
//				temp_B[i] = in_upper[Nbits * 1 + i];
//				temp_C[i] = in_upper[Nbits * 2 + i];
//				temp_D[i] = in_upper[Nbits * 3 + i];
//			}
//			conencoder(temp_A, con_A, rate_up);
//			conencoder(temp_B, con_B, rate_up);
//			conencoder(temp_C, con_C, rate_up);
//			conencoder(temp_D, con_D, rate_up);
//			break;
//		}
//	default:
//		{
//			cout << "UEP模式选择错误！！！！" << endl;
//			exit(EXIT_FAILURE);
//			break;
//		}
//	}
//}
//
//void waveform_generator_3c(vector<int> &macheader, vector<int> &macbody, vector<complex<double>> &dataout, Protocol_param_3C &param_3c)
//{
//	if (param_3c.Sig_mode == SC)
//	{
//		genSC(macbody, macheader, dataout, param_3c.SC_p);
//	}
//	else if (param_3c.Sig_mode == HSI)
//	{
//		genHSI(macbody, macheader, dataout, param_3c.HSI_p);
//	}
//	else if (param_3c.Sig_mode == AV)
//	{
//		genAV(macbody, macheader, dataout, param_3c.AV_p);
//	}
//	else 
//	{
//		exit(EXIT_FAILURE);
//	}
//}
//
//int gen_lmh_3c(Protocol_param_3C& params_3c)
//{
//	if (params_3c.Sig_mode == SC)
//		return params_3c.SC_p.L_mh;
//	else if (params_3c.Sig_mode == HSI)
//		return params_3c.HSI_p.L_mh;
//	else if (params_3c.Sig_mode == AV)
//		return params_3c.AV_p.L_mh;
//	else
//		exit(EXIT_FAILURE);
//}
//
//int gen_lmb_3c(Protocol_param_3C& params_3c)
//{
//	if (params_3c.Sig_mode == SC)
//		return params_3c.SC_p.L_mb;
//	else if (params_3c.Sig_mode == HSI)
//		return params_3c.HSI_p.L_mb;
//	else if (params_3c.Sig_mode == AV)
//		return params_3c.AV_p.L_mb;
//	else
//		exit(EXIT_FAILURE);
//}