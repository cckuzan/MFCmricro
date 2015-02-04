#include "StdAfx.h"
#include "CViewSliceY.h"
#include "MFCmricroDoc.h"
#include "MFCmricro.h"


IMPLEMENT_DYNCREATE(CCViewSliceY,CCViewSlice)

CCViewSliceY::CCViewSliceY(void)
{
}


CCViewSliceY::~CCViewSliceY(void)
{
}
BEGIN_MESSAGE_MAP(CCViewSliceY, CCViewSlice)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


void CCViewSliceY::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	MessageBox(_T("Y Clicked!"));
	CCViewSlice::OnLButtonDown(nFlags, point);
}



void CCViewSliceY::OnDraw(CDC* pDC)
{
	// TODO: 在此添加专用代码和/或调用基类
	CMFCmricroDoc* pDoc = (CMFCmricroDoc*)GetDocument();
	if(pDoc->bFileOpen)
	{
		BITMAPINFO* bmp = this->CreateBitmapInfo(pDoc->Reader.DimY,pDoc->Reader.DimZ);
		void* img_ptr = NULL;
		CDC MemDC;
		MemDC.CreateCompatibleDC(pDC);
		HBITMAP h_bitmap = ::CreateDIBSection(MemDC , bmp, DIB_RGB_COLORS, &img_ptr, NULL, 0);
		MemDC.SelectObject(h_bitmap);
		int TrueWidth = this->GetTrueWidth(pDoc->Reader.DimY);
		CopyData(img_ptr,pDoc->Reader.DimY,pDoc->Reader.DimZ,TrueWidth,pDoc->Reader.pBitmapData,pDoc->Reader.DimX,theApp.CurDimY);
		int iLeftCoordinate = this->GetLeftCoordinate(pDoc->Reader.DimY,pDoc->Reader.DimZ);
		int iWidth = this->GetBmpWidth(pDoc->Reader.DimY,pDoc->Reader.DimZ);
		int iHeight = this->GetBmpHeight(pDoc->Reader.DimY,pDoc->Reader.DimZ);
		pDC->StretchBlt(iLeftCoordinate,0,iWidth,iHeight,&MemDC,
			0,0,pDoc->Reader.DimY,pDoc->Reader.DimZ,SRCCOPY);
//		pDC->BitBlt(0,0,164,220,&MemDC,0,0,SRCCOPY);
		delete[] bmp;
	}
}


void CCViewSliceY::CopyData(void* ptr,int Width,int Height,int TrueWidth,char* Src,int XWidth,int CurY)
{
	int itemp = 0;
	char cBuffer[90000];
	for(int i = 0;i < Height;i++)
	{
		for(int j = 0;j < Width; j++)
		{
			cBuffer[itemp]= Src[XWidth * j + (i * XWidth * Width) + (CurY - 1)];
			itemp++;
//			theApp.m_bitmapY[theApp.m_cY * i + j] = 
//			theApp.m_bitmap[i * theApp.m_cXPlane + j * theApp.m_cX + (theApp.m_cCurY - 1)];
		}
	}
	for(int i = 0;i < Height;i++)
	{
		memcpy((char*)ptr + (i * TrueWidth),cBuffer + (i * Width),Width);
	}
}