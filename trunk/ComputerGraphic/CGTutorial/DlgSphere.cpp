// DlgSphere.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "DlgSphere.h"
#include "afxdialogex.h"


// CDlgSphere dialog

IMPLEMENT_DYNAMIC(CDlgSphere, CDialog)

CDlgSphere::CDlgSphere(float x, float y, float z, float R, COLORREF color, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSphere::IDD, pParent)
{
	m_R = R;
	m_X = x;
	m_Y = y;
	m_Z = z;
	m_Color.SetColor(color);
}

CDlgSphere::~CDlgSphere()
{
}

void CDlgSphere::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_R, m_R);
	DDX_Text(pDX, IDC_X, m_X);
	DDX_Text(pDX, IDC_Y, m_Y);
	DDX_Text(pDX, IDC_Z, m_Z);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, m_Color);
}


BEGIN_MESSAGE_MAP(CDlgSphere, CDialog)
END_MESSAGE_MAP()


// CDlgSphere message handlers
