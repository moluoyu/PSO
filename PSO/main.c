#include "pso.h"
#include "stdio.h"


int main(int argc, const char *argv[])
{
	cur_n = 0;           //��ǰ����
	RandInitofSwarm();             //��ʼ������Ⱥ
	while (cur_n++ != ITE_N)
	{
		UpdatePandGbest();    //���¸�����ʷ���Ž�P��ȫ�����Ž�GBest
		UpdateofVandX();        //�ٶȺ�λ�ø��£�������

		

	}

	getchar();
	return 0;
}