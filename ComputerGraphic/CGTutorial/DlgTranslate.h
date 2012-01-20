#pragma once


// CDlgTranslate dialog

class CDlgTranslate : public CDialog
{
	DECLARE_DYNAMIC(CDlgTranslate)

public:
	CDlgTranslate(CWnd* pParent = NULL);   // standard constructor
	CDlgTranslate(float x, float y, float z, CWnd* pParent = NULL);
	virtual ~CDlgTranslate();

// Dialog Data
	enum { IDD = IDD_TRANSLATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	float m_X;
	float m_Y;
	float m_Z;
};
