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

// CGTutorialView.h : interface of the CCGTutorialView class
//

#pragma once
#include "../Library/GL/glut.h"
#include "DlgPipeLine.h"

class CCGTutorialView : public CView
{
protected: // create from serialization only
	CCGTutorialView();
	DECLARE_DYNCREATE(CCGTutorialView)

// Attributes
public:
	CCGTutorialDoc* GetDocument() const;
	HDC  m_hDC;
	HGLRC m_hRC;

	float m_width;
	float m_height;
	float m_near;
	float m_far;
	bool m_isCreated;
	CPoint3D angle;
	CPoint3D start;
	float m_ViewMatrix[16];
	BOOLEAN m_isMouseDown;

	BOOLEAN isShowCamera;

	CDlgPipeLine* pipeLine;
// Operations
public:
	void SetupOpenGL();
	void DetroyOpenGL();
	void EvalViewMatrix();
	void DrawCoordinate();
	void ShowPipeLine();
// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CCGTutorialView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnShowCamera();
	afx_msg void OnUpdateShowCamera(CCmdUI *pCmdUI);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};

#ifndef _DEBUG  // debug version in CGTutorialView.cpp
inline CCGTutorialDoc* CCGTutorialView::GetDocument() const
   { return reinterpret_cast<CCGTutorialDoc*>(m_pDocument); }
#endif

