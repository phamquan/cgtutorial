#include "StdAfx.h"
#include "GenCodeView.h"

#ifndef SHARED_HANDLERS
#include "CGTutorial.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CGenCodeView

IMPLEMENT_DYNCREATE(CGenCodeView, CScrollView)

BEGIN_MESSAGE_MAP(CGenCodeView, CScrollView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGenCodeView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CGenCodeView construction/destruction

CGenCodeView::CGenCodeView()
{
	// TODO: add construction code here
}

CGenCodeView::~CGenCodeView()
{
	m_MemDC.DeleteDC();
	m_MemBitmap.DeleteObject();
}

BOOL CGenCodeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

// CGenCodeView drawing

void CGenCodeView::OnDraw(CDC* pDC)
{
	CCGTutorialDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	CRect rect;
	GetClientRect(&rect);

	m_MemDC.FillSolidRect(rect, RGB(255,255,255));

	/*CStringArray strarr;
	strarr.Copy(GetDocument()->openGLCode);
	for(int i=0; i<strarr.GetSize(); i++) {
		m_MemDC.TextOutW(10,10+20*i,strarr.GetAt(i));
	}*/

	m_MemDC.DrawTextW(GetDocument()->openGLCode,&rect,DT_LEFT);
	
	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&m_MemDC,0,0,SRCCOPY);

	// TODO: add draw code for native data here
}


// CGenCodeView printing


void CGenCodeView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CGenCodeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGenCodeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGenCodeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CGenCodeView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CGenCodeView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CGenCodeView diagnostics

#ifdef _DEBUG
void CGenCodeView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CGenCodeView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CCGTutorialDoc* CGenCodeView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCGTutorialDoc)));
	return (CCGTutorialDoc*)m_pDocument;
}
#endif //_DEBUG


// CGenCodeView message handlers
BOOL CGenCodeView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	return true;
}

void CGenCodeView::OnSize(UINT nType, int cx, int cy)
{
	CScrollView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	Invalidate();
}


int CGenCodeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	CClientDC dc(this);

	int MaxX = ::GetSystemMetrics(SM_CXSCREEN);
	int MaxY = ::GetSystemMetrics(SM_CYSCREEN);

	m_MemDC.CreateCompatibleDC(&dc);
	m_MemBitmap.CreateCompatibleBitmap(&dc,MaxX,MaxY);

	m_OldBitmap = m_MemDC.SelectObject(&m_MemBitmap);

	SetScrollSizes(MM_TEXT,CSize(500,10));

	return 0;
}
