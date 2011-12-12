// DlgPoint.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "DlgPoint.h"
#include "afxdialogex.h"


// CDlgPoint dialog

IMPLEMENT_DYNAMIC(CDlgPoint, CDialogEx)

CDlgPoint::CDlgPoint(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgPoint::IDD, pParent)
{

	m_X = 0.0f;
	m_Y = 0.0f;
	m_Z = 0.0f;
}

CDlgPoint::CDlgPoint(float x, float y, float z, CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgPoint::IDD, pParent)
{

	m_X = x;
	m_Y = y;
	m_Z = z;
}

CDlgPoint::~CDlgPoint()
{
}

void CDlgPoint::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_X, m_X);
	DDX_Text(pDX, IDC_Y, m_Y);
	DDX_Text(pDX, IDC_Z, m_Z);
}


BEGIN_MESSAGE_MAP(CDlgPoint, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgPoint::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgPoint message handlers


void CDlgPoint::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CDialogEx::OnOK();
}
