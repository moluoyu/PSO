/*!
 * \file main.c
 *
 * \author thnx1
 * \date 九月 2018
 *        分成3个o-d对，我们要做的是：
 *      1 分别求出每个o-d对的最小值，
 *      2 然后求三个最小里的最大值
 *       此PSO中，只是完成第一步，
 ************************************************************************************************************
 20180925 this is a branches  to test 
 目标函数进行修正为： x[i][j]cost[i][j]
 (ref:http://t.cn/EPMAvy1)
 **********************************************************************************************************/
#include "pso.h"
#include "stdio.h"
extern double ComputAFitness(struct PARTICLE* particle);
int main(int argc, const char *argv[])
{
	cur_n = 0;           //当前代数
	RandInitofSwarm();             //初始化粒子群
	//UpdateofVandX();        //速度和位置更新
	//UpdatePandGbest();    //更新个体历史最优解P和全局最优解GBest
	lastGlobal = swarm.GBestIndex;
	swarm.Particle[0].Fitness = swarm.Particle[lastGlobal].Fitness;
	for ( int i=1;i<Dim+1;i++)
	{
		swarm.Particle[0].X[i] = swarm.Particle[lastGlobal].X[i];
	}

	while (cur_n++ != ITE_N-1)//停止条件为代数ITE_N
	{
		UpdateofVandX();        //速度和位置更新
		UpdatePandGbest();    //更新个体历史最优解P和全局最优解GBest
		if((ComputAFitness(&swarm.Particle[0]))>ComputAFitness(&swarm.Particle[swarm.GBestIndex])) //
		{
			lastGlobal = swarm.GBestIndex;
			swarm.Particle[0].Fitness = swarm.Particle[lastGlobal].Fitness;
			for (int i = 1; i < Dim + 1; i++)
			{
				swarm.Particle[0].X[i] = swarm.Particle[lastGlobal].X[i];
			}
		}
		
	

	}
	printf("本次程序执行后，所有迭代次数中最优的值适应度为为： %f\n ", swarm.Particle[0].Fitness);
	for (int i=1;i<Dim+1;i++)
	{
		{
			printf("%.1f,", swarm.Particle[0].X[i]);
		}
	}

	//getchar();
	return 0;
}