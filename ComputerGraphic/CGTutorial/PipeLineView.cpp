// GenCode.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "PipeLineView.h"


// CGenCode

IMPLEMENT_DYNCREATE(CPipeLineView, CFormView)

CPipeLineView::CPipeLineView()
	: CFormView(CPipeLineView::IDD)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif
	object = NULL;
	camera = new CPtrArray();
	world = new CPtrArray();
	clipping = new CPtrArray();
	divide = new CPtrArray();
	window = new CPtrArray();
	inited = FALSE;
	modelDlg = NULL;
}

CPipeLineView::~CPipeLineView()
{
	delete camera;
	delete world;
	delete clipping;
	delete divide;
	delete window;

	delete modelDlg;
	delete viewDlg;
	delete projectionDlg;
	delete divideWDlg;
	delete viewPortDlg;
}

void CPipeLineView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPipeLineView, CFormView)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CPipeLineView::OnSelchangeTab1)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CGenCode diagnostics

#ifdef _DEBUG
void CPipeLineView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPipeLineView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CGenCode message handlers
CCGTutorialDoc* CPipeLineView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCGTutorialDoc)));
	return (CCGTutorialDoc*)m_pDocument;
}

void CPipeLineView::SetData(COpenGLNode* in) {
	object = in;

	modelDlg->Refresh(object);
	viewDlg->Refresh();
	projectionDlg->Refresh();
	divideWDlg->Refresh();
	viewPortDlg->Refresh();
}

void CPipeLineView::OnSize(UINT nType, int cx, int cy)
{
	//CFormView::OnSize(nType, cx, cy);

	CTabCtrl* edit = (CTabCtrl*)GetDlgItem(IDC_TAB1);
	if(edit != NULL) {
		edit->MoveWindow(5,5,cx-10,cy-10);
		CRect TabRect;
		edit->GetClientRect(&TabRect);
		if(modelDlg == NULL) {
			edit->InsertItem(0,CString("Model Matrix"), -1);
			edit->InsertItem(1,CString("View Matrix"), -1);
			edit->InsertItem(2,CString("Projection Matrix"), -1);
			edit->InsertItem(3,CString("Divide W"), -1);
			edit->InsertItem(4,CString("View Port"), -1);

			edit->AdjustRect(FALSE, &TabRect);

			environment = GetDocument()->environment;
			modelDlg = new CDlgModelMatrix(camera);
			viewDlg = new CDlgViewMatrix(environment,camera,world);
			projectionDlg = new CDlgProjectionMatrix(environment,world,clipping);
			divideWDlg = new CDlgDivideW(clipping,divide);
			viewPortDlg = new CDlgViewPortMatrix(environment,divide,window);

			modelDlg->Create(CDlgMatrix::IDD,edit);
			//modelDlg->MoveWindow(TabRect);
			modelDlg->ShowWindow(SW_SHOW);

			viewDlg->Create(CDlgMatrix::IDD,edit);
			//viewDlg->MoveWindow(TabRect);

			projectionDlg->Create(CDlgMatrix::IDD,edit);
			//projectionDlg->MoveWindow(TabRect);

			divideWDlg->Create(CDlgMatrix::IDD,edit);
			//divideWDlg->MoveWindow(TabRect);

			viewPortDlg->Create(CDlgMatrix::IDD,edit);
			//viewPortDlg->MoveWindow(TabRect);

			SetData(NULL);
		}
		TabRect.left = 5;
		TabRect.top = 25;
		TabRect.right -= 5;
		TabRect.bottom -= 5;
		modelDlg->MoveWindow(TabRect);
		viewDlg->MoveWindow(TabRect);
		projectionDlg->MoveWindow(TabRect);
		divideWDlg->MoveWindow(TabRect);
		viewPortDlg->MoveWindow(TabRect);
		viewPortDlg->Refresh();
	}
}

void CPipeLineView::OnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	CTabCtrl* edit = (CTabCtrl*)GetDlgItem(IDC_TAB1);
	switch(edit->GetCurSel()) {
	case 0:
		modelDlg->ShowWindow(SW_SHOW);
		viewDlg->ShowWindow(SW_HIDE);
		projectionDlg->ShowWindow(SW_HIDE);
		divideWDlg->ShowWindow(SW_HIDE);
		viewPortDlg->ShowWindow(SW_HIDE);
		break;
	case 1:
		modelDlg->ShowWindow(SW_HIDE);
		viewDlg->ShowWindow(SW_SHOW);
		projectionDlg->ShowWindow(SW_HIDE);
		divideWDlg->ShowWindow(SW_HIDE);
		viewPortDlg->ShowWindow(SW_HIDE);
		break;
	case 2:
		modelDlg->ShowWindow(SW_HIDE);
		viewDlg->ShowWindow(SW_HIDE);
		projectionDlg->ShowWindow(SW_SHOW);
		divideWDlg->ShowWindow(SW_HIDE);
		viewPortDlg->ShowWindow(SW_HIDE);
		break;	
	case 3:
		modelDlg->ShowWindow(SW_HIDE);
		viewDlg->ShowWindow(SW_HIDE);
		projectionDlg->ShowWindow(SW_HIDE);
		divideWDlg->ShowWindow(SW_SHOW);
		viewPortDlg->ShowWindow(SW_HIDE);
		break;
	case 4:
		modelDlg->ShowWindow(SW_HIDE);
		viewDlg->ShowWindow(SW_HIDE);
		projectionDlg->ShowWindow(SW_HIDE);
		divideWDlg->ShowWindow(SW_HIDE);
		viewPortDlg->ShowWindow(SW_SHOW);
		break;
	}
	*pResult = 0;
}