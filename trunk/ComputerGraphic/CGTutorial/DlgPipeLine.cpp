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
	camera = new CPtrArray();
	world = new CPtrArray();
	clipping = new CPtrArray();
	divide = new CPtrArray();
	window = new CPtrArray();

	modelDlg = new CDlgModelMatrix(camera);
	viewDlg = new CDlgViewMatrix(env->GetCamera(),camera,world);
	projectionDlg = new CDlgProjectionMatrix(env->GetProjection(),world,clipping);
	divideWDlg = new CDlgDivideW(clipping,divide);
	viewPortDlg = new CDlgViewPort(env->GetViewPort(),divide,window);
}

CDlgPipeLine::~CDlgPipeLine()
{
	delete camera;
	delete world;
	delete clipping;
	delete divide;
	delete window;

	delete modelDlg;
	delete viewDlg;
	delete projectionDlg;
	delete divideWDlg;
	delete viewPortDlg;
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

	modelDlg->Refresh(object);
	viewDlg->Refresh();
	projectionDlg->Refresh();
	divideWDlg->Refresh();
	viewPortDlg->Refresh();
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
	m_Tab.InsertItem(3,CString("Divide W"), -1);
	m_Tab.InsertItem(4,CString("View Port"), -1);

	m_Tab.AdjustRect(FALSE, &TabRect);
	
	modelDlg->Create(CDlgMatrix::IDD,&m_Tab);
	modelDlg->MoveWindow(TabRect);
	modelDlg->ShowWindow(SW_SHOW);

	viewDlg->Create(CDlgMatrix::IDD,&m_Tab);
	viewDlg->MoveWindow(TabRect);

	projectionDlg->Create(CDlgMatrix::IDD,&m_Tab);
	projectionDlg->MoveWindow(TabRect);

	divideWDlg->Create(CDlgMatrix::IDD,&m_Tab);
	divideWDlg->MoveWindow(TabRect);

	viewPortDlg->Create(CDlgMatrix::IDD,&m_Tab);
	viewPortDlg->MoveWindow(TabRect);

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
		divideWDlg->ShowWindow(SW_HIDE);
		viewPortDlg->ShowWindow(SW_HIDE);
		break;
	case 1:
		modelDlg->ShowWindow(SW_HIDE);
		viewDlg->ShowWindow(SW_SHOW);
		projectionDlg->ShowWindow(SW_HIDE);
		divideWDlg->ShowWindow(SW_HIDE);
		viewPortDlg->ShowWindow(SW_HIDE);
		break;
	case 2:
		modelDlg->ShowWindow(SW_HIDE);
		viewDlg->ShowWindow(SW_HIDE);
		projectionDlg->ShowWindow(SW_SHOW);
		divideWDlg->ShowWindow(SW_HIDE);
		viewPortDlg->ShowWindow(SW_HIDE);
		break;	
	case 3:
		modelDlg->ShowWindow(SW_HIDE);
		viewDlg->ShowWindow(SW_HIDE);
		projectionDlg->ShowWindow(SW_HIDE);
		divideWDlg->ShowWindow(SW_SHOW);
		viewPortDlg->ShowWindow(SW_HIDE);
		break;
	case 4:
		modelDlg->ShowWindow(SW_HIDE);
		viewDlg->ShowWindow(SW_HIDE);
		projectionDlg->ShowWindow(SW_HIDE);
		divideWDlg->ShowWindow(SW_HIDE);
		viewPortDlg->ShowWindow(SW_SHOW);
		break;
	}
	*pResult = 0;
}
