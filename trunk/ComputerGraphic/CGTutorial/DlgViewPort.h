#pragma once
#include "dlgmatrix.h"
#include "OpenGLNode.h"
#include "ViewPort.h"

class CDlgViewPort : public CDlgMatrix
{
	DECLARE_DYNAMIC(CDlgViewPort)

public:
	CDlgViewPort(CViewPort* vp, CPtrArray* in, CPtrArray* out, CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgViewPort();

	CViewPort* viewport;

	void Refresh();
protected:
	int type;
	float x1,y1,x2,y2;
	CRect rect;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
};
