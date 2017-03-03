// WavSZDlg.h : header file
//

#if !defined(AFX_WAVSZDLG_H__89953A12_BF9E_4D31_845D_3F0AC11F50CD__INCLUDED_)
#define AFX_WAVSZDLG_H__89953A12_BF9E_4D31_845D_3F0AC11F50CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define PLAY_NONE       0
#define PLAY_WAV        1
#define PLAY_RAW        2
#define PLAY_BUF        3

#define NOERR           0
#define MCI_OPEN_ERROR  -100
#define MCI_PLAY_ERROR  -101

#define ERR_WAVEOUTOPEN     -8
#define ERR_OUTPREHDR       -9
#define ERR_WAVEOUTWRITE    -10


#include "WAVEDECREC.h"
#include "Equalizer.h"
#include "WaveFile.h"
#include "PlayWav.h"
#include "PlayEQ.h"

#define BUFLEN  50 //1s
/////////////////////////////////////////////////////////////////////////////
// CWavSZDlg dialog

class CWavSZDlg : public CDialog
{
// Construction
		enum {nMin=-12};
    enum {nMax=12};
public:
	double bandpow[10];
	CWavSZDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CWavSZDlg)
	enum { IDD = IDD_WAVSZ_DIALOG };
	CStatic	m_pic;
	CSliderCtrl	m_scrg;
	CSliderCtrl	m_scr9;
	CSliderCtrl	m_scr8;
	CSliderCtrl	m_scr7;
	CSliderCtrl	m_scr6;
	CSliderCtrl	m_scr5;
	CSliderCtrl	m_scr4;
	CSliderCtrl	m_scr3;
	CSliderCtrl	m_scr2;
	CSliderCtrl	m_scr10;
	CSliderCtrl	m_scr1;
	CComboBox	m_preef;
	int		m_edit1;
	int		m_edit10;
	int		m_editg;
	int		m_edit2;
	int		m_edit3;
	int		m_edit4;
	int		m_edit5;
	int		m_edit6;
	int		m_edit7;
	int		m_edit8;
	int		m_edit9;
	CString	m_wavpath;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWavSZDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CWavSZDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBtnplay();
	afx_msg void OnBtnsel();
	afx_msg void OnBtnstop();
	afx_msg void OnBtnzero();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnViewWav();
	afx_msg void OnShuiyin();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	private:
	CPlayEQ mwavefile;
	CString wavname;
	WORD nchn, bitpersmp;
	DWORD smprate;
	CBitmap m_BKbitmap;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WAVSZDLG_H__89953A12_BF9E_4D31_845D_3F0AC11F50CD__INCLUDED_)
