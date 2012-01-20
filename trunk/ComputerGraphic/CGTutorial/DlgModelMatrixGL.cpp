// DlgModelMatrix.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "DlgModelMatrixGL.h"


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
	if(object != NULL) {
		count[0]  = count[1] = count[2] = 1;
		total = "";
		for(int i=0; i<16; i++)
			sum[i] = 0;
		sum[0] = sum[5] = sum[10] = sum[15] = 1;
		matrix.RemoveAll();
		CalNode(object->parent);
	}
	Invalidate();
}

void CDlgModelMatrixGL::CalNode(COpenGLNode* node) {
	float m[16];
	int id = node->ID;
	char buff[128];

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	if(id == NODE_OBJECT) {
		total = total.Right(total.GetLength()-1);
		if(total == "")
			matrix.Add(new Element(CString("M"),CString(),sum));
		else
			matrix.Add(new Element(CString("M = ") + total,CString(),sum));
	} else {
		if(id != NODE_COLOR) {			
			if(id == NODE_TRANSLATE) {
				sprintf_s(buff,"T%d",count[0]++);
				node->DoOpenGL();
			} else if(id == NODE_SCALE) {
				sprintf_s(buff,"S%d",count[1]++);
				node->DoOpenGL();
			} else if(id == NODE_ROTATE) {
				sprintf_s(buff,"R%d",count[2]++);
				node->DoOpenGL();
			}
			total = CString("*") + buff + total;
			glGetFloatv(GL_MODELVIEW_MATRIX,m);
			glMultMatrixf(sum);
			glGetFloatv(GL_MODELVIEW_MATRIX,sum);
			matrix.Add(new Element(CString(buff),node->ToString(),m));
		}
		CalNode(node->parent);
	}
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void CDlgModelMatrixGL::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDlgMatrix::OnPaint() for painting messages
	CRect rect;
	GetClientRect(&rect);

	dc.MoveTo(rect.left,rect.top);
	dc.LineTo(rect.left,rect.bottom);

	rect.top += 10;

	dc.DrawText(CString("OPENGL"),-1,rect,DT_CENTER);

	int top = 30, left = 10;
		
	if(object == NULL) {
		dc.TextOutW(left,top,CString("Select geometric object to view data"));
	} else {
		for(int i=0; i<matrix.GetSize(); i++)
		{
			Element* e = (Element*)matrix.GetAt(i);
			ShowMatrix(&dc,e->font,e->tail,e->data,top,left);
		}
	}
}
