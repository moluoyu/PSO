#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "math.h"
#include "pso.h"

f()
{

}
/*计算适应度函数的适应度*/
static double ComputAFitness(double X[]) //求x^2 + y^2 + 3 最小值
{

	return X[0] * X[0] + X[1] * X[1] + 3;
}

//初始化种群
void RandInitofSwarm(void)
{
	int i, j;
	//学习因子C1,C2
	swarm.C1 = 2.0;
	swarm.C2 = 2.0;
	for (j = 0; j < Dim; j++)
	{
		swarm.Xdown[j] = 15;    //搜索空间范围，绿灯时间最小值
		swarm.Xup[j] = 90;		// 绿灯时间最大值
		swarm.Vmax[j] = 0.1;       //粒子飞翔速度最大值
	}

	srand((unsigned)time(NULL));
	for (i = 0; i < PNum; i++)      //PNum 总群规模，即是粒子个数
	{
		for (j = 0; j < Dim; j++)   //设定每个粒子每个维度上的随机位置与随机速度
		{
			swarm.Particle[i].X[j] = rand() / (double)RAND_MAX * (swarm.Xup[j] - swarm.Xdown[j]) + swarm.Xdown[j];
			//-Xdown~Xup
			swarm.Particle[i].V[j] = rand() / (double)RAND_MAX * swarm.Vmax[j] * 2 - swarm.Vmax[j];
			//-Vmax~Vmax
			swarm.Particle[i].P[j] = swarm.Particle[i].X[j]; //设定初代粒子的当前最优值的位置

		}

		swarm.Particle[i].Fitness = ComputAFitness(swarm.Particle[i].X);  //计算每个粒子的适应度值

	}
	

}

//update  V and X 更新速度和位置
void UpdateofVandX(void)
{
	int i, j;
	srand((unsigned)time(NULL));
	for (i = 0; i < PNum; i++)	//pNum种群大小
	{
		//速度更新公式：标准pso:    w*v[i] +c1xrand()x(pbest[i]-x[i])+c2xrand()x(gbest[i]-x[i])		
		//w为惯性因子，值为非负，c1 c2为学习因子，一般为常数效果好，常取为 2
		for (j = 0; j < Dim; j++)
			swarm.Particle[i].V[j] = W_FUN * swarm.Particle[i].V[j] +
			rand() / (double)RAND_MAX * swarm.C1 * (swarm.Particle[i].P[j] - swarm.Particle[i].X[j]) +
			rand() / (double)RAND_MAX * swarm.C2 * (swarm.GBest[j] - swarm.Particle[i].X[j]);
		for (j = 0; j < Dim; j++)
		{
			if (swarm.Particle[i].V[j] > swarm.Vmax[j])  //控制粒子速度范围
			{
				swarm.Particle[i].V[j] = swarm.Vmax[j];
			}
			if (swarm.Particle[i].V[j] < -swarm.Vmax[j])
			{
				swarm.Particle[i].V[j] = -swarm.Vmax[j];
			}
		}

		for (j = 0; j < Dim; j++)     //更新位置：x(i+1)=x(i)+v(i)
		{
			swarm.Particle[i].X[j] += swarm.Particle[i].V[j];
			if (swarm.Particle[i].X[j] > swarm.Xup[j])
				swarm.Particle[i].X[j] = swarm.Xup[j];
			if (swarm.Particle[i].X[j] < swarm.Xdown[j])
				swarm.Particle[i].X[j] = swarm.Xdown[j];
		}
		/*********
		2017/7/26
		因为少了下面这行代码，找了一个晚上
		**********/
		
		swarm.Particle[i].Fitness = ComputAFitness(swarm.Particle[i].X);  //重新计算每个粒子的适应度值
	}
	
}

/*更新个体极值P和全局极值GBest*/
void UpdatePandGbest(void)
{
	int i, j;
	//update of P if the X is less than current P
	for (i = 0; i < PNum; i++)
	{
		if (swarm.Particle[i].Fitness < ComputAFitness(swarm.Particle[i].P)) //更新当前这一代个体p值，
		{
			for (j = 0; j < Dim; j++)
			{
				swarm.Particle[i].P[j] = swarm.Particle[i].X[j];
			}
		}
	}
	
	//update of GBest

	for (i = 0; i < PNum; i++)
	{
		
		if (ComputAFitness(swarm.Particle[i].P) < ComputAFitness(swarm.Particle[swarm.GBestIndex].P))
		{
			//mppbest = ComputAFitness(swarm.Particle[i].P);
			swarm.GBestIndex = i;
		}
			
	}

	for (j = 0; j < Dim; j++)
	{
		swarm.GBest[j] = swarm.Particle[swarm.GBestIndex].P[j];
	}

	printf("The %dth iteraction.\n", cur_n);
	printf("GBestIndex:%d \n", swarm.GBestIndex);
	printf("GBest:");
	for (j = 0; j<Dim; j++)
	{
		printf("%.4f ,", swarm.GBest[j]);
	}
	printf("\n");
	printf("Fitness of GBest: %f \n\n", ComputAFitness(swarm.Particle[swarm.GBestIndex].P));
}