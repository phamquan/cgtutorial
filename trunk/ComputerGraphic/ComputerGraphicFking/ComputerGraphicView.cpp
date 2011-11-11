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

#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

// CComputerGraphicView

IMPLEMENT_DYNCREATE(CComputerGraphicView, CView)

BEGIN_MESSAGE_MAP(CComputerGraphicView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CComputerGraphicView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_SIZE()

//	ON_WM_CHILDACTIVATE()
END_MESSAGE_MAP()

// CComputerGraphicView construction/destruction

CComputerGraphicView::CComputerGraphicView()
{
	// TODO: add construction code here
	//CComputerGraphicDoc::count = 0;
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


// setup environment for OpenGL Canvas


void CComputerGraphicView::setupOpenGL(void)
{
	//Declare Pixel Format
	static PIXELFORMATDESCRIPTOR pfd =
	{
	sizeof(PIXELFORMATDESCRIPTOR),
	1,
	PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
	PFD_TYPE_RGBA,
	32, // bit depth
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	16, // z-buffer depth
	0, 0, 0, 0, 0, 0, 0,
	};
	// Get device context only once.
	m_hDC = GetDC()->m_hDC;
	// Set Pixel format.
	int nPixelFormat = ChoosePixelFormat(m_hDC, &pfd);
	SetPixelFormat(m_hDC, nPixelFormat, &pfd);
	// Create the OpenGL Rendering Context.
	m_hRC = wglCreateContext(m_hDC);
	wglMakeCurrent( m_hDC, m_hRC );
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
}


int CComputerGraphicView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
		//Setup Opengl
	setupOpenGL();
	return 0;
}


void CComputerGraphicView::removeOpenGL(void)
{
	//Delete Rendering Context
	if(wglGetCurrentContext() != NULL)
		wglMakeCurrent(NULL,NULL);

	if(m_hRC != NULL)
	{
		wglDeleteContext(m_hRC);
		m_hRC = NULL;
	}
}


void CComputerGraphicView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CView::OnPaint() for painting messages
	wglMakeCurrent( m_hDC, m_hRC );
	glClearColor(0.0f, 0.7f, 0.7f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT); 
	glColor3f(1.0f, 0.0f, 0.0f);

	glBegin(GL_POLYGON);        
		glVertex2f(- 0.5, - 0.5);        
		glVertex2f(- 0.5,  0.5);        
		glVertex2f(0.5,  0.5);        
		glVertex2f(0.5, - 0.5);    
	glEnd();
	glFlush();
	
	SwapBuffers(dc.m_ps.hdc);
}


void CComputerGraphicView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: Add your message handler code here
	removeOpenGL();
}


void CComputerGraphicView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	//Setting up viewport
	CRect rect;
	GetClientRect(rect);
	int size = min(rect.Width(), rect.Height());
	glViewport(0, 0, size, size);
}


void CComputerGraphicView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	GetParent()->SetWindowText(GetDocument()->GetTitle()+
								" - This is a test!");

}




//void CComputerGraphicView::OnChildActivate()
//{
//	CView::OnChildActivate();
//
//	// TODO: Add your message handler code here
//	::AfxMessageBox(CString("choose doc"));
//}
