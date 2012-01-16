#pragma once
#include "dlgmatrix.h"

class CDlgDivideW : public CDlgMatrix
{
	DECLARE_DYNAMIC(CDlgDivideW)

public:
	CDlgDivideW(CPtrArray* in, CPtrArray* out, CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgDivideW();

	void Refresh();
protected:

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
};
