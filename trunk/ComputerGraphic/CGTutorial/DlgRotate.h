#pragma once

// CDlgRotate dialog

class CDlgRotate : public CDialog
{
	DECLARE_DYNAMIC(CDlgRotate)

public:
	CDlgRotate(CWnd* pParent = NULL);   // standard constructor
	CDlgRotate(float x, float y, float z, float angle, CWnd* pParent = NULL);
	virtual ~CDlgRotate();

// Dialog Data
	enum { IDD = IDD_ROTATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	float m_A;
	float m_X;
	float m_Y;
	float m_Z;
};
