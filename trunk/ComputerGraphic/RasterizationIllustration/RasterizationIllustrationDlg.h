
// RasterizationIllustrationDlg.h : header file
//

#pragma once


// CRasterizationIllustrationDlg dialog
class CRasterizationIllustrationDlg : public CDialogEx
{
// Construction
public:
	CRasterizationIllustrationDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_RASTERIZATIONILLUSTRATION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	HGLRC m_hRC;
	HDC m_hDC;
public:
	void setupOpenGL(void);
};
