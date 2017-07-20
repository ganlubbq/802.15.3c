//函数描述：HSI-PHY前导生成模块
//参数描述：HSI_preamble:HSI PHY前导,结构与SC PHY一致；Pre_mod:前导模式：CMS-0；MR-1；HR-2；ti-选择是否进行载波交织

//#include<iostream>
//#include<complex>
#include"genParam.h"
#include "stdafx.h"

using namespace std;

void HSI_genPreamble(vector<complex<double> > &vHSI_Pre, int Pre_mod, int ti)
{
	int a_golay_hex_32[32] = {0x0,0x5,0x3,0x6,0x6,0x3,0x5,0x0,0x0,0x5,0xC,0x9,0x6,0x3,0xA,0xF,
							  0xF,0xA,0xC,0x9,0x9,0xC,0xA,0xF,0x0,0x5,0xC,0x9,0x6,0x3,0xA,0xF};
	int b_golay_hex_32[32] = {0x0,0xA,0x3,0x9,0x6,0xC,0x5,0xF,0x0,0xA,0xC,0x6,0x6,0xC,0xA,0x0,
		                      0xF,0x5,0xC,0x6,0x9,0x3,0xA,0x0,0x0,0xA,0xC,0x6,0x6,0xC,0xA,0x0};
	vector<int> a_golay_binary_128;
	hex2binary(a_golay_hex_32, a_golay_binary_128, 32);//a128
	vector<int> b_golay_binary_128;
	hex2binary(b_golay_hex_32, b_golay_binary_128, 32);//b128
	vector<int> a_golay_binary_128_N (128, 0);
	for (int i = 0; i < 128; i++)
				a_golay_binary_128_N[i]=floor((2-(a_golay_binary_128[i]*1.0))/2);//a128补码
	vector<int> b_golay_binary_128_N (128, 0);
	for (int i = 0; i < 128; i++)
				b_golay_binary_128_N[i]=floor((2-(b_golay_binary_128[i]*1.0))/2);//b128补码
	vector<int> a_golay_binary_256;
	for (int i = 0; i < 128; i++)
		a_golay_binary_256.push_back(a_golay_binary_128[i]);
	for (int i = 0; i < 128; i++)
		a_golay_binary_256.push_back(a_golay_binary_128_N[i]);
	vector<int> b_golay_binary_256;
	for (int i = 0; i < 128; i++)
		b_golay_binary_256.push_back(b_golay_binary_128[i]);
	for (int i = 0; i < 128; i++)
		b_golay_binary_256.push_back(b_golay_binary_128_N[i]);//b256
	switch (Pre_mod)
	{
	case 0:
		{
			int Lpreb = 48 * 128 + 7 * 128 + (5 * 256);//前导长度
			vector<int> sync;//前导sync部分
			for (int i = 0; i < 48; i++)
			{
				for (int j = 0; j < 128; j++)
					sync.push_back(b_golay_binary_128[j]);
			}
			vector<int> sfd;//前导sfd部分
			int seed[7] = {1, -1, 1, 1, -1, -1, -1};
			for (int i = 0; i < 7; i++)
			{
				if (seed[i] == 1)
				{
					for (int j = 0; j < 128; j++)
						sfd.push_back(b_golay_binary_128[j]);
				}
				else
				{
					for (int j = 0; j < 128; j++)
						sfd.push_back(b_golay_binary_128_N[j]);
				}
			}
			vector<int> ces;//前导ces部分
			for (int i = 0; i < 128; i++)
				ces.push_back(a_golay_binary_128[i]);
			for (int i = 0; i < 256; i++)
				ces.push_back(a_golay_binary_256[i]);
			for (int i = 0; i < 256; i++)
				ces.push_back(b_golay_binary_256[i]);
			for (int i = 0; i < 256; i++)
				ces.push_back(a_golay_binary_256[i]);
			for (int i = 0; i < 256; i++)
				ces.push_back(b_golay_binary_256[i]);
			for (int i = 0; i < 128; i++)
				ces.push_back(b_golay_binary_128[i]);
			vector<int> Preamble;//Preamble
			for (int i = 0; i < sync.size(); i++)
				Preamble.push_back(sync[i]);
			for (int i = 0; i < sfd.size(); i++)
				Preamble.push_back(sfd[i]);
			for (int i = 0; i < ces.size(); i++)
				Preamble.push_back(ces[i]);
			//SC_tx_modulation(Preamble, vHSI_Pre, 1);//对preamble进行调制
			vector<complex<double>> Preamble_mod;
			HSI_tx_modulation(Preamble, Preamble_mod, 2, 0);//对preamble进行调制
			HSI_OFDMer_header(Preamble_mod, vHSI_Pre, ti);
			//int Num_ifft = Preamble_mod.size() / 512;
			//for (int i = 0; i <= Num_ifft; ++i)
			//{
			//	if (i != Num_ifft)
			//	{
			//		vector<complex<double>> ifft_temp;
			//		for (int ii = 0; ii < 512; ++ii)
			//			ifft_temp.push_back(Preamble_mod[i * 512 + ii]);
			//		IFFT(ifft_temp, 512);
			//		for (auto ii = ifft_temp.cbegin(); ii != ifft_temp.cend(); ++ii)
			//			vHSI_Pre.push_back(*ii);
			//	}
			//	else
			//	{
			//		vector<complex<double>> ifft_temp;
			//		//int Num_last = (Preamble_mod.size() - 512 * i);
			//		for (int ii = 512 * i; ii < Preamble_mod.size(); ++ii)
			//			ifft_temp.push_back(Preamble_mod[ii]);
			//		IFFT(ifft_temp, ifft_temp.size());
			//		for (auto ii = ifft_temp.cbegin(); ii != ifft_temp.cend(); ++ii)
			//			vHSI_Pre.push_back(*ii);
			//	}
			//}
			break;
		}
	case 1:
		{
			int Lpreb = 14 * 128 + 4 * 128 + (4 * 256 + 128);//前导长度
			vector<int> sync;//前导sync部分
			for (int i = 0; i < 14; i++)
			{
				for (int j = 0; j < 128; j++)
					sync.push_back(a_golay_binary_128[j]);
			}
			vector<int> sfd;//前导sfd部分
			int seed[4] = {1, -1, 1, -1};
			for (int i = 0; i < 4; i++)
			{
				if (seed[i] == 1)
				{
					for (int j = 0; j < 128; j++)
						sfd.push_back(a_golay_binary_128[j]);
				}
				else
				{
					for (int j = 0; j < 128; j++)
						sfd.push_back(a_golay_binary_128_N[j]);
				}
			}
			vector<int> ces;//前导ces部分
			for (int i = 0; i < 256; i++)
				ces.push_back(a_golay_binary_256[i]);
			for (int i = 0; i < 256; i++)
				ces.push_back(b_golay_binary_256[i]);
			for (int i = 0; i < 256; i++)
				ces.push_back(a_golay_binary_256[i]);
			for (int i = 0; i < 256; i++)
				ces.push_back(b_golay_binary_256[i]);
			for (int i = 0; i < 128; i++)
				ces.push_back(b_golay_binary_128[i]);
			vector<int> Preamble;//Preamble
			for (int i = 0; i < sync.size(); i++)
				Preamble.push_back(sync[i]);
			for (int i = 0; i < sfd.size(); i++)
				Preamble.push_back(sfd[i]);
			for (int i = 0; i < ces.size(); i++)
				Preamble.push_back(ces[i]);
			//SC_tx_modulation(Preamble, vHSI_Pre, 1);//对preamble进行调制
			//HSI_tx_modulation(Preamble, vHSI_Pre, 2, 0);//QPSK调制
			/***************************测试数据*****************************/
			/*ofstream AV_MCS0_Preamble("AV_MCS0_Preamble.txt");
			for (int i = 0; i < Preamble.size(); ++i)
				AV_MCS0_Preamble << Preamble[i] << endl;*/
			/**************************************************************/
			vector<complex<double>> Preamble_mod;
			HSI_tx_modulation(Preamble, Preamble_mod, 2, 0);//对preamble进行调制
			/***************************测试数据*****************************/
			/*ofstream AV_MCS0_Preamble_map("AV_MCS0_Preamble_map.txt");
			for (int i = 0; i < Preamble_mod.size(); ++i)
				AV_MCS0_Preamble_map << Preamble_mod[i] << endl;*/
			/**************************************************************/
			HSI_OFDMer_header(Preamble_mod, vHSI_Pre, ti);
			/***************************测试数据*****************************/
			/*ofstream AV_MCS0_Preamble_ofdm("AV_MCS0_Preamble_ofdm.txt");
			for (int i = 0; i < vHSI_Pre.size(); ++i)
				AV_MCS0_Preamble_ofdm << vHSI_Pre[i] << endl;*/
			/**************************************************************/
			//int Num_ifft = Preamble_mod.size() / 512;
			//for (int i = 0; i <= Num_ifft; ++i)
			//{
			//	if (i != Num_ifft)
			//	{
			//		vector<complex<double>> ifft_temp;
			//		for (int ii = 0; ii < 512; ++ii)
			//			ifft_temp.push_back(Preamble_mod[i * 512 + ii]);
			//		IFFT(ifft_temp, 512);
			//		for (auto ii = ifft_temp.cbegin(); ii != ifft_temp.cend(); ++ii)
			//			vHSI_Pre.push_back(*ii);
			//	}
			//	else
			//	{
			//		vector<complex<double>> ifft_temp;
			//		//int Num_last = (Preamble_mod.size() - 512 * i);
			//		for (int ii = 512 * i; ii < Preamble_mod.size(); ++ii)
			//			ifft_temp.push_back(Preamble_mod[ii]);
			//		IFFT(ifft_temp, ifft_temp.size());
			//		for (auto ii = ifft_temp.cbegin(); ii != ifft_temp.cend(); ++ii)
			//			vHSI_Pre.push_back(*ii);
			//	}
			//}
			break;
		}
	case 2:
		{
			int Lpreb = 14 * 128 + 4 * 128 + (4 * 256 + 128);//前导长度
			vector<int> sync;//前导sync部分
			for (int i = 0; i < 14; i++)
			{
				for (int j = 0; j < 128; j++)
					sync.push_back(a_golay_binary_128[j]);
			}
			vector<int> sfd;//前导sfd部分
			int seed[4] = {1, 1, -1, -1};
			for (int i = 0; i < 4; i++)
			{
				if (seed[i] == 1)
				{
					for (int j = 0; j < 128; j++)
						sfd.push_back(a_golay_binary_128[j]);
				}
				else
				{
					for (int j = 0; j < 128; j++)
						sfd.push_back(a_golay_binary_128_N[j]);
				}
			}
			vector<int> ces;//前导ces部分
			for (int i = 0; i < 256; i++)
				ces.push_back(a_golay_binary_256[i]);
			for (int i = 0; i < 256; i++)
				ces.push_back(b_golay_binary_256[i]);
			for (int i = 0; i < 256; i++)
				ces.push_back(a_golay_binary_256[i]);
			for (int i = 0; i < 256; i++)
				ces.push_back(b_golay_binary_256[i]);
			for (int i = 0; i < 128; i++)
				ces.push_back(b_golay_binary_128[i]);
			vector<int> Preamble;//Preamble
			for (int i = 0; i < sync.size(); i++)
				Preamble.push_back(sync[i]);
			for (int i = 0; i < sfd.size(); i++)
				Preamble.push_back(sfd[i]);
			for (int i = 0; i < ces.size(); i++)
				Preamble.push_back(ces[i]);
			//SC_tx_modulation(Preamble, vHSI_Pre, 1);//对preamble进行调制
			//HSI_tx_modulation(Preamble, vHSI_Pre, 2, 0);//QPSK调制
			vector<complex<double>> Preamble_mod;
			HSI_tx_modulation(Preamble, Preamble_mod, 2, 0);//对preamble进行调制
			HSI_OFDMer_header(Preamble_mod, vHSI_Pre, ti);
			//int Num_ifft = Preamble_mod.size() / 512;
			//for (int i = 0; i <= Num_ifft; ++i)
			//{
			//	if (i != Num_ifft)
			//	{
			//		vector<complex<double>> ifft_temp;
			//		for (int ii = 0; ii < 512; ++ii)
			//			ifft_temp.push_back(Preamble_mod[i * 512 + ii]);
			//		IFFT(ifft_temp, 512);
			//		for (auto ii = ifft_temp.cbegin(); ii != ifft_temp.cend(); ++ii)
			//			vHSI_Pre.push_back(*ii);
			//	}
			//	else
			//	{
			//		vector<complex<double>> ifft_temp;
			//		//int Num_last = (Preamble_mod.size() - 512 * i);
			//		for (int ii = 512 * i; ii < Preamble_mod.size(); ++ii)
			//			ifft_temp.push_back(Preamble_mod[ii]);
			//		IFFT(ifft_temp, ifft_temp.size());
			//		for (auto ii = ifft_temp.cbegin(); ii != ifft_temp.cend(); ++ii)
			//			vHSI_Pre.push_back(*ii);
			//	}
			//}
			break;
		}
	default:
		{
			cout << "前导模式错误！！" << endl;
			break;
		}
	}
}