// ShuiyinDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WavSZ.h"
#include "ShuiyinDlg.h"
#include "math.h"
#include"ReadPicture1.h"
#include "gaosi.h"
#include <time.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#ifdef PI
#define PI 3.1415
#endif
#define Len 64
#define TEST 64
#define N 64
#define M 6
#define L 64*64


int  loc=0;
int D =0;
int CShuiyinDlg:: zero(short a,short b)
{
	if(a>=0&&b>=0)
		return 0;
	else if(a<0&&b<0)
		return 0;
	else
		return 1;
}


/////////////////////////////////////////////////////////////////////////////
// CShuiyinDlg dialog


CShuiyinDlg::CShuiyinDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShuiyinDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShuiyinDlg)
	m_bmpbit = 0;
	m_bmpfmt = _T("");
	m_bmpw = 0;
	m_bmph = 0;
	m_channel = _T("");
	m_impath1 = _T("");
	m_impath2 = _T("");
	m_wavpath1 = _T("");
	m_quanbit = _T("");
	m_sampl = _T("");
	m_timelen = 0.0f;
	m_psnr = 0.0f;
	m_bmpsize = 0.0f;
	m_xsd = 0;
	m_wavfmt = _T("");
	m_bfb = 0.0f;
	m_aver = _T("");
	m_fangcha = _T("");
	m_suanfa = _T("");
	m_min = _T("");
	m_max = _T("");
	m_qiangdu = _T("");
	//}}AFX_DATA_INIT
		lHeight=0;
		lHeight2=0;
	//	m_cb.SetCurSel(0);
}


void CShuiyinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShuiyinDlg)
	DDX_Control(pDX, IDC_COMBO1, m_cb);
	DDX_Control(pDX, IDC_PIC2, m_pic2);
	DDX_Control(pDX, IDC_PIC, m_pic1);
	DDX_Text(pDX, IDC_BMPBIT, m_bmpbit);
	DDX_Text(pDX, IDC_BMPFMT, m_bmpfmt);
	DDX_Text(pDX, IDC_BMPWD, m_bmpw);
	DDX_Text(pDX, IDC_BMPHT, m_bmph);
	DDX_Text(pDX, IDC_CHANNEL, m_channel);
	DDX_Text(pDX, IDC_PATHOFBMP1, m_impath1);
	DDX_Text(pDX, IDC_PATHOFBMP2, m_impath2);
	DDX_Text(pDX, IDC_PATHOFWAV, m_wavpath1);
	DDX_Text(pDX, IDC_QUANBIT, m_quanbit);
	DDX_Text(pDX, IDC_SAMPL, m_sampl);
	DDX_Text(pDX, IDC_TIMELEN, m_timelen);
	DDX_Control(pDX, IDC_OCX1, m_player);
	DDX_Text(pDX, IDC_PSNR, m_psnr);
	DDX_Text(pDX, IDC_BMPSIZE, m_bmpsize);
	DDX_Text(pDX, IDC_XSD, m_xsd);
	DDX_Text(pDX, IDC_WAVFMT, m_wavfmt);
	DDX_Text(pDX, IDC_BFB, m_bfb);
	DDX_Text(pDX, IDC_EDIT11, m_aver);
	DDX_Text(pDX, IDC_EDIT1, m_fangcha);
	DDX_CBString(pDX, IDC_COMBO1, m_suanfa);
	DDX_Text(pDX, IDC_EDIT2, m_min);
	DDX_Text(pDX, IDC_EDIT3, m_max);
	DDX_Text(pDX, IDC_EDIT4, m_qiangdu);
	//}}AFX_DATA_MAP
}
BOOL CShuiyinDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	m_cb.SetCurSel(0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

BEGIN_MESSAGE_MAP(CShuiyinDlg, CDialog)
	//{{AFX_MSG_MAP(CShuiyinDlg)
	ON_BN_CLICKED(IDC_BUTTON1, OnBtnReadBmp1)
	ON_BN_CLICKED(IDC_BUTTON2, OnBtnReadBmp2)
	ON_BN_CLICKED(IDC_BUTTON3, OnBtnPSNR)
	ON_BN_CLICKED(IDC_BUTTON4, OnBtnReadWav)
	ON_BN_CLICKED(IDC_BUTTON5, OnBtnInSY)
	ON_BN_CLICKED(IDC_BUTTON6, OnBtnRebuildPic)
	ON_BN_CLICKED(IDC_BUTTON7, OnGauss)
	ON_BN_CLICKED(IDC_, OnInsertRand)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON9, OnExit)
	ON_EN_CHANGE(IDC_EDIT4, OnShuiyinD)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShuiyinDlg message handlers
