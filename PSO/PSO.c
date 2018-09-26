#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "math.h"
#include "pso.h"

f()
{

}
/*������Ӧ�Ⱥ�������Ӧ��*/
static double ComputAFitness(double X[]) //��x^2 + y^2 + 3 ��Сֵ
{

	return X[0] * X[0] + X[1] * X[1] + 3;
}

//��ʼ����Ⱥ
void RandInitofSwarm(void)
{
	int i, j;
	//ѧϰ����C1,C2
	swarm.C1 = 2.0;
	swarm.C2 = 2.0;
	for (j = 0; j < Dim; j++)
	{
		swarm.Xdown[j] = 15;    //�����ռ䷶Χ���̵�ʱ����Сֵ
		swarm.Xup[j] = 90;		// �̵�ʱ�����ֵ
		swarm.Vmax[j] = 0.1;       //���ӷ����ٶ����ֵ
	}

	srand((unsigned)time(NULL));
	for (i = 0; i < PNum; i++)      //PNum ��Ⱥ��ģ���������Ӹ���
	{
		for (j = 0; j < Dim; j++)   //�趨ÿ������ÿ��ά���ϵ����λ��������ٶ�
		{
			swarm.Particle[i].X[j] = rand() / (double)RAND_MAX * (swarm.Xup[j] - swarm.Xdown[j]) + swarm.Xdown[j];
			//-Xdown~Xup
			swarm.Particle[i].V[j] = rand() / (double)RAND_MAX * swarm.Vmax[j] * 2 - swarm.Vmax[j];
			//-Vmax~Vmax
			swarm.Particle[i].P[j] = swarm.Particle[i].X[j]; //�趨�������ӵĵ�ǰ����ֵ��λ��

		}

		swarm.Particle[i].Fitness = ComputAFitness(swarm.Particle[i].X);  //����ÿ�����ӵ���Ӧ��ֵ

	}
	

}

//update  V and X �����ٶȺ�λ��
void UpdateofVandX(void)
{
	int i, j;
	srand((unsigned)time(NULL));
	for (i = 0; i < PNum; i++)	//pNum��Ⱥ��С
	{
		//�ٶȸ��¹�ʽ����׼pso:    w*v[i] +c1xrand()x(pbest[i]-x[i])+c2xrand()x(gbest[i]-x[i])		
		//wΪ�������ӣ�ֵΪ�Ǹ���c1 c2Ϊѧϰ���ӣ�һ��Ϊ����Ч���ã���ȡΪ 2
		for (j = 0; j < Dim; j++)
			swarm.Particle[i].V[j] = W_FUN * swarm.Particle[i].V[j] +
			rand() / (double)RAND_MAX * swarm.C1 * (swarm.Particle[i].P[j] - swarm.Particle[i].X[j]) +
			rand() / (double)RAND_MAX * swarm.C2 * (swarm.GBest[j] - swarm.Particle[i].X[j]);
		for (j = 0; j < Dim; j++)
		{
			if (swarm.Particle[i].V[j] > swarm.Vmax[j])  //���������ٶȷ�Χ
			{
				swarm.Particle[i].V[j] = swarm.Vmax[j];
			}
			if (swarm.Particle[i].V[j] < -swarm.Vmax[j])
			{
				swarm.Particle[i].V[j] = -swarm.Vmax[j];
			}
		}

		for (j = 0; j < Dim; j++)     //����λ�ã�x(i+1)=x(i)+v(i)
		{
			swarm.Particle[i].X[j] += swarm.Particle[i].V[j];
			if (swarm.Particle[i].X[j] > swarm.Xup[j])
				swarm.Particle[i].X[j] = swarm.Xup[j];
			if (swarm.Particle[i].X[j] < swarm.Xdown[j])
				swarm.Particle[i].X[j] = swarm.Xdown[j];
		}
		/*********
		2017/7/26
		��Ϊ�����������д��룬����һ������
		**********/
		
		swarm.Particle[i].Fitness = ComputAFitness(swarm.Particle[i].X);  //���¼���ÿ�����ӵ���Ӧ��ֵ
	}
	
}

/*���¸��弫ֵP��ȫ�ּ�ֵGBest*/
void UpdatePandGbest(void)
{
	int i, j;
	//update of P if the X is less than current P
	for (i = 0; i < PNum; i++)
	{
		if (swarm.Particle[i].Fitness < ComputAFitness(swarm.Particle[i].P)) //���µ�ǰ��һ������pֵ��
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