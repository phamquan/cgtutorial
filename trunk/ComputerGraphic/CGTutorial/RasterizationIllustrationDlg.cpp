// RasterizationIllustrationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "RasterizationIllustrationDlg.h"
#include "afxdialogex.h"
#include <afxpriv.h>
#include "GL/glut.h"


// CRasterizationIllustrationDlg dialog

IMPLEMENT_DYNAMIC(CRasterizationIllustrationDlg, CDialogEx)

CRasterizationIllustrationDlg::CRasterizationIllustrationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRasterizationIllustrationDlg::IDD, pParent)
{

}

CRasterizationIllustrationDlg::~CRasterizationIllustrationDlg()
{
}

void CRasterizationIllustrationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRasterizationIllustrationDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_WM_MOUSEWHEEL()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_CONTEXTRI_DDA, &CRasterizationIllustrationDlg::OnContextriDda)
	ON_UPDATE_COMMAND_UI(ID_CONTEXTRI_DDA, &CRasterizationIllustrationDlg::OnUpdateContextriDda)
	ON_COMMAND(ID_CONTEXTRI_BRESENHAM, &CRasterizationIllustrationDlg::OnContextriBresenham)
	ON_UPDATE_COMMAND_UI(ID_CONTEXTRI_BRESENHAM, &CRasterizationIllustrationDlg::OnUpdateContextriBresenham)
	ON_COMMAND(ID_CONTEXTRI_ERASE, &CRasterizationIllustrationDlg::OnContextriErase)
	ON_COMMAND(ID_CONTEXTRI_MOREINFO, &CRasterizationIllustrationDlg::OnContextriMoreinfo)
	ON_COMMAND(ID_CONTEXTRI_RUNALL, &CRasterizationIllustrationDlg::OnContextriRunall)
	ON_COMMAND(ID_CONTEXTRI_RUNSTEP, &CRasterizationIllustrationDlg::OnContextriRunstep)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CRasterizationIllustrationDlg message handlers


BOOL CRasterizationIllustrationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_infoDlg->Create(IDD_RASTERIZATIONINFODLG, this);
	m_infoDlg->ShowWindow(SW_SHOW);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CRasterizationIllustrationDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialogEx::OnPaint() for paiting messages
	wglMakeCurrent( m_hDC, m_hRC );
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(targetX, targetY, 0);
	COLOR bg = m_config->getBackgroundColor();
	glClearColor(bg.red, bg.green, bg.blue, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT); 
	glColor3f(0.2f, 0.2f, 0.2f);
	setCamera();
	drawBoard();
	drawPixel();
	glFlush();
	SwapBuffers(dc.m_ps.hdc);
}

void CRasterizationIllustrationDlg::setupOpenGL() {
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

void CRasterizationIllustrationDlg::removeOpenGL() {
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
}


void CRasterizationIllustrationDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	removeOpenGL();
	delete m_config;
}

void CRasterizationIllustrationDlg::drawBoard() {
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
	m_isLeftMouseDown = m_isMidMouseDown = false;
	debugMode = false;
	m_infoDlg = new CRasterizationInfoDlg();
	m_config = new CRasterizationConfig(400, 300, 0.012, BRESENHAM, BLUE);
	int width = m_config->getWidth(),
		height = m_config->getHeight();
	if (width*height == 0) 
		m_pixelState = NULL;
	else {
		m_pixelState = new PIXELTYPE[width * height];
		m_pixelColor = new COLOR[width * height];
		Erase();
	}
	targetX = targetY = 0.0f;

	p.nEdge = 3;
	p.vertex = new PIXEL[p.nEdge];
	p.vertex[0].x = 0;
	p.vertex[0].y = 0;
	p.vertex[0].color.red = 1;
	p.vertex[0].color.green = 0;
	p.vertex[0].color.blue = 0;

	p.vertex[1].x = 10;
	p.vertex[1].y = 40;
	p.vertex[1].color.red = 0;
	p.vertex[1].color.green = 1;
	p.vertex[1].color.blue = 0;

	p.vertex[2].x = 90;
	p.vertex[2].y = 20;
	p.vertex[2].color.red = 1;
	p.vertex[2].color.green = 1;
	p.vertex[2].color.blue = 0;
}

BOOL CRasterizationIllustrationDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: Add your message handler code here and/or call default
	float delta = 0.001f;
	m_config->modifyScale(zDelta>0? delta:-delta);
	Invalidate();
	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}

