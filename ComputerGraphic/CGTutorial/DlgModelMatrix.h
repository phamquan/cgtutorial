#pragma once

#include "DlgMatrix.h"
#include "OpenGLNode.h"

// CDlgModelMatrix dialog

class CDlgModelMatrix : public CDlgMatrix
{
	DECLARE_DYNAMIC(CDlgModelMatrix)

public:
	CDlgModelMatrix(CWnd* pParent = NULL);   // standard constructor
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
	afx_msg void OnPaint();
};
