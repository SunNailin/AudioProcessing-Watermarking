// ViewWavDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WavSZ.h"
#include "ViewWavDlg.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define pi 3.1415927
#define Len 64
#define TEST 64
#define REDCL #FF0000
#define YELLOWCL #E6E61A
#define BLUECL #33AECC
#define LENTWO 1024
#define LENONE 512
#define N 1024
/////////////////////////////////////////////////////////////////////////////
// CViewWavDlg dialog


CViewWavDlg::CViewWavDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CViewWavDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CViewWavDlg)
	m_wavpathofview = _T("");
	//}}AFX_DATA_INIT
}


void CViewWavDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViewWavDlg)
	DDX_Text(pDX, IDC_EDIT1, m_wavpathofview);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CViewWavDlg, CDialog)
	//{{AFX_MSG_MAP(CViewWavDlg)
	ON_BN_CLICKED(IDC_BUTTON1, OnBtnSelofView)
	ON_BN_CLICKED(IDC_BTNVIEWWAV, OnBtnviewwav)
	ON_BN_CLICKED(IDC_BTNVIEWSPEC, OnBtnviewspec)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewWavDlg message handlers
int  zero(short a,short b)
{
	if(a>=0&&b>=0)
		return 0;
	else if(a<0&&b<0)
		return 0;
	else
		return 1;
}

/********************FFT�㷨����*****************************/
inline void CViewWavDlg::swap (float &a, float &b) 
{ 
     float t; 
     t = a; 
     a = b; 
     b = t; 
}  

void CViewWavDlg::bitrp (float xreal [], float ximag [], int n) 
{ 
     // λ��ת�û� Bit-reversal Permutation 
     int i, j, a, b, p; 
      for (i = 1, p = 0; i < n; i *= 2) 
{ 
         p ++; 
} 
     for (i = 0; i < n; i ++) 
{ 
         a = i; 
         b = 0; 
         for (j = 0; j < p; j ++) 
   { 
             b = (b << 1) + (a & 1);     // b = b * 2 + a % 2; 
             a >>= 1;         // a = a / 2; 
   } 
         if ( b > i) 
   { 
             swap (xreal [i], xreal [b]); 
             swap (ximag [i], ximag [b]); 
   } 
} 
} 

void CViewWavDlg::FFT(float xreal [], float ximag [], int n) 

{ 

     // ���ٸ���Ҷ�任�������� x �任���Ա����� x �У�xreal, ximag �ֱ��� x ��ʵ�����鲿 
     float wreal [N / 2], wimag [N / 2], treal, timag, ureal, uimag, arg; 
     int m, k, j, t, index1, index2;      
     bitrp (xreal, ximag, n); 
     // ���� 1 ��ǰ n / 2 �� n �η����Ĺ���� W'j = wreal [j] + i * wimag [j] , j = 0, 1,   , n / 2 - 1 
     arg = - 2 * PI / n; 
     treal = cos (arg); 
     timag = sin (arg); 
     wreal [0] = 1.0; 
     wimag [0] = 0.0; 
     for (j = 1; j < n / 2; j ++) 
{ 
         wreal [j] = wreal [j - 1] * treal - wimag [j - 1] * timag; 
         wimag [j] = wreal [j - 1] * timag + wimag [j - 1] * treal; 
} 
 
     for (m = 2; m <= n; m *= 2) { 
         for (k = 0; k < n; k += m) 
   { 
             for (j = 0; j < m / 2; j ++) 
    { 
                 index1 = k + j; 
                 index2 = index1 + m / 2; 
                 t = n * j / m;     // ��ת���� w ��ʵ���� wreal [] �е��±�Ϊ t 
                 treal = wreal [t] * xreal [index2] - wimag [t] * ximag [index2]; 
                 timag = wreal [t] * ximag [index2] + wimag [t] * xreal [index2]; 
                 ureal = xreal [index1]; 
                 uimag = ximag [index1]; 
                 xreal [index1] = ureal + treal; 
                 ximag [index1] = uimag + timag; 
                 xreal [index2] = ureal - treal; 
                 ximag [index2] = uimag - timag; 
    } 
   } 
} 
} 

 

