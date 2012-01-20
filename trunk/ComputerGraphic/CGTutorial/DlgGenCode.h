#pragma once
#include "resource.h"

// CDlgGenCode dialog

class CDlgGenCode : public CDialog
{
	DECLARE_DYNAMIC(CDlgGenCode)

public:
	CDlgGenCode(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgGenCode();

	void Refresh(CString code);
// Dialog Data
	enum { IDD = IDD_GENCODE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CString m_Data;
	CEdit m_Ctrl;
};
