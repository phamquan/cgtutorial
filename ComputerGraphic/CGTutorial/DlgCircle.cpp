// DlgCircle.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "DlgCircle.h"
#include "afxdialogex.h"


// CDlgCircle dialog

IMPLEMENT_DYNAMIC(CDlgCircle, CDialog)

CDlgCircle::CDlgCircle(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCircle::IDD, pParent)
{

	m_R = 0.0f;
	m_X = 0.0f;
	m_Y = 0.0f;
	m_Z = 0.0f;
}

CDlgCircle::CDlgCircle(float x, float y, float z, float R, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCircle::IDD, pParent)
{

	m_R = R;
	m_X = x;
	m_Y = y;
	m_Z = z;
}

CDlgCircle::~CDlgCircle()
{
}

void CDlgCircle::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_R, m_R);
	DDX_Text(pDX, IDC_X, m_X);
	DDX_Text(pDX, IDC_Y, m_Y);
	DDX_Text(pDX, IDC_Z, m_Z);
}


BEGIN_MESSAGE_MAP(CDlgCircle, CDialog)
END_MESSAGE_MAP()


// CDlgCircle message handlers
