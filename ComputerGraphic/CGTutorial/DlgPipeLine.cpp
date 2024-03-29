// DlgPipeLine.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "MainFrm.h"
#include "DlgPipeLine.h"
#include "Point4D.h"
#include "Line.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Circle.h"
#include "Ellipse.h"
#include "Cube.h"
#include "Tetrahedron.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Ring.h" 

// CDlgPipeLine dialog

IMPLEMENT_DYNAMIC(CDlgPipeLine, CDlgMatrix)

CDlgPipeLine::CDlgPipeLine(CEnvironment *env, CWnd* pParent /*=NULL*/)
	: CDlgMatrix(pParent)
{
	environment = env;
	modelTip = new CPipeLineTip();
	viewTip = new CPipeLineTip();
	projectionTip = new CPipeLineTip();
	viewportTip = new CPipeLineTip();
}

CDlgPipeLine::~CDlgPipeLine()
{
	delete modelTip;
	delete viewTip;
	delete projectionTip;
	delete viewportTip;
}

void CDlgPipeLine::DoDataExchange(CDataExchange* pDX)
{
	CDlgMatrix::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgPipeLine, CDlgMatrix)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_MODEL, &CDlgPipeLine::OnClickedModel)
	ON_BN_CLICKED(IDC_VIEW, &CDlgPipeLine::OnClickedView)
	ON_BN_CLICKED(IDC_PROJECTION, &CDlgPipeLine::OnClickedProjection)
	ON_BN_CLICKED(IDC_VIEWPORT, &CDlgPipeLine::OnClickedViewport)
END_MESSAGE_MAP()


// CDlgPipeLine message handlers
void CDlgPipeLine::Refresh(COpenGLNode *obj)
{
	object = obj;
	float x1,y1,z1,x2,y2,z2,x3,y3,z3,x4,y4,z4;
	int id;
	if(object != NULL)
	{
		Clear();
		id = object->ID;
		if(id == NODE_POINT)
		{
			((CPoint4D*)object)->GetData(x1,y1,z1);
			matrix.Add(new CPoint3D(x1,y1,z1));
		}
		else if(id == NODE_LINE)
		{
			((CLine*)object)->GetData(x1,y1,z1,x2,y2,z2);
			matrix.Add(new CPoint3D(x1,y1,z1));
			matrix.Add(new CPoint3D(x2,y2,z2));
		}
		else if(id == NODE_RECTANGLE)
		{
			((CRectangle*)object)->GetData(x1,y1,x2,y2);
			matrix.Add(new CPoint3D(x1,y1,0));
			matrix.Add(new CPoint3D(x2,y1,0));
			matrix.Add(new CPoint3D(x2,y2,0));
			matrix.Add(new CPoint3D(x1,y2,0));
		}
		else if(id == NODE_TRIANGLE)
		{
			((CTriangle*)object)->GetData(x1,y1,z1,x2,y2,z2,x3,y3,z3);
			matrix.Add(new CPoint3D(x1,y1,z1));
			matrix.Add(new CPoint3D(x2,y2,z2));
			matrix.Add(new CPoint3D(x3,y3,z3));
		}
		else if(id == NODE_CIRCLE)
		{
			((CCircle*)object)->GetData(x1,y1,z1,x2);
			matrix.Add(new CPoint3D(x1,y1,z1));
		}
		else if(id == NODE_ELLIPSE)
		{
			((CEllipse*)object)->GetData(x1,y1,z1,x2,y2);
			matrix.Add(new CPoint3D(x1,y1,z1));
		}
		else if(id == NODE_CUBE)
		{
			((CCube*)object)->GetData(x1,y1,z1,x2,y2,z2);
			matrix.Add(new CPoint3D(x1,y1,z1));
			matrix.Add(new CPoint3D(x2,y2,z2));
		}
		else if(id == NODE_TETRAHEDRON)
		{
			((CTetrahedron*)object)->GetData(x1,y1,z1,x2,y2,z2,x3,y3,z3,x4,y4,z4);
			matrix.Add(new CPoint3D(x1,y1,z1));
			matrix.Add(new CPoint3D(x2,y2,z2));
			matrix.Add(new CPoint3D(x3,y3,z3));
			matrix.Add(new CPoint3D(x4,y4,z4));
		}
		else if(id == NODE_SPHERE)
		{
			((CSphere*)object)->GetData(x1,y1,z1,x2);
			matrix.Add(new CPoint3D(x1,y1,z1));
		}
		else if(id == NODE_CYLINDER)
		{
			((CCylinder*)object)->GetData(x1,y1,z1,x2,y2);
			matrix.Add(new CPoint3D(x1,y1,z1));
		}
		else if(id == NODE_RING)
		{
			((CRing*)object)->GetData(x1,y1,z1,x2,y2);
			matrix.Add(new CPoint3D(x1,y1,z1));
		}

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		CalNode(object->parent);
		glGetFloatv(GL_MODELVIEW_MATRIX,sum);
		glPopMatrix();
		
		modelTip->Refresh(sum);
	}
	else
	{
		modelTip->ReSet();
	}

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	environment->GetCamera()->GetData(x1,y1,z1,x2,y2,z2,x3,y3,z3);
	gluLookAt(x1,y1,z1,x2,y2,z2,x3,y3,z3);
	glGetFloatv(GL_MODELVIEW_MATRIX,view);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	environment->GetProjection()->GetData(x1,y1,z1,x2,y2,z2,id);
	if(id == ORTHO)
		glOrtho(x1,y1,z1,x2,y2,z2);
	else
		glFrustum(x1,y1,z1,x2,y2,z2);
	glGetFloatv(GL_PROJECTION_MATRIX,projection);
	glPopMatrix();

	environment->GetViewPort()->GetData(x,y,w,h,type);
	if(type == VIEWPORT_DEFAULT) {
		CSize s = ((CMainFrame*)GetParent())->GetViewPort();
		x = y = 0;
		w = s.cx;
		h = s.cy;
	}
	float m[16];
	m[0] = w/2;		m[4] = 0;		m[8] = 0;		m[12] = x+w/2;
	m[1] = 0;		m[5] = h/2;		m[9] = 0;		m[13] = y+h/2;
	m[2] = 0;		m[6] = 0;		m[10] = 0;		m[14] = 0;
	m[3] = 0;		m[7] = 0;		m[11] = 0;		m[15] = 0;

	viewTip->Refresh(view);
	projectionTip->Refresh(projection);
	viewportTip->Refresh(m);

	Invalidate();
}

