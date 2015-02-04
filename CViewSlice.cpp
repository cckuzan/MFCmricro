// CViewSlice.cpp : 实现文件
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


// CCViewSlice 绘图

//void CCViewSlice::OnDraw(CDC* pDC)
//{
//	CDocument* pDoc = GetDocument();
//	// TODO: 在此添加绘制代码
//
//}


// CCViewSlice 诊断

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


// CCViewSlice 消息处理程序


BITMAPINFO* CCViewSlice::CreateBitmapInfo(int Width,int Height)
{
		unsigned full_size = sizeof(BITMAPINFOHEADER) + 1024;	
		//为BITMAPINFO结构分配内存
		BITMAPINFO *bmp = (BITMAPINFO *) new unsigned char[full_size];	
     
		bmp->bmiHeader.biSize   = sizeof(BITMAPINFOHEADER);
		bmp->bmiHeader.biWidth  = Width;
		bmp->bmiHeader.biHeight = Height;

		//test
//		bmp->bmiHeader.biWidth  = theApp.m_cY;
//		bmp->bmiHeader.biHeight = theApp.m_cX;
		//test end
		bmp->bmiHeader.biPlanes = 1;
		bmp->bmiHeader.biBitCount = 8;	//8位位图
		bmp->bmiHeader.biCompression = 0;	
		bmp->bmiHeader.biSizeImage = 0;
		bmp->bmiHeader.biXPelsPerMeter = 0;
		bmp->bmiHeader.biYPelsPerMeter = 0;
		bmp->bmiHeader.biClrUsed = 0;
		bmp->bmiHeader.biClrImportant = 0;

		//建立256级灰度调色板
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
	// TODO: 在此添加专用代码和/或调用基类
}


void CCViewSlice::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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