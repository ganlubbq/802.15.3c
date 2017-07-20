#include "stdafx.h"
#include "BlueToothProtocal.h"

int intmax(int a,int b) {return a>b?a:b;}
int intmin(int a,int b) {return a<b?a:b;}

void conv(double u[],double v[],double w[], int m, int n)  
{  
	int i, j;  

	int k = m+n-1; 

	for(i=0; i<k; i++)
	{  
		for(j=intmax(0,i+1-n); j<=intmin(i,m-1); j++)
		{     
			w[i] += u[j]*v[i-j];  
		}  

		//printf("%f\n",w[i]);  
	}  
}   

double erf_fuction(double in)
{
	double out=0;
	double erf_i;
	int calcul_num=10000;

	for (erf_i=1;erf_i<=calcul_num;erf_i++)
	{
		out += 2/sqrt(bluetooth_pi)*exp(double(-1*pow(double((erf_i-1/2)*in/calcul_num),2.0)))*in/calcul_num;
	}

	return out;	
}

void Tentotwo_fuction(int data_in,int length,char data_out[])//右为高位。
{
	int i;
	for (i=0;i<length;i++)
	{
		if(data_in/int(pow(2.0,length-1-i))!=0)
		{
			data_in=data_in-int(pow(2.0,length-1-i));
			data_out[length-i-1]=1;
		}
		else data_out[length-i-1]=0;
	}
}

void Gauss_fuction(double Rs,int oversample, int irfn,double Gauss_out[])
{
	int gauss_i;
	double Bwith=0.5*Rs;
	int n=irfn*oversample;

	int mid_point=(n/2)+1;
	double F0=Bwith/sqrt(2*log(2.0));
	double icon=0;

	for (gauss_i=1;gauss_i<=n;gauss_i++)
	{
		icon=gauss_i-mid_point;
		Gauss_out[gauss_i-1]=1.0/2*(erf_fuction(-sqrt(2.0/log(2.0))*bluetooth_pi*Bwith*((icon/oversample-1.0/2)/Rs))+erf_fuction(sqrt(2.0/log(2.0))*bluetooth_pi*Bwith*((icon/oversample+1.0/2)/Rs)));
		//	    printf("%f\n",(icon/oversample+1.0/2));

	}

	/*	for(int i=0;i<10;i++)
	{
	printf("%f\n",Gauss_out[i]);
	}
	*/
}

void Inversion(char data_in[] ,int data_len,char data_out[])
{
	int i;

	if(data_len%2==0)
	{
		for(i=0;i<data_len/2;i++)
		{
			data_out[data_len-1-i]=data_in[i];
			data_out[i]=data_in[data_len-1-i];
		}
	}

	else
	{
		data_out[(data_len-1)/2]=data_in[(data_len-1)/2];

		for(i=0;i<(data_len-1)/2;i++)
		{
			data_out[data_len-1-i]=data_in[i];
			data_out[i]=data_in[data_len-1-i];
		}
	}

}

void Deconv(char data_in[],char data_indiv[],char data_out[],int data_in_len,int data_indiv_len)
{
	int i,k;
	char *data_tmp;

	data_tmp=(char *)calloc(data_in_len,sizeof(char));

	for(i=0;i<data_in_len;i++)
	{
		data_tmp[i]=data_in[i];
	}

	for(i=0;i<=data_in_len-data_indiv_len;i++)
	{
		if(data_tmp[i]!=0)
		{
			for(k=0;k<data_indiv_len;k++)
			{
				data_tmp[i+k]=(data_tmp[i+k]+data_indiv[k])%2;
			}
			data_out[i]=1;
		}
	}

	for(i=data_in_len-data_indiv_len+1;i<data_in_len;i++)
	{
		data_out[i]=data_tmp[i];
	}

	free(data_tmp);
	data_tmp=NULL;
}

void bluetooth_CRC16(char data_in[],int data_len,char CRC_statein[],char CRC_out[])
{
	char CRC_state[16]={0};
	int i,k;
	int CRC_len=16;

	for(i=0;i<data_len;i++)
	{
		CRC_state[0]=data_in[i];
		CRC_state[1]=CRC_statein[0];
		CRC_state[2]=CRC_statein[1];
		CRC_state[3]=CRC_statein[2];
		CRC_state[4]=CRC_statein[3];
		CRC_state[5]=(CRC_statein[4]+data_in[i])%2;
		CRC_state[6]=CRC_statein[5];
		CRC_state[7]=CRC_statein[6];
		CRC_state[8]=CRC_statein[7];
		CRC_state[9]=CRC_statein[8];
		CRC_state[10]=CRC_statein[9];
		CRC_state[11]=CRC_statein[10];
		CRC_state[12]=CRC_statein[11];
		CRC_state[13]=(CRC_statein[12]+data_in[i])%2;
		CRC_state[14]=CRC_statein[13];
		CRC_state[15]=CRC_statein[14];

		for (k=0;k<CRC_len;k++)
		{
			CRC_statein[k]=CRC_state[k];
		}
	}

	for (k=0;k<CRC_len;k++)
	{
		CRC_out[k]=CRC_state[k];
	}

}

void bluetooth_HEC8(char data_in[],int data_len,char HEC_statein[],char HEC_out[])
{
	char HEC_state[8]={0};
	int i,k;
	int HEC_len=8;

	for(i=0;i<data_len;i++)
	{
		HEC_state[0]=data_in[i];
		HEC_state[1]=(HEC_statein[0]+data_in[i])%2;
		HEC_state[2]=(HEC_statein[1]+data_in[i])%2;
		HEC_state[3]=HEC_statein[2];
		HEC_state[4]=HEC_statein[3];
		HEC_state[5]=(HEC_statein[4]+data_in[i])%2;
		HEC_state[6]=HEC_statein[5];
		HEC_state[7]=(HEC_statein[6]+data_in[i])%2;

		for (k=0;k<HEC_len;k++)
		{
			HEC_statein[k]=HEC_state[k];
		}
	}

	for (k=0;k<HEC_len;k++)
	{
		HEC_out[k]=HEC_state[k];
	}
}

void bluetooth_whitening(char data_in[],int data_len,char whiten_state[],char whiten_out[])
{
	int i;
	int whiten_len=7;
	char whiten_tmp;

	for(i=0;i<data_len;i++)
	{
		whiten_out[i]=(data_in[i]+whiten_state[6])%2;
		whiten_tmp=whiten_state[6];
		whiten_state[6]=whiten_state[5];
		whiten_state[5]=whiten_state[4];
		whiten_state[4]=(whiten_state[3]+whiten_state[6])%2;
		whiten_state[3]=whiten_state[2];
		whiten_state[2]=whiten_state[1];
		whiten_state[1]=whiten_state[0];
		whiten_state[0]=whiten_tmp;

	}
}

void bluetooth_FEC_encode(char data_in[],int data_len,double code_rate,char encode_out[],int encode_len, char EFC_statein[])
{
	int i,k,j;
	int basiccode_len=10;
	int EFC_state_len=5;
	char EFC_state[5]={0};

	if(code_rate==1/3)
	{
		for(i=0;i<data_len;i++)
		{
			for(k=0;k<3;k++)
			{
				encode_out[3*i+k]=data_in[i];
			}
		}
	}
	else if(code_rate==2/3)
	{

		if(data_len%basiccode_len!=0)
		{
			for(i=0;i<basiccode_len-data_len%10;i++)
			{
				encode_out[data_len+i]=0;
			}

			for(i=0;i<ceil(double (data_len)/basiccode_len);i++)
			{
				for(k=0;k<basiccode_len;k++)
				{
					encode_out[i*(basiccode_len+EFC_state_len)+k]=EFC_state[4];

					EFC_state[0]=data_in[i];
					EFC_state[1]=EFC_statein[0];
					EFC_state[2]=(EFC_statein[1]+data_in[i])%2;
					EFC_state[3]=EFC_statein[2];
					EFC_state[4]=(EFC_statein[3]+data_in[i])%2;

					for (j=0;j<EFC_state_len;j++)
					{
						EFC_statein[j]=EFC_state[j];
					}
				}

				for(k=0;k<EFC_state_len;k++)
				{
					encode_out[i*(basiccode_len+EFC_state_len)+k+basiccode_len]=EFC_state[EFC_state_len-k-1];
				}
			}
		}
	}
	else printf("Wrong code rate,the system only support 1/3 and 2/3");
}

