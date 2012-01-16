#pragma once
#include "dlgmatrix.h"
#include "OpenGLNode.h"
#include "ViewPort.h"

class CDlgViewPort : public CDlgMatrix
{
	DECLARE_DYNAMIC(CDlgViewPort)

public:
	CDlgViewPort(CViewPort* vp, CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgViewPort();

	CViewPort* viewport;

	void SetData(CPtrArray* in, CPtrArray* out);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
};
