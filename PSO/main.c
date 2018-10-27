/*!
 * \file main.c
 *
 * \author thnx1
 * \date ���� 2018
 *        �ֳ�3��o-d�ԣ�����Ҫ�����ǣ�
 *      1 �ֱ����ÿ��o-d�Ե���Сֵ��
 *      2 Ȼ����������С������ֵ
 *       ��PSO�У�ֻ����ɵ�һ����
 ************************************************************************************************************
 20180925 this is a branches  to test 
 Ŀ�꺯����������Ϊ�� x[i][j]cost[i][j]
 (ref:http://t.cn/EPMAvy1)
 **********************************************************************************************************/
#include "pso.h"
#include "stdio.h"
extern double ComputAFitness(struct PARTICLE* particle);
int main(int argc, const char *argv[])
{
	cur_n = 0;           //��ǰ����
	RandInitofSwarm();             //��ʼ������Ⱥ
	//UpdateofVandX();        //�ٶȺ�λ�ø���
	//UpdatePandGbest();    //���¸�����ʷ���Ž�P��ȫ�����Ž�GBest
	lastGlobal = swarm.GBestIndex;
	swarm.Particle[0].Fitness = swarm.Particle[lastGlobal].Fitness;
	for ( int i=1;i<Dim+1;i++)
	{
		swarm.Particle[0].X[i] = swarm.Particle[lastGlobal].X[i];
	}

	while (cur_n++ != ITE_N-1)//ֹͣ����Ϊ����ITE_N
	{
		UpdateofVandX();        //�ٶȺ�λ�ø���
		UpdatePandGbest();    //���¸�����ʷ���Ž�P��ȫ�����Ž�GBest
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
	printf("���γ���ִ�к����е������������ŵ�ֵ��Ӧ��ΪΪ�� %f\n ", swarm.Particle[0].Fitness);
	for (int i=1;i<Dim+1;i++)
	{
		{
			printf("%.1f,", swarm.Particle[0].X[i]);
		}
	}

	//getchar();
	return 0;
}