void CDlgPipeLine::CalNode(COpenGLNode* node) {
	int id = node->ID;

	if(id != NODE_OBJECT) {
		CalNode(node->parent);
		node->DoOpenGL();
	}
}

void CDlgPipeLine::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDlgMatrix::OnPaint() for painting messages
	dc.SetBkMode( TRANSPARENT );
	CRect rect;
	GetClientRect(&rect);
	if(object == NULL)
	{
		rect.top += rect.Height()/2;
		dc.DrawText(CString("Select object to view data"),-1,rect,DT_CENTER);
	}
	else
	{
		int top = 10;
		for(int i=0; i<matrix.GetSize(); i++)
		{
			int left = 10;
			CPoint3D *p1 = (CPoint3D*)matrix.GetAt(i);
			ShowPoint(&dc,*p1,top,left);
			//GetDlgItem(IDC_MODEL)->GetWindowRect(&rect);
			//ScreenToClient(&rect);
			//GetDlgItem(IDC_MODEL)->SetWindowPos(NULL,left+50-rect.Width()/2,rect.top,0,0,SWP_NOSIZE | SWP_NOZORDER);
			
			left = 210;
			CPoint3D p2 = MultMatrixPoint(sum,*p1);
			ShowPoint(&dc,p2,top,left);
			//GetDlgItem(IDC_VIEW)->GetWindowRect(&rect);
			//ScreenToClient(&rect);
			//GetDlgItem(IDC_VIEW)->SetWindowPos(NULL,left+50-rect.Width()/2,rect.top,0,0,SWP_NOSIZE | SWP_NOZORDER);
			
			left = 410;
			CPoint3D p3 = MultMatrixPoint(view,p2);
			ShowPoint(&dc,p3,top,left);
			//GetDlgItem(IDC_PROJECTION)->GetWindowRect(&rect);
			//ScreenToClient(&rect);
			//GetDlgItem(IDC_PROJECTION)->SetWindowPos(NULL,left+50-rect.Width()/2,rect.top,0,0,SWP_NOSIZE | SWP_NOZORDER);
			
			left = 610;
			CPoint3D p4 = MultMatrixPoint(projection,p3);
			ShowPoint(&dc,p4,top,left);
			//GetDlgItem(IDC_DIVIDEW)->GetWindowRect(&rect);
			//ScreenToClient(&rect);
			//GetDlgItem(IDC_DIVIDEW)->SetWindowPos(NULL,left+50-rect.Width()/2,rect.top,0,0,SWP_NOSIZE | SWP_NOZORDER);
			
			left = 810;
			CPoint3D p5(p4.getX()/p4.getW(),p4.getY()/p4.getW(),p4.getZ()/p4.getW());
			ShowPoint(&dc,p5,top,left);

			x = x + (p5.getX()+1)*w/2;
			y = y + (p5.getY()+1)*h/2;

			left = 1010;
			char buf[128];
			sprintf_s(buf,"x = %5.2f",x);
			dc.TextOut(left,top+20,CString(buf));
			sprintf_s(buf,"y = %5.2f",y);
			dc.TextOut(left,top+40,CString(buf));

			top += 100;
		}
	}
}


BOOL CDlgPipeLine::OnInitDialog()
{
	CDlgMatrix::OnInitDialog();

	// TODO:  Add extra initialization here
	modelTip->Create(this);
	modelTip->AddTool(GetDlgItem(IDC_MODEL),60,10);
	
	viewTip->Create(this);
	viewTip->AddTool(GetDlgItem(IDC_VIEW),60,10);

	projectionTip->Create(this);
	projectionTip->AddTool(GetDlgItem(IDC_PROJECTION),60,10);

	viewportTip->Create(this);
	viewportTip->AddTool(GetDlgItem(IDC_VIEWPORT),60,10);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CDlgPipeLine::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	modelTip->RelayEvent(pMsg);
	viewTip->RelayEvent(pMsg);
	projectionTip->RelayEvent(pMsg);
	viewportTip->RelayEvent(pMsg);

	return CDlgMatrix::PreTranslateMessage(pMsg);
}


void CDlgPipeLine::OnClickedModel()
{
	// TODO: Add your control notification handler code here
	((CMainFrame*)GetParent())->ShowModelMatrix();
}


void CDlgPipeLine::OnClickedView()
{
	// TODO: Add your control notification handler code here
	((CMainFrame*)GetParent())->ShowViewMatrix();
}


void CDlgPipeLine::OnClickedProjection()
{
	// TODO: Add your control notification handler code here
	((CMainFrame*)GetParent())->ShowProjectionMatrix();
}


void CDlgPipeLine::OnClickedViewport()
{
	// TODO: Add your control notification handler code here
	((CMainFrame*)GetParent())->ShowViewPort();
}
