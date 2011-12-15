#pragma once

#include "resource.h"

// CDlgViewMatrix dialog

class CDlgViewMatrix : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgViewMatrix)

public:
	CDlgViewMatrix(CCamera *node, CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgViewMatrix();

	CCamera* root;

// Dialog Data
	enum { IDD = IDD_DIALOG_PIPELINE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
