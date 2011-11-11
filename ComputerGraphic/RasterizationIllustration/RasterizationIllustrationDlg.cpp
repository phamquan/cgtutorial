
// RasterizationIllustrationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RasterizationIllustration.h"
#include "RasterizationIllustrationDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CRasterizationIllustrationDlg dialog




CRasterizationIllustrationDlg::CRasterizationIllustrationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRasterizationIllustrationDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRasterizationIllustrationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRasterizationIllustrationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_WM_MOUSEWHEEL()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_CONTEXTRI_RUNSTEP, &CRasterizationIllustrationDlg::OnContextriRunstep)
	ON_COMMAND(ID_CONTEXTRI_RUNALL, &CRasterizationIllustrationDlg::OnContextriRunall)
	ON_COMMAND(ID_CONTEXTRI_ERASE, &CRasterizationIllustrationDlg::OnContextriErase)
	ON_WM_MBUTTONDOWN()
END_MESSAGE_MAP()


// CRasterizationIllustrationDlg message handlers

BOOL CRasterizationIllustrationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	ShowWindow(SW_MAXIMIZE);

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRasterizationIllustrationDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRasterizationIllustrationDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this); // device context for painting
		// TODO: Add your message handler code here
		// Do not call CView::OnPaint() for painting messages
		CDialogEx::OnPaint();
		wglMakeCurrent( m_hDC, m_hRC );
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT); 
		glColor3f(0.2f, 0.2f, 0.2f);
		setCamera();
		drawOrigin();
		drawBoard();
		drawPixel();
		glFlush();
	
		SwapBuffers(dc.m_ps.hdc);
		
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CRasterizationIllustrationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CRasterizationIllustrationDlg::setupOpenGL(void)
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
}


void CRasterizationIllustrationDlg::removeOpenGL(void)
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


int CRasterizationIllustrationDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	initParameter();
	setupOpenGL();
	return 0;
}


void CRasterizationIllustrationDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	wglMakeCurrent( m_hDC, m_hRC );
	CRect rect;
	GetClientRect(rect);
	double w = rect.Width();
	double h = rect.Height();
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
	{
		m_width = m_dfLen;
		m_height = m_dfLen * h / w;
	}
	else
	{
		m_height = m_dfLen;
		m_width = m_dfLen * w / h;
	}
	glOrtho(-m_width, m_width, -m_height, m_height, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	Invalidate();
}


BOOL CRasterizationIllustrationDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	return true;
	//return CDialogEx::OnEraseBkgnd(pDC);
}


void CRasterizationIllustrationDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	removeOpenGL();
	delete m_config;
}


void CRasterizationIllustrationDlg::drawBoard(void)
{
	float size = m_config->getScale();
	int height = m_config->getHeight();
	int width = m_config->getWidth();
	float y = 0;
	int i;
	for (i=0;i <= height;i++) {
		glBegin(GL_LINES);
			glVertex2f(0, y);
			glVertex2f(size*width, y);
		glEnd();
		y+=size;
	}
	float x = 0;
	for (i=0;i <= width;i++) {
		glBegin(GL_LINES);
			glVertex2f(x, 0);
			glVertex2f(x, size*height);
		glEnd();
		x+=size;
	}
}

CRasterizationConfig* CRasterizationIllustrationDlg::getConfig() {
	return m_config;
}

void CRasterizationIllustrationDlg::initParameter() {
	m_dfLen = 2.0;
	hRunStep = NULL;
	dwRunStepId = 0;
	m_config = new CRasterizationConfig(800, 600, 0.1);
	int width = m_config->getWidth(),
		height = m_config->getHeight();
	if (width*height == 0) 
		m_pixelState = NULL;
	else {
		m_pixelState = new PIXELTYPE[width * height];
		Erase();
	}
}

BOOL CRasterizationIllustrationDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: Add your message handler code here and/or call default
	float delta = 0.001;
	m_config->modifyScale(zDelta>0? delta:-delta);
	Invalidate();
	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}


void CRasterizationIllustrationDlg::drawOrigin(void)
{
	//glBegin(GL_POLYGON);        
	//	glVertex2f(- 0.1, - 0.1);        
	//	glVertex2f(- 0.1,  0.1);        
	//	glVertex2f(0.1,  0.1);        
	//	glVertex2f(0.1, - 0.1);    
	//glEnd();
}