void   CViewWavDlg::IFFT (float xreal [], float ximag [], int n) 
{ 
     // ���ٸ���Ҷ��任 
     float wreal [N / 2], wimag [N / 2], treal, timag, ureal, uimag, arg; 
     int m, k, j, t, index1, index2; 
     bitrp (xreal, ximag, n); 
     // ���� 1 ��ǰ n / 2 �� n �η��� Wj = wreal [j] + i * wimag [j] , j = 0, 1,   , n / 2 - 1 
     arg = 2 * PI / n; 
     treal = cos (arg); 
     timag = sin (arg); 
     wreal [0] = 1.0; 
     wimag [0] = 0.0; 
     for (j = 1; j < n / 2; j ++) 
{ 
         wreal [j] = wreal [j - 1] * treal - wimag [j - 1] * timag; 
         wimag [j] = wreal [j - 1] * timag + wimag [j - 1] * treal; 
} 

     for (m = 2; m <= n; m *= 2) 
{ 
         for (k = 0; k < n; k += m)    { 
             for (j = 0; j < m / 2; j ++) 
    {            index1 = k + j; 
                 index2 = index1 + m / 2; 
                 t = n * j / m;     // ��ת���� w ��ʵ���� wreal [] �е��±�Ϊ t 
                 treal = wreal [t] * xreal [index2] - wimag [t] * ximag [index2]; 
                 timag = wreal [t] * ximag [index2] + wimag [t] * xreal [index2]; 
                 ureal = xreal [index1]; 
                 uimag = ximag [index1]; 
                 xreal [index1] = ureal + treal; 
                 ximag [index1] = uimag + timag; 
                 xreal [index2] = ureal - treal; 
                 ximag [index2] = uimag - timag; 
    } 
   } 
} 

      for (j=0; j < n; j ++) 
{ 
         xreal [j] /= n; 
         ximag [j] /= n; 
} 

} 
void CViewWavDlg::GetResult(float *pfRealBuffer,float *pfImagBuffer,float *pfResBuffer,int iNum)
{
	//���ظ�����ģ
	int i;
	for(i=0;i<iNum;i++)
	{
		pfResBuffer[i]=(float)sqrt(pfRealBuffer[i]*pfRealBuffer[i]+pfImagBuffer[i]*pfImagBuffer[i]);
	}
}
/********************FFT�㷨����*****************************/

