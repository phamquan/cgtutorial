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

// MainFrm.h : interface of the CMainFrame class
//

#pragma once
#include "FileView.h"
#include "DlgGenCode.h"
#include "DlgMatrixFormula.h"
#include "DlgPipeLine.h"
#include "CameraFrame.h"
#include "Stack.h"
#include "Action.h"

class CMainFrame : public CFrameWndEx
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)
	
	CAction *DoAction(CAction *action);

	CStack<CAction*> undo, redo;
// Attributes
public:
	CFileView         m_wndFileView;
	CDlgGenCode *dlgGenCode;
	CDlgMatrixFormula *dlgMatrixFormula;
	CDlgPipeLine *dlgPipeLine;
	CCameraFrame *cameraFrame;
	
// Operations
public:
	void Refresh();
	void ShowModelMatrix();
	void ShowViewMatrix();
	void ShowProjectionMatrix();
	void ShowViewPort();
	void ClearUndo();
	void ClearRedo();
	CSize GetViewPort();
// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CMFCRibbonBar     m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	CMFCToolBarImages m_PanelImages;
	CMFCRibbonStatusBar  m_wndStatusBar;

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	afx_msg void OnFilePrint();
	afx_msg void OnFilePrintPreview();
	afx_msg void OnUpdateFilePrintPreview(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);
public:
	afx_msg void OnGencode();
	afx_msg void OnMatrix();
	afx_msg void OnPipeline();
	afx_msg void OnCamera();
	afx_msg void OnPoint();
	afx_msg void OnLine();
	afx_msg void OnTriangle();
	afx_msg void OnRectangle();
	afx_msg void OnCircle();
	afx_msg void OnEllipse();
	afx_msg void OnCube();
	afx_msg void OnTetrahedron();
	afx_msg void OnSphere();
	afx_msg void OnCylinder();
	afx_msg void OnRing();
	afx_msg void OnEditUndo();
	afx_msg void OnEditRedo();
	afx_msg void OnTreeView();
};


