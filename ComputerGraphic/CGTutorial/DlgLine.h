#pragma once

#include "resource.h"

// CDlgLine dialog

class CDlgLine : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgLine)

public:
	CDlgLine(CWnd* pParent = NULL);   // standard constructor
	CDlgLine(float x1, float y1, float z1, float x2, float y2, float z2, CWnd* pParent = NULL);
	virtual ~CDlgLine();

// Dialog Data
	enum { IDD = IDD_DIALOG_LINE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	float m_X1;
	float m_X2;
	float m_Y1;
	float m_Y2;
	float m_Z1;
	float m_Z2;
	afx_msg void OnBnClickedOk();
};
