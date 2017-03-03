// PlayEQ.cpp: implementation of the CPlayEQ class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WavSZ.h"
#include "PlayEQ.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPlayEQ::CPlayEQ()
{
	bUseEQ=false;
	EQbandpow=(double*)malloc(sizeof(double)*10);
	memset(EQbandpow,0,sizeof(double)*10);
	EQbandlen=10;

}

CPlayEQ::~CPlayEQ()
{
	free(EQbandpow);

}
int CPlayEQ::ComputeData(unsigned char *IS,unsigned long slen)
{
	if (!bUseEQ)
		return 0;
//	DWORD bt=timeGetTime();
	unsigned char* tmpout=(unsigned char*)malloc(slen);
	meqparam.bitpersmp=wfxInfo.wBitsPerSample;
	meqparam.Fs=wfxInfo.nSamplesPerSec;
	meqparam.nchn=wfxInfo.nChannels;
	meqparam.wband=EQbandpow;
	meqparam.wbandlen=EQbandlen;
	CEqualizer myEQ;
	myEQ.UseEQ(&meqparam,IS,tmpout,slen);
	memcpy(IS,tmpout,slen);
	free(tmpout);
//	bt=timeGetTime()-bt;
	return 0;
}

void CPlayEQ::SetEQ(double *bandpow, int bandlen)
{
	bUseEQ=true;
	int i;
	for (i=0;i<bandlen;i++)
		EQbandpow[i]=bandpow[i];
	
	EQbandlen=bandlen;
}

void CPlayEQ::StopEQ()
{
	bUseEQ=false;
}
