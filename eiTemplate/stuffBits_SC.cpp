//SC mode 比特填充

#include "genParam.h"
#include "stdafx.h"

using namespace std;

void stuffBits_SC(std::vector<int> &bitsin, SC_param &SC_p)
{
	int NBits = bitsin.size();		//输入比特长度
	int preStuff = ceil(NBits, 8) * 8 - NBits;
	NBits = NBits + preStuff;
	for (int i = 0; i < preStuff; ++i)	//保证是8的倍数
		bitsin.push_back(0);
	int Lcode = 0;					//前向编码码字长度
	int Ldata = 0;					//码字信息位长度
	switch (SC_p.FECtype) 
	{
	case 0:
		{
			Lcode = 2040;
			Ldata = 1912;
			break;
		}
	case 1:
		{
			switch (SC_p.FECrate)
			{
			case 0:
				{
					Lcode = 672;
					Ldata = 336;
					break;
				}
			case 1:
				{
					Lcode = 672;
					Ldata = 420;
					break;
				}
			case 2:
				{
					Lcode = 672;
					Ldata = 504;
					break;
				}
			case 3:
				{
					Lcode = 672;
					Ldata = 588;
					break;
				}
			case 4:
				{
					Lcode = 1440;
					Ldata = 1344;
					break;
				}
			default:
				break;
			}
			break;
		}
	default:
		break;
	}

	int NbitsSubblock = 0;

	switch (SC_p.MCS)
	{
	case 0:
		{
			NbitsSubblock = 8;
			break;
		}
	case 1:
		{
			if (SC_p.subtype == 0)
				NbitsSubblock = 128;
			else 
				NbitsSubblock = 112;
			break;
		}
	case 2:
		{
			if (SC_p.subtype == 0)
				NbitsSubblock = 256;
			else 
				NbitsSubblock = 224;
			break;
		}
	case 3:
		{
			if (SC_p.subtype == 0)
				NbitsSubblock = 512;
			else 
				NbitsSubblock = 448;
			break;
		}
	case 4:
		{
			if (SC_p.subtype == 0)
				NbitsSubblock = 512;
			else 
				NbitsSubblock = 448;
			break;
		}
	case 5:
		{
			if (SC_p.subtype == 0)
				NbitsSubblock = 256;
			else 
				NbitsSubblock = 224;
			break;
		}
	case 6:
		{
			if (SC_p.subtype == 0)
				NbitsSubblock = 512;
			else 
				NbitsSubblock = 448;
			break;
		}
	case 7:
		{
			if (SC_p.subtype == 0)
				NbitsSubblock = 1024;
			else 
				NbitsSubblock = 896;
			break;
		}
	case 8:
		{
			if (SC_p.subtype == 0)
				NbitsSubblock = 1024;
			else 
				NbitsSubblock = 896;
			break;
		}
	case 9:
		{
			if (SC_p.subtype == 0)
				NbitsSubblock = 1024;
			else 
				NbitsSubblock = 896;
			break;
		}
	case 10:
		{
			if (SC_p.subtype == 0)
				NbitsSubblock = 1024;
			else 
				NbitsSubblock = 896;
			break;
		}
	case 11:
		{
			if (SC_p.subtype == 0)
				NbitsSubblock = 1024;
			else 
				NbitsSubblock = 896;
			break;
		}
	case 12:
		{
			if (SC_p.subtype == 0)
				NbitsSubblock = 1536;
			else 
				NbitsSubblock = 1344;
			break;
		}
	case 13:
		{
			if (SC_p.subtype == 0)
				NbitsSubblock = 2048;
			else 
				NbitsSubblock = 1792;
			break;
		}
	default:
		break;
	}

	int N_fec = ceil(NBits, Ldata);		//前向编码码字数
	int NBits2Encode = N_fec * Ldata;		//FEC编码前总的信息比特长度
	int L_ebits = NBits + N_fec * (Lcode - Ldata);	//length of bits in the encoded MAC frame body
	int N_subblocks = ceil(L_ebits, NbitsSubblock);	//The number of subblocks in the encoded MAC frame body
	int L_stuff = NbitsSubblock * N_subblocks - L_ebits;	//the length of stuff bits
	for (int i = 0; i < L_stuff; ++i)
		bitsin.push_back(0);
}