/********************��ʾ���κ���*****************************/
void CViewWavDlg::ShowWav() 
{
	//���ID��ΪIDC_TIMEWAV�Ŀؼ���CWndָ�룬��ʹ���������Ӧ���豸����
	CWnd *pWnd = GetDlgItem(IDC_VIEW);
	CDC  *pDC  = pWnd->GetDC();
	//��øÿؼ��ľ�������
	FILE *ft;

long double tmpx,tmpy;
CRect rect;
int m_Low = 0;
int m_High = (wavehead.datasize/2)/44100;
CString str;
int i;
int m_left,m_top,m_right,m_bottom;


int m_Interval = (wavehead.datasize/2)/44100/10;
if (m_Interval < 1)  m_Interval = 1;

// ��ȡ����������ı���

pWnd->GetClientRect(&rect);
pDC->Rectangle(&rect);

m_left =rect.left;
m_top = rect.top;
m_right =rect.right;
m_bottom =rect.bottom;
X_INTERVAL=(double)m_right/(double)(wavehead.datasize/2);//X���ͼ���
Y_INTERVAL=(double)m_bottom/(double)65536;

/*FILE *fp;
fp=fopen("sdgsast.txt","w");
fprintf(fp,"%lf ",X_INTERVAL);
fprintf(fp,"%d ",m_left);
fprintf(fp,"%d ",m_bottom);
fprintf(fp,"%d ",m_top);*/
int m_IntervalPan = (m_right - m_left)/10;
if (m_IntervalPan < 1 ) m_IntervalPan =1;
// �������ʶ���
CPen* pPenRed = new CPen;
// ��ɫ����
pPenRed->CreatePen(PS_SOLID,1,RGB(255,0,0));
// �������ʶ���
CPen* pPenBlue = new CPen;
// ��ɫ����
pPenBlue->CreatePen(PS_SOLID,1,RGB(0,0, 255));
// �������ʶ���
CPen* pPenGreen = new CPen;
// ��ɫ����
pPenGreen->CreatePen(PS_DOT,1,RGB(0,255,0));
// ѡ�е�ǰ��ɫ���ʣ���������ǰ�Ļ���
CGdiObject* pOldPen = pDC->SelectObject(pPenRed);
// ����������
pDC->MoveTo(m_left,m_top);
// ��ֱ��
pDC->LineTo(0,m_bottom/2);
// ˮƽ��
pDC->LineTo(m_right,m_bottom/2);

// дX��̶�ֵ
pDC->LineTo(m_left,m_bottom/2);
pDC->LineTo(m_left,m_bottom);

for(i=0;i<10;i++)
{
//str.Format(_T("%d"),m_Min+i*m_Interval);
str.Format(_T("%d"),m_Low+i*m_Interval);
pDC->TextOut(m_left+i*m_IntervalPan,m_bottom+3,str);	
}
//str.Format(_T("%d"),m_Max);
str.Format(_T("%d"),m_High);
pDC->TextOut(m_left+10*m_IntervalPan,m_bottom+3,str);	
pDC->TextOut(m_left+10*m_IntervalPan+30,m_bottom+3,"��λ����");
// ����X��̶�

for (i = m_left; i < m_right-20; i += 5)
{
if ((i & 1) == 0)
{
// 10�ı���
pDC->MoveTo(i + 10, m_bottom);
pDC->LineTo(i + 10, m_bottom+4);
}
else
{
// 10�ı���
pDC->MoveTo(i + 10, m_bottom);
pDC->LineTo(i + 10, m_bottom+2);
}
}
// ����Y���ͷ
pDC->MoveTo(m_right-5,m_bottom-5);
pDC->LineTo(m_right,m_bottom);
pDC->LineTo(m_right-5,m_bottom+5);
// ����X���ͷ	
pDC->MoveTo(m_left-5,m_top+5);
pDC->LineTo(m_left,m_top);
pDC->LineTo(m_left+5,m_top+5);

// ����Y������ ѡ����ɫ����
    pDC->SelectObject(pPenGreen);	
    //
int iTemp = (m_bottom  - m_top)/5;
    for (i = 1 ;i <= 5 ;i++)
{
pDC->MoveTo(m_left,m_bottom - i*iTemp);
pDC->LineTo(m_right,m_bottom - i*iTemp);
}

// ���ĳ���ɫ����
pDC->SelectObject(pPenBlue);  //��������ӻ������ߵĺ���
pDC->MoveTo(m_left,m_bottom/2);

for(int p=0;p<wavehead.datasize/2;p++)
{	
	tmpy=abs((*++pdata)-32768)*Y_INTERVAL;
	tmpx=p*X_INTERVAL;
	pDC->LineTo(tmpx,tmpy);
	pDC->MoveTo(tmpx,tmpy);
}
// �ָ���ǰ�Ļ���
pDC->SelectObject(pOldPen);	

//fclose(fp);

delete pPenRed;
delete pPenBlue;
delete pPenGreen;
//ָ�����
	for(int k=0;k<wavehead.datasize/2;k++)
	{
		*pdata--;
	}
	//ָ��������
return;
}
/********************��ʾ���κ�������*****************************/

