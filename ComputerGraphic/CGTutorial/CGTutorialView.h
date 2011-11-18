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
#include "GL/gl.h"
#include "GL/glu.h"
#include "HomoPoint.h"

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

	float m_ViewMatrix[16];

	bool m_isCreated;

	CPoint3D angle;
	CVector3D Pan;
// Operations
public:
	void SetupOpenGL();
	void DetroyOpenGL();
	void DrawCoordinate();
	void EvalViewMatrix();
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
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // debug version in CGTutorialView.cpp
inline CCGTutorialDoc* CCGTutorialView::GetDocument() const
   { return reinterpret_cast<CCGTutorialDoc*>(m_pDocument); }
#endif

