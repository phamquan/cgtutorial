// DlgRectangle.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "DlgRectangle.h"
#include "afxdialogex.h"


// CDlgRectangle dialog

IMPLEMENT_DYNAMIC(CDlgRectangle, CDialogEx)

CDlgRectangle::CDlgRectangle(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgRectangle::IDD, pParent)
{

	m_Bottom = 0.0f;
	m_Left = 0.0f;
	m_Right = 0.0f;
	m_Top = 0.0f;
}

CDlgRectangle::CDlgRectangle(float top, float left, float bottom, float right, CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgRectangle::IDD, pParent)
{

	m_Bottom = top;
	m_Left = left;
	m_Right = bottom;
	m_Top = right;
}

CDlgRectangle::~CDlgRectangle()
{
}

void CDlgRectangle::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_BOTTOM, m_Bottom);
	DDX_Text(pDX, IDC_LEFT, m_Left);
	DDX_Text(pDX, IDC_RIGHT, m_Right);
	DDX_Text(pDX, IDC_TOP, m_Top);
}


BEGIN_MESSAGE_MAP(CDlgRectangle, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgRectangle::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgRectangle message handlers


void CDlgRectangle::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CDialogEx::OnOK();
}
