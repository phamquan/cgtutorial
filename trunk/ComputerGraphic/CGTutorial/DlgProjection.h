#pragma once


// CDlgProjection dialog

class CDlgProjection : public CDialog
{
	DECLARE_DYNAMIC(CDlgProjection)

public:
	CDlgProjection(float left, float right, float bottom, float top, float mnear, float mfar, int type, CWnd* pParent = NULL);   
	virtual ~CDlgProjection();

// Dialog Data
	enum { IDD = IDD_PROJECTION };

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
	afx_msg void OnOrtho();
	afx_msg void OnFrustum();
	virtual BOOL OnInitDialog();
};
