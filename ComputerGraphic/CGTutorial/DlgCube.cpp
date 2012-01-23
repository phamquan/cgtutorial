// DlgCube.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "DlgCube.h"
#include "afxdialogex.h"


// CDlgCube dialog

IMPLEMENT_DYNAMIC(CDlgCube, CDialog)

CDlgCube::CDlgCube(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCube::IDD, pParent)
{

	m_Bottom = -1.0f;
	m_Far = -1.0f;
	m_Left = -1.0f;
	m_Near = 1.0f;
	m_Right = 1.0f;
	m_Top = 1.0f;
}

CDlgCube::CDlgCube(float left, float bottom, float mnear, float right, float top, float mfar, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCube::IDD, pParent)
{

	m_Bottom = bottom;
	m_Far = mfar;
	m_Left = left;
	m_Near = mnear;
	m_Right = right;
	m_Top = top;
}

CDlgCube::~CDlgCube()
{
}

void CDlgCube::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_BOTTOM, m_Bottom);
	DDX_Text(pDX, IDC_FAR, m_Far);
	DDX_Text(pDX, IDC_LEFT, m_Left);
	DDX_Text(pDX, IDC_NEAR, m_Near);
	DDX_Text(pDX, IDC_RIGHT, m_Right);
	DDX_Text(pDX, IDC_TOP, m_Top);
}


BEGIN_MESSAGE_MAP(CDlgCube, CDialog)
END_MESSAGE_MAP()


// CDlgCube message handlers
