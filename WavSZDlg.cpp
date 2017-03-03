// WavSZDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WavSZ.h"
#include "WavSZDlg.h"
#include "ViewWavDlg.h"
#include "shuiyindlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define CLASSICAL 0
#define CLUB      1
#define DANCE     2
#define DEFAULT   3

int PreEft[18][10]={0,0,0,0,0,-1,-2,-4,-6,-9,
					0,0,0,1,2,3,3,2,1,0,
					9,8,5,2,1,0,-3,-4,-3,0,
					0,0,0,0,0,0,0,0,0,0,
					8,8,8,7,4,0,-3,-5,-7,-9,
					7,6,4,1,-3,-2,-1,2,6,9,
					-9,-8,-7,-6,-3,1,5,8,10,12,
					1,5,7,3,-2,-1,0,3,6,10,
					8,7,6,3,2,0,-1,-2,-1,0,
					-4,-3,-1,0,2,3,3,2,1,0,
					4,4,3,2,0,0,0,0,0,4,
					-2,-1,0,2,3,2,0,-2,-2,-1,
					0,0,0,-1,-3,0,2,2,1,0,
					6,5,2,-2,-5,-2,0,3,5,6,
					-1,-2,-3,-2,0,1,2,3,4,5,
					2,1,0,0,-1,0,1,2,3,4,
					1,1,1,1,0,-1,-2,-2,0,3,
					3,2,1,0,-3,-2,-1,1,3,4};
static bool isset=true;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWavSZDlg dialog

