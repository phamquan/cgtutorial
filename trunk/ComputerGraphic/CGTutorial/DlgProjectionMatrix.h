#pragma once

#include "DlgMatrix.h"
#include "Environment.h"
// CDlgProjectionMatrix dialog

class CDlgProjectionMatrix : public CDlgMatrix
{
	DECLARE_DYNAMIC(CDlgProjectionMatrix)

public:
	CDlgProjectionMatrix(CEnvironment *env, CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgProjectionMatrix();

	void Refresh();

protected:
	CEnvironment *environment;
	int type;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};
