#pragma once


// CCameraView view

class CCameraView : public CView
{
	DECLARE_DYNCREATE(CCameraView)

protected:
	CCameraView();           // protected constructor used by dynamic creation
	virtual ~CCameraView();

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
};


