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

#include "ViewTree.h"
#include "../qtml/tinyxml.h"
#include "Translate.h"
#include "Rotate.h"
#include "Scale.h"
#include "Line.h"
#include "Rectangle.h"
#include "Point4D.h"

class CFileViewToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CFileView : public CDockablePane
{
// Construction
public:
	CFileView();

	void AdjustLayout();
	void OnChangeVisualStyle();
	void FillView(TiXmlNode *troot, COpenGLNode *oroot);
	void FillView(COpenGLNode *oroot);

// Attributes
protected:
	CViewTree m_wndFileView;
	CImageList m_FileViewImages;
	CFileViewToolBar m_wndToolBar;

protected:
	void FillFile(TiXmlNode *root, HTREEITEM hparrent, COpenGLNode *oparrent);
	COpenGLNode *XmltoOpenGL(TiXmlNode *node);
	void AddNode(COpenGLNode *newNode);

	HTREEITEM hTreeItem;
	COpenGLNode *node;

	BOOLEAN lockAdd;
	BOOLEAN lockDelete;
// Implementation
public:
	virtual ~CFileView();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnAddLine();
	afx_msg void OnAddRectangle();
	afx_msg void OnObjectDelete();
};

