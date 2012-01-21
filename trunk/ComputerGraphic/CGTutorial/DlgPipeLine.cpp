// DlgPipeLine.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "DlgPipeLine.h"
#include "Point4D.h"
#include "Line.h"
#include "Rectangle.h"

// CDlgPipeLine dialog

IMPLEMENT_DYNAMIC(CDlgPipeLine, CDlgMatrix)

CDlgPipeLine::CDlgPipeLine(CEnvironment *env, CWnd* pParent /*=NULL*/)
	: CDlgMatrix(pParent)
{
	environment = env;
	modelTip = new CPipeLineTip();
	viewTip = new CPipeLineTip();
	projectionTip = new CPipeLineTip();
}

CDlgPipeLine::~CDlgPipeLine()
{
	delete modelTip;
	delete viewTip;
	delete projectionTip;
}

void CDlgPipeLine::DoDataExchange(CDataExchange* pDX)
{
	CDlgMatrix::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgPipeLine, CDlgMatrix)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgPipeLine message handlers
void CDlgPipeLine::Refresh(COpenGLNode *obj)
{
	object = obj;
	if(object != NULL)
	{
		Clear();
		int id = object->ID;
		float x1,y1,z1,x2,y2,z2,x3,y3,z3;
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
			
		}

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		CalNode(object->parent);

		environment->GetCamera()->GetData(x1,y1,z1,x2,y2,z2,x3,y3,z3);
		glLoadIdentity();
		gluLookAt(x1,y1,z1,x2,y2,z2,x3,y3,z3);
		glGetFloatv(GL_MODELVIEW_MATRIX,view);
		glPopMatrix();

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();

		environment->GetProjection()->GetData(x1,y1,z1,x2,y2,z2,id);
		glLoadIdentity();
		if(id == ORTHO)
			glOrtho(x1,y1,z1,x2,y2,z2);
		else
			glFrustum(x1,y1,z1,x2,y2,z2);
		glGetFloatv(GL_PROJECTION_MATRIX,projection);
		glPopMatrix();

		modelTip->Refresh(sum);
		viewTip->Refresh(view);
		projectionTip->Refresh(projection);
	}
	else
	{
		modelTip->ReSet();
		viewTip->ReSet();
		projectionTip->ReSet();
	}
	Invalidate();
}

void CDlgPipeLine::CalNode(COpenGLNode* node) {
	int id = node->ID;

	if(id == NODE_OBJECT) {
		
	} else {
		CalNode(node->parent);
		if(id != NODE_COLOR) {			
			node->DoOpenGL();
		}
	}
	glGetFloatv(GL_MODELVIEW_MATRIX,sum);
}

void CDlgPipeLine::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDlgMatrix::OnPaint() for painting messages
	CRect rect;
	if(object != NULL)
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
			
			CPoint3D p2 = MultMatrixPoint(sum,*p1);
			ShowPoint(&dc,p2,top,left+=100);
			//GetDlgItem(IDC_VIEW)->GetWindowRect(&rect);
			//ScreenToClient(&rect);
			//GetDlgItem(IDC_VIEW)->SetWindowPos(NULL,left+50-rect.Width()/2,rect.top,0,0,SWP_NOSIZE | SWP_NOZORDER);
			
			CPoint3D p3 = MultMatrixPoint(view,p2);
			ShowPoint(&dc,p3,top,left+=100);
			//GetDlgItem(IDC_PROJECTION)->GetWindowRect(&rect);
			//ScreenToClient(&rect);
			//GetDlgItem(IDC_PROJECTION)->SetWindowPos(NULL,left+50-rect.Width()/2,rect.top,0,0,SWP_NOSIZE | SWP_NOZORDER);
			
			CPoint3D p4 = MultMatrixPoint(projection,p3);
			ShowPoint(&dc,p4,top,left+=100);
			//GetDlgItem(IDC_DIVIDEW)->GetWindowRect(&rect);
			//ScreenToClient(&rect);
			//GetDlgItem(IDC_DIVIDEW)->SetWindowPos(NULL,left+50-rect.Width()/2,rect.top,0,0,SWP_NOSIZE | SWP_NOZORDER);
			
			CPoint3D p5(p4.getX()/p4.getW(),p4.getY()/p4.getW(),p4.getZ()/p4.getW());
			ShowPoint(&dc,p5,top,left+=100);

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

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CDlgPipeLine::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	modelTip->RelayEvent(pMsg);
	viewTip->RelayEvent(pMsg);
	projectionTip->RelayEvent(pMsg);

	return CDlgMatrix::PreTranslateMessage(pMsg);
}
