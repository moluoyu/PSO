#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "math.h"
#include "pso.h"
#include <memory.h>
/**
* \method
*
* \brief 统计当前第i辆车在选择第j条道路的情况下，当前情况下从第1辆到第i辆，所有已经选择同一条道路的车辆总数numofload
* 用于计算当前道路下的路阻情况（以时间为评价标准）
* \param
* \param
* \author thnx1
* \date 九月 2018
*/
//int numOfLoad1 = 0, numOfLoad2 = 0, numOfLoad3 = 0;????还是有问题
int numofVehicle(struct PARTICLE* particle,double X[], int n)
{
	int num = 0;
	int resOfV=0;
	int tempNum1 = 0, tempNum2 = 0, tempNum3 = 0;
	//printf("%d,%d,%d\n", particle->numOfLoad1, particle->numOfLoad2, particle->numOfLoad3);
	if (4 == (int)X[n])
	{
		
		tempNum1++;
		particle->numOfLoad1 += tempNum1;
		resOfV = particle->numOfLoad1;
	}
	if (2 == (int)X[n])
	{
		
		tempNum2++;
		particle->numOfLoad2 += tempNum2;
		resOfV = particle->numOfLoad2;
	}
	if (1 == (int)X[n])
	{
		
		tempNum3++;
		particle->numOfLoad3 += tempNum3;
		resOfV = particle->numOfLoad3;
	}
	return resOfV;
}
/**
* \method
*
* \brief 计算不同路径下的路阻值（这里为：路径的行程时间）
* 每条
* \param int in_x  传入的x[i]代表第i辆车的选择路径结果
*随机生成每辆车的选择路径的值，
* 4 ---100
* 2 ---010
* 1 ---001
* \author thnx1
* \date 九月 2018
*/
double countCost(struct PARTICLE* particle,double X[], int n)
{
	double traffic = 0.0;
	double costTime = 0.0;
	double gapofTime = 0.0;
	double resOfC = 0.0;
	int  totalNum = numofVehicle(particle,X, n);
	switch ((int)X[n])
	{
		/**
		 * \brief
		 * 后续版本（待做）： * BPR函数计算不同交通流量下的路阻函数         t=t0(1+a(q/c)^b)
		 *
		 */
	case 4:
		if (particle->numOfLoad1 > 1)
		{
			gapofTime = ((n - 1)*5.0);//每5min间隔进行发一辆车
			traffic = (double)totalNum / gapofTime;//待修改为bpr函数
			if (traffic >= 0 && traffic <= 0.3*capOfLoad1)//随着车流量的增加，Cost应该越来越大  欠饱和
			{
				resOfC = 4.0;
			}
			else if (traffic > 0.3*capOfLoad1 && traffic <= 0.6*capOfLoad1)//正常饱和
			{
				resOfC = 5.0;
			}
			else if (traffic > 0.6*capOfLoad1 && traffic <= capOfLoad1)//过饱和
			{
				resOfC = 6.0;
			}

		}
		else//最开始时,由于车流比较小，没法计算路阻函数值
		{
			resOfC = 4.0;
		}
		break;
	case 2:
		if (particle->numOfLoad2 > 1)
		{
			gapofTime = ((n - 1)*5.0);
			traffic = (double)totalNum / gapofTime;
			if (traffic >= 0 && traffic <= 0.3*capOfLoad1)//随着车流量的增加，Cost应该越来越大 欠饱和
			{
				resOfC = 2.0;
			}
			else if (traffic > 0.3*capOfLoad1 && traffic <= 0.6*capOfLoad1)//正常饱和
			{
				resOfC = 4.0;
			}
			else if (traffic > 0.6*capOfLoad1 && traffic <= capOfLoad1)//过饱和
			{
				resOfC = 6.0;
			}
		}
		else//最开始时,由于车流比较小，没法计算路阻函数值
		{
			resOfC = 2.0;
		}
		break;
	case 1:
		if (particle->numOfLoad3 > 1)
		{
			gapofTime = ((n - 1)*5.0);
			traffic = (double)totalNum / gapofTime;
			if (traffic >= 0 && traffic <= 0.3*capOfLoad3)//随着车流量的增加，Cost应该越来越大 欠饱和
			{
				resOfC = 1.0;
			}
			else if (traffic > 0.3*capOfLoad3 && traffic <= 0.6*capOfLoad3)//正常饱和
			{
				resOfC = 2.0;
			}
			else if (traffic > 0.6*capOfLoad3 && traffic <= capOfLoad3)//过饱和
			{
				resOfC = 3.0;
			}
		}
		else//最开始时,由于车流比较小，没法计算路阻函数值,值过大，不在上述范围内
		{
			resOfC = 1.0;
		}
		break;
	}
	return resOfC;
}


