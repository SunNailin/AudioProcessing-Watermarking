// WAVEDECREC.h: interface for the CWAVEDECREC class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WAVEDECREC_H__606290C0_04D2_4C85_BBFD_6228D45A7B75__INCLUDED_)
#define AFX_WAVEDECREC_H__606290C0_04D2_4C85_BBFD_6228D45A7B75__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#ifndef ERR_NOERR
#define ERR_NOERR     0
#endif

#ifndef ERR_INSURMEM
#define ERR_INSURMEM -1
#endif

#ifndef ERR_PARAMERR
#define ERR_PARAMERR  -2
#endif
class CWAVEDECREC  
{
public:
	int WaveRec(double* OutBuf, long len);
	int WaveDec(double * InSig, long InLen);
	int InitFilterBank(int l);

	CWAVEDECREC();
	virtual ~CWAVEDECREC();
protected:
	double *C;
	int *Lb,*Le;
private:
	long bufflen;
	long FinalLen(long l, long N);
	double *LoD,*HiD,*LoR,*HiR;
	int FLen;
	int level;
	long SigLen,CLen;
	int Conv(double *X,long lx,double *Y,long ly,double *Z,long *lz);

};

#endif // !defined(AFX_WAVEDECREC_H__606290C0_04D2_4C85_BBFD_6228D45A7B75__INCLUDED_)
