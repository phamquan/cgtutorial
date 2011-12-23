// DlgModelMatrix.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "DlgModelMatrix.h"

// CDlgModelMatrix dialog

IMPLEMENT_DYNAMIC(CDlgModelMatrix, CDlgMatrix)

CDlgModelMatrix::CDlgModelMatrix(CWnd* pParent /*=NULL*/)
	: CDlgMatrix(pParent)
{
	object = NULL;
}

CDlgModelMatrix::~CDlgModelMatrix()
{
}

void CDlgModelMatrix::DoDataExchange(CDataExchange* pDX)
{
	CDlgMatrix::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgModelMatrix, CDlgMatrix)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgModelMatrix message handlers
BOOL CDlgModelMatrix::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	this->SetWindowTextW(CString("Model Matrix"));
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgModelMatrix::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialogEx::OnPaint() for painting messages
	int top = 0, left = 10;
		
	if(object == NULL) {
		dc.TextOutW(left,top,CString("Select geometric object to view data"));
	} else {
		count[0]  = count[1] = count[2] = 1;
		total = "";
		for(int i=0; i<16; i++)
			sum[i] = 0;
		sum[0] = sum[5] = sum[10] = sum[15] = 1;
		
		ShowNode(&dc,object->GetParent(),top,left);

		if(total == "")
			ShowMatrix(&dc,CString("M"),CString(),sum,top,left);
		else
			ShowMatrix(&dc,CString("M = ") + total,CString(),sum,top,left);

		ShowMatrixPoint(&dc,CString("M"),CString(),top,left);
	}
}

void CDlgModelMatrix::SetData(COpenGLNode* in, CPtrArray* out)
{
	object = in;
	this->out = out;
	Invalidate();
}

void CDlgModelMatrix::ShowNode(CDC* cdc, COpenGLNode* node, int &top, int left) {
	float m[16];
	int id = node->GetID();
	char buff[128];

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	if(id == NODE_OBJECT) {
		total = total.Right(total.GetLength()-1);
		glGetFloatv(GL_MODELVIEW_MATRIX,m);
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
			ShowMatrix(cdc,CString(buff),node->ToString(),m,top,left);
		}
		ShowNode(cdc,node->GetParent(),top,left);
	}
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void CDlgModelMatrix::ShowMatrixPoint(CDC* cdc, CString matrix, CString point, int &top, int left)
{
	out->RemoveAll();
	float x1,y1,z1,x2,y2,z2;
	if(object->GetID() == NODE_POINT) {
		((CPoint4D*)object)->GetData(x1,y1,z1);
		out->Add(CDlgMatrix::ShowMatrixPoint(cdc,matrix,CString("P1")+point,sum,CPoint3D(x1,y1,z1),top,left));
	} else if(object->GetID() == NODE_LINE) {
		((CLine*)object)->GetData(x1,y1,z1,x2,y2,z2);
		out->Add(CDlgMatrix::ShowMatrixPoint(cdc,matrix,CString("P1")+point,sum,CPoint3D(x1,y1,z1),top,left));
		out->Add(CDlgMatrix::ShowMatrixPoint(cdc,matrix,CString("P2")+point,sum,CPoint3D(x2,y2,z2),top,left));
	}
}