void bluetooth_access_sync_generator( char Lap_addr[],int Lap_addr_len,char sync_out[])
{
	char G_ploy[35]={1,0,1,1,0,0,0,0,1,0,1,0,1,1,1,0,0,0,1,0,0,1,1,1,1,0,1,1,0,1,0,1,0,0,1};//[10 110 000 101 011 100 010 011 110 110 101 001]
	char P_ploy[64]={0,0,1,1,1,1,1,1,0,0,1,0,1,0,1,0,0,0,1,1,0,0,1,1,1,1,0,1,1,1,0,1,0,1,1,0,1,0,0,1,1,0,1,1,0,0,0,1,0,0,1,0,0,0,0,1,1,1,0,0,0,0,0,1};//[0011 1111 0010 1010 0011 0011 1101 1101 0110 1001 1011 0001 0010 0001 1100 0001]
	char P_ploy_inver[64]={0};
	char datastr[64]={0};
	char Append_bit[6]={0};
	char Append_bit_inver[6]={0};
	char Append_bit0[6]={0,0,1,1,0,1};
	char Append_bit1[6]={1,1,0,0,1,0};
	char x_str[64]={0};
	char x_deconvstr[64]={0};
	//char scramb_x_data[30]={0};

	int i;
	int Append_bit_len=6;
	int x_str_len=64;
	int sync_out_len=64;
	int P_ploy_len=64;
	int G_ploy_len=35;

	if(Lap_addr[0]==0) 
		for(i=0;i<Append_bit_len;i++)
		{
			Append_bit[i]=Append_bit0[i];
		}
	else 
		for(i=0;i<Append_bit_len;i++)
		{
			Append_bit[i]=Append_bit1[i];
		}

		Inversion(Append_bit,Append_bit_len,Append_bit_inver);
		Inversion(P_ploy,P_ploy_len,P_ploy_inver);

		for (i=0;i<Append_bit_len;i++)	
		{
			x_str[i]=(Append_bit_inver[i]+P_ploy_inver[G_ploy_len+i-1])%2;
		}
		for (i=Append_bit_len;i<Append_bit_len+Lap_addr_len;i++)	
		{
			x_str[i]=(Lap_addr[i-Append_bit_len]+P_ploy_inver[G_ploy_len+i-1])%2;
		}

		Deconv(x_str,G_ploy,x_deconvstr,x_str_len,G_ploy_len);


		for(i=Append_bit_len+Lap_addr_len;i<sync_out_len;i++)	
		{
			x_str[i]=x_deconvstr[i];
		}

		for(i=0;i<sync_out_len;i++)
		{
			x_str[i]=(P_ploy_inver[i]+x_str[i])%2;
		}

		Inversion(x_str,sync_out_len,sync_out);
}

void bluetooth_access_preamble_generator( char pream_sync_data[] ,char preamble_out[])
{
	int i;
	int sync_len=64;
	char preamble0[4]={0,1,0,1};
	char preamble1[4]={1,0,1,0};

	for(i=0;i<sync_len;i++) preamble_out[4+i]=pream_sync_data[i];


	if(pream_sync_data[0]==1)
	{
		for(i=0;i<4;i++) preamble_out[i]=preamble1[i];
	}
	else
	{
		for(i=0;i<4;i++) preamble_out[i]=preamble0[i];
	}
}

void bluetooth_trailer_generator( char data_in[],char data_out[],int datain_len)
{
	int i;
	char trailer0[4]={0,1,0,1};
	char trailer1[4]={1,0,1,0};

	for(i=0;i<datain_len;i++) data_out[i]=data_in[i];


	if(data_in[datain_len-1]==0)
	{
		for(i=0;i<4;i++) data_out[i]=trailer1[i];
	}
	else
	{
		for(i=0;i<4;i++) data_out[i]=trailer0[i];
	}
}

void bluetooth_access_trailer_generator( char preamble_data[],char pream_sync_trailer[])
{
	int i;
	int preamble_len=4;;
	int sync_len=64;

	char trailer0[4]={0,1,0,1};
	char trailer1[4]={1,0,1,0};

	for(i=0;i<preamble_len+sync_len;i++) pream_sync_trailer[i]=preamble_data[i];


	if(preamble_data[preamble_len-1]==0)
	{
		for(i=0;i<4;i++) pream_sync_trailer[i]=trailer1[i];
	}
	else
	{
		for(i=0;i<4;i++) pream_sync_trailer[i]=trailer0[i];
	}
}

