// ReadPicture1.h: interface for the ReadPicture class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_READPICTURE1_H__E411FEC6_CA39_4AA8_B8A7_2E220054202C__INCLUDED_)
#define AFX_READPICTURE1_H__E411FEC6_CA39_4AA8_B8A7_2E220054202C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define L 64*64
    extern int lWidth;//ͼ��Ŀ�
    extern int lHeight;//ͼ��ĸ�
	extern int lBitCount;//ͼ�����ͣ�ÿ����λ��
    extern double bisize;
	extern unsigned char* m_pDibBits;
 
	extern int my[8*L];
	extern int myy[L][8];
    extern RGBQUAD *pColorTable;

class ReadPicture  
{
public:
	ReadPicture();
	virtual ~ReadPicture();
   bool saveBmp(char *bmpName,unsigned char *imgBuf, int width, int height, int biBitCount, RGBQUAD *pColorTable);

};

#endif // !defined(AFX_READPICTURE1_H__E411FEC6_CA39_4AA8_B8A7_2E220054202C__INCLUDED_)
