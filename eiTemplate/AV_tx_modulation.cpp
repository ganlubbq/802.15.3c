//����������AV-PHY���Ƴ���
//����������bitsin-������أ�symsout-������ţ�Nbits-����ı�������modtype-�������ͣ�1-BPSK��2-QPSK��4-16QAM��ueptype-UEP���ͣ�0-EEP��1-UEP

#include"genParam.h"
#include "stdafx.h"


using namespace std;
void AV_tx_modulation(vector<int> &bitsin, vector<complex<double> > &symsout, int modtype, int ueptype)
{
	int Nbits = bitsin.size();
	if (modtype == 1)
	{
		complex<double> map_temp[2] = {complex<double> (-1, 0),complex<double> (1, 0)};//ӳ���
		int map_index = 0;
		for (int i = 0; i < Nbits; i++)
		{
			map_index = bitsin[i];
			symsout[i] = map_temp[bitsin[i]];
		}
	}
	else
	{
		switch (ueptype)
		{
		case 0:
			{
				double d1 = 1.0;
			    double d2 = 1.0;
				switch (modtype)
				{
				case 2:
					{
						double nor_index = 1 / sqrt(d1 * d1 + d2 * d2);//��һ��ϵ��
						complex<double> map_temp[4] = {complex<double>(-d1, -d2), complex<double>(+d1, -d2), 
							                           complex<double>(-d1, +d2), complex<double>(+d1, +d2)};//ӳ���
						for (int i = 0; i < 4; i++)
							map_temp[i] = map_temp[i] * nor_index;
						int Nsyms = Nbits / modtype;
						vector<int> nums;
						//HSI_bits2nums(bitsin, nums, modtype);
						bits2nums(bitsin, nums, modtype);//����ת��Ϊ����
						for (int i = 0; i < Nsyms; i++)
						{
							int num_temp = nums[i];
							//symsout[i] = map_temp[num_temp];
							symsout.push_back(map_temp[num_temp]);
						}
						break;
					}
				case 4:
					{
						double nor_index = 1 / sqrt(5 * (d1 * d1 + d2 * d2));//��һ��ϵ��
						complex<double> map_temp[16] = {complex<double>(-3 * d1, -3 * d2), complex<double>(-3 * d1, -1 * d2), complex<double>(-3 * d1, +3 * d2), complex<double>(-3 * d1, +1 * d2), 
							                            complex<double>(-1 * d1, -3 * d2), complex<double>(-1 * d1, -1 * d2), complex<double>(-1 * d1, +3 * d2), complex<double>(-1 * d1, +1 * d2),
														complex<double>(+3 * d1, -3 * d2), complex<double>(+3 * d1, -1 * d2), complex<double>(+3 * d1, +3 * d2), complex<double>(+3 * d1, +1 * d2), 
														complex<double>(+1 * d1, -3 * d2), complex<double>(+1 * d1, -1 * d2), complex<double>(+1 * d1, +3 * d2), complex<double>(+1 * d1, +1 * d2)};//ӳ���
						for (int i = 0; i < 16; i++)
							map_temp[i] = map_temp[i] * nor_index;
						int Nsyms = Nbits / modtype;
						vector<int> nums;
						//HSI_bits2nums(bitsin, nums, modtype);
						bits2nums(bitsin, nums, modtype);//����ת��Ϊ����
						for (int i = 0; i < Nsyms; i++)
						{
							int num_temp = nums[i];
							symsout.push_back(map_temp[num_temp]);
						}
						break;
					}
				default:
					{
						cout<<"����ģʽ�������"<<endl;
				        exit(EXIT_FAILURE);
						break;
					}
				}
				break;
			}
		case 1:
			{
				double d1 = 1.25;
			    double d2 = 1.0;
				switch (modtype)
				{
				case 2:
					{
						double nor_index = 1 / sqrt(d1 * d1 + d2 * d2);//��һ��ϵ��
						complex<double> map_temp[4] = {complex<double>(-d1, -d2), complex<double>(+d1, -d2), 
							                           complex<double>(-d1, +d2), complex<double>(+d1, +d2)};//ӳ���
						for (int i = 0; i < 4; i++)
							map_temp[i] = map_temp[i] * nor_index;
						int Nsyms = Nbits / modtype;
						vector<int> nums;
						//HSI_bits2nums(bitsin, nums, modtype);
						bits2nums(bitsin, nums, modtype);//����ת��Ϊ����
						for (int i = 0; i < Nsyms; i++)
						{
							int num_temp = nums[i];
							symsout.push_back(map_temp[num_temp]);;
						}
						break;
					}
				case 4:
					{
						double nor_index = 1 / sqrt(5 * (d1 * d1 + d2 * d2));//��һ��ϵ��
						complex<double> map_temp[16] = {complex<double>(-3 * d1, -3 * d2), complex<double>(-3 * d1, -1 * d2), complex<double>(-3 * d1, +3 * d2), complex<double>(-3 * d1, +1 * d2), 
							                            complex<double>(-1 * d1, -3 * d2), complex<double>(-1 * d1, -1 * d2), complex<double>(-1 * d1, +3 * d2), complex<double>(-1 * d1, +1 * d2),
														complex<double>(+3 * d1, -3 * d2), complex<double>(+3 * d1, -1 * d2), complex<double>(+3 * d1, +3 * d2), complex<double>(+3 * d1, +1 * d2), 
														complex<double>(+1 * d1, -3 * d2), complex<double>(+1 * d1, -1 * d2), complex<double>(+1 * d1, +3 * d2), complex<double>(+1 * d1, +1 * d2)};//ӳ���
						for (int i = 0; i < 16; i++)
							map_temp[i] = map_temp[i] * nor_index;
						int Nsyms = Nbits / modtype;
						vector<int> nums;
						//HSI_bits2nums(bitsin, nums, modtype);
						bits2nums(bitsin, nums, modtype);//����ת��Ϊ����
						for (int i = 0; i < Nsyms; i++)
						{
							int num_temp = nums[i];
							symsout.push_back(map_temp[num_temp]);
						}
						break;
					}
				default:
					{
						cout<<"����ģʽ�������"<<endl;
						exit(EXIT_FAILURE);
						break;
					}
				}
				break;
			}
		case 2:
			{
				double d1 = 1.0;
				double d2 = 1.0;
				switch (modtype)
				{
				case 2:
					{
						double nor_index = 1 / sqrt(d1 * d1 + d2 * d2);//��һ��ϵ��
						complex<double> map_temp[4] = {complex<double>(-d1, -d2), complex<double>(+d1, -d2), 
							complex<double>(-d1, +d2), complex<double>(+d1, +d2)};//ӳ���
						for (int i = 0; i < 4; i++)
							map_temp[i] = map_temp[i] * nor_index;
						int Nsyms = Nbits / modtype;
						vector<int> nums;
						//HSI_bits2nums(bitsin, nums, modtype);
						bits2nums(bitsin, nums, modtype);//����ת��Ϊ����
						for (int i = 0; i < Nsyms; i++)
						{
							int num_temp = nums[i];
							//symsout[i] = map_temp[num_temp];
							symsout.push_back(map_temp[num_temp]);
						}
						break;
					}
				case 4:
					{
						double nor_index = 1 / sqrt(5 * (d1 * d1 + d2 * d2));//��һ��ϵ��
						complex<double> map_temp[16] = {complex<double>(-3 * d1, -3 * d2), complex<double>(-3 * d1, -1 * d2), complex<double>(-3 * d1, +3 * d2), complex<double>(-3 * d1, +1 * d2), 
							complex<double>(-1 * d1, -3 * d2), complex<double>(-1 * d1, -1 * d2), complex<double>(-1 * d1, +3 * d2), complex<double>(-1 * d1, +1 * d2),
							complex<double>(+3 * d1, -3 * d2), complex<double>(+3 * d1, -1 * d2), complex<double>(+3 * d1, +3 * d2), complex<double>(+3 * d1, +1 * d2), 
							complex<double>(+1 * d1, -3 * d2), complex<double>(+1 * d1, -1 * d2), complex<double>(+1 * d1, +3 * d2), complex<double>(+1 * d1, +1 * d2)};//ӳ���
						for (int i = 0; i < 16; i++)
							map_temp[i] = map_temp[i] * nor_index;
						int Nsyms = Nbits / modtype;
						vector<int> nums;
						//HSI_bits2nums(bitsin, nums, modtype);
						bits2nums(bitsin, nums, modtype);//����ת��Ϊ����
						for (int i = 0; i < Nsyms; i++)
						{
							int num_temp = nums[i];
							symsout.push_back(map_temp[num_temp]);
						}
						break;
					}
				default:
					{
						cout<<"����ģʽ�������"<<endl;
						exit(EXIT_FAILURE);
					}
				}
				break;
			}
		default:
			{
				cout<<"UEPģʽ�������"<<endl;
				exit(EXIT_FAILURE);
			}
		}
	}
}