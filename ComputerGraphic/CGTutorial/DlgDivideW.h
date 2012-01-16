#pragma once
#include "dlgmatrix.h"

class CDlgDivideW : public CDlgMatrix
{
	DECLARE_DYNAMIC(CDlgDivideW)

public:
	CDlgDivideW(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgDivideW();

	void SetData(CPtrArray* in, CPtrArray* out);
protected:
	void CalW();

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
};
