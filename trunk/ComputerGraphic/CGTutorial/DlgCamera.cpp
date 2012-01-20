// DlgCamera.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "DlgCamera.h"
#include "afxdialogex.h"


// CDlgCamera dialog

IMPLEMENT_DYNAMIC(CDlgCamera, CDialog)

CDlgCamera::CDlgCamera(float xpos, float ypos, float zpos, float xlook, float ylook, float zlook, float xup, float yup, float zup, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCamera::IDD, pParent)
{

	m_EX = xpos;
	m_EY = ypos;
	m_EZ = zpos;
	m_RX = xlook;
	m_RY = ylook;
	m_RZ = zlook;
	m_UX = xup;
	m_UY = yup;
	m_UZ = zup;
}

CDlgCamera::~CDlgCamera()
{
}

void CDlgCamera::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EX, m_EX);
	DDX_Text(pDX, IDC_EY, m_EY);
	DDX_Text(pDX, IDC_EZ, m_EZ);
	DDX_Text(pDX, IDC_RX, m_RX);
	DDX_Text(pDX, IDC_RY, m_RY);
	DDX_Text(pDX, IDC_RZ, m_RZ);
	DDX_Text(pDX, IDC_UX, m_UX);
	DDX_Text(pDX, IDC_UY, m_UY);
	DDX_Text(pDX, IDC_UZ, m_UZ);
}


BEGIN_MESSAGE_MAP(CDlgCamera, CDialog)
END_MESSAGE_MAP()


// CDlgCamera message handlers
