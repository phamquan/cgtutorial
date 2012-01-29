#pragma once


// CDlgCircle dialog

class CDlgCircle : public CDialog
{
	DECLARE_DYNAMIC(CDlgCircle)

public:
	CDlgCircle(float x, float y, float z, float R, COLORREF color, CWnd* pParent = NULL);
	virtual ~CDlgCircle();

// Dialog Data
	enum { IDD = IDD_CIRCLE };

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