/********************��ʾ����ͼ����*****************************/
void CViewWavDlg::ShowSpec(){
		CWnd *pWnd = GetDlgItem(IDC_VIEW);
		CDC  *pDC  = pWnd->GetDC();
	CRect rect;
	int m_Low = 0;
	int m_High = (wavehead.datasize/2)/44100;
	CString str;
	int i;
	int m_left,m_top,m_right,m_bottom;
	long double X_INTERVAL,Y_INTERVAL;
	FILE *fs,*fs1;


	int m_Interval = (wavehead.datasize/2)/44100/10;
	if (m_Interval < 1)  m_Interval = 1;
	int m_YInterval = (22000)/4;
	if (m_YInterval < 1)  m_YInterval = 1;
	int m_YLow = 0;
	int m_YHigh = 24000;
	int fall=20000;

// ��ȡ����������ı���

	pWnd->GetClientRect(&rect);
	pDC->Rectangle(&rect);

	m_left =rect.left;
	m_top = rect.top;
	m_right =rect.right;
	m_bottom =rect.bottom;
	float tmpi[LENTWO],tmpr[LENTWO];
	float tmp[LENTWO],tmpres[LENTWO];
	double maxtt;
	double resdb[LENTWO];
	double tmpx,tmpy;



	int m_IntervalPan = (m_right - m_left)/10;
	if (m_IntervalPan < 1 ) m_IntervalPan =1;
	int m_YIntervalPan = (m_top - m_bottom - 20)/4;
	if (m_YIntervalPan < 1 ) m_YIntervalPan =1;
	// �������ʶ���
	CPen* pPenRed = new CPen;
	// ��ɫ����
	pPenRed->CreatePen(PS_SOLID,1,RGB(255,0,0));
	// �������ʶ���
	CPen* pPenBlue = new CPen;
	// ��ɫ����
	pPenBlue->CreatePen(PS_SOLID,1,RGB(0,0, 255));
	// �������ʶ���
	CPen* pPenGreen = new CPen;
	// ��ɫ����
	pPenGreen->CreatePen(PS_DOT,1,RGB(0,255,0));
	// ѡ�е�ǰ��ɫ���ʣ���������ǰ�Ļ���
	CGdiObject* pOldPen = pDC->SelectObject(pPenRed);
	// ����������
	pDC->MoveTo(m_left,m_top);
	// ��ֱ��
	pDC->LineTo(0,m_bottom);
	// ˮƽ��
	pDC->LineTo(m_right,m_bottom);

	// дX��̶�ֵ
	pDC->LineTo(m_left,m_bottom);
	pDC->LineTo(m_left,m_bottom);

	for(i=0;i<10;i++)
	{
	//str.Format(_T("%d"),m_Min+i*m_Interval);
	str.Format(_T("%d"),m_Low+i*m_Interval);
	pDC->TextOut(m_left+i*m_IntervalPan,m_bottom+3,str);
		}
	//str.Format(_T("%d"),m_Max);
	str.Format(_T("%d"),m_High);
	pDC->TextOut(m_left+10*m_IntervalPan,m_bottom+3,str);
	pDC->TextOut(m_left+10*m_IntervalPan+30,m_bottom+3,"��λ����");
	// ����X��̶�
	//����Ϊ����X��̶�
	pDC->MoveTo(m_left,m_bottom);

	

	for (i = m_left; i < m_right-20; i += 5)
	{
	if ((i & 1) == 0)
	{
	// 10�ı���
	pDC->MoveTo(i + 10, m_bottom);
	pDC->LineTo(i + 10, m_bottom+4);
	}
	else
	{
	// 10�ı���
	pDC->MoveTo(i + 10, m_bottom);
	pDC->LineTo(i + 10, m_bottom+2);
	}
	}
	// ����Y���ͷ
	pDC->MoveTo(m_right-5,m_bottom-5);
	pDC->LineTo(m_right,m_bottom);
	pDC->LineTo(m_right-5,m_bottom+5);
	// ����X���ͷ	
	pDC->MoveTo(m_left-5,m_top+5);
	pDC->LineTo(m_left,m_top);
	pDC->LineTo(m_left+5,m_top+5);

	// ����Y������ ѡ����ɫ���ʣ�����ͼ����Ϊ��Ч�����ǲ���Y������
/*
    pDC->SelectObject(pPenGreen);	
    //
	int iTemp = (m_bottom  - m_top)/5;
		for (i = 1 ;i <= 5 ;i++)
	{
	pDC->MoveTo(m_left,m_bottom - i*iTemp);
	pDC->LineTo(m_right,m_bottom - i*iTemp);
	}*/

	// ���ĳ���ɫ����
	pDC->SelectObject(pPenBlue);  
	pDC->MoveTo(m_left,m_bottom);
	
	//����Ϊ��������ͼ�������Ĵ���
	fs=fopen("fs.txt","w");
	fs1=fopen("fs1.txt","w");
	for(i=0;i<wavehead.datasize/(2*LENTWO);i++)
	{for(int k=0;k<LENTWO;k++)
		{
		 tmp[k]=(float)*pdata++;
		 tmpr[k]=(float)tmp[k];
		 tmpi[k]=(float)tmp[k];
		}
		double wn=2*pi/LENTWO;
		for(k=0;k<LENTWO;k++)
		{
			tmpr[k]=(0.5*(cos(wn*(k-LENTWO*0.5+0.5))+1));//���Ҵ�
		}
		FFT(tmpr,tmpi,LENTWO);
		GetResult(tmpr,tmpi,tmpres,LENTWO);
		for(k=0;k<LENTWO;k++)
		{
			resdb[k]=20*log(tmpres[k]);
		}
		
		maxtt=resdb[0];
		for(k=0;k<LENTWO;k++)
		{
			if(maxtt<resdb[k])
			{
				maxtt=resdb[k];
			}
		}
		Y_INTERVAL=(double)m_bottom/LENONE;
		X_INTERVAL=(double)m_right/(wavehead.datasize/2/LENTWO);

		for(k=LENONE;k<LENTWO;k++)
		{
			tmpx=i*X_INTERVAL;
			tmpy=(k-LENONE)*Y_INTERVAL;
			fprintf(fs1,"%lf ",resdb[k]);
			fprintf(fs,"%lf ",tmpres[k]);
			if(resdb[k]<2)
			{pDC->SetPixel(tmpx, tmpy, RGB(255,255,255) );}
			if(resdb[k]>2&&resdb[k]<80)
			{pDC->SetPixel(tmpx, tmpy, RGB(0,0,255) );}
			else if (resdb[k]>80&&resdb[k]<90)
			{pDC->SetPixel( tmpx, tmpy, RGB(0,64,255)  );}
			else if (resdb[k]>90&&resdb[k]<100)
			{pDC->SetPixel( tmpx, tmpy, RGB(0,128,255)  );}
			else if (resdb[k]>100&&resdb[k]<110)
			{pDC->SetPixel( tmpx, tmpy, RGB(0,192,255)  );}
			else if (resdb[k]>110&&resdb[k]<120)
			{pDC->SetPixel( tmpx, tmpy, RGB(0,255,255)  );}
			else if (resdb[k]>120&&resdb[k]<130)
			{pDC->SetPixel( tmpx, tmpy, RGB(0,255,192)  );}
			else if (resdb[k]>130&&resdb[k]<140)
			{pDC->SetPixel( tmpx, tmpy, RGB(0,255,128)  );}
			else if (resdb[k]>140&&resdb[k]<150)
			{pDC->SetPixel( tmpx, tmpy, RGB(0,255,64)  );}
			else if (resdb[k]>150&&resdb[k]<160)
			{pDC->SetPixel( tmpx, tmpy, RGB(0,255,0)  );}
			else if (resdb[k]>160&&resdb[k]<170)
			{pDC->SetPixel( tmpx, tmpy, RGB(64,255,0)  );}
			else if (resdb[k]>170&&resdb[k]<180)
			{pDC->SetPixel( tmpx, tmpy, RGB(128,255,0)  );}
			else if (resdb[k]>180&&resdb[k]<190)
			{pDC->SetPixel( tmpx, tmpy, RGB(192,255,0)  );}
			else if (resdb[k]>190&&resdb[k]<200)
			{pDC->SetPixel( tmpx, tmpy, RGB(255,255,0)  );}
			else if (resdb[k]>200&&resdb[k]<210)
			{pDC->SetPixel( tmpx, tmpy, RGB(255,224,0)  );}
			else if (resdb[k]>210&&resdb[k]<220)
			{pDC->SetPixel( tmpx, tmpy, RGB(255,192,0)  );}
			else if (resdb[k]>220&&resdb[k]<230)
			{pDC->SetPixel( tmpx, tmpy, RGB(255,160,0)  );}
			else if (resdb[k]>230&&resdb[k]<240)
			{pDC->SetPixel( tmpx, tmpy, RGB(255,128,0)  );}
			else if (resdb[k]>240&&resdb[k]<250)
			{pDC->SetPixel( tmpx, tmpy, RGB(255,96,0)  );}
			else if (resdb[k]>250&&resdb[k]<260)
			{pDC->SetPixel( tmpx, tmpy, RGB(255,64,0)  );}
			else if (resdb[k]>260&&resdb[k]<270)
			{pDC->SetPixel( tmpx, tmpy, RGB(255,32,0)  );}
			else if (resdb[k]>270&&resdb[k]<280)
			{pDC->SetPixel( tmpx, tmpy, RGB(255,0,0)  );}
			else if (resdb[k]>280)
			{pDC->SetPixel( tmpx, tmpy, RGB(255,0,0)  );}

			//pDC->LineTo(X_INTERVAL*(k),Y_INTERVAL*tmpres[k]);
			//pDC->MoveTo(X_INTERVAL*(k),Y_INTERVAL*tmpres[k]);
		}
}

	int xxx=(m_top-m_bottom-20)/5;
	//str.Format(_T("%d"),m_Min+i*m_Interval);
	for(i =0;i<5;i++){
	str.Format(_T("%d"),m_YLow+i*m_YInterval);
	pDC->TextOut(m_left+3,m_bottom+i*xxx,str);
	}
	
// �ָ���ǰ�Ļ���
pDC->SelectObject(pOldPen);	

str.Format(_T("%d"),m_YHigh);
	pDC->TextOut(m_left+3,m_top-3,"��λ��Hz");
fclose(fs);
fclose(fs1);

delete pPenRed;
delete pPenBlue;
delete pPenGreen;
//ָ�����
	for(int k=0;k<wavehead.datasize/2;k++)
	{
		*pdata--;
	}
	//ָ��������
return;
}
/********************��ʾ����ͼ��������*****************************/

