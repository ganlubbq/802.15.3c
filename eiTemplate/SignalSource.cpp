#include "stdafx.h"
#include "genParam.h"

using namespace std;

vector<int> PN9(int length, int seed)
{
	// 确保随机种子的范围正确
	if (seed>511)
		seed = 511;
	else if (seed<0)
		seed =0;
	vector<int> src;

	int connection [] ={1,0,0,0,0,1,0,0,0,1};
	int M = 9;// sizeof(connection) / sizeof(connection[0])-1; //寄存器位数
	int con[9]={0};
	for(int i=0;i<M;i++)
		con[i]=connection[i+1]; //用于计算的抽头位数 c1~c9

	int registers[9]={0}; //把10进制种子seed转成二进制比特，填充到寄存器中，低位填充到DM位
	int j=M-1;
	while(seed)
	{
		registers[j]=seed%2;
		seed/=2;
		j--;
	}

	for(int i=0;i<length;i++)
	{
		int tmp=0;
		src.push_back(registers[M-1]); //寄存器M位的值作为PN9序列的一个比特
		for(int m=0;m<M;m++)
			tmp += registers[m] * con[m];//寄存器与抽头系数按位乘

		tmp = tmp % 2;  //模2操作
		for(int n=M-1;n>0;n--)
			registers[n]=registers[n-1]; // 寄存器移位
		registers[0]=tmp; //将tmp2作为反馈的值，输入到寄存器的第一位i
	}

	return src;
}

vector<int> PN15(int length, int seed)
{
	// 输入保护
	if (seed > 32767)
		seed = 32767;
	else if (seed<0)
		seed = 0;

	vector<int> src;

	int connection [] = {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1};//c14=1，c15=1
	int M = 15;// sizeof(connection) / sizeof(connection[0])-1; //寄存器位数

	int con[15]={0};
	for(int i=0;i<M;i++)
		con[i]=connection[i+1]; //用于计算的抽头位数

	int registers[15]={0};
	int j = M-1;
	while(seed)
	{
		registers[j]=seed%2;
		seed/=2;
		j--;
	}

	for(int i = 0; i < length; i++)
	{
		int tmp=0;
		src.push_back(registers[M-1]); //寄存器M位的值作为PN9序列的一个比特
		for(int m=0;m<M;m++)
			tmp+=registers[m]*con[m];    //寄存器与抽头系数按位乘
		tmp=tmp%2;  //模2操作
		for(int n=M-1;n>0;n--)
			registers[n]=registers[n-1]; // 寄存器移位
		registers[0]=tmp; //将tmp2作为反馈的值，输入到寄存器的第一位i
	}
	return src;
}

vector<int> All0(int length)
{
	vector<int> src;
	for (int i = 0; i < length; i++)
		src.push_back(0);
	return src;
}

vector<int> FromFile(int length, const char* filename)
{
	vector<int> src;

	ifstream file;
	file.open(filename);
	if (!file)
		return src;

	int count = 0;//统计文件位数
	char c = '0';
	while (file.get(c) && count<length) 
	{
		int temp = (c=='0') ? 0 : 1;
		src.push_back(temp);
		count++;
	}
	file.close();

	// 不足位全部补零
	if (count < length)
		for (int i = count; i < length; i++)
			src.push_back(0);

	return src;
}

vector<int> GenerateSource(int mode,int length, int seed, const char* filename)
{
	vector<int> src;
	switch (mode)
	{
	case 0: //PN9
		src = PN9(length,seed);
		break;
	case 1: //PN15
		src = PN15(length,seed);
		break;
	case 2: //ALL0
		src = All0(length);
		break;
	case 3: //read file
		src = FromFile(length,filename);
		break;
	default: //PN9
		src = PN9(length,seed);
		break;
	}
	return src;
}