CWavSZDlg::CWavSZDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWavSZDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWavSZDlg)
	m_edit1 = 0;
	m_edit10 = 0;
	m_editg = 0;
	m_edit2 = 0;
	m_edit3 = 0;
	m_edit4 = 0;
	m_edit5 = 0;
	m_edit6 = 0;
	m_edit7 = 0;
	m_edit8 = 0;
	m_edit9 = 0;
	m_wavpath = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWavSZDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWavSZDlg)
	DDX_Control(pDX, IDC_LOGO, m_pic);
	DDX_Control(pDX, IDC_SCRG, m_scrg);
	DDX_Control(pDX, IDC_SCR9, m_scr9);
	DDX_Control(pDX, IDC_SCR8, m_scr8);
	DDX_Control(pDX, IDC_SCR7, m_scr7);
	DDX_Control(pDX, IDC_SCR6, m_scr6);
	DDX_Control(pDX, IDC_SCR5, m_scr5);
	DDX_Control(pDX, IDC_SCR4, m_scr4);
	DDX_Control(pDX, IDC_SCR3, m_scr3);
	DDX_Control(pDX, IDC_SCR2, m_scr2);
	DDX_Control(pDX, IDC_SCR10, m_scr10);
	DDX_Control(pDX, IDC_SCR1, m_scr1);
	DDX_Control(pDX, IDC_COMBO1, m_preef);
	DDX_Text(pDX, IDC_EDIT1, m_edit1);
	DDX_Text(pDX, IDC_EDIT10, m_edit10);
	DDX_Text(pDX, IDC_EDIT11, m_editg);
	DDX_Text(pDX, IDC_EDIT2, m_edit2);
	DDX_Text(pDX, IDC_EDIT3, m_edit3);
	DDX_Text(pDX, IDC_EDIT4, m_edit4);
	DDX_Text(pDX, IDC_EDIT5, m_edit5);
	DDX_Text(pDX, IDC_EDIT6, m_edit6);
	DDX_Text(pDX, IDC_EDIT7, m_edit7);
	DDX_Text(pDX, IDC_EDIT8, m_edit8);
	DDX_Text(pDX, IDC_EDIT9, m_edit9);
	DDX_Text(pDX, IDC_EDIT12, m_wavpath);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWavSZDlg, CDialog)
	//{{AFX_MSG_MAP(CWavSZDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_BTNPLAY, OnBtnplay)
	ON_BN_CLICKED(IDC_BTNSEL, OnBtnsel)
	ON_BN_CLICKED(IDC_BTNSTOP, OnBtnstop)
	ON_BN_CLICKED(IDC_BTNZERO, OnBtnzero)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON5, OnViewWav)
	ON_BN_CLICKED(IDC_BUTTON6, OnShuiyin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWavSZDlg message handlers

BOOL CWavSZDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.
	m_BKbitmap.LoadBitmap(IDB_LOGO);
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	//32
	m_scr1.SetRange(nMin,nMax);
	m_scr1.SetPos(0);
	m_scr1.SetTicFreq(2);
	//64
	m_scr2.SetRange(nMin,nMax);
	m_scr2.SetPos(0);
	m_scr2.SetTicFreq(2);
	//125
	m_scr3.SetRange(nMin,nMax);
	m_scr3.SetPos(0);
	m_scr3.SetTicFreq(2);
	//250
	m_scr4.SetRange(nMin,nMax);
	m_scr4.SetPos(0);
	m_scr4.SetTicFreq(2);
	//500
	m_scr5.SetRange(nMin,nMax);
	m_scr5.SetPos(0);
	m_scr5.SetTicFreq(2);
	//1k
	m_scr6.SetRange(nMin,nMax);
	m_scr6.SetPos(0);
	m_scr6.SetTicFreq(2);
	//2k
	m_scr7.SetRange(nMin,nMax);
	m_scr7.SetPos(0);
	m_scr7.SetTicFreq(2);
	//4k
	m_scr8.SetRange(nMin,nMax);
	m_scr8.SetPos(0);
	m_scr8.SetTicFreq(2);
	//8k
	m_scr9.SetRange(nMin,nMax);
	m_scr9.SetPos(0);
	m_scr9.SetTicFreq(2);
	//16k
	m_scr10.SetRange(nMin,nMax);
	m_scr10.SetPos(0);
	m_scr10.SetTicFreq(2);
	//gain
	m_scrg.SetRange(nMin,nMax);
	m_scrg.SetPos(0);
	m_scrg.SetTicFreq(2);
	UpdateData();

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	for (int i=0;i<10;i++) bandpow[i]=0;
	m_preef.SetCurSel(DEFAULT);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWavSZDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWavSZDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		BITMAP bm;
		CPaintDC   dc(&m_pic); 
		CRect rect1;
		CDC dcMem1;
		m_BKbitmap.GetBitmap (&bm);
		GetClientRect(&rect1);
		dcMem1.CreateCompatibleDC (&dc);
		CBitmap *oldbitmap=dcMem1.SelectObject (&m_BKbitmap);
		dc.BitBlt (0,0,bm.bmWidth ,bm.bmHeight ,&dcMem1,0,0,SRCCOPY);
		dcMem1.SelectObject(oldbitmap);
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWavSZDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CWavSZDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
		int nTemp1, nTemp2;

	nTemp1=pScrollBar->GetScrollPos();
    
	switch(nSBCode) 
	{ 
		case SB_THUMBPOSITION:
		pScrollBar->SetScrollPos(nPos);
		break;

		case SB_LINELEFT: // 左按钮
			nTemp2=(nMax-nMin) / 24; //划为12等份
			if ((nTemp1-nTemp2)>nMin)
			{ nTemp1-=nTemp2; }
			else 
			{
				nTemp1=nMin;
			}
			pScrollBar->SetScrollPos(nTemp1);
			break;

			case SB_LINERIGHT: // 右箭头按钮

				nTemp2=(nMax-nMin)/24;

				if ((nTemp1+nTemp2)<nMax) { nTemp1+=nTemp2; }

				else { nTemp1=nMax; }

				pScrollBar->SetScrollPos(nTemp1);

		break; }
	UpdateData();
		bandpow[0]=m_edit1=-m_scr1.GetPos();
		bandpow[1]=m_edit2=-m_scr2.GetPos();
		bandpow[2]=m_edit3=-m_scr3.GetPos();
		bandpow[3]=m_edit4=-m_scr4.GetPos();
		bandpow[4]=m_edit5=-m_scr5.GetPos();
		bandpow[5]=m_edit6=-m_scr6.GetPos();
		bandpow[6]=m_edit7=-m_scr7.GetPos();
		bandpow[7]=m_edit8=-m_scr8.GetPos();
		bandpow[8]=m_edit9=-m_scr9.GetPos();
		bandpow[9]=m_edit10=-m_scr10.GetPos();
		m_editg=-m_scrg.GetPos();
		if(isset) 
		{
			for (int i=0;i<10;i++) bandpow[i]+=m_editg;
			mwavefile.SetEQ(bandpow,10);
		}

	UpdateData(FALSE);
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CWavSZDlg::OnBtnplay() 
{
	// TODO: Add your control notification handler code here
	if(wavname=="")
	{
		AfxMessageBox("您还没有选择文件！");
	}
	mwavefile.OpenWavFile((LPSTR)(LPCTSTR)wavname,&nchn, &bitpersmp,&smprate);
	mwavefile.PlayWav((LPSTR)(LPCSTR)wavname);

}

void CWavSZDlg::OnBtnsel() 
{
	// TODO: Add your control notification handler code here
		CFileDialog fwave(true,"wav",NULL,OFN_READONLY|OFN_PATHMUSTEXIST,"WAV Files (*.wav)|*.wav|All Files (*.*)|*.*||",this);
	if(IDOK==fwave.DoModal())
	{
		wavname=fwave.GetPathName();
		mwavefile.ReadWavFile((LPSTR)(LPCTSTR)wavname,&nchn, &bitpersmp,&smprate);
		mwavefile.OpenWavFile((LPSTR)(LPCTSTR)wavname,&nchn, &bitpersmp,&smprate);
		m_wavpath=wavname;
		UpdateData(false);
	}
}

void CWavSZDlg::OnBtnstop() 
{
	// TODO: Add your control notification handler code here
		mwavefile.StopPlay();

}

void CWavSZDlg::OnBtnzero() 
{
	// TODO: Add your control notification handler code here
		if (isset)
	{
		m_scr1.SetPos(0);
		m_scr2.SetPos(0);
		m_scr3.SetPos(0);
		m_scr4.SetPos(0);
		m_scr5.SetPos(0);
		m_scr6.SetPos(0);
		m_scr7.SetPos(0);
		m_scr8.SetPos(0);
		m_scr9.SetPos(0);
		m_scr10.SetPos(0);
		m_scrg.SetPos(0);
		UpdateData();
		bandpow[0]=m_edit1=0;
		bandpow[1]=m_edit2=0;
		bandpow[2]=m_edit3=0;
		bandpow[3]=m_edit4=0;
		bandpow[4]=m_edit5=0;
		bandpow[5]=m_edit6=0;
		bandpow[6]=m_edit7=0;
		bandpow[7]=m_edit8=0;
		bandpow[8]=m_edit9=0;
		bandpow[9]=m_edit10=0;
		m_editg=0;
		m_preef.SetCurSel(3);
		UpdateData(FALSE);
		if(isset) mwavefile.SetEQ(bandpow,10);
	}	
}

void CWavSZDlg::OnSelchangeCombo1() 
{
	// TODO: Add your control notification handler code here
		isset=true;
	int ix=m_preef.GetCurSel();
	bandpow[0]=m_edit1=PreEft[ix][0];
	bandpow[1]=m_edit2=PreEft[ix][1];
	bandpow[2]=m_edit3=PreEft[ix][2];
	bandpow[3]=m_edit4=PreEft[ix][3];
	bandpow[4]=m_edit5=PreEft[ix][4];
	bandpow[5]=m_edit6=PreEft[ix][5];
	bandpow[6]=m_edit7=PreEft[ix][6];
	bandpow[7]=m_edit8=PreEft[ix][7];
	bandpow[8]=m_edit9=PreEft[ix][8];
	bandpow[9]=m_edit10=PreEft[ix][9];
	m_scr1.SetPos(-m_edit1);
	m_scr2.SetPos(-m_edit2);
	m_scr3.SetPos(-m_edit3);
	m_scr4.SetPos(-m_edit4);
	m_scr5.SetPos(-m_edit5);
	m_scr6.SetPos(-m_edit6);
	m_scr7.SetPos(-m_edit7);
	m_scr8.SetPos(-m_edit8);
	m_scr9.SetPos(-m_edit9);
	m_scr10.SetPos(-m_edit10);

	UpdateData(FALSE);
	if(isset) 
	{
		for (int i=0;i<10;i++) bandpow[i]+=m_editg;
		mwavefile.SetEQ(bandpow,10);
	}
	mwavefile.SetEQ(bandpow,10);
}

void CWavSZDlg::OnViewWav() 
{
	// TODO: Add your control notification handler code here
	CViewWavDlg *pDlg=new CViewWavDlg(); 
	pDlg->Create(IDD_VIEWWAV_DIALOG); 
	pDlg->ShowWindow(SW_RESTORE); 
}

void CWavSZDlg::OnShuiyin() 
{
	// TODO: Add your control notification handler code here
	/*CShuiyinDlg *pDlg=new CShuiyinDlg(); 
	pDlg->Create(IDD_SHUIYIN_DIALOG); 
	pDlg->ShowWindow(SW_RESTORE); */
	CShuiyinDlg sy;  
	sy.DoModal();   
}
