// DlgCamera.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "DlgCamera.h"
#include "afxdialogex.h"


// CDlgCamera dialog

IMPLEMENT_DYNAMIC(CDlgCamera, CDialogEx)

CDlgCamera::CDlgCamera(float xpos, float ypos, float zpos, float xlook, float ylook, float zlook, float xup, float yup, float zup, CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgCamera::IDD, pParent)
{

	m_X1 = xpos;
	m_X2 = xlook;
	m_X3 = xup;
	m_Y1 = ypos;
	m_Y2 = ylook;
	m_Y3 = yup;
	m_Z1 = zpos;
	m_Z2 = zlook;
	m_Z3 = zup;
}

CDlgCamera::~CDlgCamera()
{
}

void CDlgCamera::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_X1, m_X1);
	DDX_Text(pDX, IDC_X2, m_X2);
	DDX_Text(pDX, IDC_X3, m_X3);
	DDX_Text(pDX, IDC_Y1, m_Y1);
	DDX_Text(pDX, IDC_Y2, m_Y2);
	DDX_Text(pDX, IDC_Y3, m_Y3);
	DDX_Text(pDX, IDC_Z1, m_Z1);
	DDX_Text(pDX, IDC_Z2, m_Z2);
	DDX_Text(pDX, IDC_Z3, m_Z3);
}


BEGIN_MESSAGE_MAP(CDlgCamera, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgCamera::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgCamera message handlers


void CDlgCamera::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CDialogEx::OnOK();
}
