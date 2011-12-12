// DlgShowMatrix.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "DlgShowMatrix.h"
#include "afxdialogex.h"


// CDlgShowMatrix dialog

IMPLEMENT_DYNAMIC(CDlgShowMatrix, CScrollDialog)

CDlgShowMatrix::CDlgShowMatrix(CWnd* pParent /*=NULL*/)
	: CScrollDialog(CDlgShowMatrix::IDD, pParent)
{

}

CDlgShowMatrix::~CDlgShowMatrix()
{
}

void CDlgShowMatrix::DoDataExchange(CDataExchange* pDX)
{
	CScrollDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgShowMatrix, CScrollDialog)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CDlgShowMatrix message handlers


void CDlgShowMatrix::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialogEx::OnPaint() for painting messages
	CRect rect;
	GetClientRect(&rect);

	for(int i=0; i<10; i++)
		dc.DrawText(CString("dasdasdasd"),-1,CRect(0,i*2,rect.Width(),rect.Height()), DT_TOP | DT_LEFT);
	//dc.DrawText(CString("dasdasdasd"),-1,CRect(0,20,rect.Width(),rect.Height()), DT_TOP | DT_LEFT);
}


BOOL CDlgShowMatrix::OnInitDialog()
{
	CScrollDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	GetWindowRect(m_rect);
	m_nScrollPos = 0;
	m_brush.CreateSolidBrush(RGB(255, 255, 255));

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CDlgShowMatrix::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	return m_brush;
}
