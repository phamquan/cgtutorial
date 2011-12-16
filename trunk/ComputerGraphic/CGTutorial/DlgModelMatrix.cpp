// DlgModelMatrix.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "DlgModelMatrix.h"

// CDlgModelMatrix dialog

IMPLEMENT_DYNAMIC(CDlgModelMatrix, CDlgMatrix)

CDlgModelMatrix::CDlgModelMatrix(COpenGLNode* node, CWnd* pParent /*=NULL*/)
	: CDlgMatrix(pParent)
{
	root = node;
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
	count[0]  = count[1] = count[2] = 1;
	total = "";
	for(int i=0; i<16; i++)
		sum[i] = 0;
	sum[0] = sum[5] = sum[10] = sum[15] = 1;

	ShowNode(&dc,root->GetParent(),top,left);

	if(total == "")
		ShowMatrix(&dc,CString("M"),CString(),sum,top,left);
	else
		ShowMatrix(&dc,CString("M = ") + total,CString(),sum,top,left);

	float x1,y1,z1,x2,y2,z2;
	switch(root->GetID()) {
	case NODE_POINT:
		((CPoint4D*)root)->GetData(x1,y1,z1);
		ShowMatrixPoint(&dc,CString("M"),CString("P"),sum,CPoint3D(x1,y1,z1),top,left);
		break;
	case NODE_LINE:
		((CLine*)root)->GetData(x1,y1,z1,x2,y2,z2);
		ShowMatrixPoint(&dc,CString("M"),CString("P1"),sum,CPoint3D(x1,y1,z1),top,left);
		ShowMatrixPoint(&dc,CString("M"),CString("P2"),sum,CPoint3D(x2,y2,z2),top,left);
		break;
	}
}

void CDlgModelMatrix::ShowNode(CDC* cdc, COpenGLNode* node, int &top, int left) {
	float m[16];
	int id = node->GetID();
	char buff[128];

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	float x1,y1,z1,w1;
	if(id == NODE_OBJECT) {
		total = total.Right(total.GetLength()-1);
		glGetFloatv(GL_MODELVIEW_MATRIX,m);
	} else {
		if(id != NODE_COLOR) {			
			if(id == NODE_TRANSLATE) {
				sprintf(buff,"T%d",count[0]++);
				node->DoOpenGL();
				/*((CTranslate*)node)->GetData(x1,y1,z1,w1);
				glTranslatef(x1,y1,z1);*/
			} else if(id == NODE_SCALE) {
				sprintf(buff,"S%d",count[1]++);
				node->DoOpenGL();
				/*((CScale*)node)->GetData(x1,y1,z1,w1);
				glScalef(x1,y1,z1);*/
			} else if(id == NODE_ROTATE) {
				sprintf(buff,"R%d",count[2]++);
				node->DoOpenGL();
				/*((CRotate*)node)->GetData(x1,y1,z1,w1);
				glRotatef(w1,x1,y1,z1);*/
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