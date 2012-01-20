#pragma once

#include "DlgMatrix.h"
#include "Environment.h"
// CDlgProjectionMatrixGL dialog

class CDlgProjectionMatrixGL : public CDlgMatrix
{
	DECLARE_DYNAMIC(CDlgProjectionMatrixGL)

public:
	CDlgProjectionMatrixGL(CEnvironment *env, CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgProjectionMatrixGL();

	void Refresh();

protected:
	CEnvironment *environment;
	int type;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};
