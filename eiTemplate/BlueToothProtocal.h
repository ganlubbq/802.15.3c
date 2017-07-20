#ifndef BLUETOOTHHEAD_H
#define BLUETOOTHHEAD_H

#include "stdafx.h"
#include <stdio.h>  
#include <stdlib.h> 
#include <complex>
#include <iostream>
#include <cmath>
#include <string>
#include <assert.h>
#include "BlueToothParams.h"

using namespace std;

//typedef std::complex<double> complex;

int intmax(int a,int b);
int intmin(int a,int b);

void conv(double u[],double v[],double w[], int m, int n);  
 
double erf_fuction(double in);

void Tentotwo_fuction(int data_in,int length,char data_out[]);

void Gauss_fuction(double Rs,int oversample, int irfn,double Gauss_out[]);

void Inversion(char data_in[] ,int data_len,char data_out[]);

void Deconv(char data_in[],char data_indiv[],char data_out[],int data_in_len,int data_indiv_len);

void bluetooth_CRC16(char data_in[],int data_len,char CRC_statein[],char CRC_out[]);

void bluetooth_HEC8(char data_in[],int data_len,char HEC_statein[],char HEC_out[]);

void bluetooth_whitening(char data_in[],int data_len,char whiten_state[],char whiten_out[]);

void bluetooth_FEC_encode(char data_in[],int data_len,double code_rate,char encode_out[],int encode_len, char EFC_statein[]);

void bluetooth_access_sync_generator( char Lap_addr[],int Lap_addr_len,char sync_out[]);

void bluetooth_access_preamble_generator( char pream_sync_data[] ,char preamble_out[]);

void bluetooth_trailer_generator( char data_in[],char data_out[],int datain_len);

void bluetooth_access_trailer_generator( char preamble_data[],char pream_sync_trailer[]);

void bluetooth_header_generator(Packettype Packettype,Transtype transtype,char ltaddress[],char HEC_state[],char Header_out[],int Header_len,char EFC_state[]);

void bluetooth_access_generator( char Lapaddress[], int Lapaddress_len, char Access_out[]);

void bluetooth_payload_generator(Packettype packettype,char lapaddress[],int lapaddress_len,char crc_state[],char efc_state[],char payload_in[],int data_len,char payload_out[]);

void bluetooth_packet_generator(Packettype packettype, Transtype transtype,char lapaddress[], char crc_state[],char hec_state[],char efc_state[],char data_in[],int data_len,char payload_out[], int &packet_len);

void bluetooth_GFSK_modulation( char date_in[],int data_inlen, double I_gfsk[],double Q_gfsk[],double Rs, double fc, double BTb, int oversample);

void bluetooth_waveform_generator(BlueToothParams *BTpacket,double I_gfsk[],double Q_gfsk[],char data_in[],int data_inlen, int &Packet_len);


#endif