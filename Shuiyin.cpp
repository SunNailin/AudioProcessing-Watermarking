// Shuiyin.cpp : implementation file
//

#include "stdafx.h"
#include "WavSZ.h"
#include "Shuiyin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShuiyin dialog


CShuiyin::CShuiyin(CWnd* pParent /*=NULL*/)
	: CDialog(CShuiyin::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShuiyin)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CShuiyin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShuiyin)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CShuiyin, CDialog)
	//{{AFX_MSG_MAP(CShuiyin)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShuiyin message handlers
