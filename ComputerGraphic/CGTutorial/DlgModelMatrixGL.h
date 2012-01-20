#pragma once

#include "DlgMatrix.h"
#include "OpenGLNode.h"

// CDlgModelMatrixGL dialog

class CDlgModelMatrixGL : public CDlgMatrix
{
	DECLARE_DYNAMIC(CDlgModelMatrixGL)

public:
	CDlgModelMatrixGL(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgModelMatrixGL();

	void Refresh(COpenGLNode* in);

protected:
	COpenGLNode* object;
	void ShowNode(COpenGLNode* node, int &top, CDC *cdc);

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};
