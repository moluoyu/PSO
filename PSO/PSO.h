#ifndef _PSO_H_
#define _PSO_H_
#define NumofVehicle 10  //Ŀǰ��������
#define gapofTime    0.1 //unit:h
//��ͬ·�����������
#define  capOfLoad1   5    //pcu/h
#define  capOfLoad2   3    //pcu/h
#define  capOfLoad3   4    //pcu/h

/**
* \method
* ÿ��ά�ȴ���һ��������ѡ����,000 ������ʮ��������ʾ������ѡ���·
* ���磺ѡ���һ����·��Ϊ  100 -->��Ӧ��ʮ����  4
* ���磺ѡ��ڶ�����·��Ϊ  010 -->��Ӧ��ʮ����  2
* ���磺ѡ���������·��Ϊ  001 -->��Ӧ��ʮ����  1
*
*/
#define Dim NumofVehicle //����ά�� 
#define PNum 1000 	     //��Ⱥ��ģ        ����ÿ������3�ֿ��� ����һ����3^10=59049�ֽ�
#define ITE_N  200  	 //����������
int cur_n;			//��ǰ��������

					/*����Ȩ�غ���*/
#define W_START 1.4
#define W_END	0.4
#define W_FUN	(W_START-(W_START-W_END)*pow((double)cur_n/ITE_N,2))
					/*�������Ⱥ�ṹ��*/
struct PARTICLE
{
	double X[Dim + 1];     //���ӵ�ǰλ��
	double P[Dim + 1]; 	 //���ӵ�ǰ����ֵ��λ��
	double V[Dim + 1];     //���ӵ�ǰ�ٶ�
	double Fitness;      //���ӵ�ǰ��Ӧ��
} particle;

struct SWARM
{
	struct PARTICLE Particle[PNum + 1];
	int GBestIndex;             //Ⱥ������ֵ����
	double GBest[Dim + 1];          //Ⱥ������ֵ����
	double C1;                  //ѧϰ����
	double C2;
	double Xup[Dim + 1];            //λ��������
	double Xdown[Dim + 1];
	double Vmax[Dim + 1];           //�ٶ����ֵ
} swarm;

void RandInitofSwarm(void);
void UpdateofVandX(void);
void UpdatePandGbest(void);

#endif
