// DlgModelMatrix.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "DlgModelMatrix.h"

// CDlgModelMatrix dialog

IMPLEMENT_DYNAMIC(CDlgModelMatrix, CDlgMatrix)

CDlgModelMatrix::CDlgModelMatrix(CPtrArray* out, CWnd* pParent /*=NULL*/)
	: CDlgMatrix(pParent)
{
	object = NULL;
	in = new CPtrArray();
	this->out = out;
}

CDlgModelMatrix::~CDlgModelMatrix()
{
	delete in;
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
		for(int i=0; i<matrix.GetSize(); i++)
		{
			Element* e = (Element*)matrix.GetAt(i);
			ShowMatrix(&dc,e->font,e->tail,e->data,top,left);
		}
		for(int i=0; i<out->GetSize(); i++)
		{
			char buff[128];
			sprintf_s(buff,"P%d' = M*P%d",i+1,i+1);
			ShowMatrixPoint(&dc,CString(buff),sum,(CPoint3D*)in->GetAt(i),(CPoint3D*)out->GetAt(i),top,left);
		}
	}
}

void CDlgModelMatrix::Refresh(COpenGLNode* obj)
{
	object = obj;
	if(object != NULL) {
		count[0]  = count[1] = count[2] = 1;
		total = "";
		for(int i=0; i<16; i++)
			sum[i] = 0;
		sum[0] = sum[5] = sum[10] = sum[15] = 1;
		matrix.RemoveAll();
		CalNode(object->GetParent());

		in->RemoveAll();
		float x1,y1,z1,x2,y2,z2;
		if(object->GetID() == NODE_POINT) {
			((CPoint4D*)object)->GetData(x1,y1,z1);
			in->Add(new CPoint3D(CPoint3D(x1,y1,z1)));
		} else if(object->GetID() == NODE_LINE) {
			((CLine*)object)->GetData(x1,y1,z1,x2,y2,z2);
			in->Add(new CPoint3D(CPoint3D(x1,y1,z1)));
			in->Add(new CPoint3D(CPoint3D(x2,y2,z2)));
		}

		CalMatrixPoint();
	}
	Invalidate();
}

void CDlgModelMatrix::CalNode(COpenGLNode* node) {
	float m[16];
	int id = node->GetID();
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
		CalNode(node->GetParent());
	}
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}