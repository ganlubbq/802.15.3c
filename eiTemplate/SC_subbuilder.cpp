//SC PHY划分子块程序，每个数据块包含64个子块，每个子块长度为512个码片，导频长度为0/8/64，在子块前插入导频，除了最后一个数据块；
//函数参数：symin：输入的符号；symout：输出的符号；sub_mod：子块模式0/8/64；Lsymin：输入符号数量；Lsymout：输出符号数量；

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
			hex2binary(b_golay_hex,b_golay_bits,2);//子块前插入的导频
			for (int i=0;i<8;i++)
				a_golay_bits_N[i]=floor((2-(a_golay_bits[i]*1.0))/2);
			for (int i=0;i<8;i++)
				b_golay_bits_N[i]=floor((2-(b_golay_bits[i]*1.0))/2);//极性相反的格雷序列
			SC_tx_modulation(a_golay_bits,a_golay_sym,1);
			SC_tx_modulation(b_golay_bits,b_golay_sym,1);
			SC_tx_modulation(a_golay_bits_N,a_golay_sym_N,1);
			SC_tx_modulation(b_golay_bits_N,b_golay_sym_N,1);//插入的导频进行π/2 BPSK调制
			int Nblocks=ceil(Lsymin*1.0/(448*64));//每个数据块包含64个数据子块，其中每个子块的数据长度为448，导频长度为8
			if (Nblocks==1)
			{
				for (int i=1;i<Lsymin;i++)
					symout.push_back(symin[i]);
				//Lsymout=Lsymin;
			}
			else
			{
				//Lsymout=(Nblocks-1)*(64*64+8)+Lsymin;//输出符号数
				int Nlfsr=Nblocks-1;
				int Lblock=64*512+8;//每个数据块长度
				vector<int> S_lfsr;
				SC_LFSR(S_lfsr,Nlfsr);
				int LLblock=Lsymin-(Nblocks-1)*448*64;//最后一个数据块符号数
				for (int i=0;i<(Nblocks-1);i++)
				{
					if ((i%2)==0)
					{
						if (S_lfsr[i]==0)//根据线性寄存器输出选择导频极性
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
						if (S_lfsr[i]==0)//根据线性寄存器输出选择导频极性
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
				for (int ii=0;ii<LLblock;ii++)//最后一个数据块不需要插入导频
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
			hex2binary(b_golay_hex,b_golay_bits,16);//子块前插入的导频
			for (int i=0;i<64;i++)
				a_golay_bits_N[i]=floor((2-(a_golay_bits[i]*1.0))/2);
			for (int i=0;i<64;i++)
				b_golay_bits_N[i]=floor((2-(b_golay_bits[i]*1.0))/2);//极性相反的格雷序列
			SC_tx_modulation(a_golay_bits,a_golay_sym,1);
			SC_tx_modulation(b_golay_bits,b_golay_sym,1);
			SC_tx_modulation(a_golay_bits_N,a_golay_sym_N,1);
			SC_tx_modulation(b_golay_bits_N,b_golay_sym_N,1);//插入的导频进行π/2 BPSK调制
			int Nblocks=ceil(Lsymin*1.0/(448*64));//每个数据块包含64个数据子块，其中每个子块的数据长度为448，导频长度为64
			if (Nblocks==1)
			{
				for (int i=1;i<Lsymin;i++)
					symout.push_back(symin[i]);
			}
			else
			{
				int LLblock=Lsymin-(Nblocks-1)*448*64;//最后一个数据块符号数
				int Nlfsr=Nblocks-1;
				int Lblock=64*512+64;//每个数据块长度
				vector<int> S_lfsr;
				SC_LFSR(S_lfsr,Nlfsr);
				for (int i=0;i<(Nblocks-1);i++)
				{
					if ((i%2)==0)//根据极性选择导频a、b
					{
						if (S_lfsr[i]==0)//根据线性寄存器输出选择导频极性
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
						if (S_lfsr[i]==0)//根据线性寄存器输出选择导频极性
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
				for (int ii=0;ii<LLblock;ii++)//最后一个数据块不需要插入导频
				{
					symout.push_back(symin[(Nblocks-1)*448*64+ii]);
				}
			}
			break;
		}
	default:
		{
			cout<<"划分子块输入模式错误"<<endl;
			exit(EXIT_FAILURE);
			break;
		}
	}
}