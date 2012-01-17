// UsefulSplitterWnd.cpp : implementation file
//

#include "stdafx.h"
#include "UsefulSplitterWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//The CUsefulSplitterWnd class primary extened use is for Replacing Views.
//In the function CUsefulSplitterWnd::ReplaceView pDoc->AutoDelete has to be changed to prevent
//the one and only doc object from being deleted.
/////////////////////////////////////////////////////////////////////////////
// CUsefulSplitterWnd

CUsefulSplitterWnd::CUsefulSplitterWnd()
{
	m_bBarLocked=FALSE;
	m_nHidedCol = -1;
}

CUsefulSplitterWnd::~CUsefulSplitterWnd()
{
}


BEGIN_MESSAGE_MAP(CUsefulSplitterWnd, CSplitterWnd)
	//{{AFX_MSG_MAP(CUsefulSplitterWnd)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CUsefulSplitterWnd message handlers

void CUsefulSplitterWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (!m_bBarLocked)
		CSplitterWnd::OnLButtonDown(nFlags, point);
}

void CUsefulSplitterWnd::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (!m_bBarLocked) {
		CSplitterWnd::OnMouseMove(nFlags, point);
	} else
		CWnd::OnMouseMove(nFlags, point);
}

BOOL CUsefulSplitterWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	if (!m_bBarLocked)
		return CWnd::OnSetCursor(pWnd, nHitTest, message);

	return CSplitterWnd::OnSetCursor(pWnd, nHitTest, message);
}

BOOL CUsefulSplitterWnd::ReplaceView(int row, int col,CRuntimeClass * pViewClass)
{
	CCreateContext context;
	BOOL bSetActive;
	
	if ((GetPane(row,col)->IsKindOf(pViewClass))==TRUE)
		return FALSE;
	
	// Get pointer to CDocument object so that it can be used in the creation 
	// process of the new view
	CDocument * pDoc= ((CView *)GetPane(row,col))->GetDocument();
	CView * pActiveView=GetParentFrame()->GetActiveView();
	if (pActiveView==NULL || pActiveView==GetPane(row,col))
		bSetActive=TRUE;
	else
		bSetActive=FALSE;

	// set flag so that document will not be deleted when view is destroyed
	pDoc->m_bAutoDelete=FALSE;    
	// Delete existing view 
	SIZE size;
	int x,y;
	GetColumnInfo(col,x,y);
	size.cx = x - 10;
	GetRowInfo(row,x,y);
	size.cy = x;
	((CView *) GetPane(row,col))->DestroyWindow();
	// set flag back to default 
	pDoc->m_bAutoDelete=TRUE;

	// Create new view                      

	context.m_pNewViewClass=pViewClass;
	context.m_pCurrentDoc=pDoc;
	context.m_pNewDocTemplate=NULL;
	context.m_pLastView=NULL;
	context.m_pCurrentFrame=NULL;

	CreateView(row,col,pViewClass,size, &context);

	CView * pNewView= (CView *)GetPane(row,col);

	if (bSetActive==TRUE)
		GetParentFrame()->SetActiveView(pNewView);

	RecalcLayout(); 
	GetPane(row,col)->SendMessage(WM_PAINT);
	
	return TRUE;
}
    
void CUsefulSplitterWnd::ShowColumn()
{
	ASSERT_VALID(this);
	ASSERT(m_nCols < m_nMaxCols);
	ASSERT(m_nHidedCol != -1);

	int colNew = m_nHidedCol;
	m_nHidedCol = -1;
	int cxNew = m_pColInfo[m_nCols].nCurSize;
	m_nCols++;    // add a column
	ASSERT(m_nCols == m_nMaxCols);

	// fill the hidden column
	int col;
	for (int row = 0; row < m_nRows; row++)
	{
		CWnd* pPaneShow = GetDlgItem(
			AFX_IDW_PANE_FIRST + row * 16 + m_nCols);
		ASSERT(pPaneShow != NULL);
		pPaneShow->ShowWindow(SW_SHOWNA);

		for (col = m_nCols - 2; col >= colNew; col--)
		{
			CWnd* pPane = GetPane(row, col);
			ASSERT(pPane != NULL);
			pPane->SetDlgCtrlID(IdFromRowCol(row, col + 1));
		}

		pPaneShow->SetDlgCtrlID(IdFromRowCol(row, colNew));
	}

	// new panes have been created -- recalculate layout
	for (col = colNew + 1; col < m_nCols; col++)
		m_pColInfo[col].nIdealSize = m_pColInfo[col - 1].nCurSize;
	m_pColInfo[colNew].nIdealSize = cxNew;
	RecalcLayout();
}

void CUsefulSplitterWnd::HideColumn(int colHide)
{
	ASSERT_VALID(this);
	ASSERT(m_nCols > 1);
	ASSERT(colHide < m_nCols);
	ASSERT(m_nHidedCol == -1);
	m_nHidedCol = colHide;

	// if the column has an active window -- change it
	int rowActive, colActive;
	if (GetActivePane(&rowActive, &colActive) != NULL &&
		colActive == colHide)
	{
		if (++colActive >= m_nCols)
			colActive = 0;
		SetActivePane(rowActive, colActive);
	}

	// hide all column panes
	for (int row = 0; row < m_nRows; row++)
	{
		CWnd* pPaneHide = GetPane(row, colHide);
		ASSERT(pPaneHide != NULL);
		pPaneHide->ShowWindow(SW_HIDE);
		pPaneHide->SetDlgCtrlID(
			AFX_IDW_PANE_FIRST + row * 16 + m_nCols);

		for (int col = colHide + 1; col < m_nCols; col++)
		{
			CWnd* pPane = GetPane(row, col);
			ASSERT(pPane != NULL);
			pPane->SetDlgCtrlID(IdFromRowCol(row, col - 1));
		}
	}
	m_nCols--;
	m_pColInfo[m_nCols].nCurSize = m_pColInfo[colHide].nCurSize;
	RecalcLayout();
}