void bluetooth_header_generator(Packettype Packettype,Transtype transtype,char ltaddress[],char HEC_state[],char Header_out[],int Header_len,char EFC_state[])
{
	int i;

	if(transtype==BlueTooth_SCO)
	{
		switch(Packettype)
		{
		case NuLLpack:
			{
				int EFC_len=18;
				double coderate=1/3;
				char Sequen[10]={0};                         //Sequen=[Lt_addr Type Flow Arqn Seqn];
				char Type[4]={0,0,0,0};
				char HEC[8]={0};
				char HEC_data[18]={0};

				for (i=0;i<3;i++) Sequen[i]=0;                //Lt_addr=0
				for (i=3;i<7;i++) Sequen[i]=Type[i-3];         //Type
				Sequen[7]=0;                                 //Flow
				Sequen[8]=0;                                 //Arqn
				Sequen[9]=0;                                 //Seqn

				bluetooth_HEC8(Sequen,10,HEC_state,HEC);

				for(i=0;i<10;i++) HEC_data[i]=Sequen[i];
				for(i=10;i<EFC_len;i++) HEC_data[i]=HEC[i];
				bluetooth_FEC_encode(HEC_data, EFC_len, coderate, Header_out, Header_len, EFC_state);

				break;
			}

		case POLL:
			{
				int EFC_len=18;
				double coderate=1/3;
				char Sequen[10]={0};                         //Sequen=[Lt_addr Type Flow Arqn Seqn];
				char Type[4]={1,0,0,0};
				char HEC[8]={0};
				char HEC_data[18]={0};

				for (i=0;i<3;i++) Sequen[i]=0;                //Lt_addr=0
				for (i=3;i<7;i++) Sequen[i]=Type[i-3];         //Type
				Sequen[7]=0;                                 //Flow
				Sequen[8]=0;                                 //Arqn
				Sequen[9]=0;                                 //Seqn

				bluetooth_HEC8(Sequen,10,HEC_state,HEC);

				for(i=0;i<10;i++) HEC_data[i]=Sequen[i];
				for(i=10;i<EFC_len;i++) HEC_data[i]=HEC[i];
				bluetooth_FEC_encode(HEC_data, EFC_len, coderate, Header_out, Header_len, EFC_state);

				break;
			}



		case HV1:
			{
				int EFC_len=18;
				double coderate=1/3;
				char Sequen[10]={0};                         //Sequen=[Lt_addr Type Flow Arqn Seqn];
				char Type[4]={1,0,1,0};
				char HEC[8]={0};
				char HEC_data[18]={0};

				for (i=0;i<3;i++) Sequen[i]=0;               //Lt_addr=0
				for (i=3;i<7;i++) Sequen[i]=Type[i-3];         //Type
				Sequen[7]=0;                                 //Flow
				Sequen[8]=0;                                 //Arqn
				Sequen[9]=0;                                 //Seqn

				bluetooth_HEC8(Sequen,10,HEC_state,HEC);

				for(i=0;i<10;i++) HEC_data[i]=Sequen[i];
				for(i=10;i<EFC_len;i++) HEC_data[i]=HEC[i-10];
				bluetooth_FEC_encode(HEC_data, EFC_len, coderate, Header_out, Header_len, EFC_state);

				break;
			}

		case HV2:
			{
				int EFC_len=18;
				double coderate=1/3;
				char Sequen[10]={0};                         //Sequen=[Lt_addr Type Flow Arqn Seqn];
				char Type[4]={0,1,1,0};
				char HEC[8]={0};
				char HEC_data[18]={0};

				for (i=0;i<3;i++) Sequen[i]=0;               //Lt_addr=0
				for (i=3;i<7;i++) Sequen[i]=Type[i-3];         //Type
				Sequen[7]=0;                                 //Flow
				Sequen[8]=0;                                 //Arqn
				Sequen[9]=0;                                 //Seqn

				bluetooth_HEC8(Sequen,10,HEC_state,HEC);

				for(i=0;i<10;i++) HEC_data[i]=Sequen[i];
				for(i=10;i<EFC_len;i++) HEC_data[i]=HEC[i-10];
				bluetooth_FEC_encode(HEC_data, EFC_len, coderate, Header_out, Header_len, EFC_state);

				break;
			}

		case HV3:
			{
				int EFC_len=18;
				double coderate=1/3;
				char Sequen[10]={0};                         //Sequen=[Lt_addr Type Flow Arqn Seqn];
				char Type[4]={1,1,1,0};
				char HEC[8]={0};
				char HEC_data[18]={0};

				for (i=0;i<3;i++) Sequen[i]=0;               //Lt_addr=0
				for (i=3;i<7;i++) Sequen[i]=Type[i-3];         //Type
				Sequen[7]=0;                                 //Flow
				Sequen[8]=0;                                 //Arqn
				Sequen[9]=0;                                 //Seqn

				bluetooth_HEC8(Sequen,10,HEC_state,HEC);

				for(i=0;i<10;i++) HEC_data[i]=Sequen[i];
				for(i=10;i<EFC_len;i++) HEC_data[i]=HEC[i-10];
				bluetooth_FEC_encode(HEC_data, EFC_len, coderate, Header_out, Header_len, EFC_state);

				break;
			}

		case DM1:
			{
				int EFC_len=18;
				double coderate=1/3;
				char Sequen[10]={0};                         //Sequen=[Lt_addr Type Flow Arqn Seqn];
				char Type[4]={1,1,0,0};
				char HEC[8]={0};
				char HEC_data[18]={0};

				for (i=0;i<3;i++) Sequen[i]=0;               //Lt_addr=0
				for (i=3;i<7;i++) Sequen[i]=Type[i-3];         //Type
				Sequen[7]=0;                                 //Flow
				Sequen[8]=0;                                 //Arqn
				Sequen[9]=0;                                 //Seqn

				bluetooth_HEC8(Sequen,10,HEC_state,HEC);

				for(i=0;i<10;i++) HEC_data[i]=Sequen[i];
				for(i=10;i<EFC_len;i++) HEC_data[i]=HEC[i-10];
				bluetooth_FEC_encode(HEC_data, EFC_len, coderate, Header_out, Header_len, EFC_state);

				break;
			}

		default: printf("Wrong packet type in SCO");
		}

	}

	else if(transtype==BlueTooth_ACL)
	{
		switch(Packettype)
		{
		case NuLLpack:
			{
				int EFC_len=18;
				double coderate=1/3;
				char Sequen[10]={0};                         //Sequen=[Lt_addr Type Flow Arqn Seqn];
				char Type[4]={0,0,0,0};
				char HEC[8]={0};
				char HEC_data[18]={0};

				for (i=0;i<3;i++) Sequen[i]=0;               //Lt_addr=0
				for (i=3;i<7;i++) Sequen[i]=Type[i-3];         //Type
				Sequen[7]=0;                                 //Flow
				Sequen[8]=0;                                 //Arqn
				Sequen[9]=0;                                 //Seqn

				bluetooth_HEC8(Sequen,10,HEC_state,HEC);

				for(i=0;i<10;i++) HEC_data[i]=Sequen[i];
				for(i=10;i<EFC_len;i++) HEC_data[i]=HEC[i-10];
				bluetooth_FEC_encode(HEC_data, EFC_len, coderate, Header_out, Header_len, EFC_state);

				break;
			}

		case POLL:
			{
				int EFC_len=18;
				double coderate=1/3;
				char Sequen[10]={0};                         //Sequen=[Lt_addr Type Flow Arqn Seqn];
				char Type[4]={1,0,0,0};
				char HEC[8]={0};
				char HEC_data[18]={0};

				for (i=0;i<3;i++) Sequen[i]=0;               //Lt_addr=0
				for (i=3;i<7;i++) Sequen[i]=Type[i-3];         //Type
				Sequen[7]=0;                                 //Flow
				Sequen[8]=0;                                 //Arqn
				Sequen[9]=0;                                 //Seqn

				bluetooth_HEC8(Sequen,10,HEC_state,HEC);

				for(i=0;i<10;i++) HEC_data[i]=Sequen[i];
				for(i=10;i<EFC_len;i++) HEC_data[i]=HEC[i-10];
				bluetooth_FEC_encode(HEC_data, EFC_len, coderate, Header_out, Header_len, EFC_state);

				break;
			}

		case DM1:
			{
				int EFC_len=18;
				double coderate=1/3;
				char Sequen[10]={0};                         //Sequen=[Lt_addr Type Flow Arqn Seqn];
				char Type[4]={1,1,0,0};
				char HEC[8]={0};
				char HEC_data[18]={0};

				for (i=0;i<3;i++) Sequen[i]=0;               //Lt_addr=0
				for (i=3;i<7;i++) Sequen[i]=Type[i-3];         //Type
				Sequen[7]=0;                                 //Flow
				Sequen[8]=0;                                 //Arqn
				Sequen[9]=0;                                 //Seqn

				bluetooth_HEC8(Sequen,10,HEC_state,HEC);

				for(i=0;i<10;i++) HEC_data[i]=Sequen[i];
				for(i=10;i<EFC_len;i++) HEC_data[i]=HEC[i-10];
				bluetooth_FEC_encode(HEC_data, EFC_len, coderate, Header_out, Header_len, EFC_state);

				break;
			}

		case DH1:
			{
				int EFC_len=18;
				double coderate=1/3;
				char Sequen[10]={0};                         //Sequen=[Lt_addr Type Flow Arqn Seqn];
				char Type[4]={0,0,1,0};
				char HEC[8]={0};
				char HEC_data[18]={0};

				for (i=0;i<3;i++) Sequen[i]=0;               //Lt_addr0
				for (i=3;i<7;i++) Sequen[i]=Type[i-3];         //Type
				Sequen[7]=0;                                 //Flow
				Sequen[8]=0;                                 //Arqn
				Sequen[9]=0;                                 //Seqn

				bluetooth_HEC8(Sequen,10,HEC_state,HEC);

				for(i=0;i<10;i++) HEC_data[i]=Sequen[i];
				for(i=10;i<EFC_len;i++) HEC_data[i]=HEC[i-10];
				bluetooth_FEC_encode(HEC_data, EFC_len, coderate, Header_out, Header_len, EFC_state);

				break;
			}

		case DM3:
			{
				int EFC_len=18;
				double coderate=1/3;
				char Sequen[10]={0};                         //Sequen=[Lt_addr Type Flow Arqn Seqn];
				char Type[4]={0,1,0,1};
				char HEC[8]={0};
				char HEC_data[18]={0};

				for (i=0;i<3;i++) Sequen[i]=0;               //Lt_addr0
				for (i=3;i<7;i++) Sequen[i]=Type[i-3];         //Type
				Sequen[7]=0;                                 //Flow
				Sequen[8]=0;                                 //Arqn
				Sequen[9]=0;                                 //Seqn

				bluetooth_HEC8(Sequen,10,HEC_state,HEC);

				for(i=0;i<10;i++) HEC_data[i]=Sequen[i];
				for(i=10;i<EFC_len;i++) HEC_data[i]=HEC[i-10];
				bluetooth_FEC_encode(HEC_data, EFC_len, coderate, Header_out, Header_len, EFC_state);

				break;
			}

		case DH3:
			{
				int EFC_len=18;
				double coderate=1/3;
				char Sequen[10]={0};                         //Sequen=[Lt_addr Type Flow Arqn Seqn];
				char Type[4]={1,1,0,1};
				char HEC[8]={0};
				char HEC_data[18]={0};

				for (i=0;i<3;i++) Sequen[i]=0;               //Lt_addr0
				for (i=3;i<7;i++) Sequen[i]=Type[i-3];         //Type
				Sequen[7]=0;                                 //Flow
				Sequen[8]=0;                                 //Arqn
				Sequen[9]=0;                                 //Seqn

				bluetooth_HEC8(Sequen,10,HEC_state,HEC);

				for(i=0;i<10;i++) HEC_data[i]=Sequen[i];
				for(i=10;i<EFC_len;i++) HEC_data[i]=HEC[i-10];
				bluetooth_FEC_encode(HEC_data, EFC_len, coderate, Header_out, Header_len, EFC_state);

				break;
			}

		case DM5:
			{
				int EFC_len=18;
				double coderate=1/3;
				char Sequen[10]={0};                         //Sequen=[Lt_addr Type Flow Arqn Seqn];
				char Type[4]={0,1,1,1};
				char HEC[8]={0};
				char HEC_data[18]={0};

				for (i=0;i<3;i++) Sequen[i]=0;               //Lt_addr0
				for (i=3;i<7;i++) Sequen[i]=Type[i-3];         //Type
				Sequen[7]=0;                                 //Flow
				Sequen[8]=0;                                 //Arqn
				Sequen[9]=0;                                 //Seqn

				bluetooth_HEC8(Sequen,10,HEC_state,HEC);

				for(i=0;i<10;i++) HEC_data[i]=Sequen[i];
				for(i=10;i<EFC_len;i++) HEC_data[i]=HEC[i-10];
				bluetooth_FEC_encode(HEC_data, EFC_len, coderate, Header_out, Header_len, EFC_state);

				break;
			}

		case DH5:
			{
				int EFC_len=18;
				double coderate=1/3;
				char Sequen[10]={0};                         //Sequen=[Lt_addr Type Flow Arqn Seqn];
				char Type[4]={1,1,1,1};
				char HEC[8]={0};
				char HEC_data[18]={0};

				for (i=0;i<3;i++) Sequen[i]=0;               //Lt_addr0
				for (i=3;i<7;i++) Sequen[i]=Type[i-3];         //Type
				Sequen[7]=0;                                 //Flow
				Sequen[8]=0;                                 //Arqn
				Sequen[9]=0;                                 //Seqn

				bluetooth_HEC8(Sequen,10,HEC_state,HEC);

				for(i=0;i<10;i++) HEC_data[i]=Sequen[i];
				for(i=10;i<EFC_len;i++) HEC_data[i]=HEC[i-10];
				bluetooth_FEC_encode(HEC_data, EFC_len, coderate, Header_out, Header_len, EFC_state);

				break;
			}

		case AUX1:
			{
				int EFC_len=18;
				double coderate=1/3;
				char Sequen[10]={0};                         //Sequen=[Lt_addr Type Flow Arqn Seqn];
				char Type[4]={1,0,0,1};
				char HEC[8]={0};
				char HEC_data[18]={0};

				for (i=0;i<3;i++) Sequen[i]=0;               //Lt_addr0
				for (i=3;i<7;i++) Sequen[i]=Type[i-3];         //Type
				Sequen[7]=0;                                 //Flow
				Sequen[8]=0;                                 //Arqn
				Sequen[9]=0;                                 //Seqn

				bluetooth_HEC8(Sequen,10,HEC_state,HEC);

				for(i=0;i<10;i++) HEC_data[i]=Sequen[i];
				for(i=10;i<EFC_len;i++) HEC_data[i]=HEC[i-10];
				bluetooth_FEC_encode(HEC_data, EFC_len, coderate, Header_out, Header_len, EFC_state);

				break;
			}

		default: printf("Wrong packet type in ACL");
		}
	}

	else printf("Wrong transport type type, only support SCO eSCO ACL");
}

