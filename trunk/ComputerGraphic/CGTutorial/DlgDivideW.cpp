#include "StdAfx.h"
#include "CGTutorial.h"
#include "DlgDivideW.h"

IMPLEMENT_DYNAMIC(CDlgDivideW, CDlgMatrix)

CDlgDivideW::CDlgDivideW(CWnd* pParent /*=NULL*/)
	: CDlgMatrix(pParent)
{
}

CDlgDivideW::~CDlgDivideW()
{
}

void CDlgDivideW::DoDataExchange(CDataExchange* pDX)
{
	CDlgMatrix::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgDivideW, CDlgMatrix)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgModelMatrix message handlers
BOOL CDlgDivideW::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	this->SetWindowTextW(CString("Divide W"));
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgDivideW::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialogEx::OnPaint() for painting messages
	int top = 0, left = 10;
		
	if(in->GetSize() == 0) {
		dc.TextOutW(left,top,CString("Select geometric object to view data"));
	} else {
		for(int i=0; i<in->GetSize(); i++) {
			CPoint3D* p = (CPoint3D*)in->GetAt(i);
			char buf[128];
			itoa(i+1,buf,10);
			CString name = CString("P") + buf + "'''";
			if(p->getW() == 1)
				ShowPoint(&dc,name,*p,top,left);
			else
				ShowPointPoint(&dc,name,*p,CPoint3D(p->getX()/p->getW(),p->getY()/p->getW(),p->getZ()/p->getW()),top,left);
			top += 100;
		}
	}
}