//DCT�任��������
void dct1c2 (short x[Len], float y[Len]);
void idct1c2 (float y[Len], float z[Len]);
//ȫ�ֱ�������
double FF[L*8][M];
double F[L*M*8];
double FFF[L*M*8];
double SDATA[N];
short *pw;
short *pdata;

//ˮӡ��ض���
int zhengfu(int k);
int  findminzheng(int k);
int  findminfu(int k);
double findmaxzheng(int k);
double findmaxfu(int k);
void waterprint();
void WriteWave();
int FZ[L*8];
int zhengnum[L*8];

///ˮӡ��غ���

int  findminzheng(int k){
    double  min=findmaxzheng(k);
	int num=0;
	for(int i=0;i<M;i++){
		if((FF[k][i]>=0)&&(abs(FF[k][i])<min))
		{	num=i;min=FF[k][i];
		
		}
	}
		return num;

}
int  findminfu(int k){
    double  min=findmaxfu(k);
	int num=0;
	for(int i=0;i<M;i++){
		if((FF[k][i]<0)&&(abs(FF[k][i])<min))
		{
			num=i;min=abs(FF[k][i]);
		}
	}
		return num;

}



int zhengfu(int k){
	int zheng=0;//int fu=0
	for (int i=0;i<M;i++)
	{	if (FF[k][i]>0) zheng++;}
		
		return zheng;
}


double findmaxzheng(int k){
	double max=0;
	for (int i=0;i<M;i++){
		if ((FF[k][i]>0)&&(FF[k][i]>max))
			max=FF[k][i];}
	return max;
		
}



double findmaxfu(int k){
	double max=0;
	for (int i=0;i<M;i++){
		if ((FF[k][i]<0)&&(abs(FF[k][i])>max))
			max=abs(FF[k][i]);}
		return max;
}



void CShuiyinDlg::ShowBMP(CString strFileName) //��ʾ��Ҫ�����ˮӡͼƬ
{	

	CFile file;int NColor;unsigned char *m_pData;
	if(!file.Open(strFileName, CFile::modeRead))
			return;
		BITMAPFILEHEADER bmfHeader;
		
		nFileLen = file.GetLength();
		dwDibSize = nFileLen - sizeof(BITMAPFILEHEADER); //dwDibSizeΪBMP�ܴ�С��ȥBMP�ļ�ͷ�ĳ���
        
		m_pDib = new unsigned char[dwDibSize]; // ΪDIBλͼ�����ڴ�
		
		if (file.Read((LPSTR)&bmfHeader, sizeof(bmfHeader)) != sizeof(bmfHeader)) //���ļ�ͷ
			return;
		
		
		if (bmfHeader.bfType != ((WORD)('M' <<8) | 'B'))  //�ж��Ƿ���BMPλͼ
			return ;

		if (file.Read(m_pDib, dwDibSize) != dwDibSize) //���ļ�ͷ�Ժ��ͼƬ����
			return ;
	
		m_bmpInfoHeader = (BITMAPINFOHEADER*)m_pDib;
		
        int bmpHeight = m_bmpInfoHeader->biHeight; //ͼ��
		int bmpWidth = m_bmpInfoHeader->biWidth; //ͼ���
       int bmpBitCount = m_bmpInfoHeader->biBitCount; //ͼ��λ��
      
		switch(bmpBitCount) 
		{
		case 1:
			NColor = 2;
			break;
		case 4:
			NColor = 16;
			break;
		case 8:
			NColor = 256;
			break;
		case 24:
			NColor = 0;
			break;
		default:
			return;
		}
				m_pData = m_pDib + sizeof(BITMAPINFOHEADER) + NColor * sizeof (RGBQUAD);
	CDC *pDC;
	CRect rect;	
	if(m_pData){
	CWnd *pWnd = GetDlgItem(IDC_PIC);
	pWnd->GetClientRect(&rect);
	pDC = pWnd->GetDC();	
	SetStretchBltMode(pDC->m_hDC,HALFTONE);//��ֹ����Ӧ����ͼ����ʾʧ��
	StretchDIBits(pDC->m_hDC,rect.left, rect.top, rect.right, rect.bottom, 0, 0, 
		bmpWidth, bmpHeight, m_pData, (BITMAPINFO*)m_bmpInfoHeader, BI_RGB, SRCCOPY);
	BOOL bErase=FALSE;
 Invalidate( bErase );

	}
	else  AfxMessageBox("��ȡ��Ϣʧ��");
	
	
		UpdateData(false);

}



