#ifndef FUNC_H
#define FUNC_H
#include<iostream>
#include<complex>
#include<vector>
using namespace std;
double maxCCDFData(double *s,int sizeN);
double sumCCDF(double *acceptPointArray,double *pPointArrayCCDF,int m_RealValuenSize,int ScaleXend,int Num_of_space);
void   bitrp (vector<complex<double>> &Data_In, int n);
int    FFT(vector<complex<double>> &Data_in, int n);
void   FFTShift(vector<complex<double>> &Data_in);
#endif