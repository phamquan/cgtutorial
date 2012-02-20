#pragma once


// CRasterizationInfoDlg dialog

class CRasterizationInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRasterizationInfoDlg)

public:
	CRasterizationInfoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRasterizationInfoDlg();

// Dialog Data
	enum { IDD = IDD_RASTERIZATIONINFODLG };
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	UINT m_cx;
	UINT m_cy;
	void Refresh(void);
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnNewCount(WPARAM wParam, LPARAM);
	float m_cr;
	float m_cg;
	float m_cb;
};
