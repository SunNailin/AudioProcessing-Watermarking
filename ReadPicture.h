#if !defined(AFX_READPICTURE_H__CD3CDB0A_0D4B_4D6D_975D_63B1C4946F39__INCLUDED_)
#define AFX_READPICTURE_H__CD3CDB0A_0D4B_4D6D_975D_63B1C4946F39__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReadPicture.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ReadPicture dialog

class ReadPicture : public CDialog
{
// Construction
public:
	ReadPicture(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ReadPicture)
	enum { IDD = IDD_READPICTURE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ReadPicture)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ReadPicture)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_READPICTURE_H__CD3CDB0A_0D4B_4D6D_975D_63B1C4946F39__INCLUDED_)
