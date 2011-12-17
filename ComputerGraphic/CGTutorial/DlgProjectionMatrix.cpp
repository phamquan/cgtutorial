#include "StdAfx.h"
#include "CGTutorial.h"
#include "DlgProjectionMatrix.h"

IMPLEMENT_DYNAMIC(CDlgProjectionMatrix, CDlgMatrix)

CDlgProjectionMatrix::CDlgProjectionMatrix(CProjection *proj, COpenGLNode* node, CWnd* pParent /*=NULL*/)
	: CDlgMatrix(pParent)
{
	projection = proj;
	root = node;
}

CDlgProjectionMatrix::~CDlgProjectionMatrix(void)
{
}

void CDlgProjectionMatrix::DoDataExchange(CDataExchange* pDX)
{
	CDlgMatrix::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDlgProjectionMatrix, CDlgMatrix)
	ON_WM_PAINT()
END_MESSAGE_MAP()

BOOL CDlgProjectionMatrix::OnInitDialog()
{
	CDlgMatrix::OnInitDialog();

	// TODO:  Add extra initialization here
	this->SetWindowTextW(CString("Projection Matrix"));
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgProjectionMatrix::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDlgMatrix::OnPaint() for painting messages
}
