
// MFCmricroView.cpp : CMFCmricroView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCmricroView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMFCmricroView 构造/析构

CMFCmricroView::CMFCmricroView()
{
	// TODO: 在此处添加构造代码

}

CMFCmricroView::~CMFCmricroView()
{
}

BOOL CMFCmricroView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCmricroView 绘制

void CMFCmricroView::OnDraw(CDC* /*pDC*/)
{
	CMFCmricroDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMFCmricroView 打印


void CMFCmricroView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCmricroView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCmricroView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMFCmricroView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
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


// CMFCmricroView 诊断

#ifdef _DEBUG
void CMFCmricroView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCmricroView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCmricroDoc* CMFCmricroView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCmricroDoc)));
	return (CMFCmricroDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCmricroView 消息处理程序
