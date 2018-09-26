#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "math.h"
#include "pso.h"
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
int numofVehicle(double X[], int n)
{
	int num = 0;
	int numOfLoad1 = 0, numOfLoad2 = 0, numOfLoad3 = 0;

	if (4 == (int)X[n])
	{
		for (int i = 1; i <= n; i++)
		{
			if (4 == (int)X[i])
				numOfLoad1++;
		}
		return numOfLoad1;
	}
	if (2 == (int)X[n])
	{
		for (int i = 1; i <= n; i++)
		{
			if (2 == (int)X[i])
				numOfLoad2++;
		}
		return numOfLoad2;
	}
	if (1 == (int)X[n])
	{
		for (int i = 1; i <= n; i++)
		{
			if (4 == (int)X[i])
				numOfLoad3++;
		}
		return numOfLoad3;
	}
}
/**
* \method
*impedance function
阻抗函数
* \brief
* \param
* \param
* \author thnx1
* \date 九月 2018
*/
double impedOfLoad(int volatile traffic, int id)
{



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
double countCost(double X[], int n)
{
	int volatile traffic = 0;
	double costTime = 0;
	double res = 0.0;
	int  totalNum = numofVehicle(X, n);
	switch ((int)X[n])
	{
	case 4:
		traffic = totalNum / gapofTime;
		if (traffic > 0 && traffic < 0.3*capOfLoad1)//随着车流量的增加，Cost应该越来越大  欠饱和
		{

			res = impedOfLoad(traffic, 4);
		}
		else if (traffic > 0.3*capOfLoad1 && traffic < 0.6*capOfLoad1)//正常饱和
		{
			res = impedOfLoad(traffic, 4);
		}
		else if (traffic > 0.6*capOfLoad1 && traffic <= capOfLoad1)//过饱和
		{
			res = impedOfLoad(traffic, 4);
		}
		break;
	case 2:
		traffic = totalNum / gapofTime;
		if (traffic > 0 && traffic < 0.3*capOfLoad1)//随着车流量的增加，Cost应该越来越大  欠饱和
		{
			res = impedOfLoad(traffic, 2);
		}
		else if (traffic > 0.3*capOfLoad1 && traffic < 0.6*capOfLoad1)//正常饱和
		{
			res = impedOfLoad(traffic, 2);
		}
		else if (traffic > 0.6*capOfLoad1 && traffic < capOfLoad1)//过饱和
		{
			res = impedOfLoad(traffic, 2);
		}
		break;
	case 1:
		traffic = totalNum / gapofTime;
		if (traffic >= 0 && traffic <= 0.3*capOfLoad1)//随着车流量的增加，Cost应该越来越大  欠饱和
		{
			res = impedOfLoad(traffic, 1);
		}
		else if (traffic > 0.3*capOfLoad1 && traffic <= 0.6*capOfLoad1)//正常饱和
		{
			res = impedOfLoad(traffic, 1);
		}
		else if (traffic > 0.6*capOfLoad1 && traffic <= capOfLoad1)//过饱和
		{
			res = impedOfLoad(traffic, 1);
		}
		break;
	}
	return res;
}


static  double ComputAFitness(double X[]) //
{
	double res = 0.0;
	for (int i = 1; i < Dim + 1; i++)
	{
		//to do code 
		res += X[i] * countCost((int)X[i], i);
	}
	return res;
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
int randomGenValue()
{
	int a = rand() % 3 + 1;
	int temp;
	switch (a)
	{
	case 1:
		temp = 1;
		break;
	case 2:
		temp = 2;
		break;
	case 3:
		temp = 4;
		break;
	}
	return  temp;
}
int randomGenSpeed()
{

	int a = rand() % 2 + 1;
	int temp;
	switch (a)
	{
	case 1:
		temp = 1;
		break;
	case 2:
		temp = 2;
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
	for (j = 1; j < Dim + 1; j++)
	{
		swarm.Xdown[j] = 1;    //每辆车的选择结果最小为1
		swarm.Xup[j] = 4;		// 每辆车的选择结果最大为4
		swarm.Vmax[j] = 2;       //粒子飞翔速度最大值
	}

	srand((unsigned)time(0));
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

		swarm.Particle[i].Fitness = ComputAFitness(swarm.Particle[i].X);  //计算每个粒子的适应度值

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
			if (swarm.Particle[i].V[j] > 0)//速度方向为递增
			{
				if (swarm.Particle[i].X[j] > 1 && swarm.Particle[i].X[j] < 2)
					swarm.Particle[i].X[j] = 2;
				if (swarm.Particle[i].X[j] > 2 && swarm.Particle[i].X[j] < 4)
					swarm.Particle[i].X[j] = 4;
			}
			if (swarm.Particle[i].V[j] < 0)              //速度方向为递减
			{
				if (swarm.Particle[i].X[j] > 1 && swarm.Particle[i].X[j] < 2)
					swarm.Particle[i].X[j] = 1;
				if (swarm.Particle[i].X[j] > 2 && swarm.Particle[i].X[j] < 4)
					swarm.Particle[i].X[j] = 2;
			}
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
	for (j = 1; j<Dim + 1; j++)
	{
		printf("%.4f ,", swarm.GBest[j]);
	}
	printf("\n");
	printf("Fitness of GBest: %f \n\n", ComputAFitness(swarm.Particle[swarm.GBestIndex].P));
}