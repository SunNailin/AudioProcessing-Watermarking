#if !defined(AFX_SHUIYIN_H__2DD50910_C7D8_4DD3_A9D1_B39CA9BC1304__INCLUDED_)
#define AFX_SHUIYIN_H__2DD50910_C7D8_4DD3_A9D1_B39CA9BC1304__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Shuiyin.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CShuiyin dialog

class CShuiyin : public CDialog
{
// Construction
public:
	CShuiyin(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CShuiyin)
	enum { IDD = IDD_SHUIYIN_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShuiyin)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CShuiyin)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHUIYIN_H__2DD50910_C7D8_4DD3_A9D1_B39CA9BC1304__INCLUDED_)
