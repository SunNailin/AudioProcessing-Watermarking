// gaosi.cpp: implementation of the gaosi class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WavSZ.h"
#include "gaosi.h"
#include<math.h>
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
# define pi        3.1415
#define N_perpoint 50  //ÿ����1000����˹���е�һ������Ҫ50�����ȷֲ���������������Խ��Խ��ȷ
//float gauss[M];

#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

gaosi::gaosi()
{

}

gaosi::~gaosi()
{

}
int randnumber(int t,int d) //���������
{

double randshu;

randshu =rand()%(d-t)+t;  /*����һ��[t,d)�����ڵ�����*/

return randshu;

}
//#define MeanNeed 100   //MeanNeed  : the expected value of mean of generated gauss series
//#define SigmaNeed sqrt(2)  //SigmaNeed : the expected value of sigma of generated gauss seri
double gaoss(float MeanNeed ,float SigmaNeed )  //�Ӹ�˹����,x�Ǿ�ֵ��y�Ǿ�����
{
	int i;
    double sum=0.0,j;

	for(i=0;i<12;i++) 
	{
       j=(double) rand()/RAND_MAX;//����12�������
	   sum+=j;//�����֮��
	} 
	sum=MeanNeed+SigmaNeed*(sum-6.0); 

	return sum;
	 /*int         n,i,stime;
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
       sigma=sigma+(gauss[i]-mean)*(gauss[i]-mean)/M;*/
       
}



