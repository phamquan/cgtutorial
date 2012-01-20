#pragma once


// CDlgPoint dialog

class CDlgPoint : public CDialog
{
	DECLARE_DYNAMIC(CDlgPoint)

public:
	CDlgPoint(CWnd* pParent = NULL);   // standard constructor
	CDlgPoint(float x, float y, float z, CWnd* pParent = NULL);
	virtual ~CDlgPoint();

// Dialog Data
	enum { IDD = IDD_POINT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	float m_X;
	float m_Y;
	float m_Z;
};
