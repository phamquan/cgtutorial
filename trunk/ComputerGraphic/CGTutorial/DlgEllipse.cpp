// DlgEllipse.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "DlgEllipse.h"
#include "afxdialogex.h"


// CDlgEllipse dialog

IMPLEMENT_DYNAMIC(CDlgEllipse, CDialog)

CDlgEllipse::CDlgEllipse(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEllipse::IDD, pParent)
{

	m_A = 2.0f;
	m_B = 1.0f;
	m_X = 0.0f;
	m_Y = 0.0f;
	m_Z = 0.0f;
}

CDlgEllipse::CDlgEllipse(float x, float y, float z, float a, float b, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEllipse::IDD, pParent)
{

	m_A = a;
	m_B = b;
	m_X = x;
	m_Y = y;
	m_Z = z;
}

CDlgEllipse::~CDlgEllipse()
{
}

void CDlgEllipse::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_A, m_A);
	DDX_Text(pDX, IDC_B, m_B);
	DDX_Text(pDX, IDC_X, m_X);
	DDX_Text(pDX, IDC_Y, m_Y);
	DDX_Text(pDX, IDC_Z, m_Z);
}


BEGIN_MESSAGE_MAP(CDlgEllipse, CDialog)
END_MESSAGE_MAP()


// CDlgEllipse message handlers
