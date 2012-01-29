// DlgLine.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "DlgLine.h"
#include "afxdialogex.h"


// CDlgLine dialog

IMPLEMENT_DYNAMIC(CDlgLine, CDialog)

CDlgLine::CDlgLine(float x1, float y1, float z1, float x2, float y2, float z2, COLORREF color, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLine::IDD, pParent)
{

	m_BX = x1;
	m_BY = y1;
	m_BZ = z1;
	m_EX = x2;
	m_EY = y2;
	m_EZ = z2;
	m_Color.SetColor(color);
}

CDlgLine::~CDlgLine()
{
}

void CDlgLine::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_BX, m_BX);
	DDX_Text(pDX, IDC_BY, m_BY);
	DDX_Text(pDX, IDC_BZ, m_BZ);
	DDX_Text(pDX, IDC_EX, m_EX);
	DDX_Text(pDX, IDC_EY, m_EY);
	DDX_Text(pDX, IDC_EZ, m_EZ);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, m_Color);
}


BEGIN_MESSAGE_MAP(CDlgLine, CDialog)
END_MESSAGE_MAP()


// CDlgLine message handlers
