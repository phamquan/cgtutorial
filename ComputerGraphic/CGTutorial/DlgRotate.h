#pragma once

#include "resource.h"

// CDlgRotate dialog

class CDlgRotate : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgRotate)

public:
	CDlgRotate(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgRotate();

// Dialog Data
	enum { IDD = IDD_DIALOG_ROTATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
