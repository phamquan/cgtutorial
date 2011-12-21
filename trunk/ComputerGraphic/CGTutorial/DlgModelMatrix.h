#pragma once

#include "DlgMatrix.h"

// CDlgModelMatrix dialog

class CDlgModelMatrix : public CDlgMatrix
{
	DECLARE_DYNAMIC(CDlgModelMatrix)

public:
	CDlgModelMatrix(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgModelMatrix();

	void SetData(COpenGLNode* in, CPtrArray* out);

	COpenGLNode* object;

	CString total;
	int count[3];

protected:
	void ShowNode(CDC* cdc, COpenGLNode* node, int &top, int left);
	void ShowMatrixPoint(CDC* cdc, CString matrix, CString point, int &top, int left);

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
};
