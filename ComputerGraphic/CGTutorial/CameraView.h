#pragma once
#include "../Library/GL/glut.h"

// CCameraView view

class CCameraView : public CView
{
	DECLARE_DYNCREATE(CCameraView)

protected:
	CCameraView();           // protected constructor used by dynamic creation
	virtual ~CCameraView();

	HDC  m_hDC;
	HGLRC m_hRC;

	void SetupOpenGL();
	void DetroyOpenGL();
public:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


