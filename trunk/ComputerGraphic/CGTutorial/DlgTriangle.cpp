// DlgTriangle.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "DlgTriangle.h"
#include "afxdialogex.h"


// CDlgTriangle dialog

IMPLEMENT_DYNAMIC(CDlgTriangle, CDialog)

CDlgTriangle::CDlgTriangle(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTriangle::IDD, pParent)
{

	m_X1 = 0.0f;
	m_Y1 = 0.0f;
	m_Z1 = 0.0f;
	m_X2 = 1.0f;
	m_Y2 = 0.0f;
	m_Z2 = 0.0f;
	m_X3 = 0.0f;
	m_Y3 = 1.0f;
	m_Z3 = 0.0f;
}

CDlgTriangle::CDlgTriangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTriangle::IDD, pParent)
{
	m_X1 = x1;
	m_X2 = x2;
	m_X3 = x3;
	m_Y1 = y1;
	m_Y2 = y2;
	m_Y3 = y3;
	m_Z1 = z1;
	m_Z2 = z2;
	m_Z3 = z3;
}

CDlgTriangle::~CDlgTriangle()
{
}

void CDlgTriangle::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
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


BEGIN_MESSAGE_MAP(CDlgTriangle, CDialog)
END_MESSAGE_MAP()


// CDlgTriangle message handlers