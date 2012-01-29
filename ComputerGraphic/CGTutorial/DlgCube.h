#pragma once


// CDlgCube dialog

class CDlgCube : public CDialog
{
	DECLARE_DYNAMIC(CDlgCube)

public:
	CDlgCube(float left, float bottom, float mnear, float right, float top, float mfar, COLORREF color, CWnd* pParent = NULL);
	virtual ~CDlgCube();

// Dialog Data
	enum { IDD = IDD_CUBE };

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
	CMFCColorButton m_Color;
};