void bluetooth_access_generator( char Lapaddress[], int Lapaddress_len, char Access_out[])
{
	int sync_len=64;
	int premble_len=4;

	char *sync_out=(char *)calloc(sync_len,sizeof(char));
	char *Preamble_out=(char *)calloc(sync_len+premble_len,sizeof(char));

	bluetooth_access_sync_generator( Lapaddress, Lapaddress_len, sync_out);
	bluetooth_access_preamble_generator( sync_out, Preamble_out);
	bluetooth_access_trailer_generator( Preamble_out, Access_out);

	//for (int i=0;i<68;i++) cout<< int(Preamble_out[i]) <<endl;
	free(sync_out);
	sync_out=NULL;
	free(Preamble_out);
	Preamble_out=NULL;
}

void bluetooth_payload_generator(Packettype packettype,char lapaddress[],int lapaddress_len,char crc_state[],char efc_state[],char payload_in[],int data_len,char payload_out[])
{
	int i;
	int crc_len=16;
	double code_rate;

	char crc[16]={0};


	switch(packettype)
	{

	case HV1:
		{
			code_rate=1/3;

			bluetooth_FEC_encode(payload_in, data_len, code_rate, payload_out, int(data_len/code_rate), efc_state);

			break;
		}

	case HV2:
		{
			code_rate=2/3;

			bluetooth_FEC_encode(payload_in, data_len, code_rate, payload_out, int(data_len/code_rate), efc_state);

			break;
		}

	case HV3:
		{

			for (i=0;i<data_len;i++)payload_out[i]=payload_in[i];

			break;
		}

	case DM1:
		{
			char *playload_tmp=(char *)calloc(data_len+8,sizeof(char));
			char *playload_crc_tmp=(char *)calloc(data_len+crc_len+8,sizeof(char));

			char llid[2]={0};
			char flow=0;
			char length[5]={0};                             //17的二进制数,右位高。

			Tentotwo_fuction(data_len,5,length);

			code_rate=2/3;

			for(i=0;i<2;i++)playload_tmp[i]=llid[i];
			playload_tmp[2]=flow;
			for(i=3;i<8;i++)playload_tmp[i]=length[i-3];
			for(i=8;i<8+data_len;i++)playload_tmp[i]=payload_in[i-8];

			bluetooth_CRC16(playload_tmp,data_len,crc_state,crc);

			for (i=0;i<data_len+8;i++) playload_crc_tmp[i]=playload_tmp[i];
			for (i=data_len+8;i<crc_len+data_len+8;i++) playload_crc_tmp[i]=crc[i-(data_len+8)];

			bluetooth_FEC_encode(playload_crc_tmp, data_len, code_rate, payload_out, int(data_len/code_rate), efc_state);

			free(playload_tmp);
			playload_tmp=NULL;
			free(playload_crc_tmp);
			playload_crc_tmp=NULL;

			break;
		}

	case DH1:
		{
			char *playload_tmp=(char *)calloc(data_len+8,sizeof(char));

			char llid[2]={0};
			char flow=0;
			char length[5]={0};                             //27的二进制数,右位高。

			Tentotwo_fuction(data_len,5,length);

			for(i=0;i<2;i++)playload_tmp[i]=llid[i];
			playload_tmp[2]=flow;
			for(i=3;i<8;i++)playload_tmp[i]=length[i-3];
			for(i=8;i<8+data_len;i++)playload_tmp[i]=payload_in[i-8];

			bluetooth_CRC16(playload_tmp,data_len,crc_state,crc);

			for (i=0;i<data_len+8;i++) payload_out[i]=playload_tmp[i];
			for (i=data_len+8;i<crc_len+data_len+8;i++) payload_out[i]=crc[i-(data_len+8)];

			free(playload_tmp);
			playload_tmp=NULL;

			break;
		}

	case DM3:
		{
			char *playload_tmp=(char *)calloc(data_len+16,sizeof(char));
			char *playload_crc_tmp=(char *)calloc(data_len+crc_len+16,sizeof(char));

			char llid[2]={0};
			char flow=0;
			char length[10];                             //右位高。
			char reserved[3]={0};

			code_rate=2/3;

			Tentotwo_fuction(data_len,10,length);

			for(i=0;i<2;i++)playload_tmp[i]=llid[i];
			playload_tmp[2]=flow;
			for(i=3;i<13;i++)playload_tmp[i]=length[i-3];
			for(i=13;i<16;i++)playload_tmp[i]=reserved[i-13];
			for(i=16;i<16+data_len;i++)playload_tmp[i]=payload_in[i-16];

			bluetooth_CRC16(playload_tmp,data_len,crc_state,crc);

			for (i=0;i<data_len+16;i++) payload_out[i]=playload_crc_tmp[i];
			for (i=data_len+16;i<crc_len+data_len+16;i++) playload_crc_tmp[i]=crc[i-(data_len+16)];

			bluetooth_FEC_encode(playload_crc_tmp, data_len, code_rate, payload_out, int(data_len/code_rate), efc_state);

			free(playload_tmp);
			playload_tmp=NULL;
			free(playload_crc_tmp);
			playload_crc_tmp=NULL;

			break;
		}

	case DH3:
		{
			char *playload_tmp=(char *)calloc(data_len+16,sizeof(char));

			char llid[2]={0};
			char flow=0;
			char length[10];                             
			char reserved[3]={0};

			Tentotwo_fuction(data_len,10,length);

			for(i=0;i<2;i++)playload_tmp[i]=llid[i];
			playload_tmp[2]=flow;
			for(i=3;i<13;i++)playload_tmp[i]=length[i-3];
			for(i=13;i<16;i++)playload_tmp[i]=reserved[i-13];
			for(i=16;i<16+data_len;i++)playload_tmp[i]=payload_in[i-16];

			bluetooth_CRC16(playload_tmp,data_len,crc_state,crc);

			for (i=0;i<data_len+16;i++) payload_out[i]=playload_tmp[i];
			for (i=data_len+16;i<crc_len+data_len+16;i++) payload_out[i]=crc[i-(data_len+16)];

			free(playload_tmp);
			playload_tmp=NULL;

			break;
		}

	case DM5:
		{
			char *playload_tmp=(char *)calloc(data_len+16,sizeof(char));
			char *playload_crc_tmp=(char *)calloc(data_len+crc_len+16,sizeof(char));

			char llid[2]={0};
			char flow=0;
			char length[10];                             //右位高。
			char reserved[3]={0};

			code_rate=2/3;

			Tentotwo_fuction(data_len,10,length);

			for(i=0;i<2;i++)playload_tmp[i]=llid[i];
			playload_tmp[2]=flow;
			for(i=3;i<13;i++)playload_tmp[i]=length[i-3];
			for(i=13;i<16;i++)playload_tmp[i]=reserved[i-13];
			for(i=16;i<16+data_len;i++)playload_tmp[i]=payload_in[i-16];

			bluetooth_CRC16(playload_tmp,data_len,crc_state,crc);

			for (i=0;i<data_len+16;i++) payload_out[i]=playload_crc_tmp[i];
			for (i=data_len+16;i<crc_len+data_len+16;i++) playload_crc_tmp[i]=crc[i-(data_len+16)];

			bluetooth_FEC_encode(playload_crc_tmp, data_len, code_rate, payload_out, int(data_len/code_rate), efc_state);

			free(playload_tmp);
			playload_tmp=NULL;
			free(playload_crc_tmp);
			playload_crc_tmp=NULL;

			break;
		}

	case DH5:
		{
			char *playload_tmp=(char *)calloc(data_len+16,sizeof(char));

			char llid[2]={0};
			char flow=0;
			char length[10];                             
			char reserved[3]={0};

			Tentotwo_fuction(data_len,10,length);

			for(i=0;i<2;i++)playload_tmp[i]=llid[i];
			playload_tmp[2]=flow;
			for(i=3;i<13;i++)playload_tmp[i]=length[i-3];
			for(i=13;i<16;i++)playload_tmp[i]=reserved[i-13];
			for(i=16;i<16+data_len;i++)playload_tmp[i]=payload_in[i-16];

			bluetooth_CRC16(playload_tmp,data_len,crc_state,crc);

			for (i=0;i<data_len+16;i++) payload_out[i]=playload_tmp[i];
			for (i=data_len+16;i<crc_len+data_len+16;i++) payload_out[i]=crc[i-(data_len+16)];

			free(playload_tmp);
			playload_tmp=NULL;

			break;
		}

	case AUX1:
		{
			char llid[2]={0};
			char flow=0;
			char length[10];                             
			char reserved[3]={0};

			Tentotwo_fuction(data_len,10,length);

			for(i=0;i<2;i++)payload_out[i]=llid[i];
			payload_out[2]=flow;
			for(i=3;i<13;i++)payload_out[i]=length[i-3];
			for(i=13;i<16;i++)payload_out[i]=reserved[i-13];
			for(i=16;i<16+data_len;i++)payload_out[i]=payload_in[i-16];

			break;
		}
	}

}

