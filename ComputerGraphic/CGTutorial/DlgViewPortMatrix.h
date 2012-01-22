#pragma once

#include "DlgMatrix.h"
#include "Environment.h"
// CDlgViewPort dialog

class CDlgViewPortMatrix : public CDlgMatrix
{
	DECLARE_DYNAMIC(CDlgViewPortMatrix)

public:
	CDlgViewPortMatrix(CEnvironment *env, CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgViewPortMatrix();

	void Refresh();
protected:
	CEnvironment *environment;
	float x,y,w,h;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};
