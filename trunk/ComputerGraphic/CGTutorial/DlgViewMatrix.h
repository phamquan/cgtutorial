#pragma once

#include "DlgMatrix.h"
// CDlgViewMatrix dialog

class CDlgViewMatrix : public CDlgMatrix
{
	DECLARE_DYNAMIC(CDlgViewMatrix)

public:
	CDlgViewMatrix(CCamera *cam, CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgViewMatrix();

	CCamera* camera;

protected:
	float sum[16];

	void ShowCamera(CDC* cdc, int &top, int left);

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
};
