// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://msdn.microsoft.com/officeui.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// ComputerGraphicView.cpp : implementation of the CComputerGraphicView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ComputerGraphic.h"
#endif

#include "ComputerGraphicDoc.h"
#include "ComputerGraphicView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CComputerGraphicView

IMPLEMENT_DYNCREATE(CComputerGraphicView, CView)

BEGIN_MESSAGE_MAP(CComputerGraphicView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CComputerGraphicView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CComputerGraphicView construction/destruction

CComputerGraphicView::CComputerGraphicView()
{
	// TODO: add construction code here

}

CComputerGraphicView::~CComputerGraphicView()
{
}

BOOL CComputerGraphicView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CComputerGraphicView drawing

void CComputerGraphicView::OnDraw(CDC* /*pDC*/)
{
	CComputerGraphicDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CComputerGraphicView printing


void CComputerGraphicView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CComputerGraphicView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CComputerGraphicView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CComputerGraphicView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CComputerGraphicView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CComputerGraphicView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CComputerGraphicView diagnostics

#ifdef _DEBUG
void CComputerGraphicView::AssertValid() const
{
	CView::AssertValid();
}

void CComputerGraphicView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CComputerGraphicDoc* CComputerGraphicView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CComputerGraphicDoc)));
	return (CComputerGraphicDoc*)m_pDocument;
}
#endif //_DEBUG


// CComputerGraphicView message handlers
