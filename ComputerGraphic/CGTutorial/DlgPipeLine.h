#pragma once

#include "resource.h"

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
	COpenGLNode* camera;
	COpenGLNode* world;
	COpenGLNode* clipping;
	COpenGLNode* divide;
	COpenGLNode* window;

	CDlgModelMatrix* modelDlg;
	CDlgViewMatrix* viewDlg;
	CDlgProjectionMatrix* projectionDlg;

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
