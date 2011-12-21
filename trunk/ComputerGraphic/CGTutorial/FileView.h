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
#include "Translate.h"
#include "Rotate.h"
#include "Scale.h"
#include "Color.h"
#include "Line.h"
#include "Rectangle.h"
#include "Point4D.h"

#include "DlgModelMatrix.h"
#include "DlgViewMatrix.h"
#include "DlgProjectionMatrix.h"
#include "DlgProjection.h"
#include "DlgCamera.h"
#include "DlgRotate.h"
#include "DlgPoint.h"
#include "DlgLine.h"
#include "DlgRectangle.h"

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

	void ShowModelMatrix();
	void ShowViewMatrix();
	void ShowProjectionMatrix();
	COpenGLNode* GetSelected();
// Attributes
protected:
	CViewTree m_wndFileView;
	CImageList m_FileViewImages;
	CFileViewToolBar m_wndToolBar;

protected:
	BOOLEAN ValidateAdd();
	BOOLEAN ValidateDelete();

	void FillFile(TiXmlNode *root, HTREEITEM hparrent, COpenGLNode *oparrent);
	COpenGLNode *XmltoOpenGL(TiXmlNode *node);
	void AddNode(COpenGLNode *newNode);

	HTREEITEM hTreeItem;
	COpenGLNode *node;

	HTREEITEM environment;
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
	afx_msg void OnAddobjectLine();
	afx_msg void OnAddobjectRectangle();
	afx_msg void OnObjectDelete();
	afx_msg void OnAddobjectPoint();
	afx_msg void OnObjectAddcolor();
	afx_msg void OnAddtransformationTranslate();
	afx_msg void OnAddtransformationScale();
	afx_msg void OnAddtransformationRotate();
	afx_msg void OnObjectEdit();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

