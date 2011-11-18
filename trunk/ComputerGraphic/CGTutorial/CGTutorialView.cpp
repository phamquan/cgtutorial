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
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 
		32, // z-buffer depth 
		8, 0, PFD_MAIN_PLANE, 0, 0, 0, 0, 
	}; 
	
	// Get device context only once. 
	m_hDC = GetDC()->m_hDC; 

	// Set Pixel format. 
	int nPixelFormat = ChoosePixelFormat(m_hDC, &pfd); 
	SetPixelFormat(m_hDC, nPixelFormat, &pfd); 

	// Create the OpenGL Rendering Context. 
	m_hRC = wglCreateContext(m_hDC); 
	wglMakeCurrent(m_hDC,m_hRC); 

	glClearColor(0.769f, 0.812f, 0.824f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);
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
	int w = rect.Width();
	int h = rect.Height();
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
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

	glOrtho(-m_width, m_width, -m_height, m_height, m_near, m_far);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void CCGTutorialView::DrawCoordinate() {
	glBegin(GL_LINES);
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(1000.0f,0.0f,0.0f);
		/*glVertex3f(1.1f,0.05f,0.0f);
		glVertex3f(1.2f,-0.05f,0.0f);
		glVertex3f(1.2f,0.05f,0.0f);
		glVertex3f(1.1f,-0.05f,0.0f);*/
		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,1000.0f,0.0f);
		/*glVertex3f(-0.05f,1.2f,0.0f);
		glVertex3f(0.0f,1.15f,0.0f);
		glVertex3f(0.05f,1.2f,0.0f);
		glVertex3f(0.0f,1.15f,0.0f);
		glVertex3f(0.0f,1.1f,0.0f);
		glVertex3f(0.0f,1.15f,0.0f);*/
		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,0.0f,1000.0f);
		/*glVertex3f(0.0f,0.05f,1.2f);
		glVertex3f(0.0f,0.05f,1.1f);
		glVertex3f(0.0f,-0.05f,1.2f);
		glVertex3f(0.0f,-0.05f,1.1f);
		glVertex3f(0.0f,0.05f,1.1f);
		glVertex3f(0.0f,-0.05f,1.2f);*/
	glEnd();
}

void CCGTutorialView::EvalViewMatrix() {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
    glRotatef(angle.getY(),1,0,0);
	glRotatef(angle.getX(),0,1,0);
	glTranslatef(Pan.getX(),Pan.getY(),Pan.getZ());	
	glGetFloatv(GL_MODELVIEW_MATRIX,m_ViewMatrix);
	glPopMatrix();
}

void CCGTutorialView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CView::OnPaint() for painting messages
	wglMakeCurrent(m_hDC,m_hRC); 
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	EvalViewMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMultMatrixf(m_ViewMatrix);

	DrawCoordinate();

	//TODO:
	/*if(m_isCamera == TRUE)
		camera.Draw();

	if(m_isLight == TRUE) {
		float m[4];
		light.Draw();
		light.GetPosition(m);
		glLightfv(GL_LIGHT0,GL_POSITION,m);
		light.Light.GetAmbient(m);
		glLightfv(GL_LIGHT0,GL_AMBIENT,m);
		light.Light.GetDiffuse(m);
		glLightfv(GL_LIGHT0,GL_DIFFUSE,m);
		light.Light.GetSpecular(m);
		glLightfv(GL_LIGHT0,GL_SPECULAR,m);
		light.Light.GetDirection(m);
		glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,m);

		glLightf(GL_LIGHT0,GL_SPOT_EXPONENT,light.Light.m_Exponent);
		glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,light.Light.m_Cutoff);
		glLightf(GL_LIGHT0,GL_CONSTANT_ATTENUATION,light.Light.m_Constant);
		glLightf(GL_LIGHT0,GL_LINEAR_ATTENUATION,light.Light.m_Linear);
		glLightf(GL_LIGHT0,GL_QUADRATIC_ATTENUATION,light.Light.m_Quadratic);
	}*/

	for(int i = 2; i < m_listObjects.GetSize(); i++) {
		//if(m_isLight == TRUE)
		//	glEnable(GL_LIGHTING);
		((CGeometricObject*)m_listObjects.GetAt(i))->Draw();
	}

	if(object != NULL)
		object->Draw();

	glFlush();
	SwapBuffers(m_hDC);
	//cameraframe->Invalidate();
}


int CCGTutorialView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	SetupOpenGL();
	//m_listObjects.Add(&light);
	m_listObjects.Add(&camera);

	//cameraframe = new CCameraFrame(&m_listObjects,&camera,&m_isLight);
	//cameraframe->Create(IDD_CAMERA,this);
	//cameraframe->ShowWindow(SW_HIDE);

	//CameraMenu.LoadMenu(IDR_CAMERA);
	//CameraMenu.GetSubMenu(0)->CheckMenuItem(ID_ORTHO,MF_CHECKED);
	//
	//LightMenu.LoadMenu(IDR_LIGHT);

	//ShapeMenu.LoadMenu(IDR_SHAPE);

	return 0;
}


BOOL CCGTutorialView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return true;
}