//////////////////////��ʾ��ȡ����ˮӡͼƬ//////////////////////////

void CShuiyinDlg::ShowBMP2() 
{
	CDC *pDC;
	CRect rect;	
	if(m_pDibBits2){
	CWnd *pWnd = GetDlgItem(IDC_PIC2);
	pWnd->GetClientRect(&rect);
	pDC = pWnd->GetDC();	
	SetStretchBltMode(pDC->m_hDC,HALFTONE);//��ֹ����Ӧ����ͼ����ʾʧ��
	StretchDIBits(pDC->m_hDC,rect.left, rect.top, rect.right, rect.bottom, 0, 0, 
		lWidth2, lHeight2, m_pDibBits2, (BITMAPINFO*)m_bmpInfoHeader2, BI_RGB, SRCCOPY);
	}
	//pWnd->Invalidate();
	else  AfxMessageBox("��ȡ��Ϣʧ��");
}


///////////////////////��ȡ��Ϊˮӡ��ͼƬ//////////////////////////

void CShuiyinDlg::OnBtnReadBmp1() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE, "*.BMP", NULL, NULL,"λͼ�ļ�(*.BMP)|*.bmp;*.BMP|");
	CString PathName;

 
//	BITMAPFILEHEADER bmfHeader;
    if (dlg.DoModal() == IDOK)
	{		           
	
		     
			  PathName=dlg.GetPathName(); 
              PathName.MakeUpper();  
		
		 AfxMessageBox("�ļ��򿪳ɹ�");

		readBmp(PathName) ;
		ShowBMP(PathName);
		FILE * zx2=fopen("zx2.txt","wb");
		for (int i=0;i<64;i++)
			fprintf(zx2,"%d ",m_pDibBits[i]);
		fclose(zx2);
    	m_impath1=PathName;
		m_bmpw=lWidth;
		m_bmph=lHeight;
		m_bmpbit=lBitCount;
		m_bmpsize=bisize/1024;
		m_bmpfmt="BMP";


		UpdateData(false);
	}//if
	}

