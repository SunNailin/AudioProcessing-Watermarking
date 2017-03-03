// Dct.cpp: implementation of the CDct class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WavSZ.h"
#include "Dct.h"
#include "math.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#define PI 3.1415
double*C=NULL;
bool bHasInit=false;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDct::CDct()
{

}

CDct::~CDct()
{

}
	void initIDCTParam(int deg);
	int bitrev(int bi,int deg);
	void fbitrev(double *f,int deg);
	void swap(double &a,double &b);
	void initDCTParam(int deg);
	void dct_forward(double *f,int deg);
	void idct_backward(double *F,int deg);
	void dct_backward(double *f,int deg);
	void idct_forward(double *F,int deg);
	void fidct_1D_no_param(double *F,int deg);
	void fdct_1D_no_param(double *f,int deg);
	void fidct_1D(double *F,int deg);
	void fdct_1D(double *f,int deg);
void initIDCTParam(int deg)
{
	int total,halftotal,i,group,endstart,factor;
	total=1<<deg;
	if(C!=NULL) delete []C;
	C=(double *)new double[total];
	halftotal=total>>1;
	for(i=0;i<halftotal;i++)
		C[total-i-1]=(double)(2*i+1);
	
	for(group=0;group<deg-1;group++)
	{ 
		endstart=1<<(deg-1-group);
		int len=endstart>>1;
		factor=1<<(group+1);
		for(int j=0;j<len;j++)
			C[endstart-j-1]=factor*C[total-j-1];
	}
	for(i=1;i<total;i++)
		C[i]=1.0/(2.0*cos(C[i]*PI/(total<<1)));	
	
}
int bitrev(int bi,int deg)
{
	int j=1,temp=0,degnum,halfnum;
	degnum=deg;
	//if(deg<0) return 0;
	if(deg==0) return bi;
	halfnum=1<<(deg-1);
	while(halfnum)
	{
		if(halfnum&bi)
			temp+=j;
		j<<=1;
		halfnum>>=1;
	}
	return temp;	
}
void fbitrev(double *f,int deg)
{    
	if(deg==1) return;
	int len=(1<<deg)-1;
	int i=1;
	int ii;
	double temp;
	while(i<len)
	{   ii=bitrev(i,deg); 
	if(ii>i)
	{  temp=f[ii];
		  f[ii]=f[i];
		  f[i]=temp;
	}
	i++;
	}
}

