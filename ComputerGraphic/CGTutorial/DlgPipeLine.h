#pragma once

#include "DlgMatrix.h"
#include "Environment.h"
#include "PipeLineTip.h"
// CDlgPipeLine dialog

class CDlgPipeLine : public CDlgMatrix
{
	DECLARE_DYNAMIC(CDlgPipeLine)

public:
	CDlgPipeLine(CEnvironment *env, CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgPipeLine();

	void Refresh(COpenGLNode *obj);
// Dialog Data
	
	enum { IDD = IDD_PIPELINE };

protected:
	COpenGLNode* object;
	CEnvironment *environment;
	float view[16];
	float projection[16];

	CPipeLineTip *modelTip;
	CPipeLineTip *viewTip;
	CPipeLineTip *projectionTip;

	void CalNode(COpenGLNode* node);

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
