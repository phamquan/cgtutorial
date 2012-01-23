// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://msdn.microsoft.com/officeui.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

#include "stdafx.h"
#include "ViewTree.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewTree

CViewTree::CViewTree()
{
	m_boDragging   = false;
	m_pDragImgList = NULL;
}

CViewTree::~CViewTree()
{
	delete m_pDragImgList;
}

BEGIN_MESSAGE_MAP(CViewTree, CTreeCtrl)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_NOTIFY_REFLECT(TVN_BEGINDRAG, &CViewTree::OnTvnBegindrag)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEWHEEL()
	ON_WM_TIMER()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewTree message handlers

BOOL CViewTree::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	BOOL bRes = CTreeCtrl::OnNotify(wParam, lParam, pResult);

	NMHDR* pNMHDR = (NMHDR*)lParam;
	ASSERT(pNMHDR != NULL);

	if (pNMHDR && pNMHDR->code == TTN_SHOW && GetToolTips() != NULL)
	{
		GetToolTips()->SetWindowPos(&wndTop, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
	}

	return bRes;
}


void CViewTree::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CTreeCtrl::OnLButtonDown(nFlags, point);
	((CMainFrame*)AfxGetMainWnd())->Refresh();
}


BOOL CViewTree::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: Add your message handler code here and/or call default
	if(m_pDragImgList)
		m_pDragImgList->DragShowNolock(false);
	
	BOOL Res = CTreeCtrl::OnMouseWheel(nFlags, zDelta, pt);
	
	if(m_pDragImgList)
		m_pDragImgList->DragShowNolock(true);
	
	return Res;
}

void CViewTree::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if(m_boDragging)
	{
		/*TVHITTESTINFO tvHit;
		tvHit.pt = point;*/
		HTREEITEM hTarget = HitTest(point);

		if(hTarget)
		{
			if(hTarget != m_hDragTarget)
			{                                                     // this test avoids flickering
				m_pDragImgList->DragShowNolock(false);
				SelectDropTarget(hTarget);
				m_pDragImgList->DragShowNolock(true);
				m_hDragTarget = hTarget;
			}
		}

		// move image being dragged
		m_pDragImgList->DragMove(point);
	}
	CTreeCtrl::OnMouseMove(nFlags, point);
}


void CViewTree::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if(m_boDragging)
	{
		KillTimer(1);

		ReleaseCapture();
		ShowCursor(true);
		m_boDragging = false;

		m_pDragImgList->DragLeave(this);
		m_pDragImgList->EndDrag();
		delete m_pDragImgList;
		m_pDragImgList = NULL;

		SelectDropTarget(NULL);
		SelectItem(m_hDragItem);

		if(m_hDragTarget && (m_hDragTarget != m_hDragItem))
		{
			SuccessfulDrag(m_hDragTarget,m_hDragItem);
		}
	}   
	CTreeCtrl::OnLButtonUp(nFlags, point);
}


void CViewTree::OnTvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_hDragItem = ((NM_TREEVIEW*)pNMHDR)->itemNew.hItem;
	m_hDragTarget = NULL;

	if(m_hDragItem == NULL)
		return;

	SelectItem(m_hDragItem);
	m_pDragImgList = CreateDragImage(m_hDragItem);
	
	if(m_pDragImgList == NULL)
		return;
  
	m_pDragImgList->BeginDrag(0,CPoint(0,0));
	m_pDragImgList->DragEnter(this,((NM_TREEVIEW*)pNMHDR)->ptDrag);
	m_boDragging = true;

	ShowCursor(false);
	SetCapture();

	SetTimer(1,25,NULL);
	*pResult = 0;
}

void CViewTree::SuccessfulDrag(HTREEITEM hDest,HTREEITEM hSrc)
{
	// test : no op if hSrc is already a child of hDest
	if(GetParentItem(hSrc) == hDest)
		return;

	// test : if hDest is a child of hSrc, we're going to have a stack overflow ! (infinite loop)
	HTREEITEM hParent = hDest;
	while(hParent)
	{
		if(hParent == hSrc)
		{
			return;
		}
		hParent = GetParentItem(hParent);
	}

	COpenGLNode *source, *dest;
	myMap.Lookup(hSrc,source);
	myMap.Lookup(hDest,dest);
	int id = source->ID;
	if(id == NODE_OBJECT || id == NODE_ENVIRONMENT || id == NODE_CAMERA || id == NODE_PROJECTION || id == NODE_VIEWPORT)
		return;

	id = dest->ID;
	if(id != NODE_OBJECT && id != NODE_TRANSLATE && id != NODE_SCALE && id != NODE_ROTATE)
		return;

	COpenGLNode *parent = source->parent;
	parent->RemoveChild(source,FALSE);
	dest->AddChild(source);

	// create a copy of the source subtree
	HTREEITEM hNew = InsertItemAndSubtree(hDest,hSrc);
	SelectItem   (hNew);
	EnsureVisible(hNew);
	DeleteItem   (hSrc);

	((CMainFrame*)AfxGetMainWnd())->Refresh();
}


