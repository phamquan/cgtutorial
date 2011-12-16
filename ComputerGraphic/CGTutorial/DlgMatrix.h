#pragma once


// CDlgMatrix dialog

class CDlgMatrix : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgMatrix)

public:
	CDlgMatrix(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgMatrix();

	enum { IDD = IDD_DIALOG_PIPELINE };
protected:
	void ShowMatrix(CDC* cdc, float m[16], int top, int left);
	void ShowMatrix(CDC* cdc, CString m[16], int top, int left);
	void ShowPoint(CDC* cdc, CHomoPoint point, int top, int left);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
