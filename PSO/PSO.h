#ifndef _PSO_H_
#define _PSO_H_

#define Dim 2		//粒子维度
#define PNum 40		//种群规模
#define ITE_N  200  	//最大迭代次数
int cur_n;			//当前迭代次数
#define ACCURACY_F1 1e-3
#define ACCURACY_F2 1e-5
#define ACCURACY_F3 0.3
#define ACCURACY_F4 1e-5
#define ACCURACY_F5 1e-3

int numofacc;     //达到精度的次数
					/*惯性权重函数*/
#define W_MAX 0.9
#define W_MIN	0.6
//#define W_FUN	(W_MAX-W_MIN)*(ITE_N-cur_n)/ITE_N+W_MIN
#define W_FUN	0.792

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
