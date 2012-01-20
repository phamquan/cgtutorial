#pragma once

#include "DlgMatrix.h"
#include "Environment.h"

// CDlgViewMatrixGL dialog

class CDlgViewMatrixGL : public CDlgMatrix
{
	DECLARE_DYNAMIC(CDlgViewMatrixGL)

public:
	CDlgViewMatrixGL(CEnvironment *env, CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgViewMatrixGL();

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