void bluetooth_packet_generator(Packettype packettype, Transtype transtype,char lapaddress[], char crc_state[],char hec_state[],char efc_state[],char data_in[],int data_len,char payload_out[], int &packet_len)
{
	
	int access_len=0;
	int header_len=0;
	int preamble_len=0;
	int single_packet_len=0;
	int payload_bitlen=0;
	int payload_tmplen=0;
	int pack_payload_index=0;
	int payload_len=0;
	int pack_num=0;
	int data_bit_index=0;
	int data_len_tmp=0;

	int i,pack_i;
	double code_rate;
	int lapaddress_len=24;

	char access_data[72]={0};
	char header_data[54]={0};
	char data_in_tmp[500]={0};//定义最大payload
	char payload_data[3000]={0};
	char data_inexpend[3000]={0};

	switch(packettype)
	{

	case ID:   //len=68;
		{
			char sync_data[64]={0};

			access_len=68;
			packet_len=access_len;

			bluetooth_access_sync_generator(lapaddress,lapaddress_len,sync_data);
			bluetooth_access_preamble_generator( sync_data, payload_out);

			break; 
		}

	case NuLLpack:   //len=126;
		{
			access_len=72;
			header_len=54;
			packet_len=access_len+header_len;

			bluetooth_access_generator( lapaddress, lapaddress_len, access_data);
			bluetooth_header_generator(packettype,transtype,lapaddress,hec_state,header_data,header_len,efc_state);

			for (i=0;i<access_len;i++) payload_out[i]=access_data[i];
			for (i=access_len;i<packet_len;i++) payload_out[i]=header_data[i];

			break; 

		}

	case POLL:
		{
			access_len=72;
			header_len=54;
			packet_len=access_len+header_len;

			bluetooth_access_generator( lapaddress, lapaddress_len, access_data);
			bluetooth_header_generator(packettype,transtype,lapaddress,hec_state,header_data,header_len,efc_state);

			for (i=0;i<access_len;i++) payload_out[i]=access_data[i];
			for (i=access_len;i<packet_len;i++) payload_out[i]=header_data[i];

			break;
		}

	case HV1:
		{
			access_len = 72;
			header_len = 54;
			payload_len = 240;
			payload_bitlen=80;
			code_rate=1.0 / 3;
			single_packet_len=access_len+header_len+payload_len;
			pack_num=data_len/payload_bitlen+1;
			packet_len=data_len/payload_bitlen*single_packet_len+access_len+header_len+int((data_len%payload_bitlen)/code_rate);

			bluetooth_access_generator( lapaddress, lapaddress_len, access_data);
			bluetooth_header_generator(packettype,transtype,lapaddress,hec_state,header_data,header_len,efc_state);

			data_bit_index=0;
			for (pack_i=0;pack_i<pack_num;pack_i++)
			{
				pack_payload_index=0;
				while((data_bit_index+pack_payload_index < (pack_i+1)*payload_bitlen)&&(data_bit_index+pack_payload_index < data_len))
				{
					data_in_tmp[pack_payload_index]=data_in[pack_payload_index+pack_i*payload_bitlen];
					pack_payload_index=pack_payload_index+1;
				}

				data_bit_index=data_bit_index+pack_payload_index;
				data_len_tmp=pack_payload_index;

				payload_tmplen =access_len+header_len+int(pack_payload_index/code_rate);
				bluetooth_payload_generator(packettype, lapaddress, lapaddress_len, crc_state, efc_state, data_in_tmp, data_len_tmp, payload_data);

				for (i=pack_i*single_packet_len;i<access_len+pack_i*single_packet_len;i++) payload_out[i]=access_data[i-pack_i*single_packet_len];
				for (i=access_len+pack_i*single_packet_len;i<access_len+header_len+pack_i*single_packet_len;i++) payload_out[i]=header_data[i-access_len+pack_i*single_packet_len];
				for (i=access_len+header_len+pack_i*single_packet_len;i<payload_tmplen+pack_i*single_packet_len;i++) payload_out[i]=payload_data[i-(access_len+header_len+pack_i*single_packet_len)];
			}

			break;
		}


	case HV2:
		{
			access_len=72;
			header_len=54;
			payload_len=240;
			payload_bitlen=160;
			code_rate=2.0/3;
			single_packet_len=access_len+header_len+payload_len;

			if ((data_len%payload_bitlen)%2==1) 
			{
				for(i=0;i<data_len;i++) data_inexpend[i]=data_in[i];
				data_inexpend[data_len]=0;
				data_len=data_len+1;
			}
			else
			{
				for(i=0;i<data_len;i++) data_inexpend[i]=data_in[i];
			}

			pack_num=data_len/payload_bitlen+1;
			packet_len=data_len/payload_bitlen*single_packet_len+access_len+header_len+int((data_len%payload_bitlen)/code_rate);

			bluetooth_access_generator( lapaddress, lapaddress_len, access_data);
			bluetooth_header_generator(packettype,transtype,lapaddress,hec_state,header_data,header_len,efc_state);

			data_bit_index=0;
			for (pack_i=0;pack_i<pack_num;pack_i++)
			{
				pack_payload_index=0;
				while((data_bit_index+pack_payload_index < (pack_i+1)*payload_bitlen)&&(data_bit_index+pack_payload_index < data_len))
				{
					data_in_tmp[pack_payload_index]=data_in[pack_payload_index+pack_i*payload_bitlen];
					pack_payload_index=pack_payload_index+1;
				}

				data_bit_index=data_bit_index+pack_payload_index;
				data_len_tmp=pack_payload_index;

				payload_tmplen =access_len+header_len+int(pack_payload_index/code_rate);
				bluetooth_payload_generator(packettype, lapaddress, lapaddress_len, crc_state, efc_state, data_in_tmp, data_len_tmp, payload_data);

				for (i=pack_i*single_packet_len;i<access_len+pack_i*single_packet_len;i++) payload_out[i]=access_data[i-pack_i*single_packet_len];
				for (i=access_len+pack_i*single_packet_len;i<access_len+header_len+pack_i*single_packet_len;i++) payload_out[i]=header_data[i-access_len+pack_i*single_packet_len];
				for (i=access_len+header_len+pack_i*single_packet_len;i<payload_tmplen+pack_i*single_packet_len;i++) payload_out[i]=payload_data[i-(access_len+header_len+pack_i*single_packet_len)];
			}

			break;
		}

	case HV3:
		{
			access_len=72;
			header_len=54;
			payload_len=240;
			payload_bitlen=240;
			code_rate=1.0;
			single_packet_len=access_len+header_len+payload_len;
			pack_num=data_len/payload_bitlen+1;
			packet_len=data_len/payload_bitlen*single_packet_len+access_len+header_len+int((data_len%payload_bitlen)/code_rate);

			bluetooth_access_generator(lapaddress, lapaddress_len, access_data);
			bluetooth_header_generator(packettype,transtype,lapaddress,hec_state,header_data,header_len,efc_state);

			data_bit_index=0;
			for (pack_i=0;pack_i<pack_num;pack_i++)
			{
				pack_payload_index=0;
				while((data_bit_index+pack_payload_index < (pack_i+1)*payload_bitlen)&&(data_bit_index+pack_payload_index < data_len))
				{
					data_in_tmp[pack_payload_index]=data_in[pack_payload_index+pack_i*payload_bitlen];
					pack_payload_index=pack_payload_index+1;
				}

				data_bit_index=data_bit_index+pack_payload_index;
				data_len_tmp=pack_payload_index;

				payload_tmplen =access_len+header_len+int(pack_payload_index/code_rate);
				bluetooth_payload_generator(packettype, lapaddress, lapaddress_len, crc_state, efc_state, data_in_tmp, data_len_tmp, payload_data);

				for (i=pack_i*single_packet_len;i<access_len+pack_i*single_packet_len;i++) payload_out[i]=access_data[i-pack_i*single_packet_len];
				for (i=access_len+pack_i*single_packet_len;i<access_len+header_len+pack_i*single_packet_len;i++) payload_out[i]=header_data[i-access_len+pack_i*single_packet_len];
				for (i=access_len+header_len+pack_i*single_packet_len;i<payload_tmplen+pack_i*single_packet_len;i++) payload_out[i]=payload_data[i-(access_len+header_len+pack_i*single_packet_len)];
			}

			break;
		}

	case DM1:
		{
			access_len=72;
			header_len=54;
			payload_len=240;
			payload_bitlen=136;
			code_rate=2.0/3;
			single_packet_len=access_len+header_len+payload_len;

			if ((data_len%payload_bitlen)%2==1) 
			{
				for(i=0;i<data_len;i++) data_inexpend[i]=data_in[i];
				data_inexpend[data_len]=0;
				data_len=data_len+1;
			}
			else
			{
				for(i=0;i<data_len;i++) data_inexpend[i]=data_in[i];
			}
			//for (i=0;i<data_len;i++) cout << int(data_in[i]) << endl;
			pack_num=data_len/payload_bitlen+1;
			packet_len=data_len/payload_bitlen*single_packet_len+access_len+header_len+int(((data_len%payload_bitlen)+24)/code_rate); //24=16+2+1+5

			bluetooth_access_generator(lapaddress, lapaddress_len, access_data);
			//for (i=0;i<72;i++) cout << int(access_data[i]) << endl;
			bluetooth_header_generator(packettype,transtype,lapaddress,hec_state,header_data,header_len,efc_state);
			//for (i=0;i<54;i++) cout << int(header_data[i]) << endl;
			data_bit_index=0;
			for (pack_i=0;pack_i<pack_num;pack_i++)
			{
				pack_payload_index=0;
				while((data_bit_index+pack_payload_index < (pack_i+1)*payload_bitlen)&&(data_bit_index+pack_payload_index < data_len))
				{
					data_in_tmp[pack_payload_index]=data_inexpend[pack_payload_index+pack_i*payload_bitlen];
					pack_payload_index=pack_payload_index+1;
				}

				data_bit_index=data_bit_index+pack_payload_index;
				data_len_tmp=pack_payload_index;
				//for (i=0;i<pack_payload_index;i++) cout << int(data_in_tmp[i]) << endl;

				payload_tmplen =access_len+header_len+int((pack_payload_index+24)/code_rate);
				bluetooth_payload_generator(packettype, lapaddress, lapaddress_len, crc_state, efc_state, data_in_tmp, data_len_tmp, payload_data);

				for (i=pack_i*single_packet_len;i<access_len+pack_i*single_packet_len;i++) payload_out[i]=access_data[i-pack_i*single_packet_len];
				for (i=access_len+pack_i*single_packet_len;i<access_len+header_len+pack_i*single_packet_len;i++) payload_out[i]=header_data[i-access_len+pack_i*single_packet_len];
				for (i=access_len+header_len+pack_i*single_packet_len;i<payload_tmplen+pack_i*single_packet_len;i++) payload_out[i]=payload_data[i-(access_len+header_len+pack_i*single_packet_len)];
			}

			break;
		}

	case DH1:
		{
			access_len=72;
			header_len=54;
			payload_len=240;
			payload_bitlen=216;
			code_rate=1.0;
			single_packet_len=access_len+header_len+payload_len;

			//for (i=0;i<data_len;i++) cout << int(data_in[i]) << endl;
			pack_num=data_len/payload_bitlen+1;
			packet_len=data_len/payload_bitlen*single_packet_len+access_len+header_len+int(((data_len%payload_bitlen)+24)/code_rate); //24=16+2+1+5

			bluetooth_access_generator(lapaddress, lapaddress_len, access_data);
			//for (i=0;i<72;i++) cout << int(access_data[i]) << endl;
			bluetooth_header_generator(packettype,transtype,lapaddress,hec_state,header_data,header_len,efc_state);
			//for (i=0;i<54;i++) cout << int(header_data[i]) << endl;
			data_bit_index=0;
			for (pack_i=0;pack_i<pack_num;pack_i++)
			{
				pack_payload_index=0;
				while((data_bit_index+pack_payload_index < (pack_i+1)*payload_bitlen)&&(data_bit_index+pack_payload_index < data_len))
				{
					data_in_tmp[pack_payload_index]=data_in[pack_payload_index+pack_i*payload_bitlen];
					pack_payload_index=pack_payload_index+1;
				}

				data_bit_index=data_bit_index+pack_payload_index;
				data_len_tmp=pack_payload_index;
				//for (i=0;i<pack_payload_index;i++) cout << int(data_in_tmp[i]) << endl;

				payload_tmplen =access_len+header_len+int((pack_payload_index+24)/code_rate);
				bluetooth_payload_generator(packettype, lapaddress, lapaddress_len, crc_state, efc_state, data_in_tmp, data_len_tmp, payload_data);

				for (i=pack_i*single_packet_len;i<access_len+pack_i*single_packet_len;i++) payload_out[i]=access_data[i-pack_i*single_packet_len];
				for (i=access_len+pack_i*single_packet_len;i<access_len+header_len+pack_i*single_packet_len;i++) payload_out[i]=header_data[i-access_len+pack_i*single_packet_len];
				for (i=access_len+header_len+pack_i*single_packet_len;i<payload_tmplen+pack_i*single_packet_len;i++) payload_out[i]=payload_data[i-(access_len+header_len+pack_i*single_packet_len)];
			}

			break;
		}



	case DM3:
		{
			access_len=72;
			header_len=54;
			payload_len=1500;
			payload_bitlen=968;
			code_rate=2.0/3;
			single_packet_len=access_len+header_len+payload_len;

			if ((data_len%payload_bitlen)%2==1) 
			{
				for(i=0;i<data_len;i++) data_inexpend[i]=data_in[i];
				data_inexpend[data_len]=0;
				data_len=data_len+1;
			}
			else
			{
				for(i=0;i<data_len;i++) data_inexpend[i]=data_in[i];
			}
			//for (i=0;i<data_len;i++) cout << int(data_in[i]) << endl;
			pack_num=data_len/payload_bitlen+1;
			packet_len=data_len/payload_bitlen*single_packet_len+access_len+header_len+int(((data_len%payload_bitlen)+32)/code_rate); //32=16+3+10+2+1+2

			bluetooth_access_generator(lapaddress, lapaddress_len, access_data);
			//for (i=0;i<72;i++) cout << int(access_data[i]) << endl;
			bluetooth_header_generator(packettype,transtype,lapaddress,hec_state,header_data,header_len,efc_state);
			//for (i=0;i<54;i++) cout << int(header_data[i]) << endl;
			data_bit_index=0;
			for (pack_i=0;pack_i<pack_num;pack_i++)
			{
				pack_payload_index=0;
				while((data_bit_index+pack_payload_index < (pack_i+1)*payload_bitlen)&&(data_bit_index+pack_payload_index < data_len))
				{
					data_in_tmp[pack_payload_index]=data_inexpend[pack_payload_index+pack_i*payload_bitlen];
					pack_payload_index=pack_payload_index+1;
				}

				data_bit_index=data_bit_index+pack_payload_index;
				data_len_tmp=pack_payload_index;
				//for (i=0;i<pack_payload_index;i++) cout << int(data_in_tmp[i]) << endl;

				payload_tmplen =access_len+header_len+int((pack_payload_index+32)/code_rate);
				bluetooth_payload_generator(packettype, lapaddress, lapaddress_len, crc_state, efc_state, data_in_tmp, data_len_tmp, payload_data);

				for (i=pack_i*single_packet_len;i<access_len+pack_i*single_packet_len;i++) payload_out[i]=access_data[i-pack_i*single_packet_len];
				for (i=access_len+pack_i*single_packet_len;i<access_len+header_len+pack_i*single_packet_len;i++) payload_out[i]=header_data[i-access_len+pack_i*single_packet_len];
				for (i=access_len+header_len+pack_i*single_packet_len;i<payload_tmplen+pack_i*single_packet_len;i++) payload_out[i]=payload_data[i-(access_len+header_len+pack_i*single_packet_len)];
			}

			break;
		}

	case DH3:
		{
			access_len=72;
			header_len=54;
			payload_len=1496;
			payload_bitlen=894;
			code_rate=1.0;
			single_packet_len=access_len+header_len+payload_len;

			//for (i=0;i<data_len;i++) cout << int(data_in[i]) << endl;
			pack_num=data_len/payload_bitlen+1;
			packet_len=data_len/payload_bitlen*single_packet_len+access_len+header_len+int(((data_len%payload_bitlen)+32)/code_rate); //32=16+3+10+2+1+2

			bluetooth_access_generator(lapaddress, lapaddress_len, access_data);
			//for (i=0;i<72;i++) cout << int(access_data[i]) << endl;
			bluetooth_header_generator(packettype,transtype,lapaddress,hec_state,header_data,header_len,efc_state);
			//for (i=0;i<54;i++) cout << int(header_data[i]) << endl;
			data_bit_index=0;
			for (pack_i=0;pack_i<pack_num;pack_i++)
			{
				pack_payload_index=0;
				while((data_bit_index+pack_payload_index < (pack_i+1)*payload_bitlen)&&(data_bit_index+pack_payload_index < data_len))
				{
					data_in_tmp[pack_payload_index]=data_in[pack_payload_index+pack_i*payload_bitlen];
					pack_payload_index=pack_payload_index+1;
				}

				data_bit_index=data_bit_index+pack_payload_index;
				data_len_tmp=pack_payload_index;
				//for (i=0;i<pack_payload_index;i++) cout << int(data_in_tmp[i]) << endl;

				payload_tmplen =access_len+header_len+int((pack_payload_index+32)/code_rate);
				bluetooth_payload_generator(packettype, lapaddress, lapaddress_len, crc_state, efc_state, data_in_tmp, data_len_tmp, payload_data);

				for (i=pack_i*single_packet_len;i<access_len+pack_i*single_packet_len;i++) payload_out[i]=access_data[i-pack_i*single_packet_len];
				for (i=access_len+pack_i*single_packet_len;i<access_len+header_len+pack_i*single_packet_len;i++) payload_out[i]=header_data[i-access_len+pack_i*single_packet_len];
				for (i=access_len+header_len+pack_i*single_packet_len;i<payload_tmplen+pack_i*single_packet_len;i++) payload_out[i]=payload_data[i-(access_len+header_len+pack_i*single_packet_len)];
			}

			break;
		}

	case DM5:
		{
			access_len=72;
			header_len=54;
			payload_len=2745;
			payload_bitlen=1792;
			code_rate=2.0/3;
			single_packet_len=access_len+header_len+payload_len;

			if ((data_len%payload_bitlen)%2==1) 
			{
				for(i=0;i<data_len;i++) data_inexpend[i]=data_in[i];
				data_inexpend[data_len]=0;
				data_len=data_len+1;
			}
			else
			{
				for(i=0;i<data_len;i++) data_inexpend[i]=data_in[i];
			}
			//for (i=0;i<data_len;i++) cout << int(data_in[i]) << endl;
			pack_num=data_len/payload_bitlen+1;
			packet_len=data_len/payload_bitlen*single_packet_len+access_len+header_len+int(((data_len%payload_bitlen)+32)/code_rate); //32=16+3+10+2+1+2

			bluetooth_access_generator(lapaddress, lapaddress_len, access_data);
			//for (i=0;i<72;i++) cout << int(access_data[i]) << endl;
			bluetooth_header_generator(packettype,transtype,lapaddress,hec_state,header_data,header_len,efc_state);
			//for (i=0;i<54;i++) cout << int(header_data[i]) << endl;
			data_bit_index=0;
			for (pack_i=0;pack_i<pack_num;pack_i++)
			{
				pack_payload_index=0;
				while((data_bit_index+pack_payload_index < (pack_i+1)*payload_bitlen)&&(data_bit_index+pack_payload_index < data_len))
				{
					data_in_tmp[pack_payload_index]=data_inexpend[pack_payload_index+pack_i*payload_bitlen];
					pack_payload_index=pack_payload_index+1;
				}

				data_bit_index=data_bit_index+pack_payload_index;
				data_len_tmp=pack_payload_index;
				//for (i=0;i<pack_payload_index;i++) cout << int(data_in_tmp[i]) << endl;

				payload_tmplen =access_len+header_len+int((pack_payload_index+32)/code_rate);
				bluetooth_payload_generator(packettype, lapaddress, lapaddress_len, crc_state, efc_state, data_in_tmp, data_len_tmp, payload_data);

				for (i=pack_i*single_packet_len;i<access_len+pack_i*single_packet_len;i++) payload_out[i]=access_data[i-pack_i*single_packet_len];
				for (i=access_len+pack_i*single_packet_len;i<access_len+header_len+pack_i*single_packet_len;i++) payload_out[i]=header_data[i-access_len+pack_i*single_packet_len];
				for (i=access_len+header_len+pack_i*single_packet_len;i<payload_tmplen+pack_i*single_packet_len;i++) payload_out[i]=payload_data[i-(access_len+header_len+pack_i*single_packet_len)];
			}

			break;
		}

	case DH5:
		{
			access_len=72;
			header_len=54;
			payload_len=2744;
			payload_bitlen=2712;
			code_rate=1.0;
			single_packet_len=access_len+header_len+payload_len;

			//for (i=0;i<data_len;i++) cout << int(data_in[i]) << endl;
			pack_num=data_len/payload_bitlen+1;
			packet_len=data_len/payload_bitlen*single_packet_len+access_len+header_len+int(((data_len%payload_bitlen)+32)/code_rate); //32=16+3+10+2+1+2

			bluetooth_access_generator(lapaddress, lapaddress_len, access_data);
			//for (i=0;i<72;i++) cout << int(access_data[i]) << endl;
			bluetooth_header_generator(packettype,transtype,lapaddress,hec_state,header_data,header_len,efc_state);
			//for (i=0;i<54;i++) cout << int(header_data[i]) << endl;
			data_bit_index=0;
			for (pack_i=0;pack_i<pack_num;pack_i++)
			{
				pack_payload_index=0;
				while((data_bit_index+pack_payload_index < (pack_i+1)*payload_bitlen)&&(data_bit_index+pack_payload_index < data_len))
				{
					data_in_tmp[pack_payload_index]=data_in[pack_payload_index+pack_i*payload_bitlen];
					pack_payload_index=pack_payload_index+1;
				}

				data_bit_index=data_bit_index+pack_payload_index;
				data_len_tmp=pack_payload_index;
				//for (i=0;i<pack_payload_index;i++) cout << int(data_in_tmp[i]) << endl;

				payload_tmplen =access_len+header_len+int((pack_payload_index+32)/code_rate);
				bluetooth_payload_generator(packettype, lapaddress, lapaddress_len, crc_state, efc_state, data_in_tmp, data_len_tmp, payload_data);

				for (i=pack_i*single_packet_len;i<access_len+pack_i*single_packet_len;i++) payload_out[i]=access_data[i-pack_i*single_packet_len];
				for (i=access_len+pack_i*single_packet_len;i<access_len+header_len+pack_i*single_packet_len;i++) payload_out[i]=header_data[i-access_len+pack_i*single_packet_len];
				for (i=access_len+header_len+pack_i*single_packet_len;i<payload_tmplen+pack_i*single_packet_len;i++) payload_out[i]=payload_data[i-(access_len+header_len+pack_i*single_packet_len)];
			}

			break;
		}

	case AUX1:
		{
			access_len=72;
			header_len=54;
			payload_len=240;
			payload_bitlen=232;
			code_rate=1.0;
			single_packet_len=access_len+header_len+payload_len;

			//for (i=0;i<data_len;i++) cout << int(data_in[i]) << endl;
			pack_num=data_len/payload_bitlen+1;
			packet_len=data_len/payload_bitlen*single_packet_len+access_len+header_len+int(((data_len%payload_bitlen)+8)/code_rate); //8=2+1+5

			bluetooth_access_generator(lapaddress, lapaddress_len, access_data);
			//for (i=0;i<72;i++) cout << int(access_data[i]) << endl;
			bluetooth_header_generator(packettype,transtype,lapaddress,hec_state,header_data,header_len,efc_state);
			//for (i=0;i<54;i++) cout << int(header_data[i]) << endl;
			data_bit_index=0;
			for (pack_i=0;pack_i<pack_num;pack_i++)
			{
				pack_payload_index=0;
				while((data_bit_index+pack_payload_index < (pack_i+1)*payload_bitlen)&&(data_bit_index+pack_payload_index < data_len))
				{
					data_in_tmp[pack_payload_index]=data_in[pack_payload_index+pack_i*payload_bitlen];
					pack_payload_index=pack_payload_index+1;
				}

				data_bit_index=data_bit_index+pack_payload_index;
				data_len_tmp=pack_payload_index;
				//for (i=0;i<pack_payload_index;i++) cout << int(data_in_tmp[i]) << endl;

				payload_tmplen =access_len+header_len+int((pack_payload_index+8)/code_rate);
				bluetooth_payload_generator(packettype, lapaddress, lapaddress_len, crc_state, efc_state, data_in_tmp, data_len_tmp, payload_data);

				for (i=pack_i*single_packet_len;i<access_len+pack_i*single_packet_len;i++) payload_out[i]=access_data[i-pack_i*single_packet_len];
				for (i=access_len+pack_i*single_packet_len;i<access_len+header_len+pack_i*single_packet_len;i++) payload_out[i]=header_data[i-access_len+pack_i*single_packet_len];
				for (i=access_len+header_len+pack_i*single_packet_len;i<payload_tmplen+pack_i*single_packet_len;i++) payload_out[i]=payload_data[i-(access_len+header_len+pack_i*single_packet_len)];
			}

			break;
		}
	}
}

