#pragma once


// CDlgTriangle dialog

class CDlgTriangle : public CDialog
{
	DECLARE_DYNAMIC(CDlgTriangle)

public:
	CDlgTriangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, COLORREF color, CWnd* pParent = NULL);
	virtual ~CDlgTriangle();

// Dialog Data
	enum { IDD = IDD_TRIANGLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	float m_X1;
	float m_X2;
	float m_X3;
	float m_Y1;
	float m_Y2;
	float m_Y3;
	float m_Z1;
	float m_Z2;
	float m_Z3;
	CMFCColorButton m_Color;
};
