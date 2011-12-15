// DlgViewMatrix.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "DlgViewMatrix.h"


// CDlgViewMatrix dialog

IMPLEMENT_DYNAMIC(CDlgViewMatrix, CDlgMatrix)

CDlgViewMatrix::CDlgViewMatrix(CCamera* node, CWnd* pParent /*=NULL*/)
	: CDlgMatrix(pParent)
{
	root = node;
}

CDlgViewMatrix::~CDlgViewMatrix()
{
}

void CDlgViewMatrix::DoDataExchange(CDataExchange* pDX)
{
	CDlgMatrix::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgViewMatrix, CDlgMatrix)
END_MESSAGE_MAP()


// CDlgViewMatrix message handlers
