// PlayWav.h: interface for the CPlayWav class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLAYWAV_H__0AAD703D_0416_4123_AD2E_FCE494AD6AB2__INCLUDED_)
#define AFX_PLAYWAV_H__0AAD703D_0416_4123_AD2E_FCE494AD6AB2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define ERR_NOWAVEDATA  -201

#define BufTime   100   //100ms

#include "WaveFile.h"

class CPlayWav : public CWaveFile  
{
public:
	int CloseDev();
	virtual int ComputeData(unsigned char * IS,unsigned long slen);
	int StopPlay();
	int AddBuf();
	bool killThread;
	DWORD BufLen;
	int PlayWav(LPSTR filename);
	WAVEHDR waveouthdr[2];
	HWAVEOUT waveout;
		DWORD CurBufLen,NextBufLen;
	static void CALLBACK PlayBackCall(HWAVEIN, UINT, DWORD, DWORD, DWORD);
	DWORD threadID;
	int CurRawBufID;
	HANDLE m_SndThread;
	CPlayWav();
	virtual ~CPlayWav();
private:
	unsigned char* rawbuf[2];
	DWORD CurPos;

};

#endif // !defined(AFX_PLAYWAV_H__0AAD703D_0416_4123_AD2E_FCE494AD6AB2__INCLUDED_)