void bluetooth_GFSK_modulation( char date_in[],int data_inlen, double I_gfsk[],double Q_gfsk[],double Rs, double fc, double BTb, int oversample)

{
	int irfn=1;
	int mod_i;
	int syncpoint=irfn*oversample/2;
	double t;

	double *Gauss_fliter;
	double *in_data_o;
	double *in_data_g;
	double *in_data_m;

	Gauss_fliter=(double *)calloc(irfn*oversample,sizeof(double));
	in_data_o=(double *)calloc(data_inlen*oversample,sizeof(double));
	in_data_g=(double *)calloc(data_inlen*oversample+irfn*oversample-1,sizeof(double));
	in_data_m=(double *)calloc(data_inlen*oversample,sizeof(double));

	Gauss_fuction( Rs,oversample, irfn,Gauss_fliter);

	for(mod_i=0;mod_i<data_inlen;mod_i++)
	{
		in_data_o[oversample*mod_i]=2*date_in[mod_i]-1;
	}

	conv(in_data_o,Gauss_fliter, in_data_g, data_inlen*oversample,irfn*oversample);



	in_data_m[0]=in_data_g[syncpoint];

	for(mod_i=1;mod_i<data_inlen*oversample;mod_i++)
	{
		in_data_m[mod_i]=in_data_m[mod_i-1]+in_data_g[mod_i+syncpoint]/oversample;
	}
	for(mod_i=0;mod_i<data_inlen*oversample;mod_i++)
	{
		t=mod_i/oversample/Rs;
		I_gfsk[mod_i]=cos(2*bluetooth_pi*fc*t+2*bluetooth_pi*BTb*in_data_m[mod_i]);
		Q_gfsk[mod_i]=sin(2*bluetooth_pi*fc*t+2*bluetooth_pi*BTb*in_data_m[mod_i]);
	}

	for(int i=0;i<10;i++)
	{
		printf("%f\n",I_gfsk[i]);
	}

	free(Gauss_fliter);
	Gauss_fliter=NULL;
	free(in_data_o);
	in_data_o=NULL;
	free(in_data_g);
	in_data_g=NULL;
	free(in_data_m);
	in_data_m=NULL;
}

