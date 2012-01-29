#pragma once


// CDlgSphere dialog

class CDlgSphere : public CDialog
{
	DECLARE_DYNAMIC(CDlgSphere)

public:
	CDlgSphere(float x, float y, float z, float R, COLORREF color, CWnd* pParent = NULL); 
	virtual ~CDlgSphere();

// Dialog Data
	enum { IDD = IDD_SPHERE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	float m_R;
	float m_X;
	float m_Y;
	float m_Z;
	CMFCColorButton m_Color;
};
