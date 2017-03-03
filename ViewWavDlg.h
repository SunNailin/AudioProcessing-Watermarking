#if !defined(AFX_VIEWWAVDLG_H__FD1FCEF0_ED53_4D38_8DDB_503735953F02__INCLUDED_)
#define AFX_VIEWWAVDLG_H__FD1FCEF0_ED53_4D38_8DDB_503735953F02__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewWavDlg.h : header file
//
#define PI 3.1415926535
/////////////////////////////////////////////////////////////////////////////
// CViewWavDlg dialog
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

class CViewWavDlg : public CDialog
{
// Construction
public:
	CViewWavDlg(CWnd* pParent = NULL);   // standard constructor
	void ShowWav();
	void ShowSpec();
	void IFFT (float xreal [], float ximag [], int n);
	inline void swap (float &a, float &b);
	void bitrp (float xreal [], float ximag [], int n) ;
	void FFT(float xreal [], float ximag [], int n) ;
	void GetResult(float *pfRealBuffer,float *pfImagBuffer,float *pfResBuffer,int iNum);




//	int  zero(short a,short b);
// Dialog Data
	//{{AFX_DATA(CViewWavDlg)
	enum { IDD = IDD_VIEWWAV_DIALOG };
	CString	m_wavpathofview;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewWavDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CViewWavDlg)
	afx_msg void OnBtnSelofView();
	afx_msg void OnBtnviewwav();
	afx_msg void OnBtnviewspec();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	double X_INTERVAL;
	double Y_INTERVAL;
	CString PathName;
	struct WaveFileHead wavehead;
	BOOL checkfileopen;
	short *pdata;
	int length;
	double m_MaxValue[1];
	double m_MinValue[1];


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWWAVDLG_H__FD1FCEF0_ED53_4D38_8DDB_503735953F02__INCLUDED_)
