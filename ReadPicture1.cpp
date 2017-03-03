// ReadPicture1.cpp: implementation of the ReadPicture class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WavSZ.h"
#include "ReadPicture1.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ReadPicture::ReadPicture()
{

}

ReadPicture::~ReadPicture()
{

}
bool saveBmp(char *bmpName,unsigned char *imgBuf, int width, int height, int biBitCount, RGBQUAD *pColorTable);

//���¸�ģ�������BMPͼ��(��ɫͼ����24bit RGB��8bit)�����ػ�ȡ���������ļ���Ϊxiang_su_zhi.txt��
 unsigned char* m_pDibBits;//����ͼ�����ݵ�ָ��
int  pic[L];
int lWidth=0;//ͼ��Ŀ�
int lHeight=0;//ͼ��ĸ�
double  bisize=0.0;
RGBQUAD *pColorTable;//��ɫ��ָ��
int    m=0;
int lBitCount;//ͼ�����ͣ�ÿ����λ��
 int my[8*L];
 int myy[L][8];
 int c=0  ;


int bit_dec(int  *s)//������תʮ����
{ int len=8;
int i;
int  p=1,x=0;
 
	for(i = len; i > 0 ; i--)
	 {
      x = x + (s[i-1])*p;
       
        p*=2;
    }
   return(x);
}

//-------------------------------------------------------------------------------------------
//��ͼ���λͼ���ݡ����ߡ���ɫ��ÿ����λ�������ݽ��ڴ棬�������Ӧ��ȫ�ֱ�����
bool readBmp(CString bmpName) 
{   BITMAPINFOHEADER head;     //����λͼ��Ϣͷ�ṹ��������ȡλͼ��Ϣͷ���ڴ棬����ڱ���head��
 
    BITMAPFILEHEADER  taghead;//����λͼ�ļ�ͷ
	unsigned char  picdata[L];
   FILE *fp=fopen(bmpName,"rb");//�����ƶ���ʽ��ָ����ͼ���ļ�
  
   FILE *ft=fopen("lena.txt","wb");

    if(fp==0)
	return 0; 

    fread(&taghead, sizeof(BITMAPFILEHEADER ), 1,fp); //��ȡͼ����ߡ�ÿ������ռλ������Ϣ
    bisize=taghead.bfSize;
     fread(&head, sizeof(BITMAPINFOHEADER), 1,fp); //��ȡͼ����ߡ�ÿ������ռλ������Ϣ   
   
    lWidth = head.biWidth;

    lHeight = head.biHeight;

    lBitCount = head.biBitCount;//�������������ͼ��ÿ��������ռ���ֽ�����������4�ı�����
  
    int lineByte=(lWidth *lBitCount/8+3)/4*4;//�Ҷ�ͼ������ɫ��

    if(lBitCount==8)
	{
        //������ɫ������Ҫ�Ŀռ䣬����ɫ����ڴ�

        pColorTable=new RGBQUAD[256];

        fread(pColorTable,sizeof(RGBQUAD),256,fp);    //����Ҷ�ͼ������ɫ��д���ļ�     
	}

    //����λͼ��������Ҫ�Ŀռ䣬��λͼ���ݽ��ڴ�
    m_pDibBits=new unsigned char [ lWidth * lHeight];
    fread( m_pDibBits,lWidth *lHeight,1,fp);

   


 int k=0;
 
  for(   int i=0;i< lWidth* lHeight;i++)
       picdata[i]=m_pDibBits[i];
  for( i=0;i<lineByte * lHeight;i++)
   
	{

	  int a[8]={0,0,0,0,0,0,0,0};
	  c=0;
    while(picdata[i]!=0)
	{ 
      m=picdata[i]%2;
	  a[c]=m;
	  c++;
	  picdata[i]=picdata[i]/2;//ʮ����ת������   ����ײ����  ��Ҫ����
	}
	for(c=7;c>=0;c--)
	 
	 my[k++]=a[c];//�����������,��СΪ8*lineByte * lHeight=L*8
  }

  m=0;
  for( k=0;k< lWidth * lHeight;k++){
       for(int i=0;i<8;i++)
	   {
		   myy[k][i]=my[m++];
	   }
	  
     pic[k]=bit_dec(myy[k]);//������תʮ����
	   

  }

  for ( i=0;i< lWidth* lHeight;i++)
	  fprintf(ft,"%u ",pic[i]);
      fclose(ft);

  
     unsigned  char imgbuf[L];
	  for (i=0;i< lWidth* lHeight;i++)
          imgbuf[i]=pic[i];
     saveBmp("newlena.bmp",imgbuf, lWidth, lHeight, lBitCount, pColorTable);

    fclose(fp);//�ر��ļ�
    return 1;//��ȡ�ļ��ɹ�
}



//-----------------------------------------------------------------------------------------
//����һ��ͼ��λͼ���ݡ����ߡ���ɫ��ָ�뼰ÿ������ռ��λ������Ϣ,����д��ָ���ļ���
bool saveBmp(char *bmpName,unsigned char *imgBuf, int width, int height, int biBitCount, RGBQUAD *pColorTable)
{

    //���λͼ����ָ��Ϊ0����û�����ݴ��룬��������

    if(!imgBuf)
        return 0;

    //��ɫ���С�����ֽ�Ϊ��λ���Ҷ�ͼ����ɫ��Ϊ1024�ֽڣ���ɫͼ����ɫ���СΪ0

    int colorTablesize=0;

    if(biBitCount==8)
        colorTablesize=1024;

    //���洢ͼ������ÿ���ֽ���Ϊ4�ı���

    int lineByte=(width * biBitCount/8+3)/4*4;

    //�Զ�����д�ķ�ʽ���ļ�

    FILE *fp=fopen(bmpName,"wb");

    if(fp==0)
		return 0;

    //����λͼ�ļ�ͷ�ṹ��������д�ļ�ͷ��Ϣ

    BITMAPFILEHEADER fileHead;

    fileHead.bfType = 0x4D42;//bmp����

    //bfSize��ͼ���ļ�4����ɲ���֮��

    fileHead.bfSize= sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + colorTablesize + lineByte*height;

    fileHead.bfReserved1 = 0;

    fileHead.bfReserved2 = 0;

    //bfOffBits��ͼ���ļ�ǰ3����������ռ�֮��

    fileHead.bfOffBits=54+colorTablesize;

    //д�ļ�ͷ���ļ�

    fwrite(&fileHead, sizeof(BITMAPFILEHEADER),1, fp);

    //����λͼ��Ϣͷ�ṹ��������д��Ϣͷ��Ϣ

    BITMAPINFOHEADER head; 

    head.biBitCount=biBitCount;

    head.biClrImportant=0;

    head.biClrUsed=0;

    head.biCompression=0;

    head.biHeight=height;

    head.biPlanes=1;

    head.biSize=40;

    head.biSizeImage=lineByte*height;

    head.biWidth=width;

    head.biXPelsPerMeter=0;

    head.biYPelsPerMeter=0;

    //дλͼ��Ϣͷ���ڴ�

    fwrite(&head, sizeof(BITMAPINFOHEADER),1, fp);

    //����Ҷ�ͼ������ɫ��д���ļ� 

    if(biBitCount==8)
        fwrite(pColorTable, sizeof(RGBQUAD),256, fp);

    //дλͼ���ݽ��ļ�

    fwrite(imgBuf, height*lineByte, 1, fp);

    //�ر��ļ�

    fclose(fp);

    return 1;

}