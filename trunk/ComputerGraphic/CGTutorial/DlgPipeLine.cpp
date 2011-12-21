// DlgPipeLine.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "DlgPipeLine.h"
#include "afxdialogex.h"


// CDlgPipeLine dialog

IMPLEMENT_DYNAMIC(CDlgPipeLine, CDialogEx)

CDlgPipeLine::CDlgPipeLine(CEnvironment *env, CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgPipeLine::IDD, pParent)
{
	environment = env;
	object = NULL;
	camera = NULL;
	world = NULL;
	clipping = NULL;

	modelDlg = new CDlgModelMatrix();
	viewDlg = new CDlgViewMatrix(env->GetCamera());
	projectionDlg = new CDlgProjectionMatrix(env->GetProjection());
}

CDlgPipeLine::~CDlgPipeLine()
{
	if(camera != NULL)
		delete camera;

	if(world != NULL)
		delete world;

	if(clipping != NULL)
		delete clipping;

	if(modelDlg != NULL)
		delete modelDlg;

	if(viewDlg != NULL)
		delete viewDlg;
	
	if(projectionDlg != NULL)
		delete projectionDlg;
}

void CDlgPipeLine::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_Tab);
}


BEGIN_MESSAGE_MAP(CDlgPipeLine, CDialogEx)
//	ON_WM_MOVE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CDlgPipeLine::OnSelchangeTab1)
END_MESSAGE_MAP()


// CDlgPipeLine message handlers
void CDlgPipeLine::SetData(COpenGLNode* in) {
	object = in;

	if(camera != NULL) {
		delete camera;
		camera = NULL;
	}

	if(world != NULL) {
		delete world;
		world = NULL;
	}

	if(clipping != NULL) {
		delete clipping;
		clipping = NULL;
	}

	if(in != NULL) {
		switch(in->GetID()) {
		case NODE_POINT:
			camera = new CPoint4D(0,0,0);
			world = new CPoint4D(0,0,0);
			break;
		case NODE_LINE:
			camera = new CLine(0,0,0,0,0,0);
			world = new CLine(0,0,0,0,0,0);
			break;
		case NODE_RECTANGLE:
			camera = new CRectangle(0,0,0,0);
			world = new CRectangle(0,0,0,0);
			break;
		}
	}

	modelDlg->SetData(object,camera);
	viewDlg->SetData(camera,world);
	projectionDlg->SetData(world,clipping);
}

BOOL CDlgPipeLine::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	CRect TabRect;
	m_Tab.GetClientRect(&TabRect);
	m_Tab.InsertItem(0,CString("Model Matrix"), -1);
	m_Tab.InsertItem(1,CString("View Matrix"), -1);
	m_Tab.InsertItem(2,CString("Projection Matrix"), -1);
	m_Tab.AdjustRect(FALSE, &TabRect);
	
	modelDlg->Create(CDlgMatrix::IDD,&m_Tab);
	modelDlg->MoveWindow(TabRect);
	modelDlg->ShowWindow(SW_SHOW);

	viewDlg->Create(CDlgMatrix::IDD,&m_Tab);
	viewDlg->MoveWindow(TabRect);

	projectionDlg->Create(CDlgMatrix::IDD,&m_Tab);
	projectionDlg->MoveWindow(TabRect);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPipeLine::OnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	switch(m_Tab.GetCurSel()) {
	case 0:
		modelDlg->ShowWindow(SW_SHOW);
		viewDlg->ShowWindow(SW_HIDE);
		projectionDlg->ShowWindow(SW_HIDE);
		break;
	case 1:
		modelDlg->ShowWindow(SW_HIDE);
		viewDlg->ShowWindow(SW_SHOW);
		projectionDlg->ShowWindow(SW_HIDE);
		break;
	case 2:
		modelDlg->ShowWindow(SW_HIDE);
		viewDlg->ShowWindow(SW_HIDE);
		projectionDlg->ShowWindow(SW_SHOW);
		break;	
	}
	*pResult = 0;
}
