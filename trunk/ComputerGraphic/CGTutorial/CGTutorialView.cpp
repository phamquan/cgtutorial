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

// CGTutorialView.cpp : implementation of the CCGTutorialView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "CGTutorial.h"
#endif

#include "CGTutorialDoc.h"
#include "CGTutorialView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCGTutorialView

IMPLEMENT_DYNCREATE(CCGTutorialView, CView)

BEGIN_MESSAGE_MAP(CCGTutorialView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CCGTutorialView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CCGTutorialView construction/destruction

CCGTutorialView::CCGTutorialView()
{
	// TODO: add construction code here

}

CCGTutorialView::~CCGTutorialView()
{
}

BOOL CCGTutorialView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CCGTutorialView drawing

void CCGTutorialView::OnDraw(CDC* /*pDC*/)
{
	CCGTutorialDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CCGTutorialView printing


void CCGTutorialView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CCGTutorialView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCGTutorialView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCGTutorialView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CCGTutorialView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCGTutorialView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CCGTutorialView diagnostics

#ifdef _DEBUG
void CCGTutorialView::AssertValid() const
{
	CView::AssertValid();
}

void CCGTutorialView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCGTutorialDoc* CCGTutorialView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCGTutorialDoc)));
	return (CCGTutorialDoc*)m_pDocument;
}
#endif //_DEBUG


// CCGTutorialView message handlers
