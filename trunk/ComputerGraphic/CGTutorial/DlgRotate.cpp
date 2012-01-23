// DlgRotate.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "DlgRotate.h"
#include "afxdialogex.h"


// CDlgAddRotate dialog

IMPLEMENT_DYNAMIC(CDlgRotate, CDialog)

CDlgRotate::CDlgRotate(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRotate::IDD, pParent)
{

	m_A = 90.0f;
	m_X = 0.0f;
	m_Y = 1.0f;
	m_Z = 0.0f;
}

CDlgRotate::CDlgRotate(float x, float y, float z, float angle, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRotate::IDD, pParent)
{

	m_A = angle;
	m_X = x;
	m_Y = y;
	m_Z = z;
}

CDlgRotate::~CDlgRotate()
{
}

void CDlgRotate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_A, m_A);
	DDX_Text(pDX, IDC_X, m_X);
	DDX_Text(pDX, IDC_Y, m_Y);
	DDX_Text(pDX, IDC_Z, m_Z);
}


BEGIN_MESSAGE_MAP(CDlgRotate, CDialog)
END_MESSAGE_MAP()


// CDlgAddRotate message handlers