void swap(double &a,double &b)
{
	double temp;
	temp=a;
	a=b;
	b=temp;
}
void initDCTParam(int deg)
{
	int total,halftotal,i,group,endstart,factor;
	total=1<<deg;
	if(C!=NULL) delete []C;
	C=(double *)new double[total];
	halftotal=total>>1;
	for(i=0;i<halftotal;i++)
		C[total-i-1]=(double)(2*i+1);
	
	for(group=0;group<deg-1;group++)
	{ 
		endstart=1<<(deg-1-group);
		int len=endstart>>1;
		factor=1<<(group+1);
		for(int j=0;j<len;j++)
			C[endstart-j-1]=factor*C[total-j-1];
	}
	for(i=1;i<total;i++)
		C[i]=2.0*cos(C[i]*PI/(total<<1));	
	
}
void dct_forward(double *f,int deg)
{
	int i_deg,i_halfwing,total,wing,wings,winglen,halfwing;
	double temp1,temp2;
	total=1<<deg;
	for(i_deg=0;i_deg<deg;i_deg++)
	{
		wings=1<<i_deg;
		winglen=total>>i_deg;
		halfwing=winglen>>1;
		for(wing=0;wing<wings;wing++)
		{
			for(i_halfwing=0;i_halfwing<halfwing;i_halfwing++)
			{
				temp1=f[wing*winglen+i_halfwing];
				temp2=f[(wing+1)*winglen-1-i_halfwing];
				if(wing%2)
					swap(temp1,temp2);
				f[wing*winglen+i_halfwing]=temp1+temp2;
				f[(wing+1)*winglen-1-i_halfwing]=(temp1-temp2)*C[winglen-1-i_halfwing];
			}
		}
	}
}
void idct_backward(double *F,int deg)
{
	int i_deg,i_halfwing,total,wing,wings,winglen,halfwing;
	double temp1,temp2;
	total=1<<deg;
	for(i_deg=deg-1;i_deg>=0;i_deg--)
	{
		wings=1<<i_deg;
		winglen=total>>i_deg;
		halfwing=winglen>>1;
		for(wing=0;wing<wings;wing++)
		{
			for(i_halfwing=0;i_halfwing<halfwing;i_halfwing++)
			{
				temp1=F[wing*winglen+i_halfwing];
				temp2=F[(wing+1)*winglen-1-i_halfwing]*C[winglen-1-i_halfwing];
                if(wing%2)
				{
					F[wing*winglen+i_halfwing]=(temp1-temp2)*0.5;
					F[(wing+1)*winglen-1-i_halfwing]=(temp1+temp2)*0.5;
				}
				else
				{
					F[wing*winglen+i_halfwing]=(temp1+temp2)*0.5;
					F[(wing+1)*winglen-1-i_halfwing]=(temp1-temp2)*0.5;
				}
				
			}
		}
	}
	
}
void dct_backward(double *f,int deg)
{
	int total,i_deg,wing,wings,halfwing,winglen,i_halfwing,temp1,temp2;
    total=1<<deg;
	for(i_deg=deg-1;i_deg>=0;i_deg--)
	{
		wings=1<<i_deg;
		winglen=1<<(deg-i_deg);
		halfwing=winglen>>1;
		for(wing=0;wing<wings;wing++)
		{
			for(i_halfwing=0;i_halfwing<halfwing;i_halfwing++)
			{  //f[i_halfwing+wing*winglen]=f[i_halfwing+wing*winglen];
				if(i_halfwing==0)
					f[halfwing+wing*winglen+i_halfwing]=0.5*f[halfwing+wing*winglen+i_halfwing];
				else
				{
					temp1=bitrev(i_halfwing,deg-i_deg-1);
					temp2=bitrev(i_halfwing-1,deg-i_deg-1);
					f[halfwing+wing*winglen+temp1]=f[halfwing+wing*winglen+temp1]-f[halfwing+wing*winglen+temp2];
				}	
			}
		}
	}
}
void idct_forward(double *F,int deg)
{
	int total,i_deg,wing,wings,halfwing,winglen,i_halfwing,temp1,temp2;
    total=1<<deg;
	for(i_deg=0;i_deg<deg;i_deg++)
	{
		wings=1<<i_deg;
		winglen=1<<(deg-i_deg);
		halfwing=winglen>>1;
		for(wing=0;wing<wings;wing++)
		{
			for(i_halfwing=halfwing-1;i_halfwing>=0;i_halfwing--)
			{
				if(i_halfwing==0)
					F[halfwing+wing*winglen+i_halfwing]=2.0*F[halfwing+wing*winglen+i_halfwing];
				else
				{ 
					temp1=bitrev(i_halfwing,deg-i_deg-1);
					temp2=bitrev(i_halfwing-1,deg-i_deg-1);
					F[halfwing+wing*winglen+temp1]=F[halfwing+wing*winglen+temp1]+F[halfwing+wing*winglen+temp2];
				}
				
			}
		}
		
	}
	
} 
void fidct_1D_no_param(double *F,int deg)
{
	initIDCTParam(deg);
	F[0]=F[0]*sqrt(2.0);
	fbitrev(F,deg);
	idct_forward(F,deg);
	idct_backward(F,deg);
	
}

void fdct_1D_no_param(double *f,int deg)
{
	initDCTParam(deg);
	dct_forward(f,deg);
	dct_backward(f,deg);
	fbitrev(f,deg);
	f[0]=1/(sqrt(2.0))*f[0];
}
void fidct_1D(double *F,int deg)
{
	int total=1<<deg;
	double param=sqrt((double)total/2.0);
	for(int i=0;i<total;i++)
	{
		F[i]=param*F[i];
	}
	fidct_1D_no_param(F,deg);
}
void fdct_1D(double *f,int deg)
{
	fdct_1D_no_param(f,deg);
	int total=1<<deg;
	double param=sqrt(2.0/total);
	for(int i=0;i<total;i++)
		f[i]=param*f[i];
}