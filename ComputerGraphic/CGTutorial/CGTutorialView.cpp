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
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

// CCGTutorialView construction/destruction

CCGTutorialView::CCGTutorialView()
{
	// TODO: add construction code here
	m_isCreated = false;
	m_near = -1000;
	m_far = 1000;
	isShowCamera = true;
	m_isMouseDown = false;
	angle.setCoords(-45,45,0);
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


int CCGTutorialView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	SetupOpenGL();
	return 0;
}


void CCGTutorialView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: Add your message handler code here
	DetroyOpenGL();
}


BOOL CCGTutorialView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	return true;
}


void CCGTutorialView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	wglMakeCurrent(m_hDC, m_hRC); 
	CRect rect;
	GetClientRect(&rect);

	int w = rect.Width();
	int h = rect.Height();
	glViewport(0, 0, w, h);

	if(m_isCreated == false) {
		if (w <= h)	{
			m_width = 2.0;
			m_height = 2.0f * h / w;
		} else {
			m_height = 2.0;
			m_width = 2.0f * w / h;
		}
	} else {
		if (w <= h)	{
			m_height = m_width * h / w;
		} else {
			m_width = m_height * w / h;
		}
	}
	if(w != 0 && h != 0)
		m_isCreated = true;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-m_width, m_width, -m_height, m_height, m_near, m_far);
}


void CCGTutorialView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CView::OnPaint() for painting messages
	wglMakeCurrent( m_hDC, m_hRC );
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	EvalViewMatrix();
	DrawCoordinate();

	if(isShowCamera)
		this->GetDocument()->environment->DrawCamera();

	this->GetDocument()->object->PaintOpenGL();

	glFlush();
	SwapBuffers(dc.m_ps.hdc);
}


void CCGTutorialView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_isMouseDown = true;
	start.setCoords(point.x,point.y,0);
	Invalidate();
}


void CCGTutorialView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_isMouseDown = false;
}


void CCGTutorialView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_isMouseDown) {
		angle.setCoords(angle.getX() + (point.x - start.getX())/5,
						angle.getY() + (point.y - start.getY())/5,
						0);
		if(angle.getX()<0) angle.setX(angle.getX()+360);
		else if (angle.getX()>360) angle.setX(angle.getX()-360);
		if(angle.getY()<0) angle.setY(angle.getY()+360);
		else if (angle.getY()>360) angle.setY(angle.getY()-360);
		start.setCoords(point.x,point.y,0);
		Invalidate();
	}
}


void CCGTutorialView::SetupOpenGL()
{
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

	m_hDC = GetDC()->m_hDC;
	
	int nPixelFormat = ChoosePixelFormat(m_hDC, &pfd);
	SetPixelFormat(m_hDC, nPixelFormat, &pfd);
	
	m_hRC = wglCreateContext(m_hDC);
	wglMakeCurrent(m_hDC,m_hRC); 

	glClearColor(0.769f, 0.812f, 0.824f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glPointSize(4.0);
}

void CCGTutorialView::DetroyOpenGL()
{
	if(wglGetCurrentContext() != NULL)
		wglMakeCurrent(NULL,NULL);

	if(m_hRC != NULL)
	{
		wglDeleteContext(m_hRC);
		m_hRC = NULL;
	}
}

void CCGTutorialView::EvalViewMatrix() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    glRotatef(angle.getY(),1,0,0);
	glRotatef(angle.getX(),0,1,0);
}

void CCGTutorialView::DrawCoordinate() {
	glBegin(GL_LINES);
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(1000.0f,0.0f,0.0f);
		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,1000.0f,0.0f);
		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,0.0f,1000.0f);
	glEnd();
}

BOOL CCGTutorialView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: Add your message handler code here and/or call default
	float zoomY = (zDelta<0)? m_height*0.1:-m_height*0.1;
	float zoomX = zoomY*m_width/m_height;
	m_width += zoomX;
	m_height += zoomY;
	wglMakeCurrent(m_hDC,m_hRC); 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-m_width, m_width, -m_height, m_height, m_near, m_far);
	wglMakeCurrent(NULL,NULL); 
	Invalidate();
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}
