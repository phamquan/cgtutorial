#pragma once

#include "DlgMatrix.h"
#include "Environment.h"

// CDlgViewMatrix dialog

class CDlgViewMatrix : public CDlgMatrix
{
	DECLARE_DYNAMIC(CDlgViewMatrix)

public:
	CDlgViewMatrix(CEnvironment *env, CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgViewMatrix();

	void Refresh();
protected:
	CEnvironment *environment;
	CPoint3D eye, center;
	CVector3D up, n, u, v;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};
