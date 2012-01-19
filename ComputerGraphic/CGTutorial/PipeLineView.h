#pragma once

#include "CGTutorialDoc.h"
#include "Resource.h"
// CGenCode form view

class CPipeLineView : public CFormView
{
	DECLARE_DYNCREATE(CPipeLineView)

protected:
	CPipeLineView();           // protected constructor used by dynamic creation
	virtual ~CPipeLineView();

public:
	enum { IDD = IDD_DIALOG_PIPELINE1 };
	CCGTutorialDoc* GetDocument() const;
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_ShowCode;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
};


