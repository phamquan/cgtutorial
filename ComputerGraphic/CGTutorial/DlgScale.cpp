// DlgScale.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "DlgScale.h"
#include "afxdialogex.h"


// CDlgScale dialog

IMPLEMENT_DYNAMIC(CDlgScale, CDialog)

CDlgScale::CDlgScale(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgScale::IDD, pParent)
{
	m_X = 2.0f;
	m_Y = 2.0f;
	m_Z = 2.0f;
}

CDlgScale::CDlgScale(float x, float y, float z, CWnd* pParent) 
	: CDialog(CDlgScale::IDD, pParent)
{
	m_X = x;
	m_Y = y;
	m_Z = z;
}

CDlgScale::~CDlgScale()
{
}

void CDlgScale::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_X, m_X);
	DDX_Text(pDX, IDC_Y, m_Y);
	DDX_Text(pDX, IDC_Z, m_Z);
}


BEGIN_MESSAGE_MAP(CDlgScale, CDialog)
END_MESSAGE_MAP()


// CDlgScale message handlers
