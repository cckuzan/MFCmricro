#include "StdAfx.h"
#include "CViewSliceZ.h"
#include "MFCmricroDoc.h"
#include "MFCmricro.h"

IMPLEMENT_DYNCREATE(CCViewSliceZ,CCViewSlice)

CCViewSliceZ::CCViewSliceZ(void)
{
}


CCViewSliceZ::~CCViewSliceZ(void)
{
}
BEGIN_MESSAGE_MAP(CCViewSliceZ, CCViewSlice)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


void CCViewSliceZ::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	MessageBox(_T("Z Clicked!"));
	CCViewSlice::OnLButtonDown(nFlags, point);
}




void CCViewSliceZ::OnDraw(CDC* pDC)
{
	CMFCmricroDoc* pDoc = (CMFCmricroDoc*)GetDocument();
	if(pDoc->bFileOpen)
	{
		BITMAPINFO* bmp = this->CreateBitmapInfo(pDoc->Reader.DimX,pDoc->Reader.DimZ);
		void* img_ptr = NULL;
		CDC MemDC;
		MemDC.CreateCompatibleDC(pDC);
		HBITMAP h_bitmap = ::CreateDIBSection(MemDC , bmp, DIB_RGB_COLORS, &img_ptr, NULL, 0);
		MemDC.SelectObject(h_bitmap);
		int TrueWidth = this->GetTrueWidth(pDoc->Reader.DimX);
		CopyData(img_ptr,pDoc->Reader.DimX,pDoc->Reader.DimZ,TrueWidth,pDoc->Reader.pBitmapData,pDoc->Reader.DimY,theApp.CurDimZ);
		int iLeftCoordinate = this->GetLeftCoordinate(pDoc->Reader.DimX,pDoc->Reader.DimZ);
		int iWidth = this->GetBmpWidth(pDoc->Reader.DimX,pDoc->Reader.DimZ);
		int iHeight = this->GetBmpHeight(pDoc->Reader.DimX,pDoc->Reader.DimZ);
		pDC->StretchBlt(iLeftCoordinate,0,iWidth,iHeight,&MemDC,
		0,0,pDoc->Reader.DimX,pDoc->Reader.DimZ,SRCCOPY);
		delete[] bmp;
	}
//		pDC->BitBlt(0,0,164,220,&MemDC,0,0,SRCCOPY);
	// TODO: 在此添加专用代码和/或调用基类
}


void CCViewSliceZ::CopyData(void* ptr,int Width,int Height,int TrueWidth,char* Src,int YWidth,int CurZ)
{
	char cBuffer[90000];
	int itemp = 0;
	for(int i = 0;i < Height;i++)
	{
		for(int j = 0;j < Width;j++)
		{
			cBuffer[itemp] = Src[j + i * Width * YWidth + (CurZ - 1) * Width];
			itemp++;
		}
	}
	for(int i = 0;i < Height;i++)
	{
		memcpy((char*)ptr + (i * TrueWidth),cBuffer + (i * Width),Width);
	}
}