void CRasterizationIllustrationDlg::Rasterize(PIXEL start, PIXEL end,RASTERIZEALG alg, int delay)
{
	int width = m_config->getWidth();

	//Thoi gian delay moi buoc

	m_pixelState[start.y*width + start.x] = m_pixelState[end.y*width + end.x] = PCHOSEN;
	Sleep(delay);
	int x0 = start.x, y0=start.y, x1=end.x, y1=end.y;
	COLOR c0 = start.color;
	COLOR c1 = end.color;

	bool steep = abs(y1 - y0) > abs(x1 - x0);
	if (steep) {
		swap(int, x0, y0);
		swap(int, x1, y1);
	}
	if (x0 > x1) {
		swap(int, x0, x1);
		swap(int, y0, y1);
		swap(COLOR, c0, c1);
	}

	COLOR delta = (c1 - c0)*(1.0f/float(x1-x0));
	COLOR iter = c0;

	switch(alg) {
	case DDA:
		{
			float ystep = (float)(y1 - y0)/(x1-x0);

			float y = y0;
			for (int x = x0; x <= x1; x++) {
				if (steep) {
					m_pixelState[x*width + int(y+0.5)] = PCHOSEN;
					m_pixelColor[x*width + int(y+0.5)] = iter;
					iter += delta;
					m_infoDlg->m_cx = y;
					m_infoDlg->m_cy = x;
				}
				else {
					m_pixelState[int(y+0.5)*width + x] = PCHOSEN;
					m_pixelColor[int(y+0.5)*width + x] = iter;
					iter += delta;
					m_infoDlg->m_cx = x;
					m_infoDlg->m_cy = y;
				}

				iter += delta;
				m_infoDlg->m_cr = iter.red;
				m_infoDlg->m_cg = iter.green;
				m_infoDlg->m_cb = iter.blue;
				m_infoDlg->Refresh();
				Sleep(delay);
				if (debugMode)
					SuspendThread(hRunStep);
				this->Invalidate();

				y += ystep;
			}
		}
		break;
	case BRESENHAM:
		{
			int deltax = x1 - x0;
			int deltay = abs(y1 - y0);
			int error = deltax / 2;
			int ystep;
			int y = y0;
			if (y0 < y1)  {
				ystep = 1;

			}
			else  {
				ystep = -1;
			}
			for (int x = x0; x <= x1;x++) {
				if (steep) {
					m_pixelState[x*width + y] = PCHOSEN;
					m_pixelColor[x*width + y] = iter;
					m_infoDlg->m_cx = y;
					m_infoDlg->m_cy = x;
				}
				else {
					m_pixelState[y*width + x] = PCHOSEN;
					m_pixelColor[y*width + x] = iter;
					m_infoDlg->m_cx = x;
					m_infoDlg->m_cy = y;
				}
				iter += delta;
				m_infoDlg->m_cr = iter.red;
				m_infoDlg->m_cg = iter.green;
				m_infoDlg->m_cb = iter.blue;
				m_infoDlg->Refresh();
				Sleep(delay);
				if (debugMode)
					SuspendThread(hRunStep);
				this->Invalidate();
				error = error - deltay;
				if (error < 0) {
					y = y + ystep;
					error = error + deltax;
				}
			}
		}
		break;
	}
	Invalidate();
}

void CRasterizationIllustrationDlg::Rasterize(POLYGONPIXEL polygon, RASTERIZEALG alg, int delay) {
	int n = polygon.nEdge;
	for (int i=0; i<n; i++)
		Rasterize(polygon.vertex[i], polygon.vertex[(i+1)%n], alg, delay);
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

void CRasterizationIllustrationDlg::drawPixel()
{
	int width = m_config->getWidth();
	int height = m_config->getHeight();
	int x,y;
	for (y = 0; y < height; y++)
		for (x = 0; x < width; x++)
			switch (m_pixelState[y*width + x]) {
			case PCHOSEN:
				fillPixel(PIXEL(x,y), m_pixelColor[y*width+x]);
				break;
			case PNONE:
				//fillPixel(PIXEL(x,y), bg);
				break;
			default:
				break;
		}
}

DWORD WINAPI CRasterizationIllustrationDlg::ThreadProc(LPVOID lpParam)
{
	CRasterizationIllustrationDlg* pParent = (CRasterizationIllustrationDlg*) lpParam;

	pParent->Rasterize(pParent->p, pParent->getConfig()->getAlgorithmRasterization(), 50);

	TerminateProcess(pParent->hRunStep, 1);
	pParent->hRunStep = NULL;
	return 1;
}

void CRasterizationIllustrationDlg::runStep()
{
	this->Erase();
	if (hRunStep && !debugMode) {
		TerminateThread(hRunStep, 1);
	}
	hRunStep = CreateThread(NULL, 0, ThreadProc, this, 0, &dwRunStepId);
}

void CRasterizationIllustrationDlg::runAll()
{
	if (hRunStep) {
		TerminateThread(hRunStep,1);
	}
	this->Rasterize(this->p,m_config->getAlgorithmRasterization());
}

void CRasterizationIllustrationDlg::Erase()
{
	int width = m_config->getWidth(),
		height = m_config->getHeight();
	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
			m_pixelState[y*width + x] = PNONE;
	Invalidate();
	if (hRunStep) {
		TerminateThread(hRunStep,1);
	}
}

void CRasterizationIllustrationDlg::setCamera()
{
	int width = m_config->getWidth(),
		height = m_config->getHeight();
	float scale = m_config->getScale();
	glTranslatef(-width*scale/2.0,-height*scale/2.0,0);
}

void CRasterizationIllustrationDlg::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	// TODO: Add your message handler code here
	CMenu menu;
	if (menu.LoadMenu(IDR_CONTEXT_RI))
	{
		CCmdUI cmdUI;
		for (UINT n = 0; n < menu.GetMenuItemCount(); ++n)
		{
			CMenu* pSubMenu = menu.GetSubMenu(n);
			cmdUI.m_nIndexMax = pSubMenu->GetMenuItemCount();
			for (UINT i = 0; i < cmdUI.m_nIndexMax;++i)
			{
				cmdUI.m_nIndex = i;
				cmdUI.m_nID = pSubMenu->GetMenuItemID(i);
				cmdUI.m_pMenu = pSubMenu;
				cmdUI.DoUpdate(this, FALSE);
			}
		}

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this); // use main window for cmds
	}
}

