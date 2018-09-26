/*!
 * \file main.c
 *
 * \author thnx1
 * \date 九月 2018
 *        分成3个o-d对，我们要做的是：
 *      1 分别求出每个o-d对的最小值，
 *      2 然后求三个最小里的最大值
 *       此PSO中，只是完成第一步，
 ***************************************************************************************************************************************
 20180925 this is a branches  to test 
 目标函数进行修正为： x[i][j]cost[i][j]
 (ref:http://t.cn/EPMAvy1)






 ***************************************************************************************************************************************
 */
#include "pso.h"
#include "stdio.h"
int main(int argc, const char *argv[])
{
	cur_n = 0;           //当前代数
	RandInitofSwarm();             //初始化粒子群
	while (cur_n++ != ITE_N)//停止条件为代数
	{
		UpdateofVandX();        //速度和位置更新
		UpdatePandGbest();    //更新个体历史最优解P和全局最优解GBest

	}
	getchar();
	return 0;
}