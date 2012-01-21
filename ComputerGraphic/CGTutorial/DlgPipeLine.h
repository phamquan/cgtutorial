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
	CPipeLineTip *viewportTip;

	float x,y,w,h;
	int type;

	void CalNode(COpenGLNode* node);

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClickedModel();
	afx_msg void OnClickedView();
	afx_msg void OnClickedProjection();
};
