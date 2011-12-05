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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewTree

CViewTree::CViewTree()
{
	m_bDragging = FALSE;
    m_pDragImgList = NULL;
    m_hitemDrag = NULL;
    m_hitemDrop = NULL;
}

CViewTree::~CViewTree()
{
}

BEGIN_MESSAGE_MAP(CViewTree, CTreeCtrl)
	ON_NOTIFY_REFLECT(TVN_BEGINDRAG, &CViewTree::OnTvnBegindrag)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
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


void CViewTree::OnTvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult)
{
	CPoint ptCurrent;
    
    GetCursorPos(&ptCurrent);
    ScreenToClient(&ptCurrent);

	m_bDragging = TRUE;
    m_hitemDrag = HitTest(ptCurrent);
    m_hitemDrop = NULL;

    m_pDragImgList = CreateDragImageEx(m_hitemDrag);
	m_pDragImgList->DragShowNolock(TRUE);
	m_pDragImgList->SetDragCursorImage(0, CPoint(0, 0));
	m_pDragImgList->BeginDrag(0, CPoint(0,0));
	m_pDragImgList->DragEnter(this, ptCurrent);
}


void CViewTree::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_bDragging)
	{
		HTREEITEM hitem;
		m_pDragImgList->DragMove(point);
		if ((hitem = HitTest(point)) != NULL)
		{
			m_pDragImgList->DragLeave(this);
			SelectDropTarget(hitem);
			m_hitemDrop = hitem;
			m_pDragImgList->DragEnter(this, point);
		}
	}

	CTreeCtrl::OnMouseMove(nFlags, point);
}


void CViewTree::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CRect rectWnd;
    GetWindowRect(rectWnd);    
	
    if (m_bDragging)
	{
		ASSERT(m_pDragImgList != NULL);
		m_pDragImgList->DragLeave(this);
		m_pDragImgList->EndDrag();
		delete m_pDragImgList;
		m_pDragImgList = NULL;

        /* I did this to resolve situations in my control where there could be ambiguity in whether or not an item could become a child of another item.  
		if (m_hitemDrag != m_hitemDrop && !IsChildNodeOf(m_hitemDrop, m_hitemDrag) &&
															GetParentItem(m_hitemDrag) != m_hitemDrop)
		{

            CMenu PopupMenu;
            PopupMenu.Detach();
            PopupMenu.CreatePopupMenu();
            PopupMenu.AppendMenu(MF_STRING, TVN_POPUP_MOVE_INTO , "Move Into");
            PopupMenu.AppendMenu(MF_STRING, TVN_POPUP_MOVE_AFTER, "Move After");
            PopupMenu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON | TPM_LEFTBUTTON, point.x + rectWnd.left, point.y + rectWnd.top, this);
			//TransferItem(m_hitemDrag, m_hitemDrop);
			//DeleteItem(m_hitemDrag);
		}
		else*/
        if(m_hitemDrag != m_hitemDrop && !IsChildNodeOf(m_hitemDrop, m_hitemDrag) &&
															GetParentItem(m_hitemDrag) != m_hitemDrop)
        {
            MoveItem(m_hitemDrag, m_hitemDrop);
        }
        else
			MessageBeep(0);

		ReleaseCapture();
		m_bDragging = FALSE;
		SelectDropTarget(NULL);

	}

	CTreeCtrl::OnLButtonUp(nFlags, point);
}

BOOL CViewTree::IsChildNodeOf(HTREEITEM hitemChild, HTREEITEM hitemSuspectedParent)
{
	do
	{
		if (hitemChild == hitemSuspectedParent)
			break;
	}
	while ((hitemChild = GetParentItem(hitemChild)) != NULL);

	return (hitemChild != NULL);
}

void CViewTree::MoveItem(HTREEITEM hitemToBeMoved, HTREEITEM hitemInsertAfter)
{
    TV_INSERTSTRUCT tvStruct;
    TCHAR cBuffer[50];
    HTREEITEM hNewItem;

    tvStruct.item.hItem = hitemToBeMoved;
    tvStruct.item.cchTextMax = 49;
    tvStruct.item.pszText = cBuffer;
    tvStruct.item.mask = TVIF_CHILDREN | TVIF_HANDLE | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT | TVIF_PARAM;
    GetItem(&tvStruct.item);
    tvStruct.hParent = GetParentItem(hitemInsertAfter);
    tvStruct.hInsertAfter = hitemInsertAfter;
    tvStruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT | TVIF_PARAM;

    hNewItem = InsertItem(&tvStruct);
    HTREEITEM hChild = GetChildItem(hitemToBeMoved);
    while(hChild != NULL)
    {
        TransferItem(hChild, hNewItem);
        DeleteItem(hChild);
        hChild = GetChildItem(hitemToBeMoved);
    }
    DeleteItem(hitemToBeMoved);
}

BOOL CViewTree::TransferItem(HTREEITEM hitemDrag, HTREEITEM hitemDrop) //Used to transfer items to a new parent.
{
	TV_INSERTSTRUCT     tvstruct;
	TCHAR               sztBuffer[50];
	HTREEITEM           hNewItem, hFirstChild;

		// avoid an infinite recursion situation
	tvstruct.item.hItem = hitemDrag;
	tvstruct.item.cchTextMax = 49;
	tvstruct.item.pszText = sztBuffer;
	tvstruct.item.mask = TVIF_CHILDREN | TVIF_HANDLE | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT | TVIF_PARAM;
	GetItem(&tvstruct.item);  // get information of the dragged element
	tvstruct.hParent = hitemDrop;
	tvstruct.hInsertAfter = TVI_LAST;
	tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT | TVIF_PARAM;
	hNewItem = InsertItem(&tvstruct);

	while ((hFirstChild = GetChildItem(hitemDrag)) != NULL)
	{
		TransferItem(hFirstChild, hNewItem);  // recursively transfer all the items
		DeleteItem(hFirstChild);        // delete the first child and all its children
	}
	return TRUE;
}

CImageList* CViewTree::CreateDragImageEx(HTREEITEM hItem)
{
	if(GetImageList(TVSIL_NORMAL) != NULL)
		return CreateDragImage(hItem);

	CRect rect;
	GetItemRect(hItem, rect, TRUE);
	rect.top = rect.left = 0;

	// Create bitmap
	CClientDC	dc (this);
	CDC 		memDC;	

	if(!memDC.CreateCompatibleDC(&dc))
		return NULL;

	CBitmap bitmap;
	if(!bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height()))
		return NULL;

	CBitmap* pOldMemDCBitmap = memDC.SelectObject( &bitmap );
	CFont* pOldFont = memDC.SelectObject(GetFont());

	memDC.FillSolidRect(&rect, RGB(0, 255, 0)); // Here green is used as mask color
	memDC.SetTextColor(GetSysColor(COLOR_GRAYTEXT));
	memDC.TextOut(rect.left, rect.top, GetItemText(hItem));

	memDC.SelectObject( pOldFont );
	memDC.SelectObject( pOldMemDCBitmap );

	// Create imagelist
	CImageList* pImageList = new CImageList;
	pImageList->Create(rect.Width(), rect.Height(), 
	 ILC_COLOR | ILC_MASK, 0, 1);
	pImageList->Add(&bitmap, RGB(0, 255, 0)); // Here green is used as mask color

	return pImageList;
}