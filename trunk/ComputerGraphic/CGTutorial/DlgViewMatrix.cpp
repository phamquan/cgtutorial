// DlgViewMatrix.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "DlgViewMatrix.h"


// CDlgViewMatrix dialog

IMPLEMENT_DYNAMIC(CDlgViewMatrix, CDlgMatrix)

CDlgViewMatrix::CDlgViewMatrix(CEnvironment *env, CPtrArray* in, CPtrArray* out, CWnd* pParent /*=NULL*/)
	: CDlgMatrix(pParent)
{
	this->environment = env;
	this->in = in;
	this->out = out;
}

CDlgViewMatrix::~CDlgViewMatrix()
{
}

void CDlgViewMatrix::DoDataExchange(CDataExchange* pDX)
{
	CDlgMatrix::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgViewMatrix, CDlgMatrix)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgViewMatrix message handlers


BOOL CDlgViewMatrix::OnInitDialog()
{
	CDlgMatrix::OnInitDialog();

	// TODO:  Add extra initialization here
	this->SetWindowTextW(CString("View Matrix"));
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgViewMatrix::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDlgMatrix::OnPaint() for painting messages
	int top = 0, left = 10;
	ShowPoint(&dc,CString("eye"),eye,top,left);
	ShowPoint(&dc,CString("center"),center,top,left+200);
	ShowPoint(&dc,CString("up"),up,top,left+400);
	top += 100;
	ShowPoint(&dc,CString("n = eye - center"),n,top,left);	
	ShowPoint(&dc,CString("u = up x n"),u,top,left+200);
	ShowPoint(&dc,CString("v = n x u"),v,top,left+400);
	top += 100;

	CString data[16] = {CString("u.x"), CString("v.x"), CString("n.x"), CString("0.000"),
					CString("u.y"), CString("v.y"), CString("n.y"), CString("0.000"),
					CString("u.z"), CString("v.z"), CString ("n.z"), CString("0.000"),
					CString("0.000"), CString("0.000"), CString("0.000"), CString("1.000")};

	Element* e = (Element*)matrix.GetAt(0);
	ShowMatrix(&dc,e->font,e->tail,e->data,top,left);
	
	e = (Element*)matrix.GetAt(1);
	ShowMatrixMatrix(&dc,e->font,data,e->data,top,left);

	e = (Element*)matrix.GetAt(2);
	ShowMatrix(&dc,e->font,e->tail,e->data,top,left);
	
	for(int i=0; i<out->GetSize(); i++)
	{
		char buff[128];
		sprintf_s(buff,"P%d'' = V*P%d'",i+1,i+1);
		ShowMatrixPoint(&dc,CString(buff),sum,(CPoint3D*)in->GetAt(i),(CPoint3D*)out->GetAt(i),top,left);
	}
}

void CDlgViewMatrix::Refresh()
{
	matrix.RemoveAll();

	float x1,y1,z1,x2,y2,z2,x3,y3,z3;
	environment->GetCamera()->GetData(x1,y1,z1,x2,y2,z2,x3,y3,z3);

	eye.setCoords(x1,y1,z1);
	center.setCoords(x2,y2,z2);
	up.setCoords(x3,y3,z3);
	n = eye - center;
	u = up.crossProduct(n);
	v = n.crossProduct(u);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(-eye.getX(),-eye.getY(),-eye.getZ());

	glGetFloatv(GL_MODELVIEW_MATRIX,sum);

	matrix.Add(new Element(CString("T"),CString("glTranslate(x=-eye.x, y=-eye.y, z=-eye.z)"),sum));

	sum[0] = u.getX(), sum[1] = v.getX(), sum[2] = n.getX(), sum[3] = 0;
	sum[4] = u.getY(), sum[5] = v.getY(), sum[6] = n.getY(), sum[7] = 0;
	sum[8] = u.getZ(), sum[9] = v.getZ(), sum[10] = n.getZ(), sum[11] = 0;
	sum[12] = 0; sum[13] = 0; sum[14] = 0; sum[15] = 1;

	matrix.Add(new Element(CString("M"),CString(""),sum));

	glLoadIdentity();
	gluLookAt(x1,y1,z1,x2,y2,z2,x3,y3,z3);
	glGetFloatv(GL_MODELVIEW_MATRIX,sum);

	matrix.Add(new Element(CString("V = M*T"), CString(), sum));

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	CalMatrixPoint();
	Invalidate();
}