// DlgModelMatrix.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "DlgModelMatrix.h"
#include "afxdialogex.h"

// CDlgModelMatrix dialog

IMPLEMENT_DYNAMIC(CDlgModelMatrix, CDialogEx)

CDlgModelMatrix::CDlgModelMatrix(COpenGLNode* node, CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgModelMatrix::IDD, pParent)
{
	root = node;
}

CDlgModelMatrix::~CDlgModelMatrix()
{
}

void CDlgModelMatrix::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgModelMatrix, CDialogEx)
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
		ShowPoint(&dc,CString("P"),CPoint3D(x1,y1,z1),top,left);
		break;
	case NODE_LINE:
		((CLine*)root)->GetData(x1,y1,z1,x2,y2,z2);
		ShowPoint(&dc,CString("P1"),CPoint3D(x1,y1,z1),top,left);
		ShowPoint(&dc,CString("P2"),CPoint3D(x2,y2,z2),top,left);
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
				((CTranslate*)node)->GetData(x1,y1,z1,w1);
				glTranslatef(x1,y1,z1);
			} else if(id == NODE_SCALE) {
				sprintf(buff,"S%d",count[1]++);
				((CScale*)node)->GetData(x1,y1,z1,w1);
				glScalef(x1,y1,z1);
			} else if(id == NODE_ROTATE) {
				sprintf(buff,"R%d",count[2]++);
				((CRotate*)node)->GetData(x1,y1,z1,w1);
				glRotatef(w1,x1,y1,z1);
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

void CDlgModelMatrix::ShowMatrix(CDC* cdc, CString name, CString rear, float m[16], int &top, int left)
{
	top += 10;
	name += " =";
	cdc->TextOutW(left, top+30, name);
	left += (int)cdc->GetTextExtent(name).cx+10;

	ShowMatrix(cdc,m,top,left);

	cdc->TextOutW(left+250,top+30,rear);

	top += 20*4 + 10;
}

void CDlgModelMatrix::ShowMatrix(CDC* cdc, float m[16], int top, int left)
{
	char buff[128];
	cdc->MoveTo(left+5,top-5);
	cdc->LineTo(left-5,top-5);
	cdc->LineTo(left-5,top+80);
	cdc->LineTo(left+5,top+80);
	for(int i=0; i<4; i++) {
		for(int j=0; j<4; j++) {
			sprintf(buff,"%5.3f",m[i+j*4]);
			cdc->TextOutW(left+j*50,top+i*20,CString(buff));
		}
	}
	left += 185;
	cdc->MoveTo(left-5,top-5);
	cdc->LineTo(left+5,top-5);
	cdc->LineTo(left+5,top+80);
	cdc->LineTo(left-5,top+80);
}

void CDlgModelMatrix::ShowPoint(CDC* cdc, CString name, CPoint3D point, int &top, int left)
{
	top += 10;
	CString newname = name + "' = M*" + name + " =";
	cdc->TextOutW(left, top+30, newname);
	left += (int)cdc->GetTextExtent(newname).cx+10;

	ShowMatrix(cdc,sum,top,left);
	ShowPoint(cdc,point,top,left+205);
	cdc->TextOutW(left+250,top+30,CString("="));
	CPoint3D newpoint = MultMatrixPoint(sum,point);
	ShowPoint(cdc,newpoint,top,left+270);

	top += 20*4 + 10;
}

void CDlgModelMatrix::ShowPoint(CDC* cdc, CPoint3D point, int top, int left)
{
	char buff[128];
	cdc->MoveTo(left+5,top-5);
	cdc->LineTo(left-5,top-5);
	cdc->LineTo(left-5,top+80);
	cdc->LineTo(left+5,top+80);

	sprintf(buff,"%5.3f",point.getX());
	cdc->TextOutW(left,top,CString(buff));
	sprintf(buff,"%5.3f",point.getY());
	cdc->TextOutW(left,top+20,CString(buff));
	sprintf(buff,"%5.3f",point.getZ());
	cdc->TextOutW(left,top+40,CString(buff));
	sprintf(buff,"%5.3f",point.getW());
	cdc->TextOutW(left,top+60,CString(buff));

	left += 35;
	cdc->MoveTo(left-5,top-5);
	cdc->LineTo(left+5,top-5);
	cdc->LineTo(left+5,top+80);
	cdc->LineTo(left-5,top+80);
}