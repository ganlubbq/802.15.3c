//��������������ȡ������
//����������a��b��

#include"genParam.h"
#include "stdafx.h"

int ceil(int a, int b) {
	if (a > 0 && b > 0) {
		if (a % b == 0)
			return a / b;
		else
			return a / b + 1;
	}
	return 0;
}