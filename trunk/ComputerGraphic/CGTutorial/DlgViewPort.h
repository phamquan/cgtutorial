#pragma once

#include "DlgMatrix.h"
#include "Environment.h"
// CDlgViewPort dialog

class CDlgViewPort : public CDlgMatrix
{
	DECLARE_DYNAMIC(CDlgViewPort)

public:
	CDlgViewPort(CEnvironment *env, CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgViewPort();

	void Refresh();
protected:
	CEnvironment *environment;
	float x,y,w,h;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};
