#pragma once

#include "resource.h"
#include "DlgMatrix.h"
// CDlgViewMatrix dialog

class CDlgViewMatrix : public CDlgMatrix
{
	DECLARE_DYNAMIC(CDlgViewMatrix)

public:
	CDlgViewMatrix(CCamera *cam, COpenGLNode* node, CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgViewMatrix();

	CCamera* camera;
	COpenGLNode* root;

protected:
	float sum[16];

	void ShowMatrix(CDC* cdc, CString name, CString rear, float m[16], int &top, int left);
	void ShowPointMatrix(CDC* cdc, CString name, CPoint3D point, int &top, int left);
	void ShowPoint(CDC* cdc, CString name, CHomoPoint point, int top, int left);
	void ShowCamera(CDC* cdc, int &top, int left);

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
};
