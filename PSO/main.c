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
int main(int argc, const char *argv[])
{
	cur_n = 0;           //��ǰ����
	RandInitofSwarm();             //��ʼ������Ⱥ
	while (cur_n++ != 1000)//ֹͣ����Ϊ����ITE_N
	{
		UpdateofVandX();        //�ٶȺ�λ�ø���
		UpdatePandGbest();    //���¸�����ʷ���Ž�P��ȫ�����Ž�GBest
		//�������ѭ������Ҫ��
		//ÿ�ε����󣬽�ÿ�����ӵ�numofLoad����ȫ�����㡣��Ȼ����� 
		// numofVehicle( )������������¼��㲻ͬʱ�ε�cost�����쳣ֵ

		for(int i= 1;i<PNum+1;i++)
		{

			swarm.Particle[i].numOfLoad1 = 0;
			swarm.Particle[i].numOfLoad2 = 0;
			swarm.Particle[i].numOfLoad3 = 0;
		}

	}
	//getchar();
	return 0;
}