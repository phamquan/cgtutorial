// DlgViewMatrix.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "DlgViewMatrix.h"


// CDlgViewMatrix dialog

IMPLEMENT_DYNAMIC(CDlgViewMatrix, CDlgMatrix)

CDlgViewMatrix::CDlgViewMatrix(CCamera *cam, COpenGLNode* node, CWnd* pParent /*=NULL*/)
	: CDlgMatrix(pParent)
{
	camera = cam;
	root = node;
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
	float x1,y1,z1,x2,y2,z2;
	ShowCamera(&dc,top,left);
	if(root != NULL)
	{
		if(root->GetID() == NODE_POINT) {
			CPoint4D* newpoint = ((CPoint4D*)root)->CalculateModel();
			newpoint->GetData(x1,y1,z1);
			ShowPointMatrix(&dc,CString("P1'"),CPoint3D(x1,y1,z1),top,left);
		} else if(root->GetID() == NODE_LINE) {
			CLine* newline = ((CLine*)root)->CalculateModel();
			newline->GetData(x1,y1,z1,x2,y2,z2);
			ShowPointMatrix(&dc,CString("P1'"),CPoint3D(x1,y1,z1),top,left);
			ShowPointMatrix(&dc,CString("P2'"),CPoint3D(x2,y2,z2),top,left);
		}
	}
	/*ShowNode(&dc,root->GetParent(),top,left);
	ShowMatrix(&dc,CString("M = ") + total,CString(),sum,top,left);*/
}

void CDlgViewMatrix::ShowPointMatrix(CDC* cdc, CString name, CPoint3D point, int &top, int left)
{
	top += 10;
	CString newname = name + "' = M*" + name + " =";
	cdc->TextOutW(left, top+30, newname);
	left += (int)cdc->GetTextExtent(newname).cx+10;

	CDlgMatrix::ShowMatrix(cdc,sum,top,left);
	CDlgMatrix::ShowPoint(cdc,point,top,left+205);
	cdc->TextOutW(left+250,top+30,CString("="));
	CPoint3D newpoint = MultMatrixPoint(sum,point);
	CDlgMatrix::ShowPoint(cdc,newpoint,top,left+270);

	top += 20*4 + 10;
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
	
	top += 10;
	cdc->TextOutW(left, top+30, CString("M ="));
	left += (int)cdc->GetTextExtent(CString("M =")).cx + 10;

	CString data[16] = {CString("u.x"), CString("v.x"), CString("n.x"), CString("0.000"),
					CString("u.y"), CString("v.y"), CString("n.y"), CString("0.000"),
					CString("u.z"), CString("v.z"), CString ("n.z"), CString("0.000"),
					CString("0.000"), CString("0.000"), CString("0.000"), CString("1.000")};

	CDlgMatrix::ShowMatrix(cdc,data,top,left);
	cdc->TextOutW(left+200,top+30,CString("="));

	sum[0] = u.getX(), sum[1] = v.getX(), sum[2] = n.getX(), sum[3] = 0;
	sum[4] = u.getY(), sum[5] = v.getY(), sum[6] = n.getY(), sum[7] = 0;
	sum[8] = u.getZ(), sum[9] = v.getZ(), sum[10] = n.getZ(), sum[11] = 0;
	sum[12] = 0; sum[13] = 0; sum[14] = 0; sum[15] = 1;

	CDlgMatrix::ShowMatrix(cdc,sum,top,left+220);
	top += 90;

	left -= (int)cdc->GetTextExtent(CString("M =")).cx + 10;
	glLoadIdentity();
	gluLookAt(x1,y1,z1,x2,y2,z2,x3,y3,z3);
	glGetFloatv(GL_MODELVIEW_MATRIX,sum);

	ShowMatrix(cdc,CString("V = M*T"), CString(), sum, top, left);

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void CDlgViewMatrix::ShowMatrix(CDC* cdc, CString name, CString rear, float m[16], int &top, int left)
{
	top += 10;
	name += " =";
	cdc->TextOutW(left, top+30, name);
	left += (int)cdc->GetTextExtent(name).cx+10;

	CDlgMatrix::ShowMatrix(cdc,m,top,left);

	cdc->TextOutW(left+250,top+30,rear);

	top += 20*4 + 10;
}

void CDlgViewMatrix::ShowPoint(CDC* cdc, CString name, CHomoPoint point, int top, int left)
{
	top += 10;
	name += " =";
	cdc->TextOutW(left, top+30, name);
	left += (int)cdc->GetTextExtent(name).cx+10;

	CDlgMatrix::ShowPoint(cdc,point,top,left);
}