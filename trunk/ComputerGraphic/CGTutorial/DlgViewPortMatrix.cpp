// DlgViewPort.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "MainFrm.h"
#include "DlgViewPortMatrix.h"


// CDlgViewPort dialog

IMPLEMENT_DYNAMIC(CDlgViewPortMatrix, CDlgMatrix)

CDlgViewPortMatrix::CDlgViewPortMatrix(CEnvironment *environment, CWnd* pParent /*=NULL*/)
	: CDlgMatrix(pParent)
{
	this->environment = environment;
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


// CDlgViewPort message handlers
void CDlgViewPortMatrix::Refresh()
{
	int type;

	environment->GetViewPort()->GetData(x,y,w,h,type);
	if(type == VIEWPORT_DEFAULT)
	{
		CSize s = ((CMainFrame*)AfxGetMainWnd())->GetViewPort();
		x = y = 0;
		w = s.cx;
		h = s.cy;
	}

	sum[0] = w/2;	sum[4] = 0;		sum[8] = 0;		sum[12] = x+w/2;
	sum[1] = 0;		sum[5] = h/2;	sum[9] = 0;		sum[13] = y+h/2;
	sum[2] = 0;		sum[6] = 0;		sum[10] = 0;	sum[14] = 0;
	sum[3] = 0;		sum[7] = 0;		sum[11] = 0;	sum[15] = 0;

	Invalidate();
}

void CDlgViewPortMatrix::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDlgMatrix::OnPaint() for painting messages
	dc.SetBkMode( TRANSPARENT );
	char buf[128];
	sprintf_s(buf,"left = %5.2f, bottom = %5.2f, width = %5.2f, height = %5.2f",x,y,w,h);
	dc.TextOut(10,10,CString(buf));

	int top=30, left = 10;
	CString data[16] = {CString("width/2"), CString("0.000"), CString("0.000"), CString("0.000"),
						CString("0.000"), CString("height/2"), CString("0.000"), CString("0.000"),
						CString("0.000"), CString("0.000"), CString ("0.000"), CString("0.000"),
						CString("left + width/2"), CString("bottom + height/2"), CString("0.000"), CString("0.000")};

	ShowMatrixMatrix(&dc,CString("VP"),data,sum,top,left);
}
