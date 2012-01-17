#pragma once

#include "CGTutorialDoc.h"

class CGenCodeView : public CScrollView
{
protected: // create from serialization only
	CGenCodeView();
	DECLARE_DYNCREATE(CGenCodeView)

// Attributes
public:
	CCGTutorialDoc* GetDocument() const;
// Operations
public:
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
	virtual ~CGenCodeView();
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
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // debug version in CGTutorialView.cpp
inline CCGTutorialDoc* CGenCodeView::GetDocument() const
   { return reinterpret_cast<CCGTutorialDoc*>(m_pDocument); }
#endif