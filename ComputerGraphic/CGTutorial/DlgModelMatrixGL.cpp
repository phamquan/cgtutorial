// DlgModelMatrix.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "DlgModelMatrixGL.h"
#include "Translate.h"
#include "Scale.h"
#include "Rotate.h"

// CDlgModelMatrixGL dialog

IMPLEMENT_DYNAMIC(CDlgModelMatrixGL, CDlgMatrix)

CDlgModelMatrixGL::CDlgModelMatrixGL(CWnd* pParent /*=NULL*/)
	: CDlgMatrix(pParent)
{
}

CDlgModelMatrixGL::~CDlgModelMatrixGL()
{
}

void CDlgModelMatrixGL::DoDataExchange(CDataExchange* pDX)
{
	CDlgMatrix::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgModelMatrixGL, CDlgMatrix)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgModelMatrixGL message handlers

void CDlgModelMatrixGL::Refresh(COpenGLNode* obj)
{
	object = obj;
	Invalidate();
}

void CDlgModelMatrixGL::ShowNode(COpenGLNode* node, int &top, CDC *cdc)
{
	int id = node->ID;
	float x,y,z,w;
	if(id == NODE_OBJECT) {
		cdc->TextOutW(10,top+=20,CString("glMatrixMode(GL_MODELVIEW);"));
		cdc->TextOutW(10,top+=20,CString("glLoadIdentity();"));
	} else {
		ShowNode(node->parent,top,cdc);
		if(id != NODE_COLOR) {			
			if(id == NODE_TRANSLATE) {
				((CTranslate*)node)->GetData(x,y,z);
				glTranslatef(x,y,z);
			} else if(id == NODE_SCALE) {
				((CScale*)node)->GetData(x,y,z);
				glScalef(x,y,z);
			} else if(id == NODE_ROTATE) {
				((CRotate*)node)->GetData(x,y,z,w);
				glRotatef(w,x,y,z);
			}
			cdc->TextOutW(10,top+=20,((CTransformation*)node)->GLCode());
		}
	}
}

void CDlgModelMatrixGL::OnPaint()
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

	if(object == NULL) {
		dc.TextOutW(10,30,CString("Select geometric object to view data"));
	} else {
		int top = 20;

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		ShowNode(object->parent,top,&dc);

		dc.TextOutW(10,top+=20,CString("glGetFloatv(GL_MODELVIEW_MATRIX,M);"));
		glGetFloatv(GL_MODELVIEW_MATRIX,sum);

		ShowMatrix(&dc,CString("M"),CString(),sum,top+=30,10);
		glPopMatrix();
	}
}
