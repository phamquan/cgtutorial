#pragma once


// CDlgLine dialog

class CDlgLine : public CDialog
{
	DECLARE_DYNAMIC(CDlgLine)

public:
	CDlgLine(float x1, float y1, float z1, float x2, float y2, float z2, COLORREF color, CWnd* pParent = NULL);
	virtual ~CDlgLine();

// Dialog Data
	enum { IDD = IDD_LINE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	float m_BX;
	float m_BY;
	float m_BZ;
	float m_EX;
	float m_EY;
	float m_EZ;
	CMFCColorButton m_Color;
};
