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

//以下该模块是完成BMP图像(彩色图像是24bit RGB各8bit)的像素获取，并存在文件名为xiang_su_zhi.txt中
 unsigned char* m_pDibBits;//读入图像数据的指针
int  pic[L];
int lWidth=0;//图像的宽
int lHeight=0;//图像的高
double  bisize=0.0;
RGBQUAD *pColorTable;//颜色表指针
int    m=0;
int lBitCount;//图像类型，每像素位数
 int my[8*L];
 int myy[L][8];
 int c=0  ;


int bit_dec(int  *s)//二进制转十进制
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
//读图像的位图数据、宽、高、颜色表及每像素位数等数据进内存，存放在相应的全局变量中
bool readBmp(CString bmpName) 
{   BITMAPINFOHEADER head;     //定义位图信息头结构变量，读取位图信息头进内存，存放在变量head中
 
    BITMAPFILEHEADER  taghead;//定义位图文件头
	unsigned char  picdata[L];
   FILE *fp=fopen(bmpName,"rb");//二进制读方式打开指定的图像文件
  
   FILE *ft=fopen("lena.txt","wb");

    if(fp==0)
	return 0; 

    fread(&taghead, sizeof(BITMAPFILEHEADER ), 1,fp); //获取图像宽、高、每像素所占位数等信息
    bisize=taghead.bfSize;
     fread(&head, sizeof(BITMAPINFOHEADER), 1,fp); //获取图像宽、高、每像素所占位数等信息   
   
    lWidth = head.biWidth;

    lHeight = head.biHeight;

    lBitCount = head.biBitCount;//定义变量，计算图像每行像素所占的字节数（必须是4的倍数）
  
    int lineByte=(lWidth *lBitCount/8+3)/4*4;//灰度图像有颜色表，

    if(lBitCount==8)
	{
        //申请颜色表所需要的空间，读颜色表进内存

        pColorTable=new RGBQUAD[256];

        fread(pColorTable,sizeof(RGBQUAD),256,fp);    //如果灰度图像，有颜色表，写入文件     
	}

    //申请位图数据所需要的空间，读位图数据进内存
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
	  picdata[i]=picdata[i]/2;//十进制转二进制   这个亲测可用  不要改了
	}
	for(c=7;c>=0;c--)
	 
	 my[k++]=a[c];//存入二进制数,大小为8*lineByte * lHeight=L*8
  }

  m=0;
  for( k=0;k< lWidth * lHeight;k++){
       for(int i=0;i<8;i++)
	   {
		   myy[k][i]=my[m++];
	   }
	  
     pic[k]=bit_dec(myy[k]);//二进制转十进制
	   

  }

  for ( i=0;i< lWidth* lHeight;i++)
	  fprintf(ft,"%u ",pic[i]);
      fclose(ft);

  
     unsigned  char imgbuf[L];
	  for (i=0;i< lWidth* lHeight;i++)
          imgbuf[i]=pic[i];
     saveBmp("newlena.bmp",imgbuf, lWidth, lHeight, lBitCount, pColorTable);

    fclose(fp);//关闭文件
    return 1;//读取文件成功
}



//-----------------------------------------------------------------------------------------
//给定一个图像位图数据、宽、高、颜色表指针及每像素所占的位数等信息,将其写到指定文件中
bool saveBmp(char *bmpName,unsigned char *imgBuf, int width, int height, int biBitCount, RGBQUAD *pColorTable)
{

    //如果位图数据指针为0，则没有数据传入，函数返回

    if(!imgBuf)
        return 0;

    //颜色表大小，以字节为单位，灰度图像颜色表为1024字节，彩色图像颜色表大小为0

    int colorTablesize=0;

    if(biBitCount==8)
        colorTablesize=1024;

    //待存储图像数据每行字节数为4的倍数

    int lineByte=(width * biBitCount/8+3)/4*4;

    //以二进制写的方式打开文件

    FILE *fp=fopen(bmpName,"wb");

    if(fp==0)
		return 0;

    //申请位图文件头结构变量，填写文件头信息

    BITMAPFILEHEADER fileHead;

    fileHead.bfType = 0x4D42;//bmp类型

    //bfSize是图像文件4个组成部分之和

    fileHead.bfSize= sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + colorTablesize + lineByte*height;

    fileHead.bfReserved1 = 0;

    fileHead.bfReserved2 = 0;

    //bfOffBits是图像文件前3个部分所需空间之和

    fileHead.bfOffBits=54+colorTablesize;

    //写文件头进文件

    fwrite(&fileHead, sizeof(BITMAPFILEHEADER),1, fp);

    //申请位图信息头结构变量，填写信息头信息

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

    //写位图信息头进内存

    fwrite(&head, sizeof(BITMAPINFOHEADER),1, fp);

    //如果灰度图像，有颜色表，写入文件 

    if(biBitCount==8)
        fwrite(pColorTable, sizeof(RGBQUAD),256, fp);

    //写位图数据进文件

    fwrite(imgBuf, height*lineByte, 1, fp);

    //关闭文件

    fclose(fp);

    return 1;

}