#include "pso.h"
#include "stdio.h"
extern FILE * fp;

int main(int argc, const char *argv[])
{
	cur_n = 0;           //��ǰ����
	numofacc = 0;
	RandInitofSwarm();             //��ʼ������Ⱥ
	while (cur_n++ != ITE_N)
	{
		UpdatePandGbest();    //���¸�����ʷ���Ž�P��ȫ�����Ž�GBest
		UpdateofVandX();        //�ٶȺ�λ�ø���

	}
	fclose(fp);
	printf("\n");
	printf("numofAccuracy=%d\n",numofacc);
	//getchar();
	return 0;
}