// gaosi.h: interface for the gaosi class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAOSI_H__E647A8CD_6E3C_4946_8DE6_B3C4CD786256__INCLUDED_)
#define AFX_GAOSI_H__E647A8CD_6E3C_4946_8DE6_B3C4CD786256__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//extern float gauss[M];
class gaosi  
{
public:
	gaosi();
	virtual ~gaosi();
	double  randnumber(int t,int d); //���������
int  gaoss(float MeanNeed ,float SigmaNeed ) ; //�Ӹ�˹����,x�Ǿ�ֵ��y�Ǿ�����
void awgn(float db, int length, float *n);       //�Ӹ�˹������


};

#endif // !defined(AFX_GAOSI_H__E647A8CD_6E3C_4946_8DE6_B3C4CD786256__INCLUDED_)