static  double ComputAFitness(struct PARTICLE* particle,double X[]) //
{
	double resOfFit = 0.0;
	for (int i = 1; i < Dim + 1; i++)
	{
		//to do code 
		resOfFit += countCost(particle,X, i);
	}
	return resOfFit;
}

/**
* \method
*
* \brief 随机生成每辆车的选择路径的值，
* 4 ---100
* 2 ---010
* 1 ---001
* \param
* \param
* \author thnx1
* \date 九月 2018
*/
double randomGenValue()
{
	int a = rand() % 3 + 1;
	double temp=0.0;
	switch (a)
	{
	case 1:
		temp = 1.0;
		break;
	case 2:
		temp = 2.0;
		break;
	case 3:
		temp = 4.0;
		break;
	}
	return  temp;
}
double randomGenSpeed()
{

	int a = rand() % 2 + 1;
	double temp=0.0;
	switch (a)
	{
	case 1:
		temp = 1.0;
		break;
	case 2:
		temp = 2.0;
		break;
	}
	return  temp;
}

//初始化种群
void RandInitofSwarm(void)
{
	int i, j;
	//学习因子C1,C2
	swarm.C1 = 2.0;
	swarm.C2 = 2.0;
	swarm.GBestIndex = 1;
	for (j = 1; j < Dim + 1; j++)
	{
		swarm.Xdown[j] = 1.0;    //每辆车的选择结果最小为1
		swarm.Xup[j] = 4.0;		// 每辆车的选择结果最大为4
		swarm.Vmax[j] = 2.0;       //粒子飞翔速度最大值
	}

	srand((unsigned)time(NULL));
	for (i = 1; i < PNum + 1; i++)      //PNum 总群规模，即是粒子个数
	{
		for (j = 1; j < Dim + 1; j++)   //设定每个粒子每个维度上的随机位置与随机速度
		{
			//	swarm.Particle[i].X[j] = rand() / (double)RAND_MAX * (swarm.Xup[j] - swarm.Xdown[j]) + swarm.Xdown[j];
			swarm.Particle[i].X[j] = randomGenValue();
			//-Xdown~Xup
			// swarm.Particle[i].V[j] = rand() / (double)RAND_MAX * swarm.Vmax[j] * 2 - swarm.Vmax[j];
			swarm.Particle[i].V[j] = randomGenSpeed();

			//-Vmax~Vmax
			swarm.Particle[i].P[j] = swarm.Particle[i].X[j]; //设定初代粒子的当前最优值的位置

		}

		swarm.Particle[i].Fitness = ComputAFitness(&swarm.Particle[i],swarm.Particle[i].X);  //计算每个粒子的适应度值

	}


}

