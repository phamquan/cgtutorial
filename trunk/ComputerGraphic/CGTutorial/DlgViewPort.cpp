// DlgViewPort.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "DlgViewPort.h"
#include "ViewPort.h"
#include "afxdialogex.h"


// CDlgViewPort dialog

IMPLEMENT_DYNAMIC(CDlgViewPort, CDialog)

CDlgViewPort::CDlgViewPort(float left, float bottom, float width, float height, int type, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgViewPort::IDD, pParent)
{
	m_Bottom = bottom;
	m_Height = height;
	m_Left = left;
	m_Width = width;
	this->type = type;
}

CDlgViewPort::~CDlgViewPort()
{
}

void CDlgViewPort::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_BOTTOM, m_Bottom);
	DDX_Text(pDX, IDC_HEIGHT, m_Height);
	DDX_Text(pDX, IDC_LEFT, m_Left);
	DDX_Text(pDX, IDC_WIDTH, m_Width);
}


BEGIN_MESSAGE_MAP(CDlgViewPort, CDialog)
	ON_COMMAND(IDC_DEFAULT, &CDlgViewPort::OnDefault)
	ON_COMMAND(IDC_CUSTOM, &CDlgViewPort::OnCustom)
END_MESSAGE_MAP()


// CDlgViewPort message handlers


void CDlgViewPort::OnDefault()
{
	// TODO: Add your command handler code here
	type = VIEWPORT_DEFAULT;
}


void CDlgViewPort::OnCustom()
{
	// TODO: Add your command handler code here
	type = VIEWPORT_CUSTOM;
}


BOOL CDlgViewPort::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	((CButton*)GetDlgItem(IDC_DEFAULT))->SetCheck(type == VIEWPORT_DEFAULT);
	((CButton*)GetDlgItem(IDC_CUSTOM))->SetCheck(type == VIEWPORT_CUSTOM);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
