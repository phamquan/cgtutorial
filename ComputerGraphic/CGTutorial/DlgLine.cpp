// DlgLine.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "DlgLine.h"
#include "afxdialogex.h"


// CDlgLine dialog

IMPLEMENT_DYNAMIC(CDlgLine, CDialogEx)

CDlgLine::CDlgLine(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgLine::IDD, pParent)
{

	m_X1 = 0.0f;
	m_X2 = 0.0f;
	m_Y1 = 0.0f;
	m_Y2 = 0.0f;
	m_Z1 = 0.0f;
	m_Z2 = 0.0f;
}

CDlgLine::~CDlgLine()
{
}

void CDlgLine::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_X1, m_X1);
	DDX_Text(pDX, IDC_X2, m_X2);
	DDX_Text(pDX, IDC_Y1, m_Y1);
	DDX_Text(pDX, IDC_Y2, m_Y2);
	DDX_Text(pDX, IDC_Z1, m_Z1);
	DDX_Text(pDX, IDC_Z2, m_Z2);
}


BEGIN_MESSAGE_MAP(CDlgLine, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgLine::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgLine message handlers


void CDlgLine::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CDialogEx::OnOK();
}
