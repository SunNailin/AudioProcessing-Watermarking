// PlayWav.cpp: implementation of the CPlayWav class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WavSZ.h"
#include "PlayWav.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPlayWav::CPlayWav()
{
	waveout=0;
	rawbuf[0]=rawbuf[1]=NULL;
	CurRawBufID=0;
	killThread=true;

}

CPlayWav::~CPlayWav()
{
	if (rawbuf[0]!=NULL) {free(rawbuf[0]);rawbuf[0]=NULL;}
	if (rawbuf[1]!=NULL) {free(rawbuf[1]);rawbuf[1]=NULL;}

}
int CPlayWav::PlayWav(LPSTR filename)
{
	WORD nchn,bitpersmp;
	DWORD smprate;
	MMRESULT res;
	if (!strcmp(filename,"")) return 0;
	killThread=true;

	OpenWavFile(filename,&nchn,&bitpersmp,&smprate);

	if (waveout) waveOutClose(waveout);

//	waveOutOpen(&waveout,WAVE_MAPPER,&wfxInfo,NULL,(DWORD)this,CALLBACK_NULL);
	waveOutOpen(&waveout,WAVE_MAPPER,&wfxInfo,(DWORD)PlayBackCall,(DWORD)this,CALLBACK_FUNCTION);

	BufLen=BufTime*wfxInfo.nChannels*wfxInfo.nSamplesPerSec*wfxInfo.wBitsPerSample/8000;

	if (rawbuf[0]!=NULL) free(rawbuf[0]);
	if (rawbuf[1]!=NULL) free(rawbuf[1]);
	rawbuf[0]=(unsigned char*)malloc(BufLen);
	rawbuf[1]=(unsigned char*)malloc(BufLen);

	CurRawBufID=0;	CurPos=0;

	CurBufLen=BufLen;
	WaveDataRead(&CurBufLen,rawbuf[CurRawBufID]);CurPos+=CurBufLen;
	ComputeData(rawbuf[CurRawBufID],CurBufLen);
	waveouthdr[CurRawBufID].lpData=(LPSTR)rawbuf[CurRawBufID];
	waveouthdr[CurRawBufID].dwBufferLength=CurBufLen;
	waveouthdr[CurRawBufID].dwFlags=0L;//WHDR_BEGINLOOP;
	waveouthdr[CurRawBufID].dwLoops=0L;
	waveOutPrepareHeader(waveout,&waveouthdr[CurRawBufID],sizeof(WAVEHDR));
	if((res=waveOutWrite(waveout,&waveouthdr[CurRawBufID],sizeof(WAVEHDR)))!=MMSYSERR_NOERROR)
	{
		char errbuf[256];
		waveOutGetErrorText(res,errbuf,256);
		AfxMessageBox(errbuf,MB_OK);
	}
	if (CurBufLen<BufLen) return 0;//little wav file
	//write next buff
	WaveDataRead(&CurBufLen,rawbuf[1-CurRawBufID]);CurPos+=CurBufLen;
	ComputeData(rawbuf[1-CurRawBufID],CurBufLen);
	waveouthdr[1-CurRawBufID].lpData=(LPSTR)rawbuf[1-CurRawBufID];
	waveouthdr[1-CurRawBufID].dwBufferLength=CurBufLen;
	waveouthdr[1-CurRawBufID].dwFlags=0L;
	waveouthdr[1-CurRawBufID].dwLoops=0L;
	waveOutPrepareHeader(waveout,&waveouthdr[1-CurRawBufID],sizeof(WAVEHDR));
	if((res=waveOutWrite(waveout,&waveouthdr[1-CurRawBufID],sizeof(WAVEHDR)))!=MMSYSERR_NOERROR)
	{
		char errbuf[256];
		waveOutGetErrorText(res,errbuf,256);
		AfxMessageBox(errbuf,MB_OKCANCEL);
	}
	if (CurBufLen<BufLen) return 0;//little wav file

//	threadID = 0;
	killThread=false;
//	m_SndThread =CreateThread(NULL, 0, SendingThrd, this, 0 , &threadID);

	return 0;
}

