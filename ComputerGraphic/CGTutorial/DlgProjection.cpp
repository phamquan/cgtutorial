// DlgProjection.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "DlgProjection.h"
#include "afxdialogex.h"


// CDlgProjection dialog

IMPLEMENT_DYNAMIC(CDlgProjection, CDialogEx)

CDlgProjection::CDlgProjection(float left, float right, float bottom, float top, float mnear, float mfar, int type, CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgProjection::IDD, pParent)
{

	m_Bottom = bottom;
	m_Far = mfar;
	m_Left = left;
	m_Near = mnear;
	m_Right = right;
	m_Top = top;
	this->type = type;
}

CDlgProjection::~CDlgProjection()
{
}

void CDlgProjection::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_BOTTOM, m_Bottom);
	DDX_Text(pDX, IDC_FAR, m_Far);
	DDX_Text(pDX, IDC_LEFT, m_Left);
	DDX_Text(pDX, IDC_NEAR, m_Near);
	DDX_Text(pDX, IDC_RIGHT, m_Right);
	DDX_Text(pDX, IDC_TOP, m_Top);
}


BEGIN_MESSAGE_MAP(CDlgProjection, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgProjection::OnBnClickedOk)
	ON_COMMAND(IDC_RADIO1, &CDlgProjection::OnRadio1)
	ON_COMMAND(IDC_RADIO2, &CDlgProjection::OnRadio2)
END_MESSAGE_MAP()


// CDlgProjection message handlers


void CDlgProjection::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if(type == FRUSTUM && m_Near <= 0)
		AfxMessageBox(CString("near of frustum must greater than 0"));
	else if(type == FRUSTUM && m_Far <= 0)
		AfxMessageBox(CString("far of frustum must greater than 0"));
	else
		CDialogEx::OnOK();
}


void CDlgProjection::OnRadio1()
{
	// TODO: Add your command handler code here
	type = ORTHO;
}

void CDlgProjection::OnRadio2()
{
	// TODO: Add your command handler code here
	type = FRUSTUM;
}

BOOL CDlgProjection::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(type == ORTHO);
	((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(type == FRUSTUM);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
