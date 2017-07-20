//SC PHY�����ӿ����ÿ�����ݿ����64���ӿ飬ÿ���ӿ鳤��Ϊ512����Ƭ����Ƶ����Ϊ0/8/64�����ӿ�ǰ���뵼Ƶ���������һ�����ݿ飻
//����������symin������ķ��ţ�symout������ķ��ţ�sub_mod���ӿ�ģʽ0/8/64��Lsymin���������������Lsymout���������������

#include"genParam.h"
#include "stdafx.h"

using namespace std;

void SC_subbuilder(vector<complex<double> > &symin, vector<complex<double>> &symout, int sub_mod)
{
	int Lsymin = symin.size();
	switch (sub_mod)
	{
	case 0:
		{
			for (int i=0;i<Lsymin;i++)
			{
				symout.push_back(symin[i]);	
			}
			break;
		}
	case 8:
		{
			int a_golay_hex[2]={0xE,0xB};
			int b_golay_hex[2]={0xD,0x8};
			vector<int> a_golay_bits;
			vector<int> b_golay_bits;
			vector<int> a_golay_bits_N (8, 0);
			vector<int> b_golay_bits_N (8, 0);
			vector<complex<double> > a_golay_sym;
			vector<complex<double> > b_golay_sym;
			vector<complex<double> > a_golay_sym_N;
			vector<complex<double> > b_golay_sym_N;
			hex2binary(a_golay_hex,a_golay_bits,2);
			hex2binary(b_golay_hex,b_golay_bits,2);//�ӿ�ǰ����ĵ�Ƶ
			for (int i=0;i<8;i++)
				a_golay_bits_N[i]=floor((2-(a_golay_bits[i]*1.0))/2);
			for (int i=0;i<8;i++)
				b_golay_bits_N[i]=floor((2-(b_golay_bits[i]*1.0))/2);//�����෴�ĸ�������
			SC_tx_modulation(a_golay_bits,a_golay_sym,1);
			SC_tx_modulation(b_golay_bits,b_golay_sym,1);
			SC_tx_modulation(a_golay_bits_N,a_golay_sym_N,1);
			SC_tx_modulation(b_golay_bits_N,b_golay_sym_N,1);//����ĵ�Ƶ���Ц�/2 BPSK����
			int Nblocks=ceil(Lsymin*1.0/(448*64));//ÿ�����ݿ����64�������ӿ飬����ÿ���ӿ�����ݳ���Ϊ448����Ƶ����Ϊ8
			if (Nblocks==1)
			{
				for (int i=1;i<Lsymin;i++)
					symout.push_back(symin[i]);
				//Lsymout=Lsymin;
			}
			else
			{
				//Lsymout=(Nblocks-1)*(64*64+8)+Lsymin;//���������
				int Nlfsr=Nblocks-1;
				int Lblock=64*512+8;//ÿ�����ݿ鳤��
				vector<int> S_lfsr;
				SC_LFSR(S_lfsr,Nlfsr);
				int LLblock=Lsymin-(Nblocks-1)*448*64;//���һ�����ݿ������
				for (int i=0;i<(Nblocks-1);i++)
				{
					if ((i%2)==0)
					{
						if (S_lfsr[i]==0)//�������ԼĴ������ѡ��Ƶ����
						{
							for (int j=0;j<512;j++)
						    {
								for (int k=0;k<8;k++)
								{
									symout.push_back(a_golay_sym[k]);
								}
								for (int l=0;l<56;l++)
								{
									symout.push_back(symin[448*64*i+56*j+l]);
								}
							}
							for (int m=0;m<8;m++)
							{
								symout.push_back(a_golay_sym[m]);
							}
						}
						else
						{
							for (int j=0;j<512;j++)
						    {
								for (int k=0;k<8;k++)
								{
									symout.push_back(a_golay_sym_N[k]);
								}
								for (int l=0;l<56;l++)
								{
									symout.push_back(symin[448*64*i+56*j+l]);
								}
							}
							for (int m=0;m<8;m++)
							{
								symout.push_back(a_golay_sym_N[m]);
							}
						}
					}
					else
					{
						if (S_lfsr[i]==0)//�������ԼĴ������ѡ��Ƶ����
						{
							for (int j=0;j<512;j++)
						    {
								for (int k=0;k<8;k++)
								{
									symout.push_back(b_golay_sym[k]);
								}
								for (int l=0;l<56;l++)
								{
									symout.push_back(symin[448*64*i+56*j+l]);
								}
							}
							for (int m=0;m<8;m++)
							{
								symout.push_back(b_golay_sym[m]);
							}
						}
						else
						{
							for (int j=0;j<512;j++)
						    {
								for (int k=0;k<8;k++)
								{
									symout.push_back(b_golay_sym_N[k]);
								}
								for (int l=0;l<56;l++)
								{
									symout.push_back(symin[448*64*i+56*j+l]);
								}
							}
							for (int m=0;m<8;m++)
							{
								symout.push_back(b_golay_sym_N[m]);
							}
						}
					}
				}
				for (int ii=0;ii<LLblock;ii++)//���һ�����ݿ鲻��Ҫ���뵼Ƶ
				{
					symout.push_back(symin[(Nblocks-1)*448*64+ii]);
				}
			}
			break;
		}
	case 64:
		{
			int a_golay_hex[16]={0x6,0x3,0xA,0xF,0x0,0x5,0xC,0x9,0x6,0x3,0x5,0x0,0x0,0x5,0x3,0x6};
			int b_golay_hex[16]={0x6,0xC,0xA,0x0,0x0,0xA,0xC,0x6,0x6,0xC,0x5,0xF,0x0,0xA,0x3,0x9};
			vector<int> a_golay_bits;
			vector<int> b_golay_bits;
			vector<int> a_golay_bits_N (64, 0);
			vector<int> b_golay_bits_N (64, 0);
			vector<complex<double> > a_golay_sym;
			vector<complex<double> > b_golay_sym;
			vector<complex<double> > a_golay_sym_N;
			vector<complex<double> > b_golay_sym_N;
			hex2binary(a_golay_hex,a_golay_bits,16);
			hex2binary(b_golay_hex,b_golay_bits,16);//�ӿ�ǰ����ĵ�Ƶ
			for (int i=0;i<64;i++)
				a_golay_bits_N[i]=floor((2-(a_golay_bits[i]*1.0))/2);
			for (int i=0;i<64;i++)
				b_golay_bits_N[i]=floor((2-(b_golay_bits[i]*1.0))/2);//�����෴�ĸ�������
			SC_tx_modulation(a_golay_bits,a_golay_sym,1);
			SC_tx_modulation(b_golay_bits,b_golay_sym,1);
			SC_tx_modulation(a_golay_bits_N,a_golay_sym_N,1);
			SC_tx_modulation(b_golay_bits_N,b_golay_sym_N,1);//����ĵ�Ƶ���Ц�/2 BPSK����
			int Nblocks=ceil(Lsymin*1.0/(448*64));//ÿ�����ݿ����64�������ӿ飬����ÿ���ӿ�����ݳ���Ϊ448����Ƶ����Ϊ64
			if (Nblocks==1)
			{
				for (int i=1;i<Lsymin;i++)
					symout.push_back(symin[i]);
			}
			else
			{
				int LLblock=Lsymin-(Nblocks-1)*448*64;//���һ�����ݿ������
				int Nlfsr=Nblocks-1;
				int Lblock=64*512+64;//ÿ�����ݿ鳤��
				vector<int> S_lfsr;
				SC_LFSR(S_lfsr,Nlfsr);
				for (int i=0;i<(Nblocks-1);i++)
				{
					if ((i%2)==0)//���ݼ���ѡ��Ƶa��b
					{
						if (S_lfsr[i]==0)//�������ԼĴ������ѡ��Ƶ����
						{
							for (int j=0;j<64;j++)
						    {
								for (int k=0;k<64;k++)
								{
									symout.push_back(a_golay_sym[k]);
								}
								for (int l=0;l<448;l++)
								{
									symout.push_back(symin[448*64*i+448*j+l]);
								}
							}
							for (int m=0;m<64;m++)
							{
								symout.push_back(a_golay_sym[m]);
							}
						}
						else
						{
							for (int j=0;j<64;j++)
						    {
								for (int k=0;k<64;k++)
								{
									symout.push_back(a_golay_sym_N[k]);
								}
								for (int l=0;l<448;l++)
								{
									symout.push_back(symin[448*64*i+448*j+l]);
								}
							}
							for (int m=0;m<64;m++)
							{
								symout.push_back(a_golay_sym_N[m]);
							}
						}
					}
					else
					{
						if (S_lfsr[i]==0)//�������ԼĴ������ѡ��Ƶ����
						{
							for (int j=0;j<64;j++)
						    {
								for (int k=0;k<64;k++)
								{
									symout.push_back(b_golay_sym[k]);
								}
								for (int l=0;l<448;l++)
								{
									symout.push_back(symin[448*64*i+448*j+l]);
								}
							}
							for (int m=0;m<64;m++)
							{
								symout.push_back(b_golay_sym[m]);
							}
						}
						else
						{
							for (int j=0;j<64;j++)
						    {
								for (int k=0;k<64;k++)
								{
									symout.push_back(b_golay_sym_N[k]);
								}
								for (int l=0;l<448;l++)
								{
									symout.push_back(symin[448*64*i+448*j+l]);
								}
							}
							for (int m=0;m<64;m++)
							{
								symout[Lblock*i+64*512+m]=b_golay_sym_N[m];
							}
						}
					}
				}
				for (int ii=0;ii<LLblock;ii++)//���һ�����ݿ鲻��Ҫ���뵼Ƶ
				{
					symout.push_back(symin[(Nblocks-1)*448*64+ii]);
				}
			}
			break;
		}
	default:
		{
			cout<<"�����ӿ�����ģʽ����"<<endl;
			exit(EXIT_FAILURE);
			break;
		}
	}
}