#include "StdAfx.h"
#include "CGTutorial.h"
#include "DlgViewPort.h"

IMPLEMENT_DYNAMIC(CDlgViewPort, CDlgMatrix)

CDlgViewPort::CDlgViewPort(CViewPort* vp, CWnd* pParent /*=NULL*/)
	: CDlgMatrix(pParent)
{
	viewport = vp;
}

CDlgViewPort::~CDlgViewPort()
{
}

void CDlgViewPort::DoDataExchange(CDataExchange* pDX)
{
	CDlgMatrix::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgViewPort, CDlgMatrix)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgModelMatrix message handlers
BOOL CDlgViewPort::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	this->SetWindowTextW(CString("View port"));
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgViewPort::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialogEx::OnPaint() for painting messages
	int top = 0, left = 10;
		
	if(in->GetSize() == 0) {
		dc.TextOutW(left,top,CString("Select geometric object to view data"));
	} else {
		out->RemoveAll();
		for(int i=0; i<in->GetSize(); i++) {
			CPoint3D* p = (CPoint3D*)in->GetAt(i);
			char buf[128];
			_itoa_s(i+1,buf,10);
			CString name = CString("P") + buf + "''''";
			top += 100;
		}
	}
}