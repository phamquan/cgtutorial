#include "StdAfx.h"
#include "DlgCameraFrame.h"

/////////////////////////////////////////////////////////////////////////////
// CCameraFrame dialog


CDlgCameraFrame::CDlgCameraFrame(CEnvironment *environment, COpenGLNode *object, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCameraFrame::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCameraFrame)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	this->environment = environment;
	this->object = object;
}

void CDlgCameraFrame::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCameraFrame)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCameraFrame, CDialog)
	//{{AFX_MSG_MAP(CCameraFrame)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND() // add this line
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCameraFrame message handlers
BOOL CDlgCameraFrame::OnEraseBkgnd(CDC* pDC) {
	return TRUE;
}
void CDlgCameraFrame::SetupOpenGL(void)
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
}

void CDlgCameraFrame::DetroyOpenGL()
{
	if(wglGetCurrentContext() != NULL)
		wglMakeCurrent(NULL,NULL);

	if(m_hRC != NULL)
	{
		wglDeleteContext(m_hRC);
		m_hRC = NULL;
	}

}
void CDlgCameraFrame::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	wglMakeCurrent( m_hDC, m_hRC );
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float x1, y1, z1, x2, y2, z2;
	int w;
	environment->GetProjection()->GetData(x1,y1,z1,x2,y2,z2,w);

	environment->PaintOpenGL();
	DrawCoordinate();
	glColor3f(0.0f, 0.0f, 0.0f);
	object->PaintOpenGL();

	glFlush();
	SwapBuffers(dc.m_ps.hdc);
	wglMakeCurrent( NULL, NULL);
}

int CDlgCameraFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	SetupOpenGL();
	return 0;
}

void CDlgCameraFrame::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	// TODO: Add your message handler code here
	wglMakeCurrent( m_hDC, m_hRC ); 
	float x1,y1,z1,x2;
	int w;
	environment->GetViewPort()->GetData(x1,y1,z1,x2,w);
	if(w == VIEWPORT_CUSTOM)
		glViewport(x1,y1,z1,x2);
	else
		glViewport(0,0,cx,cy);
	wglMakeCurrent( NULL, NULL ); 
	Invalidate();
}


void CDlgCameraFrame::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
	DetroyOpenGL();
}

void CDlgCameraFrame::DrawCoordinate() {
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