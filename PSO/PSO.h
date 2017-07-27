#ifndef _PSO_H_
#define _PSO_H_

#define Dim 2		//粒子维度
#define PNum 20		//种群规模
#define ITE_N  50  	//最大迭代次数
int cur_n;			//当前迭代次数

					/*惯性权重函数*/
#define W_START 1.4
#define W_END	0.4
#define W_FUN	(W_START-(W_START-W_END)*pow((double)cur_n/ITE_N,2))
					/*个体和种群结构体*/
struct PARTICLE
{
	double X[Dim];     //粒子当前位置
	double P[Dim]; 	   //粒子当前最优值的位置
	double V[Dim];     //粒子当前速度
	double Fitness;    //粒子当前适应度
} particle;

struct SWARM
{
	struct PARTICLE Particle[PNum];
	int GBestIndex;             //群体最优值索引
	double GBest[Dim];          //群体最优值坐标
	double C1;                  //学习因子
	double C2;
	double Xup[Dim];            //位置上下限
	double Xdown[Dim];
	double Vmax[Dim];           //速度最大值
} swarm;
/*是的，只要三个就好了，更好理解点感觉*/
void RandInitofSwarm(void);
void UpdateofVandX(void);
void UpdatePandGbest(void);

#endif
