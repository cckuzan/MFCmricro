
// MFCmricroDoc.cpp : CMFCmricroDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCmricro.h"
#endif

#include "MFCmricroDoc.h"

#include <propkey.h>

#include "Nii.h"

#include "CDlg.h"

#include "MainFrm.h"

#include "CView3D.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCmricroDoc

//#define  WM_MY_BROAD_EDIT WM_USER+11

IMPLEMENT_DYNCREATE(CMFCmricroDoc, CDocument)

BEGIN_MESSAGE_MAP(CMFCmricroDoc, CDocument)
END_MESSAGE_MAP()


// CMFCmricroDoc 构造/析构

CMFCmricroDoc::CMFCmricroDoc()
{
	// TODO: 在此添加一次性构造代码
	bFileOpen = 0;
//	this->Reader.pBitmapData = NULL;
//	this->Reader.pOriginData = NULL;
	pvtkImageData = vtkImageData::New();
	popacityTransferFunction = vtkPiecewiseFunction::New();
	pvtkColorTransferFunction = vtkColorTransferFunction::New();
	pvtkVolumeProperty = vtkVolumeProperty::New();
	pCompositeFunction = vtkVolumeRayCastCompositeFunction::New();
	pVolumeMapper = vtkVolumeRayCastMapper::New();
	volume = vtkVolume::New();

//	vtkVolume *volume;

}

CMFCmricroDoc::~CMFCmricroDoc()
{
	pvtkImageData->Delete();
	popacityTransferFunction->Delete();
	pvtkColorTransferFunction->Delete();
	pvtkVolumeProperty->Delete();
	pCompositeFunction->Delete();
	pVolumeMapper->Delete();
	volume->Delete();
}

BOOL CMFCmricroDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)
	ExecutePipeline();
	return TRUE;
}




// CMFCmricroDoc 序列化

void CMFCmricroDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		this->Reader.ReadFile(ar.m_strFileName);
		bFileOpen = 1;

		this->ExecutePipeline();

		//CMainFrame* wnd = (CMainFrame*)AfxGetMainWnd();
		//auto Zwnd = wnd->m_Splitter2.GetPane(0,0);
		//Zwnd->SendMessage(WM_MY_BROAD_EDIT);
		//// TODO: 在此添加加载代码
		


	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CMFCmricroDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CMFCmricroDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:  strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CMFCmricroDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMFCmricroDoc 诊断

#ifdef _DEBUG
void CMFCmricroDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCmricroDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFCmricroDoc 命令
void CMFCmricroDoc::ExecutePipeline()
{
	POSITION pos = this->GetFirstViewPosition();
	CCView3D* pcvtkSDIView = NULL;
	CMainFrame* wnd = (CMainFrame*)AfxGetMainWnd();
	if(pos)
	{
//		pcvtkSDIView = (CCView3D*)GetNextView(pos);
		pcvtkSDIView = (CCView3D*)wnd->m_Splitter2.GetPane(0,0);
//		auto pview = GetNextView(pos);
	}
	else
	{
		ASSERT(FALSE);
		return;
	}
	if(this->bFileOpen)
	{
		if(this->pvtkImageData != NULL)
		{
			this->pvtkImageData->Delete();
			this->pvtkImageData = vtkImageData::New();
			this->pvtkImageData->SetDimensions(this->Reader.DimX,this->Reader.DimY,this->Reader.DimZ );
			this->pvtkImageData->SetScalarType(VTK_UNSIGNED_SHORT);
			this->pvtkImageData->SetSpacing(1.0,1.0,1.0);
			this->pvtkImageData->SetOrigin(0.0,0.0,0.0);
			this->pvtkImageData->SetScalarTypeToUnsignedShort();
			this->pvtkImageData->SetNumberOfScalarComponents(1);
			this->pvtkImageData->AllocateScalars();
		}
		unsigned short *ptr=(unsigned short *)this->pvtkImageData->GetScalarPointer(); 
		memcpy(ptr,this->Reader.pOriginData,this->Reader.DimX * this->Reader.DimY * this->Reader.DimZ * 2); 
		this->popacityTransferFunction->AddPoint(32,0.0);
		this->popacityTransferFunction->AddPoint(224,1.0);

		this->pvtkColorTransferFunction->AddRGBPoint(0.0, 0.0,0.0,0.0);
		this->pvtkColorTransferFunction->AddRGBPoint(64.0, 1.0,0.0,0.0);
		this->pvtkColorTransferFunction->AddRGBPoint(128.0, 0.0,0.0,1.0);
		this->pvtkColorTransferFunction->AddRGBPoint(192.0, 0.0,1.0,0.0);
		this->pvtkColorTransferFunction->AddRGBPoint(255.0, 0.0,0.2,0.0);

		

		this->pvtkVolumeProperty->SetColor(pvtkColorTransferFunction);
		this->pvtkVolumeProperty->SetScalarOpacity(popacityTransferFunction);
		this->pvtkVolumeProperty->SetInterpolationTypeToLinear();
		this->pvtkVolumeProperty->SetDiffuse(0.7);
		this->pvtkVolumeProperty->SetAmbient(0.01);
		this->pvtkVolumeProperty->SetSpecular(0.5);
		this->pvtkVolumeProperty->SetSpecularPower(70.0);


		this->pVolumeMapper->RemoveAllInputs();
		this->pVolumeMapper->Delete();
		this->pVolumeMapper = vtkVolumeRayCastMapper::New();
		
		this->pVolumeMapper->SetVolumeRayCastFunction(this->pCompositeFunction);

		this->pVolumeMapper->SetInput((vtkImageData *)this->pvtkImageData);
//		pcvtkSDIView->GetRenderer()->AddVolume(this->volume);
		pcvtkSDIView->GetRenderer()->RemoveVolume(this->volume);
		pcvtkSDIView->GetRenderer()->AddVolume(this->volume);
//		this->ren->RemoveVolume(this->volume);
		this->volume->Delete();
		this->volume = vtkVolume::New();
		this->volume->SetMapper(this->pVolumeMapper);
		this->volume->SetProperty(this->pvtkVolumeProperty);


		
		pcvtkSDIView->GetRenderer()->AddVolume(this->volume);

		pcvtkSDIView->GetRenderer()->SetBackground(0.0,0.0,0.4);
		pcvtkSDIView->GetRenderer()->ResetCamera();
	}
	else
	{
		//
//		pcvtkSDIView->GetRenderer();
		//

		pcvtkSDIView->GetRenderer()->SetBackground(0.0,0.0,0.4);
		pcvtkSDIView->GetRenderer()->ResetCamera();
//		pcvtkSDIView->pvtkRenderer->SetBackground(0.0,0.0,0.4);
//		pcvtkSDIView->pvtkRenderer->ResetCamera();
	}
}