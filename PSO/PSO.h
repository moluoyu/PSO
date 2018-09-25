#ifndef _PSO_H_
#define _PSO_H_

#define Dim 1		//����ά��  ���ݶ����Ʊ���
#define PNum 10 	//��Ⱥ��ģ  һ��10����
#define ITE_N  200  	//����������
int cur_n;			//��ǰ��������

					/*����Ȩ�غ���*/
#define W_START 1.4
#define W_END	0.4
#define W_FUN	(W_START-(W_START-W_END)*pow((double)cur_n/ITE_N,2))
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

void RandInitofSwarm(void);
void UpdateofVandX(void);
void UpdatePandGbest(void);

#endif
