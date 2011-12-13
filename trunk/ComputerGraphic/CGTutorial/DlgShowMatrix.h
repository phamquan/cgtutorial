#pragma once

#include "Resource.h"
// CDlgShowMatrix dialog

class CDlgShowMatrix : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgShowMatrix)

public:
	CDlgShowMatrix(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgShowMatrix();

// Dialog Data
	enum { IDD = IDD_SHOW_MATRIX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
