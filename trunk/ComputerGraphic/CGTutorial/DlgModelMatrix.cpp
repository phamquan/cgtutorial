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
	int top=0;
	count[0]  = count[1] = count[2] = 1;
	total = "";
	for(int i=0; i<16; i++)
		sum[i] = 0;
	sum[0] = sum[5] = sum[10] = sum[15] = 1;
	ShowNode(&dc,root->GetParent(),top,10);
	ShowMatrix(&dc,CString("M = ") + total,CString(),sum,top,10);
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
		total = CString("I") + total;
		glGetFloatv(GL_MODELVIEW_MATRIX,m);
		ShowMatrix(cdc,CString("I"),CString(),m,top,left);
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
	char buff[1024];

	top += 10;
	name += " =";
	cdc->TextOutW(left, top+30, name);
	left += (int)cdc->GetTextExtent(name).cx+10;

	for(int i=0; i<4; i++) {
		for(int j=0; j<4; j++) {
			sprintf(buff,"%5.3f",m[i+j*4]);
			cdc->TextOutW(left+j*50,top+i*20,CString(buff));
		}
	}

	cdc->TextOutW(left+250,top+30,rear);

	top += 20*4 + 10;
}