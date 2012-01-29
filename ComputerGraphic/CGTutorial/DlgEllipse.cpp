// DlgEllipse.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "DlgEllipse.h"
#include "afxdialogex.h"


// CDlgEllipse dialog

IMPLEMENT_DYNAMIC(CDlgEllipse, CDialog)

CDlgEllipse::CDlgEllipse(float x, float y, float z, float a, float b, COLORREF color, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEllipse::IDD, pParent)
{

	m_A = a;
	m_B = b;
	m_X = x;
	m_Y = y;
	m_Z = z;
	m_Color.SetColor(color);
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
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, m_Color);
}


BEGIN_MESSAGE_MAP(CDlgEllipse, CDialog)
END_MESSAGE_MAP()


// CDlgEllipse message handlers
