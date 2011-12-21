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

#pragma once
#include "OpenGLNode.h"
/////////////////////////////////////////////////////////////////////////////
// CViewTree window

class CViewTree : public CTreeCtrl
{
// Construction
public:
	CViewTree();
	CMap<HTREEITEM,HTREEITEM,COpenGLNode*,COpenGLNode*> myMap;

// Overrides
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	BOOL m_bDragging;
	HTREEITEM m_hitemDrag;
    HTREEITEM m_hitemDrop;
	CImageList* m_pDragImgList;

	BOOL IsChildNodeOf(HTREEITEM hitemChild, HTREEITEM hitemSuspectedParent);
	void MoveItem(HTREEITEM hitemToBeMoved, HTREEITEM hitemInsertAfter);
	BOOL TransferItem(HTREEITEM hitemDrag, HTREEITEM hitemDrop);
	CImageList* CreateDragImageEx(HTREEITEM hItem);
// Implementation
public:
	virtual ~CViewTree();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
