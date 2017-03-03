// Dct.h: interface for the CDct class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DCT_H__AB81184E_7063_4AAA_8388_27CA74D1F7A6__INCLUDED_)
#define AFX_DCT_H__AB81184E_7063_4AAA_8388_27CA74D1F7A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDct  
{
public:
	CDct();
	virtual ~CDct();
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

};

#endif // !defined(AFX_DCT_H__AB81184E_7063_4AAA_8388_27CA74D1F7A6__INCLUDED_)
