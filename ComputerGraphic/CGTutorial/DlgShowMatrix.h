#pragma once

#include "Resource.h"
// CDlgShowMatrix dialog

class CDlgShowMatrix : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgShowMatrix)

public:
	CDlgShowMatrix(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgShowMatrix();

	int m_nCurHeight;
	int m_nScrollPos;
	CRect m_rect;
// Dialog Data
	enum { IDD = IDD_SHOW_MATRIX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnPaint();
};
