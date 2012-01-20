#pragma once


// CDlgRectangle dialog

class CDlgRectangle : public CDialog
{
	DECLARE_DYNAMIC(CDlgRectangle)

public:
	CDlgRectangle(CWnd* pParent = NULL);   // standard constructor
	CDlgRectangle(float top, float left, float bottom, float right, CWnd* pParent = NULL);
	virtual ~CDlgRectangle();

// Dialog Data
	enum { IDD = IDD_RECTANGLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	float m_Bottom;
	float m_Left;
	float m_Right;
	float m_Top;
};
