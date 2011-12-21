// DlgViewMatrix.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "DlgViewMatrix.h"


// CDlgViewMatrix dialog

IMPLEMENT_DYNAMIC(CDlgViewMatrix, CDlgMatrix)

CDlgViewMatrix::CDlgViewMatrix(CCamera *cam, CWnd* pParent /*=NULL*/)
	: CDlgMatrix(pParent)
{
	camera = cam;
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
	ShowCamera(&dc,top,left);
	ShowMatrixPoint(&dc,CString("V"),CString("'"),top,left);
}

void CDlgViewMatrix::ShowCamera(CDC* cdc, int &top, int left) {
	char buff[128];
	
	float x1,y1,z1,x2,y2,z2,x3,y3,z3;
	camera->GetData(x1,y1,z1,x2,y2,z2,x3,y3,z3);

	CPoint3D eye(x1,y1,z1);
	CPoint3D center(x2,y2,z2);
	CVector3D up(x3,y3,z3);
	CVector3D n = eye - center;
	CVector3D u = up.crossProduct(n);
	CVector3D v = n.crossProduct(u);

	ShowPoint(cdc,CString("eye"),eye,top,left);
	ShowPoint(cdc,CString("center"),center,top,left+200);
	ShowPoint(cdc,CString("up"),up,top,left+400);
	top += 100;
	ShowPoint(cdc,CString("n = eye - center"),n,top,left);	
	ShowPoint(cdc,CString("u = up x n"),u,top,left+200);
	ShowPoint(cdc,CString("v = n x u"),v,top,left+400);
	top += 100;

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(-eye.getX(),-eye.getY(),-eye.getZ());

	glGetFloatv(GL_MODELVIEW_MATRIX,sum);

	ShowMatrix(cdc,CString("T"),CString("glTranslate(x=-eye.x, y=-eye.y, z=-eye.z)"),sum,top,left);
	
	CString data[16] = {CString("u.x"), CString("v.x"), CString("n.x"), CString("0.000"),
					CString("u.y"), CString("v.y"), CString("n.y"), CString("0.000"),
					CString("u.z"), CString("v.z"), CString ("n.z"), CString("0.000"),
					CString("0.000"), CString("0.000"), CString("0.000"), CString("1.000")};

	sum[0] = u.getX(), sum[1] = v.getX(), sum[2] = n.getX(), sum[3] = 0;
	sum[4] = u.getY(), sum[5] = v.getY(), sum[6] = n.getY(), sum[7] = 0;
	sum[8] = u.getZ(), sum[9] = v.getZ(), sum[10] = n.getZ(), sum[11] = 0;
	sum[12] = 0; sum[13] = 0; sum[14] = 0; sum[15] = 1;

	ShowMatrixMatrix(cdc,CString("M"),data,sum,top,left);

	glLoadIdentity();
	gluLookAt(x1,y1,z1,x2,y2,z2,x3,y3,z3);
	glGetFloatv(GL_MODELVIEW_MATRIX,sum);

	ShowMatrix(cdc,CString("V = M*T"), CString(), sum, top, left);

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}