///////////////////////��ȡ��ȡ����ˮӡͼƬ//////////////////////////
void CShuiyinDlg::OnBtnReadBmp2() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE, "*.BMP", NULL, NULL,"λͼ�ļ�(*.BMP)|*.bmp;*.BMP|");
	CString strFileName2;
	CFile file2;

    if (dlg.DoModal() == IDOK)
	{		           
		strFileName2 = dlg.GetPathName();
		
		if(!file2.Open(strFileName2, CFile::modeRead))
			return;
		else AfxMessageBox("�ļ��򿪳ɹ�");

		BITMAPFILEHEADER bmfHeader2;
		
		nFileLen2 = file2.GetLength();
		dwDibSize2 = nFileLen2 - sizeof(BITMAPFILEHEADER); //dwDibSizeΪBMP�ܴ�С��ȥBMP�ļ�ͷ�ĳ���
        
		m_pDib2 = new unsigned char[dwDibSize2]; // ΪDIBλͼ�����ڴ�
		
		if (file2.Read((LPSTR)&bmfHeader2, sizeof(bmfHeader2)) != sizeof(bmfHeader2)) //���ļ�ͷ
			return;
		
		
		if (bmfHeader2.bfType != ((WORD)('M' <<8) | 'B'))  //�ж��Ƿ���BMPλͼ
			return ;

		if (file2.Read(m_pDib2, dwDibSize2) != dwDibSize2) //���ļ�ͷ�Ժ��ͼƬ����
			return ;
	
		m_bmpInfoHeader2 = (BITMAPINFOHEADER*)m_pDib2;
		
		lHeight2 = m_bmpInfoHeader2->biHeight; //ͼ��
		lWidth2 = m_bmpInfoHeader2->biWidth; //ͼ���
        lBitCount2 = m_bmpInfoHeader2->biBitCount; //ͼ��λ��
      
		switch(lBitCount2) 
		{
		case 1:
			NumColor2 = 2;
			break;
		case 4:
			NumColor2 = 16;
			break;
		case 8:
			NumColor2 = 256;
			break;
		case 24:
			NumColor2 = 0;
			break;
		default:
			return;
		}
				m_pDibBits2 = m_pDib2 + sizeof(BITMAPINFOHEADER) + NumColor2 * sizeof (RGBQUAD);

		ShowBMP2();
		m_impath2=strFileName2;
		UpdateData(false);

}


}
//////////////////////////////����PSNR/////////////////////////////////
void CShuiyinDlg::OnBtnPSNR() 
{
	// TODO: Add your control notification handler code here
	/*matlab �㷨
	f1=imread('D:\Sunl\��ƵͼƬ��\lena.bmp');
	f2=imread('D:\Sunl\��ƵͼƬ��\lenajz2.bmp');
	k = 8;
	%kΪͼ���Ǳ�ʾ�ظ����ص����õĶ�����λ������λ�
	fmax = 2.^k - 1;
	a = fmax.^2;
	e = double(f1) - double(f2);
	[m, n] = size(e);
	b = mean(sum(sum(e.^2)));
	PSNR = 10*log10(m*n*a/b);
	*/
	if(!lHeight){AfxMessageBox("���ԭʼͼƬ��");}
	else if(!lHeight2){AfxMessageBox("�����ȡ����ˮӡͼƬ��");}
	else if((lHeight!=lHeight2)||(lWidth!=lWidth2)){AfxMessageBox("ͼƬ��С��ƥ�䣬������ѡ��");}
	else if(lHeight&&lHeight2)
	{
	FILE *ftt1=fopen("oo1.txt","w");
	FILE *ftt2=fopen("oo2.txt","w");
	int * m_tmp;
	int count=0;
	int count2=0;
	int m_bit = lBitCount;
	int tmp1=0,tmp2=0;
	float psnr=0;
	int fmax;
	double MSE=0;
	double b=0;
	fmax=pow(2,8)-1;
	m_tmp = new int[lWidth*lHeight];
/*
	FILE *fi;
		fi=fopen("im.txt","w");
			for (int q=0;q<lWidth;q++)
			{	
				for (int p=0;p<lHeight;p++)
				{
					fprintf(fi,"%d ",*m_pDibBits++);
				}
					fprintf(fi,"\n");
				
			}
			fclose(fi);
*/
  for (int i=0;i<lWidth;i++)
	{
		for (int j=0;j<lHeight;j++)
		{
			*m_tmp = (int)*m_pDibBits - (int)*m_pDibBits2;//e
			if((*m_tmp)==0){count++;}
			if(abs(*m_tmp)<10||abs(*m_tmp)==10){count2++;}
			MSE+= (*m_tmp) * (*m_tmp);
			m_tmp++;
			m_pDibBits++;
			m_pDibBits2++;
			fprintf(ftt1,"%d ",*m_pDibBits);
			fprintf(ftt2,"%d ",*m_pDibBits2);
		}
	}
/*	b=(255*255)/b;   
    psnr = 10*(log(b)/log(10));*/  
	
	//b=MSE/(lHeight*lWidth);//b
//	long double ccc=lHeight*lWidth;
	long double fff=fmax*fmax*lWidth;
	float ccc=0,bbb=0;
	ccc=fff/MSE;
	bbb=ccc*lHeight;
	psnr=10*log10(bbb);
	m_psnr=psnr;
	m_bfb=(float)count/((int)lHeight*(int)lWidth)*100;
	m_xsd=(float)count2/((int)lHeight*(int)lWidth)*100;
	UpdateData(false);
	fclose(ftt1);
	fclose(ftt2);}
////////////ָ�����
	for (int i=0;i<lWidth;i++)
	{
		for (int j=0;j<lHeight;j++)
		{
			m_pDibBits--;
			m_pDibBits2--;
		}
	}
}

