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
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CCGTutorialView construction/destruction

CCGTutorialView::CCGTutorialView()
{
	// TODO: add construction code here
	//m_isMouseDown = false;
	//m_isMoving = false;
	//m_isDrawing = false;
	m_isCreated = false;
	//m_isLight = false;
	//m_isCamera = false;
	//hit = -1;
	object = NULL;
	//count = 0;
	m_near = -1000;
	m_far = 1000;
	//m_state = ORBIT;
	//m_stateRotate = RXI;
	//m_stateScale = SXI;
	angle.setCoords(0,0,0);
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
void CCGTutorialView::SetupOpenGL()
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

void CCGTutorialView::DetroyOpenGL() {
	if(wglGetCurrentContext() != NULL)
		wglMakeCurrent(NULL,NULL);
	if(m_hRC != NULL)
	{
		wglDeleteContext(m_hRC);
		m_hRC = NULL;
	}
}

void CCGTutorialView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	wglMakeCurrent(m_hDC, m_hRC); 
	CRect rect;
	GetClientRect(rect);
	int size = min(rect.Width(), rect.Height());
	glViewport(0, 0, size, size);
}

void CCGTutorialView::DrawCoordinate() {
}

void CCGTutorialView::EvalViewMatrix() {
}

void CCGTutorialView::OnPaint()
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


int CCGTutorialView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	// TODO:  Add your specialized creation code here
	SetupOpenGL();
	return 0;
}


BOOL CCGTutorialView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	return true;
}
