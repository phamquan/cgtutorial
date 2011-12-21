#pragma once

#include "dlgmatrix.h"

class CDlgProjectionMatrix :
	public CDlgMatrix
{
	DECLARE_DYNAMIC(CDlgProjectionMatrix)
public:
	CDlgProjectionMatrix(CProjection *proj, CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgProjectionMatrix();

	CProjection* projection;

protected:
	void ShowProjection(CDC* cdc, int &top, int left);

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
public:
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
};

