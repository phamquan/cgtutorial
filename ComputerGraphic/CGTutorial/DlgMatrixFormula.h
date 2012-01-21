#pragma once

#include "Environment.h"
#include "OpenGLNode.h"
#include "DlgModelMatrix.h"
#include "DlgModelMatrixGL.h"
#include "DlgViewMatrix.h"
#include "DlgViewMatrixGL.h"
#include "DlgProjectionMatrix.h"
#include "DlgProjectionMatrixGL.h"
#include "DlgViewPort.h"

// CDlgMatrixFormula dialog

class CDlgMatrixFormula : public CDialog
{
	DECLARE_DYNAMIC(CDlgMatrixFormula)

public:
	CDlgMatrixFormula(CEnvironment *environment);
	virtual ~CDlgMatrixFormula();

	void Refresh(COpenGLNode *object);
	void ChangeTab(int index);
// Dialog Data
	enum { IDD = IDD_MATRIX_FORMULA };

protected:
	CDlgModelMatrix *dlgModel;
	CDlgModelMatrixGL *dlgModelGL;
	CDlgViewMatrix *dlgView;
	CDlgViewMatrixGL *dlgViewGL;
	CDlgProjectionMatrix *dlgProjection;
	CDlgProjectionMatrixGL *dlgProjectionGL;
	CDlgViewPort *dlgViewPort;
	
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_Tab;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
};
