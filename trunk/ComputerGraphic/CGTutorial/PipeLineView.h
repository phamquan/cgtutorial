#pragma once

#include "CGTutorialDoc.h"
#include "Resource.h"
#include "DlgModelMatrix.h"
#include "DlgViewMatrix.h"
#include "DlgProjectionMatrix.h"
#include "DlgDivideW.h"
#include "DlgViewPortMatrix.h"
// CGenCode form view

class CPipeLineView : public CFormView
{
	DECLARE_DYNCREATE(CPipeLineView)

protected:
	CPipeLineView();           // protected constructor used by dynamic creation
	virtual ~CPipeLineView();

	CEnvironment* environment;
	COpenGLNode* object;
	CPtrArray* camera;
	CPtrArray* world;
	CPtrArray* clipping;
	CPtrArray* divide;
	CPtrArray* window;

	CDlgModelMatrix* modelDlg;
	CDlgViewMatrix* viewDlg;
	CDlgProjectionMatrix* projectionDlg;
	CDlgDivideW* divideWDlg;
	CDlgViewPortMatrix* viewPortDlg;

	BOOL inited;
public:
	void CreateTab();
	void SetData(COpenGLNode* object);
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
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
};


