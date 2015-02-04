
// MFCmricroView.cpp : CMFCmricroView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MFCmricro.h"
#endif

#include "MFCmricroDoc.h"
#include "MFCmricroView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCmricroView

IMPLEMENT_DYNCREATE(CMFCmricroView, CView)

BEGIN_MESSAGE_MAP(CMFCmricroView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCmricroView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMFCmricroView ����/����

CMFCmricroView::CMFCmricroView()
{
	// TODO: �ڴ˴���ӹ������

}

CMFCmricroView::~CMFCmricroView()
{
}

BOOL CMFCmricroView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMFCmricroView ����

void CMFCmricroView::OnDraw(CDC* /*pDC*/)
{
	CMFCmricroDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CMFCmricroView ��ӡ


void CMFCmricroView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCmricroView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMFCmricroView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMFCmricroView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CMFCmricroView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCmricroView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCmricroView ���

#ifdef _DEBUG
void CMFCmricroView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCmricroView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCmricroDoc* CMFCmricroView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCmricroDoc)));
	return (CMFCmricroDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCmricroView ��Ϣ�������
