//�����������������0��1����
//����������genbits-����ı������У�Nbits-�����ı�����

//#include <iostream>    
//#include <stdlib.h>      
//#include <time.h> 
#include"genParam.h"
#include "stdafx.h"


using namespace std;

void gen_prbs(vector<int> &genbits, int Nbits)
{
	srand((unsigned)time(0));     
    for(int i = 0; i < Nbits; i++)          //���������    
        genbits.push_back(rand() % 2);
}