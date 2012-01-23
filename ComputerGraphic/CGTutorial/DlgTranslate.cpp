// CDlgTranslate.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "DlgTranslate.h"
#include "afxdialogex.h"


// CDlgTranslate dialog

IMPLEMENT_DYNAMIC(CDlgTranslate, CDialog)

CDlgTranslate::CDlgTranslate(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTranslate::IDD, pParent)
{
	m_X = 1.0f;
	m_Y = 1.0f;
	m_Z = 1.0f;
}

CDlgTranslate::CDlgTranslate(float x, float y, float z, CWnd* pParent)
	: CDialog(CDlgTranslate::IDD, pParent)
{
	m_X = x;
	m_Y = y;
	m_Z = z;
}

CDlgTranslate::~CDlgTranslate()
{
}

void CDlgTranslate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_X, m_X);
	DDX_Text(pDX, IDC_Y, m_Y);
	DDX_Text(pDX, IDC_Z, m_Z);
}


BEGIN_MESSAGE_MAP(CDlgTranslate, CDialog)
END_MESSAGE_MAP()


// CDlgTranslate message handlers
