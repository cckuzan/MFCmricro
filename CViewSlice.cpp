// CViewSlice.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCmricro.h"
#include "CViewSlice.h"


// CCViewSlice

IMPLEMENT_DYNCREATE(CCViewSlice, CView)

CCViewSlice::CCViewSlice()
{

}

CCViewSlice::~CCViewSlice()
{
}

BEGIN_MESSAGE_MAP(CCViewSlice, CView)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CCViewSlice ��ͼ

//void CCViewSlice::OnDraw(CDC* pDC)
//{
//	CDocument* pDoc = GetDocument();
//	// TODO: �ڴ���ӻ��ƴ���
//
//}


// CCViewSlice ���

#ifdef _DEBUG
void CCViewSlice::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CCViewSlice::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCViewSlice ��Ϣ�������


BITMAPINFO* CCViewSlice::CreateBitmapInfo(int Width,int Height)
{
		unsigned full_size = sizeof(BITMAPINFOHEADER) + 1024;	
		//ΪBITMAPINFO�ṹ�����ڴ�
		BITMAPINFO *bmp = (BITMAPINFO *) new unsigned char[full_size];	
     
		bmp->bmiHeader.biSize   = sizeof(BITMAPINFOHEADER);
		bmp->bmiHeader.biWidth  = Width;
		bmp->bmiHeader.biHeight = Height;

		//test
//		bmp->bmiHeader.biWidth  = theApp.m_cY;
//		bmp->bmiHeader.biHeight = theApp.m_cX;
		//test end
		bmp->bmiHeader.biPlanes = 1;
		bmp->bmiHeader.biBitCount = 8;	//8λλͼ
		bmp->bmiHeader.biCompression = 0;	
		bmp->bmiHeader.biSizeImage = 0;
		bmp->bmiHeader.biXPelsPerMeter = 0;
		bmp->bmiHeader.biYPelsPerMeter = 0;
		bmp->bmiHeader.biClrUsed = 0;
		bmp->bmiHeader.biClrImportant = 0;

		//����256���Ҷȵ�ɫ��
		for( int i =0 ; i < 256; i ++)
		{
			bmp->bmiColors [ i ].rgbBlue = i;
			bmp->bmiColors [ i ].rgbGreen = i;
			bmp->bmiColors [ i ].rgbRed = i;
			bmp->bmiColors [ i ].rgbReserved =0;
		}
		return bmp;
}

int CCViewSlice::GetTrueWidth(unsigned char Width)
{
	int result = Width;
	if((Width % 4) != 0)
	{
		result = Width + (4 - (Width % 4));
	}
	return result;
}

void CCViewSlice::CopyData(void* ptr,int Width,int Height,int TrueWidth,char* Src)
{
}

void CCViewSlice::OnDraw(CDC* /*pDC*/)
{
	// TODO: �ڴ����ר�ô����/����û���
}


void CCViewSlice::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	MessageBox(_T("Base Clicked!"));
	CView::OnLButtonDown(nFlags, point);
}


int CCViewSlice::GetLeftCoordinate(int Width,int Height)
{
	CRect Rct;
	GetClientRect(Rct);
	int result = 0;
	result = abs(Rct.Width() - (Width * Rct.Height() / Height)) / 2;
	return result;
}

int CCViewSlice::GetBmpWidth(int Width,int Height)
{
	CRect Rct;
	GetClientRect(Rct);
	int result = 0;
	result = Width * Rct.Height() / Height;
	return result;
}

int CCViewSlice::GetBmpHeight(int Width,int Height)
{
	CRect Rct;
	GetClientRect(Rct);
	int result = 0;
	result = Rct.Height();
	return result;
}