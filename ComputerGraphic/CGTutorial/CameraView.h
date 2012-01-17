// CCameraView.h : interface of the CCameraView class
//

#pragma once
#include "../Library/GL/glut.h"
#include "CGTutorialDoc.h"

class CCameraView : public CView
{
protected: // create from serialization only
	CCameraView();
	DECLARE_DYNCREATE(CCameraView)

// Attributes
public:
	CCGTutorialDoc* GetDocument() const;
	HDC  m_hDC;
	HGLRC m_hRC;

	int width;
	int height;
// Operations
public:
	void SetupOpenGL();
	void DetroyOpenGL();
	void DrawCoordinate();
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
	virtual ~CCameraView();
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
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
};

#ifndef _DEBUG  // debug version in CGTutorialView.cpp
inline CCGTutorialDoc* CCameraView::GetDocument() const
   { return reinterpret_cast<CCGTutorialDoc*>(m_pDocument); }
#endif

