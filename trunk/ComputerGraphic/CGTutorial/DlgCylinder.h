#pragma once


// CDlgCylinder dialog

class CDlgCylinder : public CDialog
{
	DECLARE_DYNAMIC(CDlgCylinder)

public:
	CDlgCylinder(CWnd* pParent = NULL);   // standard constructor
	CDlgCylinder(float x, float y, float z, float R, float height, CWnd* pParent = NULL); 
	virtual ~CDlgCylinder();

// Dialog Data
	enum { IDD = IDD_CYLINDER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	float m_Height;
	float m_R;
	float m_X;
	float m_Y;
	float m_Z;
};
