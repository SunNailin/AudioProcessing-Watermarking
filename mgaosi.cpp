#include "stdafx.h"
#include<stdio.h>
#include <math.h>
#include<time.h>
#define Stride 0.05
#define pi 3.1415
#define M 1000 //����1000����
#define N_perpoint 50  //ÿ����1000����˹���е�һ������Ҫ50�����ȷֲ���������������Խ��Խ��ȷ
//#define MeanNeed 100   //MeanNeed  : the expected value of mean of generated gauss series
//#define SigmaNeed sqrt(2)  //SigmaNeed : the expected value of sigma of generated gauss seri
float gauss[M];
void gaoss(float MeanNeed ,float SigmaNeed )  //�Ӹ�˹����,x�Ǿ�ֵ��y�Ǿ�����
{
/*	int i;
    double sum=0.0,j;

	for(i=0;i<12;i++) 
	{
       j=(double) rand()/RAND_MAX;//����12�������
	   sum+=j;//�����֮��
	} 
	sum=x+y*(sum-6.0); 

	return sum;*/
	 int         n,i,stime;
     long        ltime;
     float       x[N_perpoint];
    float mean=0;float sigma=0;
	 for(i=0;i<M;i++)
   	    gauss[i]=0;
     for(i=0;i<M;i++)
	 {
	   ltime=time(NULL);
       stime=(unsigned int)ltime;
	   stime=stime+i;
       srand(stime);
	   for(n=0;n<N_perpoint;n++)
	      x[n]=0;
       for(n=0;n<N_perpoint;n++)
	   {  x[n]=(float)rand()/RAND_MAX;
          gauss[i]=gauss[i]+(float)sqrt((float)12/N_perpoint)*x[n];
	   }
	   gauss[i]=gauss[i]-(float)sqrt((float)12/N_perpoint)*(N_perpoint/2);
	   gauss[i]=(float)(MeanNeed+SigmaNeed*gauss[i]);
	   mean=mean+gauss[i]/M;
	 }
    for(i=0;i<M;i++)
       sigma=sigma+(gauss[i]-mean)*(gauss[i]-mean)/M;
       
}

int   randnumber(int t,int d) //���������
{
 /*������ʼ���������ӣ�ע����unsigned int �͵�*/

int  randshu;

randshu =rand()%(d-t)+t;  /*����һ��[t,d)�����ڵ�����*/

return randshu;

}
/* ���������ڲ���SNR=db(dB)�ľ�ֵΪ0�İ��������У���д�ˣ����ݕD��baiguangyu001 */
/* db������ȣ� length��n�ĳ��ȣ�n�ǲ������İ����� */


int main(){
	double gs[10];
	double gss;
  

srand((unsigned)time(NULL));//������

for (int i=0;i<10;i++)
{
	gs[i]=randnumber(10,100);
     printf("%f\n",gs[i]);
}


return 0;
}


/*
int main(void)
{
int number[20]={0};
int i;
srand((unsigned)time(NULL));//������
for(i=0;i<20;i++)
{
number[i]=rand()%100;//����100���ڵ��������
printf("%d ",number[i]);
}
printf("\n");
return 0;
}*/