BOOL CRasterizationIllustrationDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message==WM_KEYDOWN) {
		switch(pMsg->wParam) {
		case VK_F4:
			if (hRunStep) {
				debugMode = false;
				TerminateThread(hRunStep, 1);
				hRunStep = NULL;
			}
			this->runAll();
			break;

		case VK_F5:
			if (hRunStep) {
				debugMode = false;
				ResumeThread(hRunStep);
			}
			else {
				this->runStep();
			}
			break;

		case VK_F6:
			debugMode = true;
			if (hRunStep && debugMode)
				ResumeThread(hRunStep);
			else {
				this->runStep();
			}
			break;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CRasterizationIllustrationDlg::OnContextriDda()
{
	// TODO: Add your command handler code here
	m_config->setAlgorithmRasterization(DDA);
}


void CRasterizationIllustrationDlg::OnUpdateContextriDda(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetRadio(m_config->getAlgorithmRasterization() == DDA);
}


void CRasterizationIllustrationDlg::OnContextriBresenham()
{
	// TODO: Add your command handler code here
	m_config->setAlgorithmRasterization(BRESENHAM);
}


void CRasterizationIllustrationDlg::OnUpdateContextriBresenham(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetRadio(m_config->getAlgorithmRasterization() == BRESENHAM);
}


void CRasterizationIllustrationDlg::OnContextriErase()
{
	// TODO: Add your command handler code here
		int width = m_config->getWidth(),
		height = m_config->getHeight();
	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
			m_pixelState[y*width + x] = PNONE;
	Invalidate();
	if (hRunStep) {
		TerminateThread(hRunStep,1);
	}
}


void CRasterizationIllustrationDlg::OnContextriMoreinfo()
{
	// TODO: Add your command handler code here
	m_infoDlg->ShowWindow(SW_SHOW);
}


void CRasterizationIllustrationDlg::OnContextriRunall()
{
	// TODO: Add your command handler code here
	this->runAll();
}


void CRasterizationIllustrationDlg::OnContextriRunstep()
{
	// TODO: Add your command handler code here
	this->runStep();
}


void CRasterizationIllustrationDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_isLeftMouseDown = true;
	CRect rect;
	GetClientRect(rect);
	//Change from window coordinate system to real coordinate system
	float x = (float)2 * m_width * point.x/rect.Width() - m_width;
	float y = 2 * m_height * (rect.Height() - point.y)/ (float)rect.Height() - m_height;
	startX = x;
	startY = y;
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CRasterizationIllustrationDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_isLeftMouseDown = false;
	CDialogEx::OnLButtonUp(nFlags, point);
}


void CRasterizationIllustrationDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_isLeftMouseDown) {
		CRect rect;
		GetClientRect(rect);
		//Change from window coordinate system to real coordinate system
		float x = (float)2 * m_width * point.x/rect.Width() - m_width;
		float y = 2 * m_height * (rect.Height() - point.y)/ (float)rect.Height() - m_height;
		targetX = x - startX + targetX;
		targetY = y - startY + targetY;
		startX = x;
		startY = y;
		Invalidate();
	}
	CDialogEx::OnMouseMove(nFlags, point);
}
