#pragma once

#include "resource.h"
#include "ScrollDialog.h"
// CDlgShowMatrix dialog

class CDlgShowMatrix : public CScrollDialog
{
	DECLARE_DYNAMIC(CDlgShowMatrix)

public:
	CDlgShowMatrix(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgShowMatrix();

	int m_nCurHeight;
	int m_nScrollPos;
	CRect m_rect;

	CBrush m_brush; 
// Dialog Data
	enum { IDD = IDD_SHOW_MATRIX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
