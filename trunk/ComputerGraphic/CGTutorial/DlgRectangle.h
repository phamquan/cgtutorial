#pragma once

#include "resource.h"

// CDlgRectangle dialog

class CDlgRectangle : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgRectangle)

public:
	CDlgRectangle(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgRectangle();

// Dialog Data
	enum { IDD = IDD_DIALOG_RECTANGLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	float m_Bottom;
	float m_Left;
	float m_Right;
	float m_Top;
	afx_msg void OnBnClickedOk();
};
