#include "StdAfx.h"
#include "CGTutorial.h"
#include "DlgViewPortMatrix.h"
#include "MainFrm.h"

IMPLEMENT_DYNAMIC(CDlgViewPortMatrix, CDlgMatrix)

CDlgViewPortMatrix::CDlgViewPortMatrix(CEnvironment *env, CPtrArray* in, CPtrArray* out, CWnd* pParent /*=NULL*/)
	: CDlgMatrix(pParent)
{
	environment = env;
	this->in = in;
	this->out = out;
}

CDlgViewPortMatrix::~CDlgViewPortMatrix()
{
}

void CDlgViewPortMatrix::DoDataExchange(CDataExchange* pDX)
{
	CDlgMatrix::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgViewPortMatrix, CDlgMatrix)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgModelMatrix message handlers
BOOL CDlgViewPortMatrix::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	this->SetWindowTextW(CString("View port"));
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgViewPortMatrix::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialogEx::OnPaint() for painting messages
	int top = 0, left = 10;
		
	if(in->GetSize() == 0) {
		dc.TextOutW(left,top,CString("Select geometric object to view data"));
	} else {
		char buf[128];
		dc.TextOutW(left,top+10,CString("x'''' = left + (x'''+1)*width/2"));
		top+=30;
		dc.TextOutW(left,top+10,CString("y'''' = bottom + (y'''+1)*height/2"));
		top+=30;
		sprintf_s(buf,"left = %d, bottom = %d, width = %d, height = %d",rect.left,rect.bottom,rect.right,rect.top);
		dc.TextOutW(left,top+10,CString(buf));
		top+=30;

		for(int i=0; i<in->GetSize(); i++) {
			CPoint3D* p = (CPoint3D*)in->GetAt(i);
			char buf[128];
			sprintf_s(buf,"P%d''''",i+1);
			ShowPoint(&dc,CString(buf),*((CPoint3D*)out->GetAt(i)),top,left);
			top+=100;
		}
	}
}

void CDlgViewPortMatrix::Refresh() {
	out->RemoveAll();
	
	environment->GetViewPort()->GetData(x1,y1,x2,y2,type);
	if(type == VIEWPORT_DEFAULT) {
		((CMainFrame*)AfxGetMainWnd())->cameraView->GetClientRect(&rect);
		rect.right = rect.Width();
		rect.top = rect.Height();
		rect.left = 0;
		rect.bottom = 0;
	} else {
		rect.left = x1;
		rect.bottom = y1;
		rect.right = x2;
		rect.top = y2;
	}

	for(int i=0; i<in->GetSize(); i++) {
		CPoint3D* p = (CPoint3D*)in->GetAt(i);
		out->Add(new CPoint3D(rect.left + (p->getX()+1)*rect.right/2, rect.bottom + (p->getY()+1)*rect.top/2, 0));
	}

	Invalidate();
}