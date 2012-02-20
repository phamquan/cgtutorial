// RasterizationInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RasterizationInfoDlg.h"
#include "afxdialogex.h"
#define WM_NEW_COUNT (WM_USER + 0x101)

// CRasterizationInfoDlg dialog

IMPLEMENT_DYNAMIC(CRasterizationInfoDlg, CDialogEx)

CRasterizationInfoDlg::CRasterizationInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRasterizationInfoDlg::IDD, pParent)
{

	//  m_cx = 0;
	m_cy = 0;
	//  m_cx = 0;
	m_cx = 0;
	m_cr = 0.0f;
	m_cg = 0.0f;
	m_cb = 0.0f;
}

CRasterizationInfoDlg::~CRasterizationInfoDlg()
{
}

void CRasterizationInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_EDITX, m_cx);
	//  DDX_Text(pDX, IDC_EDITX, m_cx);
	DDX_Text(pDX, IDC_EDITY, m_cy);
	//  DDX_Text(pDX, IDC_STATICCX, m_cx);
	//  DDX_Control(pDX, IDC_EDITX, m_cx);
	DDX_Text(pDX, IDC_EDITX, m_cx);
	DDX_Text(pDX, IDC_EDITR, m_cr);
	DDX_Text(pDX, IDC_EDITG, m_cg);
	DDX_Text(pDX, IDC_EDITB, m_cb);
}


BEGIN_MESSAGE_MAP(CRasterizationInfoDlg, CDialogEx)
	ON_MESSAGE(WM_NEW_COUNT, OnNewCount)
END_MESSAGE_MAP()


// CRasterizationInfoDlg message handlers


void CRasterizationInfoDlg::Refresh(void)
{
	this->SendMessage(WM_NEW_COUNT);
}

UINT MyCountFunc(LPVOID lParam)
{
    HWND hDialogWnd = (HWND)lParam;

    for (int i=0; i < 100; ++i)
    {
        PostMessage(hDialogWnd, WM_NEW_COUNT, i, NULL);
    }

	return 0;
}

BOOL CRasterizationInfoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	CWinThread* pThread = AfxBeginThread(MyCountFunc, this->GetSafeHwnd());

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT CRasterizationInfoDlg::OnNewCount(WPARAM wParam, LPARAM)
{
    UpdateData(FALSE);
    return 0;
}