//update  V and X 更新速度和位置
void UpdateofVandX(void)
{
	int i, j;
	srand((unsigned)time(NULL));
	for (i = 1; i < PNum + 1; i++)	//pNum种群大小
	{
		//速度更新公式：标准pso:    w*v[i] +c1xrand()x(pbest[i]-x[i])+c2xrand()x(gbest[i]-x[i])		
		//w为惯性因子，值为非负，c1 c2为学习因子，一般为常数效果好，常取为 2
		for (j = 1; j < Dim + 1; j++)
			swarm.Particle[i].V[j] = W_FUN * swarm.Particle[i].V[j] +
			rand() / (double)RAND_MAX * swarm.C1 * (swarm.Particle[i].P[j] - swarm.Particle[i].X[j]) +
			rand() / (double)RAND_MAX * swarm.C2 * (swarm.GBest[j] - swarm.Particle[i].X[j]);
		for (j = 1; j < Dim+1; j++)
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

		for (j = 1; j < Dim+1; j++)     //更新位置：x(i+1)=x(i)+v(i)
		{
			swarm.Particle[i].X[j] += swarm.Particle[i].V[j];
			if (swarm.Particle[i].X[j] >= swarm.Xup[j])
				swarm.Particle[i].X[j] = swarm.Xup[j];
			if (swarm.Particle[i].X[j] <= swarm.Xdown[j])
				swarm.Particle[i].X[j] = swarm.Xdown[j];
			if (swarm.Particle[i].V[j] > 0)//速度方向为递增
			{
				if (swarm.Particle[i].X[j] > 1 && swarm.Particle[i].X[j] < 2)
					swarm.Particle[i].X[j] = 2.0;
				if (swarm.Particle[i].X[j] > 2 && swarm.Particle[i].X[j] < 4)
					swarm.Particle[i].X[j] = 4.0;
			}
			if (swarm.Particle[i].V[j] < 0)              //速度方向为递减
			{
				if (swarm.Particle[i].X[j] > 1 && swarm.Particle[i].X[j] < 2)
					swarm.Particle[i].X[j] = 1.0;
				if (swarm.Particle[i].X[j] > 2 && swarm.Particle[i].X[j] < 4)
					swarm.Particle[i].X[j] = 2.0;
			}
		}
		/*********
		2017/7/26
		因为少了下面这行代码，找了一个晚上
		**********/

		swarm.Particle[i].Fitness = ComputAFitness(&swarm.Particle[i],swarm.Particle[i].X);  //重新计算每个粒子的适应度值

	}

}

/*更新个体极值P和全局极值GBest*/
void UpdatePandGbest(void)
{
	int i, j;
	//update of P if the X is less than current P
	for (i = 1; i < PNum+1; i++)
	{
		//if (swarm.Particle[i].Fitness < ComputAFitness(swarm.Particle[i].P)) //更新当前这一代个体p值，
		if (swarm.Particle[i].Fitness < ComputAFitness(&swarm.Particle[i],swarm.Particle[i].P)) //更新当前这一代个体p值
		{
			for (j = 1; j < Dim+1; j++)
			{
				swarm.Particle[i].P[j] = swarm.Particle[i].X[j];
			}
		}
	}

	//update of GBest
	//当前代数中所有粒子中的最优值

	for (i = 1; i < PNum + 1; i++)
	{

		if (ComputAFitness(&swarm.Particle[i],swarm.Particle[i].P) <
			ComputAFitness(&swarm.Particle[swarm.GBestIndex],swarm.Particle[swarm.GBestIndex].P))
		{
			swarm.GBestIndex = i;
		}

	}

	for (j = 1; j < Dim+1; j++)
	{
		swarm.GBest[j] = swarm.Particle[swarm.GBestIndex].P[j];
	}
	printf("The %dth iteraction.\n", cur_n);
	printf("GBestIndex:%d \n", swarm.GBestIndex);
	printf("GBest:");
	for (j = 1; j<Dim + 1; j++)
	{
		printf("%.1f ,", swarm.GBest[j]);
	}
	printf("\n");
	printf("Fitness of GBest: %f \n\n", ComputAFitness(&swarm.Particle[swarm.GBestIndex],swarm.Particle[swarm.GBestIndex].P));
}