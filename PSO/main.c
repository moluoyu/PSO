#include "pso.h"
#include "stdio.h"
extern FILE * fp;

int main(int argc, const char *argv[])
{
	cur_n = 0;           //当前代数
	numofacc = 0;
	RandInitofSwarm();             //初始化粒子群
	while (cur_n++ != ITE_N)
	{
		UpdatePandGbest();    //更新个体历史最优解P和全局最优解GBest
		UpdateofVandX();        //速度和位置更新

	}
	fclose(fp);
	printf("\n");
	printf("numofAccuracy=%d\n",numofacc);
	//getchar();
	return 0;
}