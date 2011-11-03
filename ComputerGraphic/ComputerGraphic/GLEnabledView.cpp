// GLEnabledView.cpp : implementation file
//

#include "stdafx.h"
#include "ComputerGraphic.h"
#include "GLEnabledView.h"


// CGLEnabledView

IMPLEMENT_DYNCREATE(CGLEnabledView, CView)

CGLEnabledView::CGLEnabledView()
{

}

CGLEnabledView::~CGLEnabledView()
{
}

BEGIN_MESSAGE_MAP(CGLEnabledView, CView)
END_MESSAGE_MAP()


// CGLEnabledView drawing

void CGLEnabledView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


// CGLEnabledView diagnostics

#ifdef _DEBUG
void CGLEnabledView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CGLEnabledView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CGLEnabledView message handlers
