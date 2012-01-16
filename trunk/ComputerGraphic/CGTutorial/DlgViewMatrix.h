#pragma once

#include "DlgMatrix.h"
// CDlgViewMatrix dialog

class CDlgViewMatrix : public CDlgMatrix
{
	DECLARE_DYNAMIC(CDlgViewMatrix)

public:
	CDlgViewMatrix(CCamera *cam, CPtrArray* in, CPtrArray* out, CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgViewMatrix();

	CCamera* camera;

	void Refresh();
protected:
	CPoint3D eye, center;
	CVector3D up, n, u, v;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
};
