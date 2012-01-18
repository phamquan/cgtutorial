// GenCode.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "GenCode.h"


// CGenCode

IMPLEMENT_DYNCREATE(CGenCode, CFormView)

CGenCode::CGenCode()
	: CFormView(CGenCode::IDD)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

	m_ShowCode = _T("");
}

CGenCode::~CGenCode()
{
}

void CGenCode::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_ShowCode);
}

BEGIN_MESSAGE_MAP(CGenCode, CFormView)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CGenCode diagnostics

#ifdef _DEBUG
void CGenCode::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CGenCode::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CGenCode message handlers
CCGTutorialDoc* CGenCode::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCGTutorialDoc)));
	return (CCGTutorialDoc*)m_pDocument;
}

void CGenCode::OnSize(UINT nType, int cx, int cy)
{
	//CFormView::OnSize(nType, cx, cy);

	CWnd* edit = GetDlgItem(IDC_EDIT1);
	if(edit != NULL)
		edit->MoveWindow(0,0,cx,cy);
}

void CGenCode::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: Add your specialized code here and/or call the base class
	m_ShowCode = GetDocument()->openGLCode;
	UpdateData(FALSE);
}


BOOL CGenCode::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: Add your specialized code here and/or call the base class
	BOOL result = CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
	m_ShowCode = GetDocument()->openGLCode;
	UpdateData(FALSE);
	return result;
}