void CShuiyinDlg::OnBtnReadWav() //����Ƶ�ļ�
{	

	// TODO: Add your control notification handler code here
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
	   pwdata=(short*)malloc(Len);
	   pw=(short*)malloc(wavehead.datasize);
	   fread(pdata,sizeof(short),wavehead.datasize/2,fp);
   	   fclose(fp);
	   checkfileopen=TRUE;
	   AfxMessageBox("���ļ��ɹ���");
   }
	   FILE* fw=fopen("zx4.txt","wb");
for ( int i=0;i<2048;i++)
fprintf(fw,"%d ",pdata[i]);
fclose(fw);

    if(checkfileopen==TRUE){
    int len=(int)wavehead.sampl/50;
	int lpp=(int)len/4;
	int num=(int)((wavehead.datasize/2-len)/lpp)+1;
	int i;
	int q;
	CString a;
	int z=0;
	float power=0;
	float *ppower=(float*)malloc(num*4);
//	int  *pz=(int*)malloc(num*4);
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
	//	pz[k]=z;
		z=0;
		power=0;
	}
	


	m_wavfmt="wave";UpdateData(false);
	a.Format(_T("%d"), wavehead.channel);
    m_channel=a;UpdateData(false);
	a.Format(_T("%d"), wavehead.sampl);
    m_sampl=a;UpdateData(false);
	a.Format(_T("%d"), wavehead.bitpersamples);
    m_quanbit=a;UpdateData(false);
	float n=(float)wavehead.datasize/(float)wavehead.bytepersecblockalign;
	a.Format(_T("%d"), n);
    m_timelen=n;UpdateData(false);
	
  }  



  m_wavpath1=PathName;
  m_player.SetUrl(PathName);
  UpdateData(false);
}

void CShuiyinDlg::OnBtnInSY() //Ƕ��ˮӡ��Ϣ
{
	// TODO: Add your control notification handler code here
  
FILE *fwav=fopen("newmusic.wav","wb");
fwrite(&wavehead,sizeof(struct WaveFileHead),1,fwav);//д�ļ�ͷ��Ϣ
FILE *fw=fopen("zx3.txt","wb");
	int n=0;int Fzheng=0;int Ffu=0;int m=0;int i=0; int j=0;
	
	for (  i=0;i<512;i++)
fprintf(fw,"%d ",pdata[i]);
fclose(fw);

for ( j=0;j<L*M*8;j++){ //�����ѭ��
  for( i=0;i<N;i++){
	SDATA[i]=pdata[m++];//��N�����ݴ�Ϊһ֡

}  

   fdct_1D(SDATA, log(N)/log(2));   //��һ֡������DCT�任
  
   F[j]=*(SDATA+loc);                 //ȡ��һλ��ֱ��ϵ���浽������
 
}//ѭ������

	  m=0;
  for ( i=0;i<L*8;i++)
	 { for (int j=0;j<M;j++)//��ֱ��ϵ����ΪL*8*M�Ķ�ά����
    FF[i][j]=F[m++];
 
 }
for(i=0;i<L*8;i++){//�޸�ǰ����������
 Fzheng=zhengfu(i);
 zhengnum[i]=Fzheng;
}

for(i=0;i<L*8;i++){
	if (my[i]==1)
	{ 
		 Fzheng=zhengfu(i);//��������������
         
		 Ffu=M-Fzheng;
		while (Ffu-Fzheng<=D)//�����ĸ��� ʹ(Ffu-Fzheng>D)��ʾ255
			
			{    j=findminzheng(i);
						
				FF[i][j]=-FF[i][j];
				Ffu++;Fzheng--;					
			}
	}
else 	if (my[i]==0)
	{    Fzheng=zhengfu(i);
		 Ffu=M-Fzheng;
		while (Fzheng-Ffu<=D)//����������,ʹ(Fzheng-Ffu>D) ��ʾ0
			
			
			{j=findminfu(i);
				FF[i][j]=-FF[i][j];
				Fzheng++;Ffu--;
			}
	}
	
}

m=0;
for(i=0;i<L*8;i++){
for (int j=0;j<M;j++)//�޸ĺ��ֱ��ϵ��һά��
FFF[m++]=FF[i][j];

} 
m=0;

for ( j=0;j<L*M*8;j++){ //�����ѭ��

  for(  i=0;i<N;i++){

	SDATA[i]=pdata[m++];//��N�����ݴ�Ϊһ֡

}   
  

   fdct_1D(SDATA, log(N)/log(2));   //��һ֡������DCT�任

    *(SDATA+loc)=FFF[j];                            //�����޸ĵ�ֱ������
    fidct_1D(SDATA, log(N)/log(2));              //���޸ĺ��������DCT��任 
	short musdata[N];
  for(i=0;i<N;i++)
	 
musdata[i]=(short)SDATA[i];
fwrite( musdata,sizeof(short),N,fwav);
}
//short *mpdata;
//for (i=0;i<wavehead.datasize/2-L*M*N*8;i++)
//*mpdata++=pdata[m++];
//fwrite(mpdata,sizeof(short),(wavehead.datasize/2-L*M*N*8),fwav);
fclose(fwav);
//free(mpdata);
free(pdata);
AfxMessageBox("Ƕ��ˮӡ�ɹ�");
}


