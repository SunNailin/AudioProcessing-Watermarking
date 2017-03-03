// WAVEDECREC.cpp: implementation of the CWAVEDECREC class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WavSZ.h"
#include "WAVEDECREC.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWAVEDECREC::CWAVEDECREC()
{
	LoD=LoR=HiD=HiR=NULL;
	C=NULL;

}

CWAVEDECREC::~CWAVEDECREC()
{
	if (LoD!=NULL) free(LoD);
	if (LoR!=NULL) free(LoR);
	if (HiD!=NULL) free(HiD);
	if (HiR!=NULL) free(HiR);
	if (C!=NULL) free(C);

}

int CWAVEDECREC::Conv(double *X,long lx,double *Y,long ly,double *Z,long *plz)
{
	long i,j,lz,ix;
	*plz=lz=lx+ly-1;
	if (lx<ly)
	{
		for (i=0;i<lz;i++)
		{
			Z[i]=0;
			j=0;
			while(j<lx)
			{
				ix=i-j;
				if (ix==ly)
				{j=i-ly+1;ix=ly-1;}
				if ((ix>=0)&&(ix<ly)) Z[i]+=X[j]*Y[i-j];
				if (!ix) break;
				j++;
			}
		}
	}
	else
	{
		for (i=0;i<lz;i++)
		{
			Z[i]=0;
			j=0;
			while(j<ly)
			{
				ix=i-j;
				if (ix==lx) 
				{j=i-lx+1;ix=lx-1;}
				if ((ix>=0)&&(ix<lx)) Z[i]+=Y[j]*X[i-j];
				if (!ix) break;
				j++;
			}
		}
	}
	return 0;
}

int CWAVEDECREC::InitFilterBank(int l)
{
	int i,flag=1;
	level=l;
	//init LoD
	double FC[10]={0.00333572528500,-0.01258075199902,
		-0.00624149021301,0.07757149384007,
		-0.03224486958503,-0.24229488706619,
		0.13842814590110,0.72430852843857,
		0.60382926979747,0.16010239797413};
	FLen=10;
/*	double FC[4]={-0.12940952255092,0.22414386804186,0.83651630373747,0.48296291314469};
	FLen=4;*/
/*	double FC[20]={-0.00001326420300,0.00009358867000,-0.00011646685499,
  -0.00068585669500,0.00199240529499,0.00139535174699,-0.01073317548298,
   0.00360655356699,0.03321267405893,-0.02945753682195,-0.07139414716586,
   0.09305736460381,0.12736934033574,-0.19594627437660,-0.24984642432649,
   0.28117234366043,0.68845903945259,0.52720118893092,0.18817680007762,0.02667005790095};
	FLen=20;*/
	if (NULL==(LoD=(double*)malloc(sizeof(double)*FLen)))
		return ERR_INSURMEM;
	if (NULL==(HiD=(double*)malloc(sizeof(double)*FLen)))
		return ERR_INSURMEM;
	if (NULL==(LoR=(double*)malloc(sizeof(double)*FLen)))
		return ERR_INSURMEM;
	if (NULL==(HiR=(double*)malloc(sizeof(double)*FLen)))
		return ERR_INSURMEM;
	
	for (i=0;i<FLen;i++)
	{
		LoD[i]=FC[i];HiD[FLen-i-1]=FC[i]*flag;
		LoR[FLen-i-1]=FC[i];HiR[i]=FC[i]*flag;
		flag*=-1;
	}
	//int Lb,Le
	if(NULL==(Lb=(int*)malloc(sizeof(int)*(level+2))))
		return ERR_INSURMEM;
	if(NULL==(Le=(int*)malloc(sizeof(int)*(level+2))))
		return ERR_INSURMEM;

	return ERR_NOERR;
}

int CWAVEDECREC::WaveDec(double *InSig, long InLen)
{
	long i,j,k,lr;

	CLen=FinalLen(InLen,level);Lb[level+1]=0;Le[level+1]=InLen-1;
	bufflen=max(FLen*3,2*(Le[level]-Lb[level])+FLen);

	double *tmpbuff=(double*)malloc(sizeof(double)*bufflen);
	double *a=(double*)malloc(sizeof(double)*bufflen);
	
	memcpy(a,InSig,sizeof(double)*InLen);
	SigLen=InLen;
	C=(double*)malloc(sizeof(double)*CLen);

	for (i=level;i>0;i--)
	{
		Conv(a,InLen,HiD,FLen,tmpbuff,&lr);
		k=Lb[i];
		for (j=1;j<lr;j+=2) C[k++]=tmpbuff[j];
		Conv(a,InLen,LoD,FLen,tmpbuff,&lr);
		k=0;
		for (j=1;j<lr;j+=2) a[k++]=tmpbuff[j];
		InLen=k;
	}
	memcpy(C,a,k*sizeof(double));
	free(tmpbuff);
	free(a);
	return ERR_NOERR;
}

long CWAVEDECREC::FinalLen(long l, long N)
{
	long len=(l+FLen-2)/2;
	if (len*2!=(l+FLen-2)) len++;
	if (N<0) return -1;
	if (N==1)
	{
		Lb[N-1]=0;Le[N-1]=len-1;
		Lb[N]=Le[N-1]+1;Le[N]=Lb[N]+Le[N-1];
		return 2*(Le[N-1]+1);
	}
	else
	{
		len=len+FinalLen(len,N-1);
		Lb[N]=Le[N-1]+1;Le[N]=len-1;
		return len;
	}
}

int CWAVEDECREC::WaveRec(double *OutBuf, long len)
{
	if (len!=SigLen) return ERR_PARAMERR;
	long i,j,k,lr=bufflen;
	double *tmp1=(double*)malloc(sizeof(double)*lr);
	double *tmp2=(double*)malloc(sizeof(double)*lr);
	double *a=(double*)malloc(sizeof(double)*lr);

	len=Le[0]+1;
	memcpy(a,C,sizeof(double)*len);

	for (i=1;i<level+1;i++)
	{
		for (j=len-1;j>0;j--) {a[2*j]=a[j];a[2*j-1]=0;}
		len=len*2-1;
		Conv(a,len,LoR,FLen,tmp1,&lr);
		k=0;
		for (j=Lb[i];j<=Le[i];j++) {a[k++]=C[j];a[k++]=0;}
		Conv(a,k-1,HiR,FLen,tmp2,&lr);
		len=Le[i+1]-Lb[i+1]+1;
		k=(long)((lr-len)/2);
		for (j=k;j<len+k;j++) a[j-k]=tmp1[j]+tmp2[j];//取中间的一部分
	}
	memcpy(OutBuf,a,len*sizeof(double));

	free(tmp1);
	free(tmp2);
	free(a);

	return ERR_NOERR;
}
