// Equalizer.h: interface for the CEqualizer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EQUALIZER_H__640BF857_78AF_45DE_9D76_56E2717A4A56__INCLUDED_)
#define AFX_EQUALIZER_H__640BF857_78AF_45DE_9D76_56E2717A4A56__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WAVEDECREC.h"

#ifndef ERR_PARAMERR
#define ERR_PARAMERR -1
#endif

#ifndef ERR_NOERR
#define ERR_NOERR     0
#endif

#ifndef ERR_INSURMEM
#define ERR_INSURMEM  -2
#endif



typedef struct tagEQPARAM
{
	double *wband;    //db of each band
	int wbandlen;     //number of bands
	unsigned long Fs;  //sample rate
	int nchn;         //channels
	int bitpersmp;    // bits per sample
//cen frequence of each band are list with 1oct
//Fs and wbank must be cooperated with this band
}EQPARAM;

class CEqualizer : public CWAVEDECREC  
{
public:
	int UseEQ(EQPARAM * param, unsigned char * Sig, unsigned char * OutSig, long ILen);
	CEqualizer();
	virtual ~CEqualizer();

};

#endif // !defined(AFX_EQUALIZER_H__640BF857_78AF_45DE_9D76_56E2717A4A56__INCLUDED_)
