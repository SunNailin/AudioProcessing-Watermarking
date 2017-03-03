// PlayEQ.h: interface for the CPlayEQ class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLAYEQ_H__583B4A75_C09F_40E2_8171_5BCCCA2FDA87__INCLUDED_)
#define AFX_PLAYEQ_H__583B4A75_C09F_40E2_8171_5BCCCA2FDA87__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PlayWav.h"
#include "Equalizer.h"

class CPlayEQ : public CPlayWav  
{
public:
	void StopEQ();
	void SetEQ(double* bandpow, int bandlen);
	bool bUseEQ;

	CPlayEQ();
	virtual ~CPlayEQ();
	int ComputeData(unsigned char * IS,unsigned long slen);
private:
	int EQbandlen;
	double* EQbandpow;
	EQPARAM meqparam;
};

#endif // !defined(AFX_PLAYEQ_H__583B4A75_C09F_40E2_8171_5BCCCA2FDA87__INCLUDED_)
