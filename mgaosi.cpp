#include "stdafx.h"
#include<stdio.h>
#include <math.h>
#include<time.h>
#define Stride 0.05
#define pi 3.1415
#define M 1000 //产生1000个点
#define N_perpoint 50  //每产生1000个高斯点中的一个点需要50个均匀分布的随机数。这个数越大越精确
//#define MeanNeed 100   //MeanNeed  : the expected value of mean of generated gauss series
//#define SigmaNeed sqrt(2)  //SigmaNeed : the expected value of sigma of generated gauss seri
float gauss[M];
void gaoss(float MeanNeed ,float SigmaNeed )  //加高斯噪声,x是均值，y是均方差
{
/*	int i;
    double sum=0.0,j;

	for(i=0;i<12;i++) 
	{
       j=(double) rand()/RAND_MAX;//产生12个随机数
	   sum+=j;//随机数之和
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

int   randnumber(int t,int d) //产生随机数
{
 /*申明初始化器的种子，注意是unsigned int 型的*/

int  randshu;

randshu =rand()%(d-t)+t;  /*生成一个[t,d)区间内的整数*/

return randshu;

}
/* 本程序用于产生SNR=db(dB)的均值为0的白噪声序列，编写人：白栎旸，baiguangyu001 */
/* db是信噪比， length是n的长度，n是产生出的白噪声 */


int main(){
	double gs[10];
	double gss;
  

srand((unsigned)time(NULL));//播种子

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
srand((unsigned)time(NULL));//播种子
for(i=0;i<20;i++)
{
number[i]=rand()%100;//产生100以内的随机整数
printf("%d ",number[i]);
}
printf("\n");
return 0;
}*/