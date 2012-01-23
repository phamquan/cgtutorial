// DlgCylinder.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "DlgCylinder.h"
#include "afxdialogex.h"


// CDlgCylinder dialog

IMPLEMENT_DYNAMIC(CDlgCylinder, CDialog)

CDlgCylinder::CDlgCylinder(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCylinder::IDD, pParent)
{

	m_Height = 1.0f;
	m_R = 1.0f;
	m_X = 0.0f;
	m_Y = 0.0f;
	m_Z = 0.0f;
}

CDlgCylinder::CDlgCylinder(float x, float y, float z, float R, float height, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCylinder::IDD, pParent)
{

	m_Height = height;
	m_R = R;
	m_X = x;
	m_Y = y;
	m_Z = z;
}

CDlgCylinder::~CDlgCylinder()
{
}

void CDlgCylinder::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_HEIGHT, m_Height);
	DDX_Text(pDX, IDC_R, m_R);
	DDX_Text(pDX, IDC_X, m_X);
	DDX_Text(pDX, IDC_Y, m_Y);
	DDX_Text(pDX, IDC_Z, m_Z);
}


BEGIN_MESSAGE_MAP(CDlgCylinder, CDialog)
END_MESSAGE_MAP()


// CDlgCylinder message handlers
