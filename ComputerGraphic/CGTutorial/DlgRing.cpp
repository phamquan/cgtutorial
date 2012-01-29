// DlgRing.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "DlgRing.h"
#include "afxdialogex.h"


// CDlgRing dialog

IMPLEMENT_DYNAMIC(CDlgRing, CDialog)

CDlgRing::CDlgRing(float x, float y, float z, float R, float r, COLORREF color, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRing::IDD, pParent)
{

	m_R = R;
	m_R1 = r;
	m_X = x;
	m_Y = y;
	m_Z = z;
	m_Color.SetColor(color);
}

CDlgRing::~CDlgRing()
{
}

void CDlgRing::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_R, m_R);
	DDX_Text(pDX, IDC_R1, m_R1);
	DDX_Text(pDX, IDC_X, m_X);
	DDX_Text(pDX, IDC_Y, m_Y);
	DDX_Text(pDX, IDC_Z, m_Z);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, m_Color);
}


BEGIN_MESSAGE_MAP(CDlgRing, CDialog)
END_MESSAGE_MAP()


// CDlgRing message handlers
