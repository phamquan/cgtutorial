// DlgViewMatrix.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "DlgViewMatrix.h"


// CDlgViewMatrix dialog

IMPLEMENT_DYNAMIC(CDlgViewMatrix, CDlgMatrix)

CDlgViewMatrix::CDlgViewMatrix(CEnvironment *env, CWnd* pParent /*=NULL*/)
	: CDlgMatrix(pParent)
{
	environment = env;
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
void CDlgViewMatrix::Refresh()
{
	Clear();

	float x1,y1,z1,x2,y2,z2,x3,y3,z3;
	environment->GetCamera()->GetData(x1,y1,z1,x2,y2,z2,x3,y3,z3);

	eye.setCoords(x1,y1,z1);
	center.setCoords(x2,y2,z2);
	up.setCoords(x3,y3,z3,0);
	n = eye - center;
	u = up.crossProduct(n);
	v = n.crossProduct(u);

	n.normalize();
	u.normalize();
	v.normalize();

	float in1[16];
	in1[0] = 1;		in1[4] = 0;		in1[8] = 0;		in1[12] = -eye.getX();
	in1[1] = 0;		in1[5] = 1;		in1[9] = 0;		in1[13] = -eye.getY();
	in1[2] = 0;		in1[6] = 0;		in1[10] = 1;	in1[14] = -eye.getZ();
	in1[3] = 0;		in1[7] = 0;		in1[11] = 0;	in1[15] = 1;
	matrix.Add(new Element(CString("T"),CString("glTranslate(x=-eye.x, y=-eye.y, z=-eye.z)"),in1));

	float in2[16];
	in2[0] = u.getX();		in2[4] = u.getY();		in2[8] = u.getZ();		in2[12] = 0;
	in2[1] = v.getX();		in2[5] = v.getY();		in2[9] = v.getZ();		in2[13] = 0;
	in2[2] = n.getX();		in2[6] = n.getY();		in2[10] = n.getZ();		in2[14] = 0;
	in2[3] = 0;				in2[7] = 0;				in2[11] = 0;			in2[15] = 1;
	matrix.Add(new Element(CString("M"),CString(""),in2));

	MultMatrixMatrix(in2,in1,sum);
	matrix.Add(new Element(CString("V = M*T"), CString(), sum));

	Invalidate();
}

void CDlgViewMatrix::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDlgMatrix::OnPaint() for painting messages
	dc.SetBkMode( TRANSPARENT );
	CRect rect;
	GetClientRect(&rect);

	rect.top += 10;

	dc.DrawText(CString("CALCULATION"),-1,rect,DT_CENTER);

	int top = 30, left = 10;

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
}
