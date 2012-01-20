#pragma once


// CDlgCamera dialog

class CDlgCamera : public CDialog
{
	DECLARE_DYNAMIC(CDlgCamera)

public:
	CDlgCamera(float xpos, float ypos, float zpos, float xlook, float ylook, float zlook, float xup, float yup, float zup, CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgCamera();

// Dialog Data
	enum { IDD = IDD_CAMERA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	float m_EX;
	float m_EY;
	float m_EZ;
	float m_RX;
	float m_RY;
	float m_RZ;
	float m_UX;
	float m_UY;
	float m_UZ;
};
