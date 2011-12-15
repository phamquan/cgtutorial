#pragma once

#include "resource.h"
#include "DlgMatrix.h"

// CDlgModelMatrix dialog

class CDlgModelMatrix : public CDlgMatrix
{
	DECLARE_DYNAMIC(CDlgModelMatrix)

public:
	CDlgModelMatrix(COpenGLNode* node, CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgModelMatrix();

	CString total;
	float sum[16];
	COpenGLNode* root;
	int count[3];

protected:
	void ShowMatrix(CDC* cdc, CString name, CString rear, float m[16], int &top, int left);
	void ShowPoint(CDC* cdc, CString name, CPoint3D point, int &top, int left);
	void ShowNode(CDC* cdc, COpenGLNode* node, int &top, int left);

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
};
