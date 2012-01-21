// DlgMatrixFormula.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "DlgMatrixFormula.h"
#include "afxdialogex.h"


// CDlgMatrixFormula dialog

IMPLEMENT_DYNAMIC(CDlgMatrixFormula, CDialog)

CDlgMatrixFormula::CDlgMatrixFormula(CEnvironment *environment)
	: CDialog(CDlgMatrixFormula::IDD, NULL)
{
	dlgModel = new CDlgModelMatrix();
	dlgModelGL = new CDlgModelMatrixGL();
	dlgView = new CDlgViewMatrix(environment);
	dlgViewGL = new CDlgViewMatrixGL(environment);
	dlgProjection = new CDlgProjectionMatrix(environment);
	dlgProjectionGL = new CDlgProjectionMatrixGL(environment);
}

CDlgMatrixFormula::~CDlgMatrixFormula()
{
	delete dlgModel;
	delete dlgModelGL;
	delete dlgView;
	delete dlgViewGL;
	delete dlgProjection;
	delete dlgProjectionGL;
}

void CDlgMatrixFormula::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_Tab);
}


BEGIN_MESSAGE_MAP(CDlgMatrixFormula, CDialog)
	ON_WM_SIZE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CDlgMatrixFormula::OnSelchangeTab1)
END_MESSAGE_MAP()


// CDlgMatrixFormula message handlers


void CDlgMatrixFormula::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if(m_Tab.GetSafeHwnd() != NULL) {
		m_Tab.MoveWindow(0,0,cx,cy);

		CRect TabRect;
		m_Tab.GetClientRect(&TabRect);
		m_Tab.AdjustRect(FALSE, &TabRect);
		
		CRect Left(TabRect.left,TabRect.top,TabRect.left+TabRect.Width()/2,TabRect.bottom);
		CRect Right(TabRect.left+TabRect.Width()/2,TabRect.top,TabRect.right,TabRect.bottom);

		dlgModel->MoveWindow(Left);
		dlgModelGL->MoveWindow(Right);
		dlgView->MoveWindow(Left);
		dlgViewGL->MoveWindow(Right);
		dlgProjection->MoveWindow(Left);
		dlgProjectionGL->MoveWindow(Right);
	}
}

void CDlgMatrixFormula::Refresh(COpenGLNode *object)
{
	dlgModel->Refresh(object);
	dlgModelGL->Refresh(object);
	dlgView->Refresh();
	dlgViewGL->Refresh();
	dlgProjection->Refresh();
	dlgProjectionGL->Refresh();
}

BOOL CDlgMatrixFormula::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	CRect TabRect;
	m_Tab.GetClientRect(&TabRect);
	m_Tab.InsertItem(0,CString("Model Matrix"), -1);
	m_Tab.InsertItem(1,CString("View Matrix"), -1);
	m_Tab.InsertItem(2,CString("Projection Matrix"), -1);

	m_Tab.AdjustRect(FALSE, &TabRect);

	CRect Left(TabRect.left,TabRect.top,TabRect.left+TabRect.Width()/2,TabRect.bottom);
	CRect Right(TabRect.left+TabRect.Width()/2,TabRect.top,TabRect.right,TabRect.bottom);

	dlgModel->Create(CDlgMatrix::IDD,&m_Tab);
	dlgModel->MoveWindow(Left);
	dlgModel->ShowWindow(SW_SHOW);

	dlgModelGL->Create(CDlgMatrix::IDD,&m_Tab);
	dlgModelGL->MoveWindow(Right);
	dlgModelGL->ShowWindow(SW_SHOW);

	dlgView->Create(CDlgMatrix::IDD,&m_Tab);
	dlgView->MoveWindow(Left);

	dlgViewGL->Create(CDlgMatrix::IDD,&m_Tab);
	dlgViewGL->MoveWindow(Right);

	dlgProjection->Create(CDlgMatrix::IDD,&m_Tab);
	dlgProjection->MoveWindow(Left);

	dlgProjectionGL->Create(CDlgMatrix::IDD,&m_Tab);
	dlgProjectionGL->MoveWindow(Right);

	Refresh(NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgMatrixFormula::OnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	ChangeTab(m_Tab.GetCurSel());
	*pResult = 0;
}

void CDlgMatrixFormula::ChangeTab(int index)
{
	switch(index) {
	case 0:
		dlgModel->ShowWindow(SW_SHOW);
		dlgModelGL->ShowWindow(SW_SHOW);
		dlgView->ShowWindow(SW_HIDE);
		dlgViewGL->ShowWindow(SW_HIDE);
		dlgProjection->ShowWindow(SW_HIDE);
		dlgProjectionGL->ShowWindow(SW_HIDE);
		break;
	case 1:
		dlgModel->ShowWindow(SW_HIDE);
		dlgModelGL->ShowWindow(SW_HIDE);
		dlgView->ShowWindow(SW_SHOW);
		dlgViewGL->ShowWindow(SW_SHOW);
		dlgProjection->ShowWindow(SW_HIDE);
		dlgProjectionGL->ShowWindow(SW_HIDE);
		break;
	case 2:
		dlgModel->ShowWindow(SW_HIDE);
		dlgModelGL->ShowWindow(SW_HIDE);
		dlgView->ShowWindow(SW_HIDE);
		dlgViewGL->ShowWindow(SW_HIDE);
		dlgProjection->ShowWindow(SW_SHOW);
		dlgProjectionGL->ShowWindow(SW_SHOW);
		break;	
	}
	m_Tab.SetCurSel(index);
}