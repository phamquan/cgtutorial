// DlgRotate.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "DlgRotate.h"
#include "afxdialogex.h"


// CDlgRotate dialog

IMPLEMENT_DYNAMIC(CDlgRotate, CDialogEx)

CDlgRotate::CDlgRotate(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgRotate::IDD, pParent)
{

	m_Angle = 0.0f;
	m_X = 0.0f;
	m_Y = 0.0f;
	m_Z = 0.0f;
}

CDlgRotate::~CDlgRotate()
{
}

void CDlgRotate::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ANGLE, m_Angle);
	DDV_MinMaxFloat(pDX, m_Angle, -360, 360);
	DDX_Text(pDX, IDC_X, m_X);
	DDX_Text(pDX, IDC_Y, m_Y);
	DDX_Text(pDX, IDC_Z, m_Z);
}


BEGIN_MESSAGE_MAP(CDlgRotate, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgRotate::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgRotate message handlers


void CDlgRotate::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CDialogEx::OnOK();
}