void CShuiyinDlg::OnBtnRebuildPic() //��ȡˮӡͼƬ
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	FILE *flena=fopen("flena.txt","wb");
     BOOL checkfileopen;
	 CString PathName;
	 struct WaveFileHead wavehead1;
     short  * pdata;
    char  szFileFilter[]=
              "Wave   File(*.wav)|*.wav|"                
              "All   File(*.*)|*.*|| ";//�ļ����͹���  
       CFileDialog  dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY,szFileFilter);  
      FILE* fp;

	   if(dlg.DoModal()==IDOK)  
       {
                  
			  PathName=dlg.GetPathName(); 
              PathName.MakeUpper();  
		
	   fp=fopen(PathName,"rb"); 
	   fread(&wavehead1,sizeof(struct WaveFileHead),1,fp);
       pdata=(short*)malloc(wavehead1.datasize);
	   fread(pdata,sizeof(short),wavehead1.datasize/2,fp); 
	      
	   checkfileopen=TRUE;
	   AfxMessageBox("���ļ��ɹ���");
   }	
int m=0;int n=0;
int Fzheng=0;
int Ffu=0;
    for (int j=0;j<L*M*8;j++){ //�����ѭ��

for( int i=0;i<N;i++){

	SDATA[i]=pdata[m++];}  //��N��Ϊһ֡

   fdct_1D(SDATA, log(N)/log(2));   //��һ֡������DCT�任
  
   F[j]=*(SDATA+loc);                 //ȡ��һλ��ֱ��ϵ���浽������

} 
m=0;
  for ( int i=0;i<L*8;i++)
  {  for ( j=0;j<M;j++)
    FF[i][j]=F[m++];
 
 }
 
	  for(i=0;i<L*8;i++){//L*M
        
		 Fzheng=zhengfu(i);//��������������
         FZ[i]=Fzheng;
		 Ffu=M-Fzheng;
		if  (Fzheng>Ffu)
			my[i]=0;
	else 	my[i]=1;				
	}
free(pdata);
m=0;
int pic[L];

  for( int k=0;k<L;k++){
       for(int i=0;i<8;i++)
	   {
		   myy[k][i]=my[m++];
		    fprintf(flena,"%d ",my[m]);
	   }
	  
       pic[k]=bit_dec(myy[k]);//������תʮ����
	   

  }
 unsigned  char imgbuf[L];
	  for ( i=0;i<L;i++)
	  {
         imgbuf[i]=pic[i];
	
	  }
