// DlgViewMatrix.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "DlgViewMatrix.h"
#include "afxdialogex.h"


// CDlgViewMatrix dialog

IMPLEMENT_DYNAMIC(CDlgViewMatrix, CDialogEx)

CDlgViewMatrix::CDlgViewMatrix(CCamera* node, CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgViewMatrix::IDD, pParent)
{
	root = node;
}

CDlgViewMatrix::~CDlgViewMatrix()
{
}

void CDlgViewMatrix::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgViewMatrix, CDialogEx)
END_MESSAGE_MAP()


// CDlgViewMatrix message handlers