void CViewTree::CopyItem(HTREEITEM hDest,HTREEITEM hSrc)
{
	TV_ITEM tvSrc;
	tvSrc.mask  = TVIF_HANDLE | TVIF_PARAM | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_STATE;
	tvSrc.hItem = hSrc;
	if(!GetItem(&tvSrc))
		return;

	tvSrc.hItem = hDest;
	SetItem(&tvSrc);
	SetItemText(hDest,GetItemText(hSrc));
	SetCheck   (hDest,GetCheck   (hSrc));

	if(tvSrc.state & TVIS_EXPANDED)
		Expand(hDest,TVE_EXPAND);
}

void CViewTree::CopySubtree(HTREEITEM hDest,HTREEITEM hSrc)
{
	HTREEITEM hChildSrc = GetChildItem(hSrc);
	while(hChildSrc)
	{
		HTREEITEM   hChildDest = InsertItem(CString("dest child"),hDest);

		COpenGLNode* node;
		myMap.Lookup(hChildSrc,node);
		myMap.RemoveKey(hChildSrc);
		myMap.SetAt(hChildDest,node);

		CopySubtree(hChildDest,hChildSrc);
		CopyItem   (hChildDest,hChildSrc);

		hChildSrc = GetNextSiblingItem(hChildSrc);
	}
}

HTREEITEM CViewTree::InsertItemAndSubtree(HTREEITEM hDest,HTREEITEM hSrc)
{
	HTREEITEM hNew = InsertItem(CString("new"),hDest);			//insert new node into dest

	COpenGLNode* node;
	myMap.Lookup(hSrc,node);
	myMap.RemoveKey(hSrc);
	myMap.SetAt(hNew,node);

	CopySubtree(hNew,hSrc);                                   // start with subtree so that item is correctly expanded
	CopyItem   (hNew,hSrc);
	return hNew;
}


void CViewTree::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if(m_boDragging)
	{
		POINT point;
		GetCursorPos(&point);
		ScreenToClient(&point);

		// highlight target
		TVHITTESTINFO tvHit;
		tvHit.pt = point;
		HTREEITEM hTarget = HitTest(&tvHit);

		if(hTarget)
		{
			if(hTarget != m_hDragTarget)
			{                                                     // this test avoids flickering
				m_pDragImgList->DragShowNolock(false);
				EnsureVisible(hTarget);
				SelectDropTarget(hTarget);
				m_pDragImgList->DragShowNolock(true);
				m_hDragTarget = hTarget;
			}
		}
		else // scroll tree
		{
			RECT rect;
			GetClientRect(&rect);

			int iMaxV = GetScrollLimit(SB_VERT);
			int iPosV = GetScrollPos  (SB_VERT);

			// up
			if((point.y < rect.top -10) && iPosV)
			{
				HTREEITEM hPrev = GetPrevVisibleItem(GetFirstVisibleItem());
				m_pDragImgList->DragShowNolock(false);
				EnsureVisible(hPrev);
				m_pDragImgList->DragShowNolock(true);
			}

			// down
			if((point.y > rect.bottom +10) && (iPosV != iMaxV))
			{
				UINT Nb = GetVisibleCount();
				if(Nb != -1)
				{
					HTREEITEM hNext = GetFirstVisibleItem();
					for(UINT i = 0; i < Nb; i++) hNext = GetNextVisibleItem(hNext);
					m_pDragImgList->DragShowNolock(false);
					EnsureVisible(hNext);
					m_pDragImgList->DragShowNolock(true);
				}
			}

			int iPosH = GetScrollPos  (SB_HORZ);
			int iMaxH = GetScrollLimit(SB_HORZ);

			// left
			if((point.x < rect.left) && iPosH)
			{
				m_pDragImgList->DragShowNolock(false);
				SendMessage(WM_HSCROLL,SB_LINELEFT);
				m_pDragImgList->DragShowNolock(true);
			}

			// right
			if((point.x > rect.right) && (iPosH != iMaxH))
			{
				m_pDragImgList->DragShowNolock(false);
				SendMessage(WM_HSCROLL,SB_LINERIGHT);
				m_pDragImgList->DragShowNolock(true);
			}
		}

		m_pDragImgList->DragMove(point);
	}
	CTreeCtrl::OnTimer(nIDEvent);
}
