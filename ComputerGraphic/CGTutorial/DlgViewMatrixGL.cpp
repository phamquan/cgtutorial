// DlgViewMatrix.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "DlgViewMatrixGL.h"


// CDlgViewMatrixGL dialog

IMPLEMENT_DYNAMIC(CDlgViewMatrixGL, CDlgMatrix)

CDlgViewMatrixGL::CDlgViewMatrixGL(CEnvironment *env, CWnd* pParent /*=NULL*/)
	: CDlgMatrix(pParent)
{
	environment = env;
}

CDlgViewMatrixGL::~CDlgViewMatrixGL()
{
}

void CDlgViewMatrixGL::DoDataExchange(CDataExchange* pDX)
{
	CDlgMatrix::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgViewMatrixGL, CDlgMatrix)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgViewMatrixGL message handlers
void CDlgViewMatrixGL::Refresh()
{
	Invalidate();
}

void CDlgViewMatrixGL::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDlgMatrix::OnPaint() for painting messages
	dc.SetBkMode( TRANSPARENT );
	CRect rect;
	GetClientRect(&rect);

	dc.MoveTo(rect.left,rect.top);
	dc.LineTo(rect.left,rect.bottom);

	rect.top += 10;

	dc.DrawText(CString("OPENGL"),-1,rect,DT_CENTER);

	char buff[128];
	int top = 20, left = 10;
	float x1,y1,z1,x2,y2,z2,x3,y3,z3;
	environment->GetCamera()->GetData(x1,y1,z1,x2,y2,z2,x3,y3,z3);
	
	dc.TextOutW(left,top+=20,CString("glMatrixMode(GL_MODELVIEW);"));
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();

	dc.TextOutW(left,top+=20,CString("glLoadIdentity();"));
	glLoadIdentity();

	sprintf_s(buff,"gluLookAt(%5.2f,%5.2f,%5.2f,%5.2f,%5.2f,%5.2f,%5.2f,%5.2f,%5.2f)",x1,y1,z1,x2,y2,z2,x3,y3,z3);
	dc.TextOutW(left,top+=20,CString(buff));
	gluLookAt(x1,y1,z1,x2,y2,z2,x3,y3,z3);

	dc.TextOutW(left,top+=20,CString("glGetFloatv(GL_MODELVIEW_MATRIX,V);"));
	glGetFloatv(GL_MODELVIEW_MATRIX,sum);

	ShowMatrix(&dc,CString("V"),CString(),sum,top+=30,left);
	glPopMatrix();
}