void bluetooth_waveform_generator(BlueToothParams *BTpacket,double I_gfsk[],double Q_gfsk[],char data_in[],int data_inlen, int &Packet_len)
{
	int i;
    double Rs=BTpacket->Rs;
	long fc=BTpacket->fc;
	double BTb=BTpacket->BTb;
	int oversample=BTpacket->oversample;
	Packettype packettype=BTpacket->packettype;
	Transtype transtype=BTpacket->transtype;
	char efc_state[5]  = {0};
	char crc_state[16] = {0};
	char hec_state[8]  = {0};
	char Lapadder[24] ={0};
	char payload_out[5000]={0};

	for (i=0;i<5;i++)
	{
		efc_state[i]=BTpacket->efc_state[i];
	}
	for (i=0;i<16;i++)
	{
		crc_state[i]=BTpacket->crc_state[i];
	}
	for (i=0;i<8;i++)
	{
		hec_state[i]=BTpacket->hec_state[i];
	}
	for (i=0;i<24;i++)
	{
		Lapadder[i]=BTpacket->Lapadder[i];
	}


	bluetooth_packet_generator(packettype, transtype, Lapadder, crc_state, hec_state, efc_state, data_in, data_inlen, payload_out, Packet_len);
	bluetooth_GFSK_modulation( payload_out, Packet_len, I_gfsk,Q_gfsk, Rs,  fc, BTb, oversample);
	for (i=0; i<Packet_len*oversample; i++) ;
}