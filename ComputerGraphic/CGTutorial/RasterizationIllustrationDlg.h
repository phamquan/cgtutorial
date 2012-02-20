#pragma once


// CRasterizationIllustrationDlg dialog

class CRasterizationIllustrationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRasterizationIllustrationDlg)

public:
	CRasterizationIllustrationDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRasterizationIllustrationDlg();

// Dialog Data
	enum { IDD = IDD_RASTERIZATIONILLUSTRATION_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
