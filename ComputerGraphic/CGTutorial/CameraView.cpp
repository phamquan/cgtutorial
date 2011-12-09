// CameraView.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "CameraView.h"
#include "CGTutorialDoc.h"

// CCameraView

IMPLEMENT_DYNCREATE(CCameraView, CView)

CCameraView::CCameraView()
{

}

CCameraView::~CCameraView()
{
}

BEGIN_MESSAGE_MAP(CCameraView, CView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_SIZE()
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
void CCameraView::SetupOpenGL()
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
}

void CCameraView::DetroyOpenGL()
{
	if(wglGetCurrentContext() != NULL)
		wglMakeCurrent(NULL,NULL);

	if(m_hRC != NULL)
	{
		wglDeleteContext(m_hRC);
		m_hRC = NULL;
	}
}

int CCameraView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	SetupOpenGL();
	return 0;
}


void CCameraView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: Add your message handler code here
	DetroyOpenGL();
}


BOOL CCameraView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return true;
}


void CCameraView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CView::OnPaint() for painting messages
	wglMakeCurrent( m_hDC, m_hRC );
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(0.0f, 0.0f, 0.0f);

	CMainFrame* mainFrame = (CMainFrame*)AfxGetMainWnd();
	CCGTutorialDoc* doc = (CCGTutorialDoc*) mainFrame->GetActiveDocument();

	/*doc->projection->PaintOpenGL();
	doc->camera->PaintOpenGL();
	doc->object->PaintOpenGL();*/

	glFlush();
	SwapBuffers(dc.m_ps.hdc);
}


void CCameraView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	wglMakeCurrent(m_hDC, m_hRC); 
	CRect rect;
	GetClientRect(rect);
	int w = rect.Width();
	int h = rect.Height();
	glViewport(0, 0, w, h);
}
