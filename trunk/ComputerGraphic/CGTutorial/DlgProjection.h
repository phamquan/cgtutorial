#pragma once

#include "resource.h"

// CDlgProjection dialog

class CDlgProjection : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgProjection)

public:
	CDlgProjection(float left, float right, float bottom, float top, float mnear, float mfar, int type, CWnd* pParent = NULL);   
	virtual ~CDlgProjection();

// Dialog Data
	enum { IDD = IDD_DIALOG_PROJECTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	float m_Bottom;
	float m_Far;
	float m_Left;
	float m_Near;
	float m_Right;
	float m_Top;

	int type;

	afx_msg void OnBnClickedOk();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	virtual BOOL OnInitDialog();
};
