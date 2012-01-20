// DlgGenCode.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "DlgGenCode.h"
#include "afxdialogex.h"


// CDlgGenCode dialog

IMPLEMENT_DYNAMIC(CDlgGenCode, CDialog)

CDlgGenCode::CDlgGenCode(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgGenCode::IDD, pParent)
{

	m_Data = _T("");
}

CDlgGenCode::~CDlgGenCode()
{
}

void CDlgGenCode::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_GENCODE, m_Data);
	DDX_Control(pDX, IDC_GENCODE, m_Ctrl);
}


BEGIN_MESSAGE_MAP(CDlgGenCode, CDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CDlgGenCode message handlers


void CDlgGenCode::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if(m_Ctrl.GetSafeHwnd()) {
		m_Ctrl.MoveWindow(0,0,cx,cy);
	}
}

void CDlgGenCode::Refresh(CString code)
{
	m_Data = code;
	UpdateData(FALSE);
	Invalidate();
}