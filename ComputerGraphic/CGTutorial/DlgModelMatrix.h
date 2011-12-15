#pragma once

#include "resource.h"

// CDlgModelMatrix dialog

class CDlgModelMatrix : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgModelMatrix)

public:
	CDlgModelMatrix(COpenGLNode* node, CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgModelMatrix();

	CString total;
	float sum[16];
	COpenGLNode* root;
	int count[3];

// Dialog Data
	enum { IDD = IDD_DIALOG_PIPELINE };

protected:
	static void ShowMatrix(CDC* dc, CString name, CString rear, float m[16], int &top, int left);
	void ShowNode(CDC* cdc, COpenGLNode* node, int &top, int left);

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
};
