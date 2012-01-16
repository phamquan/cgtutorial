#pragma once

#include "DlgMatrix.h"

// CDlgModelMatrix dialog

class CDlgModelMatrix : public CDlgMatrix
{
	DECLARE_DYNAMIC(CDlgModelMatrix)

public:
	CDlgModelMatrix(CPtrArray* out, CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgModelMatrix();

	void Refresh(COpenGLNode* in);

protected:
	COpenGLNode* object;
	CString total;
	int count[3];

	void CalNode(COpenGLNode* node);

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
};
