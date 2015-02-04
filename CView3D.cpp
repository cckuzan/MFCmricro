// CView3D.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCmricro.h"
#include "CView3D.h"
#include "MFCmricroDoc.h"


// CCView3D

IMPLEMENT_DYNCREATE(CCView3D, CView)

CCView3D::CCView3D()
{
 	this->pvtkMFCWindow = NULL;
	this->pvtkRenderer = vtkRenderer::New();
//	ASSERT(this->pvtkRenderer);

}

CCView3D::~CCView3D()
{
	if(this->pvtkMFCWindow)delete this->pvtkMFCWindow;
}

BEGIN_MESSAGE_MAP(CCView3D, CView)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CCView3D ��ͼ

void CCView3D::OnDraw(CDC* pDC)
{
	CMFCmricroDoc* pDoc = (CMFCmricroDoc*)GetDocument();




	// TODO: �ڴ���ӻ��ƴ���
	ASSERT_VALID(pDoc);
	if(this->pvtkMFCWindow)
	{
		if(pDC->IsPrinting())
			this->pvtkMFCWindow->DrawDC(pDC);
	}
}


// CCView3D ���

#ifdef _DEBUG
void CCView3D::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CCView3D::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCView3D ��Ϣ�������


void CCView3D::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if(this->pvtkMFCWindow)
	{
		this->pvtkMFCWindow->MoveWindow(0,0,cx,cy);
	}
}


void CCView3D::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	if(this->pvtkMFCWindow) 
	{
		delete this->pvtkMFCWindow;
	}
	this->pvtkMFCWindow = new vtkMFCWindow(this);
	this->pvtkMFCWindow->GetRenderWindow()->AddRenderer(this->pvtkRenderer);
}


BOOL CCView3D::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return TRUE;
//	return CView::OnEraseBkgnd(pDC);
}


void CCView3D::OnDestroy()
{

	if(this->pvtkRenderer)this->pvtkRenderer->Delete();
	CView::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
}
