//函数描述：产生随机0、1序列
//函数参数：genbits-输出的比特序列；Nbits-产生的比特数

//#include <iostream>    
//#include <stdlib.h>      
//#include <time.h> 
#include"genParam.h"
#include "stdafx.h"


using namespace std;

void gen_prbs(vector<int> &genbits, int Nbits)
{
	srand((unsigned)time(0));     
    for(int i = 0; i < Nbits; i++)          //产生随机数    
        genbits.push_back(rand() % 2);
}