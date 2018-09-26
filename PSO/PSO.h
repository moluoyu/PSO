#ifndef _PSO_H_
#define _PSO_H_
#define NumofVehicle 10  //目前车辆总数
#define gapofTime    0.1 //unit:h
//不同路径的最大车流量
#define  capOfLoad1   5    //pcu/h
#define  capOfLoad2   3    //pcu/h
#define  capOfLoad3   4    //pcu/h

/**
* \method
* 每个维度代表一辆车辆的选择结果,000 我们用十进制来表示车辆的选择道路
* 比如：选择第一条道路则为  100 -->对应的十进制  4
* 比如：选择第二条道路则为  010 -->对应的十进制  2
* 比如：选择第三条道路则为  001 -->对应的十进制  1
*
*/
#define Dim NumofVehicle //粒子维度 
#define PNum 1000 	     //种群规模        由于每辆车有3种可能 所以一共有3^10=59049种解
#define ITE_N  200  	 //最大迭代次数
int cur_n;			//当前迭代次数

					/*惯性权重函数*/
#define W_START 1.4
#define W_END	0.4
#define W_FUN	(W_START-(W_START-W_END)*pow((double)cur_n/ITE_N,2))
					/*个体和种群结构体*/
struct PARTICLE
{
	double X[Dim + 1];     //粒子当前位置
	double P[Dim + 1]; 	 //粒子当前最优值的位置
	double V[Dim + 1];     //粒子当前速度
	double Fitness;      //粒子当前适应度
} particle;

struct SWARM
{
	struct PARTICLE Particle[PNum + 1];
	int GBestIndex;             //群体最优值索引
	double GBest[Dim + 1];          //群体最优值坐标
	double C1;                  //学习因子
	double C2;
	double Xup[Dim + 1];            //位置上下限
	double Xdown[Dim + 1];
	double Vmax[Dim + 1];           //速度最大值
} swarm;

void RandInitofSwarm(void);
void UpdateofVandX(void);
void UpdatePandGbest(void);

#endif
