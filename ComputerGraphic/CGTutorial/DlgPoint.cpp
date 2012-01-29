// DlgPoint.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "DlgPoint.h"
#include "afxdialogex.h"


// CDlgPoint dialog

IMPLEMENT_DYNAMIC(CDlgPoint, CDialog)

CDlgPoint::CDlgPoint(float x, float y, float z, COLORREF color, CWnd* pParent)
	: CDialog(CDlgPoint::IDD, pParent)
{
	m_X = x;
	m_Y = y;
	m_Z = z;
	m_Color.SetColor(color);
}

CDlgPoint::~CDlgPoint()
{
}

void CDlgPoint::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_X, m_X);
	DDX_Text(pDX, IDC_Y, m_Y);
	DDX_Text(pDX, IDC_Z, m_Z);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, m_Color);
}


BEGIN_MESSAGE_MAP(CDlgPoint, CDialog)
END_MESSAGE_MAP()


// CDlgPoint message handlers
