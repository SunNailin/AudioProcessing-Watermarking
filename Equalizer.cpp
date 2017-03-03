// Equalizer.cpp: implementation of the CEqualizer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WavSZ.h"
#include "Equalizer.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
unsigned long CenBand[10]={32,65,125,250,500,1000,2000,4000,8000,16000};
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEqualizer::CEqualizer()
{

}

CEqualizer::~CEqualizer()
{

}
int CEqualizer::UseEQ(EQPARAM *param, unsigned char *Sig, unsigned char * OutSig, long ILen)
{
	unsigned long Hband=(unsigned long)(3*param->Fs/8);
	double * bandpow=(double*)malloc(param->wbandlen*sizeof(double));
	long i,k,len,level=-1;
	for (i=9;i>=0;i--)
	{
		if (CenBand[i]<Hband) 
		{level=i;break;}
	}
	if ((level<1)||((level+1)>param->wbandlen)) return ERR_PARAMERR;
	if (level==1) return ERR_NOERR;
	InitFilterBank(level);

	for (i=0;i<param->wbandlen;i++) bandpow[i]=pow(10,(param->wband[i]/20));
	double *tSig1=NULL;
	double *tSig2=NULL;
	if (param->bitpersmp==16)
	{
		short * sig16=NULL;
		if(param->nchn==2)
		{
			len=ILen>>2;
			if(NULL==(tSig1=(double*)malloc(sizeof(double)*len)))
				return ERR_INSURMEM;
			if(NULL==(tSig2=(double*)malloc(sizeof(double)*len)))
				return ERR_INSURMEM;
			sig16=(short*)Sig;k=0;
			for (i=0;i<len;i++)
			{tSig1[i]=sig16[k++]/32768.;tSig2[i]=sig16[k++]/32768.;}
			//channel1
			WaveDec(tSig1,len);
			for (i=0;i<level+1;i++)//add weight
			{
				k=Lb[i];
				while (k<=Le[i]) {C[k]*=bandpow[i];k++;}
			}
			WaveRec(tSig1,len);
			//channel2
			WaveDec(tSig2,len);
			for (i=0;i<level+1;i++)//add weight
			{
				k=Lb[i];
				while (k<=Le[i]) {C[k]*=bandpow[i];k++;}
			}
			WaveRec(tSig2,len);
			//write back to OutSig
			sig16=(short*)OutSig;k=0;
			for (i=0;i<len;i++)
			{
				if (tSig1[i]>1) sig16[k++]=32767;
				else if (tSig1[i]<-1) sig16[k++]=-31768;
				else sig16[k++]=(short)(tSig1[i]*32768);

				if (tSig2[i]>1) sig16[k++]=32767;
				else if (tSig2[i]<-1) sig16[k++]=-31768;
				else sig16[k++]=(short)(tSig2[i]*32768);
			}
		}
		else if(param->nchn==1)
		{
			len=ILen>>1;
			if(NULL==(tSig1=(double*)malloc(sizeof(double)*len)))
				return ERR_INSURMEM;
			sig16=(short*)Sig;
			for (i=0;i<len;i++)
			{tSig1[i]=sig16[i]/32768.;}
			//channel1
			WaveDec(tSig1,len);
			for (i=0;i<level+1;i++)//add weight
			{
				k=Lb[i];
				while (k<=Le[i]) {C[k]*=bandpow[i];k++;}
			}
			WaveRec(tSig1,len);
			//write back to OutSig
			sig16=(short*)OutSig;
			for (i=0;i<len;i++)
			{
				if (tSig1[i]>1) sig16[i]=32767;
				else if (tSig1[i]<-1) sig16[i]=-31768;
				else sig16[i]=(short)(tSig1[i]*32768);
			}
		}
		else
			return ERR_PARAMERR;
	}
	else if (param->bitpersmp==8)
	{
		if(param->nchn==2)
		{
			len=ILen>>1;
			if(NULL==(tSig1=(double*)malloc(sizeof(double)*len)))
				return ERR_INSURMEM;
			if(NULL==(tSig2=(double*)malloc(sizeof(double)*len)))
				return ERR_INSURMEM;
			k=0;
			for (i=0;i<len;i++)
			{tSig1[i]=(Sig[k++]-128)/128.;tSig2[i]=(Sig[k++]-128)/128.;}
			//channel1
			WaveDec(tSig1,len);
			for (i=0;i<level+1;i++)//add weight
			{
				k=Lb[i];
				while (k<=Le[i]) {C[k]*=bandpow[i];k++;}
			}
			WaveRec(tSig1,len);
			//channel2
			WaveDec(tSig2,len);
			for (i=0;i<level+1;i++)//add weight
			{
				k=Lb[i];
				while (k<=Le[i]) {C[k]*=bandpow[i];k++;}
			}
			WaveRec(tSig2,len);
			//write back to OutSig
			k=0;
			for (i=0;i<len;i++)
			{
				if (tSig1[i]>1) OutSig[k++]=255;
				else if (tSig1[i]<-1) OutSig[k++]=0;
				else OutSig[k++]=(unsigned char)(tSig1[i]*128+128);

				if (tSig2[i]>1) OutSig[k++]=255;
				else if (tSig2[i]<-1) OutSig[k++]=0;
				else OutSig[k++]=(unsigned char)(tSig2[i]*128+128);

//				OutSig[k++]=(unsigned char)(tSig1[i]*128+128);
//				OutSig[k++]=(unsigned char)(tSig2[i]*128+128);
			}
		}
		else if(param->nchn==1)
		{
			len=ILen;
			if(NULL==(tSig1=(double*)malloc(sizeof(double)*len)))
				return ERR_INSURMEM;
			for (i=0;i<len;i++)
			{tSig1[i]=(Sig[i]-128)/128;}
			//channel1
			WaveDec(tSig1,len);
			for (i=0;i<level+1;i++)//add weight
			{
				k=Lb[i];
				while (k<=Le[i]) {C[k]*=bandpow[i];k++;}
			}
			WaveRec(tSig1,len);
			//write back to OutSig
			for (i=0;i<len;i++)
			{
				if (tSig1[i]>1) OutSig[i]=255;
				else if (tSig1[i]<-1) OutSig[i]=0;
				else OutSig[i]=(unsigned char)(tSig1[i]*128+128);
//				OutSig[i]=(unsigned char)(tSig1[i]*128+128);
			}
		}
		else
			return ERR_PARAMERR;
	}

	free(bandpow);
	if(tSig1!=NULL) free(tSig1);
	if(tSig2!=NULL) free(tSig2);
	return ERR_NOERR;
}
