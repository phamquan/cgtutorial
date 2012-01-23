// DlgRectangle.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "DlgRectangle.h"
#include "afxdialogex.h"


// CDlgRectangle dialog

IMPLEMENT_DYNAMIC(CDlgRectangle, CDialog)

CDlgRectangle::CDlgRectangle(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRectangle::IDD, pParent)
{

	m_Bottom = 0.0f;
	m_Left = 0.0f;
	m_Right = 1.0f;
	m_Top = 1.0f;
}

CDlgRectangle::CDlgRectangle(float top, float left, float bottom, float right, CWnd* pParent)
	: CDialog(CDlgRectangle::IDD, pParent)
{
	m_Bottom = bottom;
	m_Left = left;
	m_Right = right;
	m_Top = top;
}

CDlgRectangle::~CDlgRectangle()
{
}

void CDlgRectangle::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_BOTTOM, m_Bottom);
	DDX_Text(pDX, IDC_LEFT, m_Left);
	DDX_Text(pDX, IDC_RIGHT, m_Right);
	DDX_Text(pDX, IDC_TOP, m_Top);
}


BEGIN_MESSAGE_MAP(CDlgRectangle, CDialog)
END_MESSAGE_MAP()
// CDlgRectangle message handlers
