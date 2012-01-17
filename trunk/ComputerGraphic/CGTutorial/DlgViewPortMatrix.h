#pragma once
#include "dlgmatrix.h"
#include "OpenGLNode.h"
#include "ViewPort.h"

class CDlgViewPortMatrix : public CDlgMatrix
{
	DECLARE_DYNAMIC(CDlgViewPortMatrix)

public:
	CDlgViewPortMatrix(CEnvironment *env, CPtrArray* in, CPtrArray* out, CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgViewPortMatrix();

	void Refresh();
protected:
	CEnvironment *environment;
	int type;
	float x1,y1,x2,y2;
	CRect rect;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
};
