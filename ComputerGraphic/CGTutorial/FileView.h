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
#include "Environment.h"

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
	void FillView(TiXmlNode* tobject, TiXmlNode* tenvironment, COpenGLNode* oobject, CEnvironment* oenvironment);
	void FillView(COpenGLNode* object, COpenGLNode* environment);
	void AddNode(COpenGLNode *newNode, BOOL isGeometric, BOOL toParent=FALSE);
	COpenGLNode* GetObject();
	//COpenGLNode* GetGeometric();
// Attributes
protected:
	CViewTree m_wndFileView;
	CImageList m_FileViewImages;
	CFileViewToolBar m_wndToolBar;
	CMenu *contextMenu;

	BOOL ToParent();
	const char* GetValue(char* name,TiXmlNode* node);
	void FillFile(TiXmlNode *root, HTREEITEM hparrent, COpenGLNode *oparrent);
	COpenGLNode *XmltoOpenGL(TiXmlNode *node);

	HTREEITEM hTreeItem;
	COpenGLNode *node;

	HTREEITEM environment;
	HTREEITEM object;

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
	afx_msg void OnTransformationTranslate();
	afx_msg void OnTransformationRotate();
	afx_msg void OnTransformationScale();
	afx_msg void OnFileviewEdit();
	afx_msg void OnFileviewDelete();
};

