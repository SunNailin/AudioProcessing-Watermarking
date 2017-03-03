//{{AFX_INCLUDES()
#include "wmpplayer4.h"
//}}AFX_INCLUDES
#if !defined(AFX_SHUIYINDLG_H__C7BA70F2_4E44_4ADA_8C57_6901AF6FAC54__INCLUDED_)
#define AFX_SHUIYINDLG_H__C7BA70F2_4E44_4ADA_8C57_6901AF6FAC54__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ShuiyinDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CShuiyinDlg dialog

class CShuiyinDlg : public CDialog
{
// Construction
public:
	struct WaveFileHead
{
	char   riff_id[4];     //"RIFF"
	int    size0;          //���ο�Ĵ�С
	char   wave_fmt[8];    //"wave" and "fmt"
	int    size1;          //��ʽ��Ĵ�С
	short  fmttag;         //���α����ʽ
	short  channel;        //�����ļ������е�ͨ����
	int    sampl;          //�����ļ��Ĳ�����
	int    bytepersecblockalign;  //ƽ��ÿ�벨����Ƶ����Ҫ�ļ�¼���ֽ���
    short  blockalign;      //һ����������Ҫ���ֽ���
    short  bitpersamples;   //�����ļ����ݵ�ÿ��������λ��
	char   data[4];         //"data"
	int    datasize;        //samples
};
	CShuiyinDlg(CWnd* pParent = NULL);   // standard constructor
	friend 	void fidct_1D(double *F,int deg);
	friend 	void fdct_1D(double *f,int deg);
	friend bool readBmp(CString bmpName) ;
    struct WaveFileHead wavehead;
friend bool saveBmp(char *bmpName,unsigned char *imgBuf, int width, int height, int biBitCount, RGBQUAD *pColorTable);
	void ShowBMP(CString strFileName);	
	void ShowBMP2();
friend int bit_dec(int  *s);//������תʮ����
friend void awgn(float db, int length, float *n) ;      //�Ӹ�˹������
friend int   randnumber(int t,int d); //���������
 	friend double  gaoss(float MeanNeed ,float SigmaNeed ) ; //�Ӹ�˹����,x�Ǿ�ֵ��y�Ǿ�����

		 int zero(short a,short b);
      void Wave(CDC*pDC);
      void Energy(CDC*pDC);
      void Abovezero(CDC*pDC); 
      void Information(CDC*pDC); 
	  BOOL OnInitDialog();
// Dialog Data
	//{{AFX_DATA(CShuiyinDlg)
	enum { IDD = IDD_SHUIYIN_DIALOG };
	CComboBox	m_cb;
	CStatic	m_pic2;
	CStatic	m_pic1;
	int		m_bmpbit;
	CString	m_bmpfmt;
	int		m_bmpw;
	int		m_bmph;
	CString	m_channel;
	CString	m_impath1;
	CString	m_impath2;
	CString	m_wavpath1;
	CString	m_quanbit;
	CString	m_sampl;
	float	m_timelen;
	CWMPPlayer4	m_player;
	float	m_psnr;
	float	m_bmpsize;
	int		m_xsd;
	CString	m_wavfmt;
	float	m_bfb;
	CString	m_aver;
	CString	m_fangcha;
	CString	m_suanfa;
	CString	m_min;
	CString	m_max;
	CString	m_qiangdu;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShuiyinDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CShuiyinDlg)
	afx_msg void OnBtnReadBmp1();
	afx_msg void OnBtnReadBmp2();
	afx_msg void OnBtnPSNR();
	afx_msg void OnBtnReadWav();
	afx_msg void OnBtnInSY();
	afx_msg void OnBtnRebuildPic();
	afx_msg void OnGauss();
	afx_msg void OnInsertRand();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnExit();
	afx_msg void OnShuiyinD();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString PathName;
//	CString imPathName;
//	CBitmap  m_bmp;
//	char * id;
//	short * pdata;
	short * pwdata;

BITMAPINFOHEADER *m_bmpInfoHeader;	
//	BITMAPINFOHEADER *infohead;	
	unsigned char *m_pDib;
	//unsigned char *m_pDibBits;	
	DWORD dwDibSize;
	DWORD nFileLen;	
/*	int lWidth;
	int lHeight;
	int lBitCount;
	int bisize;
	int NumColor; */   // Dialog Data
//	unsigned char * idata;
	BOOL checkfileopen;

	BITMAPINFOHEADER *m_bmpInfoHeader2;	
	unsigned char *m_pDib2;
	unsigned char *m_pDibBits2;	
	DWORD dwDibSize2;
	DWORD nFileLen2;	
	int lWidth2;
	int lHeight2;
	int lBitCount2;
	int NumColor2; 
//	RGBQUAD *pColorTable;//��ɫ��ָ��
//	struct WaveFileHead wavehead;


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHUIYINDLG_H__C7BA70F2_4E44_4ADA_8C57_6901AF6FAC54__INCLUDED_)