saveBmp("newlena64.bmp",imgbuf, lWidth, lHeight, lBitCount, pColorTable);
	 
   
	UpdateData(false);


UpdateData(false);
AfxMessageBox("����ͼƬ�ɹ���");
}
	




void CShuiyinDlg::OnGauss() 
{
	// TODO: Add your control notification handler code here
UpdateData(true);
struct WaveFileHead wavehead1;
short  * pdata;
FILE *fwav1=fopen("newmusic.wav","rb");
FILE *fwav2=fopen("newmusic2.wav","wb");
fread(&wavehead1,sizeof(struct WaveFileHead),1,fwav1);//���ļ�ͷ��Ϣ
fwrite(&wavehead1,sizeof(struct WaveFileHead),1,fwav2);//д�ļ�ͷ��Ϣ
pdata=(short*)malloc(wavehead1.datasize);
fread(pdata,sizeof(short),wavehead1.datasize/2,fwav1); 

int i;
	srand((unsigned)time(NULL));//������
	float aver,fangcha=0;
	aver=atof(m_aver);
	fangcha=atof(m_fangcha);



for(i=0;i<wavehead1.datasize/2;)
{
	
	pdata[i]=pdata[i]+gaoss(aver,fangcha);;
	i=i+10;
}
fwrite( pdata,sizeof(short),wavehead1.datasize/2,fwav2);



fclose(fwav1);
fclose(fwav2);
free(pdata);
UpdateData(false);
AfxMessageBox("����ɹ���");
}

void CShuiyinDlg::OnInsertRand() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	struct WaveFileHead wavehead1;
	int  rnumber;
	int min,max;
	int i;
short  * pdata1;
 FILE * ft=fopen("�����.txt","wb");
FILE *fwav1=fopen("newmusic.wav","rb");
FILE *fwav2=fopen("newmusic2.wav","wb");
fread(&wavehead1,sizeof(struct WaveFileHead),1,fwav1);//���ļ�ͷ��Ϣ
fwrite(&wavehead1,sizeof(struct WaveFileHead),1,fwav2);//д�ļ�ͷ��Ϣ
pdata1=(short*)malloc(wavehead1.datasize);
fread(pdata1,sizeof(short),wavehead1.datasize/2,fwav1); 

	srand((unsigned)time(NULL));/*������*/
	min=atof(m_min);
	max=atof(m_max);

for(i=0;i<wavehead1.datasize/2;)
{
	
	rnumber=randnumber(min,max);
	fprintf(ft,"%d ",rnumber);
	pdata1[i]=pdata1[i]+rnumber;
	i=i+10;
}
fwrite( pdata1,sizeof(short),wavehead1.datasize/2,fwav2);
fclose(ft);
fclose(fwav1);
fclose(fwav2);
free(pdata1);
UpdateData(false);
AfxMessageBox("����ɹ���");
	
}

void CShuiyinDlg::OnSelchangeCombo1() 
{
	// TODO: Add your control notification handler code here
UpdateData(true);//ˢ�¿ؼ���ֵ����Ӧ�ı�����(�ⲿ����ֵ�����ڲ�����)

	int nIndex = m_cb.GetCurSel();
	FILE *fp=fopen("index.txt","wb");
	switch(nIndex){
	case 0:loc=0;break;
	case 1:loc=3;break;
	case 2:loc=7;break;
	case 3:loc=31;break;
	default:loc=0;
	}
	fprintf(fp,"%d ",loc);
	fclose (fp);
UpdateData(false);//��������ֵ���ؼ���ʾ


}

void CShuiyinDlg::OnExit() 
{
	// TODO: Add your control notification handler code here
	OnCancel();
}

void CShuiyinDlg::OnShuiyinD() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
		UpdateData(true);
		int qiangdu=atoi(m_qiangdu);
		if ((qiangdu>=0)&&(qiangdu<6))
			D=qiangdu;
		else AfxMessageBox("������0��5������!");
        UpdateData(false);//��������ֵ���ؼ���ʾ

	
}
