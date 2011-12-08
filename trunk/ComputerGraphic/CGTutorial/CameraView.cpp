// CameraView.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "CameraView.h"


// CCameraView

IMPLEMENT_DYNCREATE(CCameraView, CView)

CCameraView::CCameraView()
{

}

CCameraView::~CCameraView()
{
}

BEGIN_MESSAGE_MAP(CCameraView, CView)
END_MESSAGE_MAP()


// CCameraView drawing

void CCameraView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


// CCameraView diagnostics

#ifdef _DEBUG
void CCameraView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CCameraView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCameraView message handlers
