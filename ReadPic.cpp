// ReadPic.cpp: implementation of the ReadPic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DSP1.h"
#include "ReadPic.h"
#include<math.h>
#include <iomanip.h> 
#include <stdlib.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream.h>
#include <fstream.h>
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ReadPic::ReadPic()
{
}
int len;
int bit_dec(int  *s)//������תʮ����
{ len=8;
int i;
int  p=1,x=0;
 
	for(i = len; i > 0 ; i--)
	 {
      x = x + (s[i-1])*p;
       
        p*=2;
    }
   return(x);
}
//���¸�ģ�������BMPͼ��(��ɫͼ����24bit RGB��8bit)�����ػ�ȡ���������ļ���Ϊxiang_su_zhi.txt��
 unsigned char *pBmpBuf;//����ͼ�����ݵ�ָ��
int  pic[L];
int  picdata[L];
int bmpWidth=0;//ͼ��Ŀ�
int bmpHeight=0;//ͼ��ĸ�
RGBQUAD *pColorTable;//��ɫ��ָ��

int    m=0;
int biBitCount;//ͼ�����ͣ�ÿ����λ��
//unsigned char  y[L];
//unsigned char  yy[L][9];
int my[L*8];
int myy[L][8];
  int c=0  ;
//-------------------------------------------------------------------------------------------
//��ͼ���λͼ���ݡ����ߡ���ɫ��ÿ����λ�������ݽ��ڴ棬�������Ӧ��ȫ�ֱ�����
bool readBmp(CString bmpName) 
{
	 unsigned char  picdata[L];

    FILE *fp=fopen(bmpName,"rb");//�����ƶ���ʽ��ָ����ͼ���ļ�
  
  FILE *fi=fopen("sun.txt","wb");
  FILE *ft=fopen("sun2.txt","wb");

    if(fp==0)
	return 0;

    //����λͼ�ļ�ͷ�ṹBITMAPFILEHEADER

    fseek(fp, sizeof(BITMAPFILEHEADER),0);

    //����λͼ��Ϣͷ�ṹ��������ȡλͼ��Ϣͷ���ڴ棬����ڱ���head��

    BITMAPINFOHEADER head;  

    fread(&head, sizeof(BITMAPINFOHEADER), 1,fp); //��ȡͼ����ߡ�ÿ������ռλ������Ϣ
	
    //fwrite(&head, sizeof(BITMAPINFOHEADER),1, fi);
    bmpWidth = head.biWidth;

    bmpHeight = head.biHeight;

    biBitCount = head.biBitCount;//�������������ͼ��ÿ��������ռ���ֽ�����������4�ı�����

    int lineByte=(bmpWidth * biBitCount/8+3)/4*4;//�Ҷ�ͼ������ɫ������ɫ�����ΪlineByte=256

    if(biBitCount==8)
	{
        //������ɫ������Ҫ�Ŀռ䣬����ɫ����ڴ�

        pColorTable=new RGBQUAD[256];

        fread(pColorTable,sizeof(RGBQUAD),256,fp);    //����Ҷ�ͼ������ɫ��д���ļ� 

       
	}

    //����λͼ��������Ҫ�Ŀռ䣬��λͼ���ݽ��ڴ�

    pBmpBuf=new unsigned char [lineByte * bmpHeight];

    fread(pBmpBuf,lineByte * bmpHeight,1,fp);

   


 int k=0;
 
  for(  int  i=0;i<lineByte * bmpHeight;i++)
       picdata[i]=pBmpBuf[i];

  for( i=0;i<lineByte * bmpHeight;i++)
   
	{
       
	//unsigned char a[9]="00000000";	
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
	{fprintf(fi,"%u",a[c]);
    
	 my[k++]=a[c];//�������������СΪ8*L
	}

  }

fclose(fi);
  m=0;
  for( k=0;k<lineByte * bmpHeight;k++){
       for(int i=0;i<8;i++)
	   {
		   myy[k][i]=my[m++];
	   }
	  
       pic[k]=bit_dec(myy[k]);//������תʮ����
	   

  }

  

  for ( i=0;i<lineByte * bmpHeight;i++)
	  fprintf(ft,"%u ",pic[i]);
      fclose(ft);
unsigned  char imgbuf[L];
	  for (i=0;i<lineByte* bmpHeight;i++)

          imgbuf[i]=pic[i];
  //saveBmp("newlena.bmp",imgbuf, bmpWidth, bmpHeight, biBitCount, pColorTable);


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
ReadPic::~ReadPic()
{

}

//����Ϊ���صĶ�ȡ����
/*void doIt()
{
	FILE *fi=fopen("ͼ����Ϣ.txt","wb");

    //����ָ��BMP�ļ����ڴ�

   // char readPath[]="hh.BMP";
  CString filter;
  CString BmpName;
  filter="�����ļ�(*.bmp,*.jpg,*.gif,*tiff)|*.bmp;*.jpg;*.gif;*.tiff| BMP(*.bmp)|*.bmp| JPG(*.jpg)|*.jpg| GIF(*.gif)|*.gif| TIFF(*.tiff)|*.tiff||";
  CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY,filter,NULL);          


  //����ȷ����ť dlg.DoModal() ������ʾ�Ի���
  if( dlg.DoModal() == IDOK )
  {
    //�򿪶Ի����ȡͼ����Ϣ
    BmpName = dlg.GetPathName();     //��ȡ�ļ�·����   ��D:\pic\abc.bmp
    CString EntName = dlg.GetFileExt();      //��ȡ�ļ���չ��
    EntName.MakeLower();   
  }                  //���ļ���չ��ת��Ϊһ��Сд�ַ�

    readBmp(BmpName);

    //���ͼ�����Ϣ

   // cout<<"width="<<bmpWidth<<" height="<<bmpHeight<<" biBitCount="<<biBitCount<<endl;
    
    //ѭ��������ͼ�������

    //ÿ���ֽ���

     //int lineByte=(bmpWidth*biBitCount/8+3);
    int lineByte=(bmpWidth*biBitCount/8+3)/4*4;

    //ѭ����������Բ�ɫͼ�񣬱���ÿ���ص���������

    int m=0,n=0,count_xiang_su=0;

    //��ͼ�����½�1/4�����óɺ�ɫ
 // fprintf(fi,"%d ", "ͼ����");
	ofstream outfile("ͼ������.txt",ios::in|ios::trunc);
//	outfile<<"ͼ����"<<bmpWidth<<endl;
    //outfile<<"ͼ��߶�"<<bmpHeight<<endl;
    //outfile<<"ɫ��"<<biBitCount<<endl;
    for (int q=0;q<lineByte;q++)
	{	
				for (int p=0;p<bmpHeight;p++)
				//outfile<<*pBmpBuf++<<endl;
			      fprintf(fi,"%d ", * pBmpBuf++);
				   //fprintf(fi,"\n");
	}
			fclose(fi);

    if(biBitCount==8) //���ڻҶ�ͼ��
	{              
	//------------------------------------------------------------------------------------
	//�������ͼ��ķָ��8*8С��Ԫ����������ֵ�洢��ָ���ı��С�����BMPͼ������������Ǵ�
	//��xia�ǣ��������ң�������������ɨ���
        int L1=0;
		int hang=63;
		int lie=0;
		//int L2=0;
        //int fen_ge=8;
		for(int fen_ge_hang=0;fen_ge_hang<8;fen_ge_hang++)//64*64������ѭ��
		{ 
			for(int fen_ge_lie=0;fen_ge_lie<8;fen_ge_lie++)//64*64�о���ѭ��
			{ 
			//--------------------------------------------
				for(L1=hang;L1>hang-8;L1--)//8*8������
				{
					for(int L2=lie;L2<lie+8;L2++)//8*8������
					{
						m=*(pBmpBuf+L1*lineByte+L2);
						outfile<<m<<" ";
						count_xiang_su++;
						if(count_xiang_su%8==0)//ÿ8*8��������ı��ļ�
						{
							outfile<<endl;
						}
					}
				}
			//---------------------------------------------
				hang=63-fen_ge_hang*8;//64*64�����б任
				lie+=8;//64*64�����б任
					//��һ�У�64����8��8*8����������
			}
			hang-=8;//64*64������б任
			lie=0;//64*64juzhen
		}
	}

    //double xiang_su[2048];
	//ofstream outfile("xiang_su_zhi.txt",ios::in|ios::trunc);
	if(!outfile)
	{
	//	cout<<"open error!"<<endl;
		exit(1);
	}
    else if(biBitCount==24)
	{//��ɫͼ��
		for(int i=0;i<bmpHeight;i++)
		{
			for(int j=0;j<bmpWidth;j++)
			{
				for(int k=0;k<3;k++)//ÿ����RGB���������ֱ���0�ű�ɺ�ɫ
				{
					//*(pBmpBuf+i*lineByte+j*3+k)-=40;
                    m=*(pBmpBuf+i*lineByte+j*3+k);
					outfile<<m<<" ";
					count_xiang_su++;
					if(count_xiang_su%8==0)
					{
						outfile<<endl;
					}
				//n++;
				}
				n++;
            }


        }
	//	cout<<"�ܵ����ظ���Ϊ:"<<n<<endl;
		//cout<<"----------------------------------------------------"<<endl;
	}
    
    //��ͼ�����ݴ���
    
    char writePath[]="nvcpy.BMP";//ͼƬ������ٴ洢

    //saveBmp(writePath, pBmpBuf, bmpWidth, bmpHeight, biBitCount, pColorTable);

    //�����������pBmpBuf��pColorTable��ȫ�ֱ��������ļ�����ʱ����Ŀռ�

    delete []pBmpBuf;

    if(biBitCount==8)
        delete []pColorTable;
}*/


