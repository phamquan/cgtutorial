#pragma once


// CDlgRing dialog

class CDlgRing : public CDialog
{
	DECLARE_DYNAMIC(CDlgRing)

public:
	CDlgRing(float x, float y, float z, float R, float r, COLORREF color, CWnd* pParent = NULL); 
	virtual ~CDlgRing();

// Dialog Data
	enum { IDD = IDD_RING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	float m_R;
	float m_R1;
	float m_X;
	float m_Y;
	float m_Z;
	CMFCColorButton m_Color;
};
