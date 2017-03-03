// WaveFile.h: interface for the CWaveFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WAVEFILE_H__519E0505_2263_4F1E_A478_7474D711EBD8__INCLUDED_)
#define AFX_WAVEFILE_H__519E0505_2263_4F1E_A478_7474D711EBD8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#ifndef ER_CANNOTOPEN 
#define ER_CANNOTOPEN -1 
#endif  

#ifndef ER_NOTWAVEFILE 
#define ER_NOTWAVEFILE -2 
#endif  

#ifndef ER_CANNOTREAD 
#define ER_CANNOTREAD -3 
#endif  

#ifndef ER_MEM 
#define ER_MEM -4 
#endif  

#ifndef ER_SIZECMP 
#define ER_SIZECMP -5 
#endif  

#ifndef ER_CORRUPTWAVEFILE 
#define ER_CORRUPTWAVEFILE -6 
#endif  

#ifndef ER_NOFILENAME 
#define ER_NOFILENAME -7 
#endif  

#ifndef ER_NOPOINTER 
#define ER_NOPOINTER -8 
#endif  

#ifndef ER_NOBUFPOINTER 
#define ER_NOBUFPOINTER -9 
#endif  

#ifndef ER_NOWANTEDSIZE 
#define ER_NOWANTEDSIZE -10 
#endif  

#ifndef ER_NOFILESTRUCT 
#define ER_NOFILESTRUCT -11 
#endif  

#ifndef ER_NOUINT 
#define ER_NOUINT -12 
#endif  

#ifndef ERROR_SAVING 
#define ERROR_SAVING -13
#endif  

#ifndef ER_CANNOTWRITE 
#define ER_CANNOTWRITE -14
#endif  

#ifndef ER_EMPTYFILE
#define ER_EMPTYFILE   -15
#endif

#include "mmsystem.h"

class CWaveFile  
{
public:
	int CloseReadFile();
	DWORD IOBufLen;
	DWORD len;
	unsigned char* pbuf;
	int ReadWavFile(LPSTR filename, WORD* pnchn, WORD *pbitpersmp, DWORD *psmprate);
	int WriteWavFile(LPSTR filename,unsigned char* databuf,
		              DWORD datalen, WORD nchn,
					  WORD bitpersmp, DWORD smprate);
	int OpenWavFile(LPSTR filename, WORD *pnchn, WORD *pbitpersmp, DWORD *psmprate);

	int WaveDataRead(DWORD *preadlen,unsigned char* OutBuf);
	CWaveFile();
	virtual ~CWaveFile();
protected:
	int WaveCloseWriteFile(MMIOINFO *pmmioinfoOut, DWORD numsmp);
	int WaveWriteFile(DWORD datalen, unsigned char* databuf, MMIOINFO *pmmioinfo);
	int WaveStartDataWrite(MMIOINFO *pmmioinfoOut);
	int WaveCreateFile(LPSTR filename);
	WAVEFORMATEX wfxInfo;
private:
	MMCKINFO ckIn;
	PCMWAVEFORMAT pcmWaveFormat;
	WORD cbExtraAlloc;
	HMMIO hmmio;
	MMCKINFO ckInRIFF;

	DWORD bpos;
};

#endif // !defined(AFX_WAVEFILE_H__519E0505_2263_4F1E_A478_7474D711EBD8__INCLUDED_)
