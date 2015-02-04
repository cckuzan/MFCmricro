// CDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCmricro.h"
#include "CDlg.h"
#include "MainFrm.h"
#include "MFCmricroDoc.h"

//#define WM_MY_ADD_MASSAGE WM_USER+11

// CCDlg

IMPLEMENT_DYNCREATE(CCDlg, CFormView)

CCDlg::CCDlg()
	: CFormView(CCDlg::IDD)
	, m_iDx(0)
	, m_iDy(0)
	, m_iDz(0)
	, m_iCurx(0)
	, m_iCury(0)
	, m_iCurz(0)
{
/*	this->m_SpinX.SetBuddy(GetDlgItem(IDC_EDIT4));
	this->m_SpinY.SetBuddy(GetDlgItem(IDC_EDIT5));
	this->m_SpinZ.SetBuddy(GetDlgItem(IDC_EDIT6));*/
//	this->m_SpinX.
	this->m_iCurx = 1;
	this->m_iCury = 1;
	this->m_iCurz = 1;
	
}

CCDlg::~CCDlg()
{
}

void CCDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_iDx);
	DDX_Text(pDX, IDC_EDIT2, m_iDy);
	DDX_Text(pDX, IDC_EDIT3, m_iDz);
	DDX_Text(pDX, IDC_EDIT4, m_iCurx);
	DDV_MinMaxInt(pDX, m_iCurx, 1, 300);
	DDX_Text(pDX, IDC_EDIT5, m_iCury);
	DDV_MinMaxInt(pDX, m_iCury, 1, 300);
	DDX_Text(pDX, IDC_EDIT6, m_iCurz);
	DDV_MinMaxInt(pDX, m_iCurz, 1, 300);
	DDX_Control(pDX, IDC_SPIN1, m_SpinX);
	DDX_Control(pDX, IDC_SPIN2, m_SpinY);
	DDX_Control(pDX, IDC_SPIN3, m_SpinZ);
}

BEGIN_MESSAGE_MAP(CCDlg, CFormView)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &CCDlg::OnDeltaposSpin1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, &CCDlg::OnDeltaposSpin2)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN3, &CCDlg::OnDeltaposSpin3)

//	ON_MESSAGE(WM_MY_ADD_MASSAGE,CCDlg::OnRecieveAddMsg)

	ON_WM_SIZE()
//	ON_WM_SETFOCUS()
END_MESSAGE_MAP()


// CCDlg 诊断

#ifdef _DEBUG
void CCDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CCDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCDlg 消息处理程序


void CCDlg::OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(pNMUpDown->iDelta == -1)
	{
		this->m_iCurx++;
		theApp.CurDimX = this->m_iCurx;
		UpdateData(FALSE);
	}
	else if( pNMUpDown->iDelta == 1)
	{
		if(this->m_iCurx != 1)
			this->m_iCurx--;
		theApp.CurDimX = this->m_iCurx;
		UpdateData(FALSE);
	}

	CMainFrame* wnd = (CMainFrame*)AfxGetMainWnd();
	auto Xwnd = wnd->m_Splitter2.GetPane(0,1);
	Xwnd->RedrawWindow();

	*pResult = 0;
}


void CCDlg::OnDeltaposSpin2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(pNMUpDown->iDelta == -1)
	{
		this->m_iCury++;
		theApp.CurDimY = this->m_iCury;
		UpdateData(FALSE);
	}
	else if( pNMUpDown->iDelta == 1)
	{
		if(this->m_iCury != 1)
			this->m_iCury--;
		theApp.CurDimY = this->m_iCury;
		UpdateData(FALSE);
	}

	CMainFrame* wnd = (CMainFrame*)AfxGetMainWnd();
	auto Ywnd = wnd->m_Splitter2.GetPane(1,0);
	Ywnd->RedrawWindow();


	*pResult = 0;
}


void CCDlg::OnDeltaposSpin3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(pNMUpDown->iDelta == -1)
	{
		this->m_iCurz++;
		theApp.CurDimZ = this->m_iCurz;
		UpdateData(FALSE);
	}
	else if( pNMUpDown->iDelta == 1)
	{
		if(this->m_iCurz != 1)
			this->m_iCurz--;
		theApp.CurDimZ = this->m_iCurz;
		UpdateData(FALSE);
	}

	CMainFrame* wnd = (CMainFrame*)AfxGetMainWnd();
	auto Zwnd = wnd->m_Splitter2.GetPane(1,1);
	Zwnd->RedrawWindow();


	*pResult = 0;
}




void CCDlg::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);
	CMFCmricroDoc* pDoc = (CMFCmricroDoc*)GetDocument();
	if(pDoc->bFileOpen)
	{
		UpdateData(TRUE);
		this->m_iDx = pDoc->Reader.DimX;
		this->m_iDy = pDoc->Reader.DimY;
		this->m_iDz = pDoc->Reader.DimZ;
//		m_SpinX.SetRange(1,pDoc->Reader.DimX);
//		m_SpinY.SetRange(1,pDoc->Reader.DimY);
//		m_SpinZ.SetRange(1,pDoc->Reader.DimZ);
		UpdateData(FALSE);
	}
	// TODO: 在此处添加消息处理程序代码
}






void CCDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	this->m_SpinX.SetBuddy(GetDlgItem(IDC_EDIT4));
	this->m_SpinY.SetBuddy(GetDlgItem(IDC_EDIT5));
	this->m_SpinZ.SetBuddy(GetDlgItem(IDC_EDIT6));
}
