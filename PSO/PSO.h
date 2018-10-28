#ifndef _PSO_H_
#define _PSO_H_

#define Dim 2		//����ά��
#define PNum 40		//��Ⱥ��ģ
#define ITE_N  200  	//����������
int cur_n;			//��ǰ��������
#define ACCURACY_F1 1e-3
#define ACCURACY_F2 1e-5
#define ACCURACY_F3 0.3
#define ACCURACY_F4 1e-5
#define ACCURACY_F5 1e-3

int numofacc;     //�ﵽ���ȵĴ���
					/*����Ȩ�غ���*/
#define W_MAX 0.9
#define W_MIN	0.6
//#define W_FUN	(W_MAX-W_MIN)*(ITE_N-cur_n)/ITE_N+W_MIN
#define W_FUN	0.792

/*�������Ⱥ�ṹ��*/
struct PARTICLE
{
	double X[Dim];     //���ӵ�ǰλ��
	double P[Dim]; 	   //���ӵ�ǰ����ֵ��λ��
	double V[Dim];     //���ӵ�ǰ�ٶ�
	double Fitness;    //���ӵ�ǰ��Ӧ��
} particle;

struct SWARM
{
	struct PARTICLE Particle[PNum];
	int GBestIndex;             //Ⱥ������ֵ����
	double GBest[Dim];          //Ⱥ������ֵ����
	double C1;                  //ѧϰ����
	double C2;
	double Xup[Dim];            //λ��������
	double Xdown[Dim];
	double Vmax[Dim];           //�ٶ����ֵ
} swarm;
/*�ǵģ�ֻҪ�����ͺ��ˣ���������о�*/
void RandInitofSwarm(void);
void UpdateofVandX(void);
void UpdatePandGbest(void);

#endif
