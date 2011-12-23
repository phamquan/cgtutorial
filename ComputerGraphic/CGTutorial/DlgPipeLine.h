#pragma once

#include "resource.h"
#include "DlgDivideW.h"
#include "DlgViewPort.h"

// CDlgPipeLine dialog

class CDlgPipeLine : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgPipeLine)

public:
	CDlgPipeLine(CEnvironment *env, CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgPipeLine();

	void SetData(COpenGLNode* object);

	CEnvironment* environment;
	COpenGLNode* object;
	CPtrArray* camera;
	CPtrArray* world;
	CPtrArray* clipping;
	CPtrArray* divide;
	CPtrArray* window;

	CDlgModelMatrix* modelDlg;
	CDlgViewMatrix* viewDlg;
	CDlgProjectionMatrix* projectionDlg;
	CDlgDivideW* divideWDlg;
	CDlgViewPort* viewPortDlg;

// Dialog Data
	enum { IDD = IDD_DIALOG_PIPELINE1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CTabCtrl m_Tab;
	afx_msg void OnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
};
