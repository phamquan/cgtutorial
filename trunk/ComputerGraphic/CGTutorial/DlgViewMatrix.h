#pragma once

#include "resource.h"
#include "DlgMatrix.h"
// CDlgViewMatrix dialog

class CDlgViewMatrix : public CDlgMatrix
{
	DECLARE_DYNAMIC(CDlgViewMatrix)

public:
	CDlgViewMatrix(CCamera *node, CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgViewMatrix();

	CCamera* root;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