void CRasterizationIllustrationDlg::Rasterize(PIXEL start, PIXEL end,RASTERIZEALG alg, bool isStep)
{
	int width = m_config->getWidth();
	//Thoi gian delay moi buoc
	int nTime = isStep? 50 : 0;
	m_pixelState[start.y*width + start.x] = m_pixelState[end.y*width + end.x] = PCHOSEN;
	Sleep(nTime);
	switch(alg) {
	case DDA:
		{
			float m = (float)(end.y - start.y)/(end.x - start.x);
			if (abs(m) < 1) {
				int x;
				float y = y=start.y;
				if (end.x > start.x) {
					for (x=start.x; x<=end.x; x++) {
						y+=(float)m;
						m_pixelState[int(y+0.5)*width + x] = PCHOSEN;
						Sleep(nTime);
						this->Invalidate();
					}
				}
				else {
					for (x=start.x; x>=end.x; x--) {
						y-=m;
						m_pixelState[int(y-0.5)*width + x] = PCHOSEN;
						Sleep(nTime);
						this->Invalidate();
					}
				}
			}
			else {
				m=1/m;
				int y;
				float x =start.x;
				if (end.y > start.y) {
					for (y=start.y; y<=end.y; y++) {
						x+=(float)m;
						m_pixelState[y*width + int(x+0.5)] = PCHOSEN;
						Sleep(nTime);
						this->Invalidate();
					}
				}
				else {
					for (y=start.y; y>=end.y; y--) {
						x-=(float)m;
						m_pixelState[y*width + int(x-0.5)] = PCHOSEN;
						Sleep(nTime);
						this->Invalidate();
					}
				}
			}
		}
		break;
	case BRESENHAM:
		break;
	}
	Invalidate();
}


void CRasterizationIllustrationDlg::fillPixel(PIXEL pixel, COLOR color)
{
	float scale = m_config->getScale();
	glColor3f(color.red, color.green, color.blue);
	glBegin(GL_QUADS);
		glVertex2f(pixel.x*scale, pixel.y*scale);
		glVertex2f((pixel.x+1)*scale, pixel.y*scale);
		glVertex2f((pixel.x+1)*scale, (pixel.y+1)*scale);
		glVertex2f(pixel.x*scale, (pixel.y+1)*scale);
	glEnd();
}


void CRasterizationIllustrationDlg::drawPixel(void)
{
	int width = m_config->getWidth();
	int height = m_config->getHeight();
	int x,y;
	for (y = 0; y < height; y++)
		for (x = 0; x < width; x++)
			if (m_pixelState[y*width + x] == PCHOSEN)
				fillPixel(PIXEL(x,y), COLOR(0.0f,1.0f,0.0f));
}


DWORD WINAPI CRasterizationIllustrationDlg::ThreadProc(LPVOID lpParam)
{
	CRasterizationIllustrationDlg* pParent = (CRasterizationIllustrationDlg*) lpParam;

	pParent->Rasterize(PIXEL(0,0),PIXEL(100,300),DDA, true);

	TerminateProcess(pParent->hRunStep, 1);
	return 1;
}


void CRasterizationIllustrationDlg::runStep(void)
{
	if (hRunStep) {
		TerminateThread(hRunStep, 1);
	}
	hRunStep = CreateThread(NULL, 0, ThreadProc, this, 0, &dwRunStepId);
}


void CRasterizationIllustrationDlg::runAll(void)
{
	if (hRunStep) {
		TerminateThread(hRunStep,1);
	}
	this->Rasterize(PIXEL(0,0),PIXEL(100,300),DDA);
}


void CRasterizationIllustrationDlg::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	// TODO: Add your message handler code here
	CMenu menu;
	if (menu.LoadMenu(IDR_CONTEXT_RI))
	{
		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
		point.x, point.y,
		AfxGetMainWnd()); // use main window for cmds
	}
}


void CRasterizationIllustrationDlg::OnContextriRunstep()
{
	// TODO: Add your command handler code here
	this->runStep();
}


void CRasterizationIllustrationDlg::OnContextriRunall()
{
	// TODO: Add your command handler code here
	this->runAll();
}


void CRasterizationIllustrationDlg::Erase(void)
{
	int width = m_config->getWidth(),
		height = m_config->getHeight();
	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
			m_pixelState[y*width + x] = PNONE;
}


void CRasterizationIllustrationDlg::OnContextriErase()
{
	// TODO: Add your command handler code here
	if (hRunStep) {
		TerminateThread(hRunStep,1);
	}
	Erase();
	Invalidate();
}


void CRasterizationIllustrationDlg::setCamera(void)
{
	int width = m_config->getWidth(),
		height = m_config->getHeight();
	float scale = m_config->getScale();
	glTranslatef(-width*scale/2.0,-height*scale/2.0,0);
}


void CRasterizationIllustrationDlg::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	
	CDialogEx::OnMButtonDown(nFlags, point);
}