/*
DWORD WINAPI CPlayWav::SendingThrd(void * pParam)
//UINT SendingThrd(LPVOID pParam)
{
	CPlayWav *pSend = (CPlayWav *)pParam;
	WAVEHDR tmphdr;
	while (!pSend->killThread) 
	{
		tmphdr=pSend->waveouthdr[pSend->CurRawBufID];
		while(tmphdr.dwFlags!=3)
		{
			if(pSend->killThread) {return 0;}
			tmphdr=pSend->waveouthdr[pSend->CurRawBufID];
		}
		waveOutUnprepareHeader(pSend->waveout,&pSend->waveouthdr[pSend->CurRawBufID],sizeof(WAVEHDR));
		pSend->AddBuf();
	}
	return 0;
}
*/
#define PT_S ((CPlayWav*)dwInstance)
void CALLBACK CPlayWav::PlayBackCall(HWAVEIN hwi,
								   UINT uMsg,
								   DWORD dwInstance,  
								   DWORD dwParam1,    
								   DWORD dwParam2)
{
	if (uMsg != WOM_DONE)
		return;

	waveOutUnprepareHeader(PT_S->waveout,&PT_S->waveouthdr[PT_S->CurRawBufID],sizeof(WAVEHDR));
	PT_S->AddBuf();
	return;
}


int CPlayWav::AddBuf()
{
	if (killThread) return 0;
	CurRawBufID=1-CurRawBufID;
if ((CurPos+CurBufLen)<len)
	{
		WaveDataRead(&CurBufLen,rawbuf[1-CurRawBufID]);CurPos+=CurBufLen;
		ComputeData(rawbuf[1-CurRawBufID],CurBufLen);
		waveouthdr[1-CurRawBufID].lpData=(LPSTR)rawbuf[1-CurRawBufID];
		waveouthdr[1-CurRawBufID].dwBufferLength=CurBufLen;
		waveouthdr[1-CurRawBufID].dwFlags=0L;
		waveouthdr[1-CurRawBufID].dwLoops=0L;
		waveOutPrepareHeader(waveout,&waveouthdr[1-CurRawBufID],sizeof(WAVEHDR));
		waveOutWrite(waveout,&waveouthdr[1-CurRawBufID],sizeof(WAVEHDR));
	}
	else
	{
		killThread=true;
		WaveDataRead(&CurBufLen,rawbuf[1-CurRawBufID]);CurPos+=CurBufLen;
		ComputeData(rawbuf[1-CurRawBufID],CurBufLen);
		waveouthdr[1-CurRawBufID].lpData=(LPSTR)rawbuf[1-CurRawBufID];
		waveouthdr[1-CurRawBufID].dwBufferLength=CurBufLen;
		waveouthdr[1-CurRawBufID].dwFlags=0L;//WHDR_ENDLOOP;
		waveouthdr[1-CurRawBufID].dwLoops=0L;
		waveOutPrepareHeader(waveout,&waveouthdr[1-CurRawBufID],sizeof(WAVEHDR));
		waveOutWrite(waveout,&waveouthdr[1-CurRawBufID],sizeof(WAVEHDR));
		CloseReadFile();
	}
	return 0;
}

int CPlayWav::StopPlay()
{
	killThread=true;
	CloseDev();
	CloseReadFile();
	return 0;
}

int CPlayWav::ComputeData(unsigned char *IS,unsigned long slen)
{
	return 0;
}

int CPlayWav::CloseDev()
{
	killThread=true;
	Sleep(BufTime);
 	if (waveout)
 	{	
		waveOutUnprepareHeader(waveout,&waveouthdr[CurRawBufID],sizeof(WAVEHDR));
		waveOutReset(waveout);
		waveOutClose(waveout);
		waveout=0;
	}
	if (rawbuf[0]!=NULL) {free(rawbuf[0]);rawbuf[0]=NULL;}
	if (rawbuf[1]!=NULL) {free(rawbuf[1]);rawbuf[1]=NULL;}
	CloseReadFile();
	return 0;

}