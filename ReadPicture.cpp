// ReadPicture.cpp : implementation file
//

#include "stdafx.h"
#include "WavSZ.h"
#include "ReadPicture.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ReadPicture dialog


ReadPicture::ReadPicture(CWnd* pParent /*=NULL*/)
	: CDialog(ReadPicture::IDD, pParent)
{
	//{{AFX_DATA_INIT(ReadPicture)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void ReadPicture::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ReadPicture)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ReadPicture, CDialog)
	//{{AFX_MSG_MAP(ReadPicture)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ReadPicture message handlers
