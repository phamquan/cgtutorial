// DlgProjectionMatrix.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "DlgProjectionMatrixGL.h"


// CDlgProjectionMatrixGL dialog

IMPLEMENT_DYNAMIC(CDlgProjectionMatrixGL, CDlgMatrix)

CDlgProjectionMatrixGL::CDlgProjectionMatrixGL(CEnvironment *env, CWnd* pParent /*=NULL*/)
	: CDlgMatrix(pParent)
{
	environment = env;
}

CDlgProjectionMatrixGL::~CDlgProjectionMatrixGL()
{
}

void CDlgProjectionMatrixGL::DoDataExchange(CDataExchange* pDX)
{
	CDlgMatrix::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgProjectionMatrixGL, CDlgMatrix)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgProjectionMatrixGL message handlers

void CDlgProjectionMatrixGL::Refresh()
{
	Invalidate();
}

void CDlgProjectionMatrixGL::OnPaint()
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
	float mleft,mright,mbottom,mtop,mnear,mfar;
	environment->GetProjection()->GetData(mleft,mright,mbottom,mtop,mnear,mfar,type);

	dc.TextOut(left,top+=20,CString("glMatrixMode(GL_PROJECTION);"));
	glMatrixMode(GL_PROJECTION);

	glPushMatrix();

	dc.TextOut(left,top+=20,CString("glLoadIdentity();"));
	glLoadIdentity();

	if(type == ORTHO) {
		sprintf_s(buff,"glOrtho(%5.2f,%5.2f,%5.2f,%5.2f,%5.2f,%5.2f)",mleft,mright,mbottom,mtop,mnear,mfar);
		dc.TextOut(left,top+=20,CString(buff));
		glOrtho(mleft,mright,mbottom,mtop,mnear,mfar);
	} else {
		sprintf_s(buff,"glFrustum(%5.2f,%5.2f,%5.2f,%5.2f,%5.2f,%5.2f)",mleft,mright,mbottom,mtop,mnear,mfar);
		dc.TextOut(left,top+=20,CString(buff));
		glFrustum(mleft,mright,mbottom,mtop,mnear,mfar);
	}
	dc.TextOut(left,top+=20,CString("glGetFloatv(GL_PROJECTION_MATRIX,P);"));
	glGetFloatv(GL_PROJECTION_MATRIX,sum);

	ShowMatrix(&dc,CString("P"),CString(),sum,top+=30,left);
	glPopMatrix();
}
