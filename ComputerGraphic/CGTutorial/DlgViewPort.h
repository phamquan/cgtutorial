#pragma once


// CDlgViewPort dialog

class CDlgViewPort : public CDialog
{
	DECLARE_DYNAMIC(CDlgViewPort)

public:
	CDlgViewPort(float left, float bottom, float width, float height, int type, CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgViewPort();

// Dialog Data
	enum { IDD = IDD_VIEWPORT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	float m_Bottom;
	float m_Height;
	float m_Left;
	float m_Width;
	int type;
	afx_msg void OnDefault();
	afx_msg void OnCustom();
	virtual BOOL OnInitDialog();
};