void CViewWavDlg::OnBtnSelofView() 
{
	// TODO: Add your control notification handler code here
		short  tes[Len];
		char  szFileFilter[]=
              "Wave   File(*.wav)|*.wav|"                
              "All   File(*.*)|*.*|| ";//�ļ����͹���  
       CFileDialog  dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY,szFileFilter);  
       FILE* fp;
	   if(dlg.DoModal()==IDOK)  
       {  
	   PathName=dlg.GetPathName(); 		
	   fp=fopen(PathName,"rb");
	   fread(&wavehead,sizeof(struct WaveFileHead),1,fp);
       pdata=(short*)malloc(wavehead.datasize);
//	   pwdata=(short*)malloc(Len);
	   short *pw=(short*)malloc(wavehead.datasize);
	   fread(pdata,sizeof(short),wavehead.datasize/2,fp);
   	   fclose(fp);
	   checkfileopen=TRUE;
	   m_wavpathofview=PathName;
	   UpdateData(false);
	   AfxMessageBox("���ļ��ɹ���");
	   }

    if(checkfileopen==TRUE)
{
    int len=(int)wavehead.sampl/50;
	int lpp=(int)len/4;
	int num=(int)((wavehead.datasize/2-len)/lpp)+1;
	int i;
	int q;
	CString a;
	int z=0;
	float power=0;
	float *ppower=(float*)malloc(num*4);
	int  *pz=(int*)malloc(num*4);
	int *data=(int*)malloc(wavehead.datasize/2);
	for (int k=0;k<wavehead.datasize/2;k++)
	{
		data+=pdata[k];
	}
	for( k=0;k<num;k+=1)
	{
		for(i=k*lpp;i<k*lpp+len;i++)
		{
			power+=pdata[i]*pdata[i];
		}
		for(i=k*lpp;i<k*lpp+len-1;i++)
		{
			z+=zero(pdata[i],pdata[i+1]);
		}
	    ppower[k]=power;
		pz[k]=z;
		z=0;
		power=0;
	}
	/*
	fp=fopen("wave.txt","wb");
	for(k=0;k<wavehead.datasize/2;k++)
	{
		fprintf(fp,"%d",*pdata++);
	}
	fclose(fp);
       }  
*/
 //  CString tmp;
	}

}


void CViewWavDlg::OnBtnviewwav() 
{
	// TODO: Add your control notification handler code here
	if(PathName!=""){
		ShowWav();
	}
	else AfxMessageBox("����û��ѡ���ļ���");
}

void CViewWavDlg::OnBtnviewspec() 
{
	// TODO: Add your control notification handler code here
	if(PathName!=""){
		ShowSpec();
	}
	else AfxMessageBox("����û��ѡ���ļ���");
}
