// WavSZ.h : main header file for the WAVSZ application
//

#if !defined(AFX_WAVSZ_H__9DDE76AB_0400_43B3_A87B_F644F00FD6D1__INCLUDED_)
#define AFX_WAVSZ_H__9DDE76AB_0400_43B3_A87B_F644F00FD6D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWavSZApp:
// See WavSZ.cpp for the implementation of this class
//

class CWavSZApp : public CWinApp
{
public:
	CWavSZApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWavSZApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWavSZApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WAVSZ_H__9DDE76AB_0400_43B3_A87B_F644F00FD6D1__INCLUDED_)
