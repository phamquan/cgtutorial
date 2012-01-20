#pragma once


// CDlgScale dialog

class CDlgScale : public CDialog
{
	DECLARE_DYNAMIC(CDlgScale)

public:
	CDlgScale(CWnd* pParent = NULL);   // standard constructor
	CDlgScale(float x, float y, float z, CWnd* pParent = NULL);
	virtual ~CDlgScale();

// Dialog Data
	enum { IDD = IDD_SCALE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	float m_X;
	float m_Y;
	float m_Z;
};
