#pragma once

#include "dlgmatrix.h"

class CDlgProjectionMatrix :
	public CDlgMatrix
{
	DECLARE_DYNAMIC(CDlgProjectionMatrix)
public:
	CDlgProjectionMatrix(CProjection *proj, CPtrArray* in, CPtrArray* out, CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgProjectionMatrix();

	void Refresh();

protected:
	CProjection* projection;
	int type;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

public:
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
};

