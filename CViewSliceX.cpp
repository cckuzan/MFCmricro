#include "StdAfx.h"
#include "CViewSliceX.h"
#include "MFCmricroDoc.h"
#include "CViewSlice.h"
#include "MFCmricro.h"


IMPLEMENT_DYNCREATE(CCViewSliceX,CCViewSlice)
CCViewSliceX::CCViewSliceX(void)
{
}


CCViewSliceX::~CCViewSliceX(void)
{
}



void CCViewSliceX::OnDraw(CDC* pDC)
{
	// TODO: 在此添加专用代码和/或调用基类
//	auto pDoc = GetDocument();
	CMFCmricroDoc* pDoc = (CMFCmricroDoc*)GetDocument();
	if(pDoc->bFileOpen)
	{
		BITMAPINFO* bmp = this->CreateBitmapInfo(pDoc->Reader.DimX,pDoc->Reader.DimY);
		void* img_ptr = NULL;
		CDC MemDC;
		MemDC.CreateCompatibleDC(pDC);
		HBITMAP h_bitmap = ::CreateDIBSection(MemDC , bmp, DIB_RGB_COLORS, &img_ptr, NULL, 0);
		MemDC.SelectObject(h_bitmap);
		int TrueWidth = this->GetTrueWidth(pDoc->Reader.DimX);
		CopyData(img_ptr,pDoc->Reader.DimX,pDoc->Reader.DimY,TrueWidth,pDoc->Reader.pBitmapData,theApp.CurDimX);
		int iLeftCoordinate = this->GetLeftCoordinate(pDoc->Reader.DimX,pDoc->Reader.DimY);
		int iWidth = this->GetBmpWidth(pDoc->Reader.DimX,pDoc->Reader.DimY);
		int iHeight = this->GetBmpHeight(pDoc->Reader.DimX,pDoc->Reader.DimY);
		pDC->StretchBlt(iLeftCoordinate,0,iWidth,iHeight,&MemDC,
			0,0,pDoc->Reader.DimX,pDoc->Reader.DimY,SRCCOPY);
//		pDC->BitBlt(0,0,164,220,&MemDC,0,0,SRCCOPY);
		delete[] bmp;
	}
}
BEGIN_MESSAGE_MAP(CCViewSliceX, CCViewSlice)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


void CCViewSliceX::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	MessageBox(_T("X Clicked!"));
	CCViewSlice::OnLButtonDown(nFlags, point);
}

void CCViewSliceX::CopyData(void* ptr,int Width,int Height,int TrueWidth,char* Src,int CurX)
{
	for(int i = 0;i < Height;i++)
	{
		memcpy((char*)ptr + (i * TrueWidth),Src + (i * Width) + (CurX - 1) * Width * Height,Width);
	}
}