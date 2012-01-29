#pragma once


// CDlgEllipse dialog

class CDlgEllipse : public CDialog
{
	DECLARE_DYNAMIC(CDlgEllipse)

public:
	CDlgEllipse(float x, float y, float z, float a, float b, COLORREF color, CWnd* pParent = NULL); 
	virtual ~CDlgEllipse();

// Dialog Data
	enum { IDD = IDD_ELLIPSE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	float m_A;
	float m_B;
	float m_X;
	float m_Y;
	float m_Z;
	CMFCColorButton m_Color;
};
