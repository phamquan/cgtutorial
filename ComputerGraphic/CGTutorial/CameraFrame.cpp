// CameraFrame.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "MainFrm.h"
#include "CameraFrame.h"
#include "afxdialogex.h"


// CCameraFrame dialog
static UINT BASED_CODE indicators[] =
{
    ID_INDICATOR_LOCATION,
};

IMPLEMENT_DYNAMIC(CCameraFrame, CDialog)

CCameraFrame::CCameraFrame(CEnvironment *environment, COpenGLNode *object, CWnd* pParent /*=NULL*/)
	: CDialog(CCameraFrame::IDD, pParent)
{
	this->environment = environment;
	this->object = object;
}

CCameraFrame::~CCameraFrame()
{
}

void CCameraFrame::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCameraFrame, CDialog)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CCameraFrame message handlers


void CCameraFrame::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialog::OnPaint() for painting messages
	wglMakeCurrent( m_hDC, m_hRC );
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	environment->PaintOpenGL();
	DrawCoordinate();
	glColor3f(0.0f, 0.0f, 0.0f);
	object->PaintOpenGL();

	glFlush();
	SwapBuffers(dc.m_ps.hdc);
}


int CCameraFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	SetupOpenGL();
	return 0;
}


void CCameraFrame::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	CRect rect;

	if(m_bar.GetSafeHwnd() == NULL) {
		m_bar.Create(this);
		m_bar.SetIndicators(indicators,1);
	}
	m_bar.SetPaneInfo(0,ID_INDICATOR_LOCATION, SBPS_NORMAL,cx);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,ID_INDICATOR_LOCATION);

	m_bar.GetClientRect(&rect);
	subheight = rect.Height();

	width = cx;
	height = cy-subheight;
	ReSize();

	((CMainFrame*)GetParent())->Refresh();
	// TODO: Add your message handler code here
}

void CCameraFrame::ReSize()
{
	wglMakeCurrent( m_hDC, m_hRC ); 
	float x1,y1,z1,x2;
	int w;
	environment->GetViewPort()->GetData(x1,y1,z1,x2,w);
	if(w == VIEWPORT_CUSTOM)
		glViewport(x1,y1+subheight,z1,x2);
	else
		glViewport(0,subheight,width,height);

	Invalidate();
}

BOOL CCameraFrame::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;
}


void CCameraFrame::OnDestroy()
{
	CDialog::OnDestroy();
	DetroyOpenGL();
	// TODO: Add your message handler code here
}

void CCameraFrame::SetupOpenGL(void)
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
	wglMakeCurrent(m_hDC,m_hRC); 
	
	glClearColor(0.769f, 0.812f, 0.824f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glPointSize(4.0);
}

void CCameraFrame::DetroyOpenGL()
{
	if(wglGetCurrentContext() != NULL)
		wglMakeCurrent(NULL,NULL);

	if(m_hRC != NULL)
	{
		wglDeleteContext(m_hRC);
		m_hRC = NULL;
	}

}

void CCameraFrame::DrawCoordinate() {
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

void CCameraFrame::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CString s;
    s.Format("X=%d Y=%d",point.x,height - point.y);
    m_bar.SetPaneText(0,s);

	CDialog::OnMouseMove(nFlags, point);
}
