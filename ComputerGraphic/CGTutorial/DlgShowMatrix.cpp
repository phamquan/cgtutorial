// DlgShowMatrix.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "DlgShowMatrix.h"
#include "afxdialogex.h"


// CDlgShowMatrix dialog

IMPLEMENT_DYNAMIC(CDlgShowMatrix, CDialogEx)

CDlgShowMatrix::CDlgShowMatrix(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgShowMatrix::IDD, pParent)
{

}

CDlgShowMatrix::~CDlgShowMatrix()
{
}

void CDlgShowMatrix::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgShowMatrix, CDialogEx)
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

	dc.TextOutW(0,10,CString("dasdasdasd"),-1);
}


BOOL CDlgShowMatrix::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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
