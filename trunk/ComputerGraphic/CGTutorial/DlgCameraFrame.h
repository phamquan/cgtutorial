#pragma once

#include "resource.h"
#include "GL/glut.h"
#include "Environment.h"
#include "OpenGLNode.h"

class CDlgCameraFrame : public CDialog
{
// Construction
public:
	CDlgCameraFrame(CEnvironment *environment, COpenGLNode *object, CWnd* pParent = NULL);
protected:
	CEnvironment *environment;
	COpenGLNode *object;

	HDC  m_hDC;
	HGLRC m_hRC;

	void SetupOpenGL();
	void DetroyOpenGL();
	void DrawCoordinate();
// Dialog Data
	//{{AFX_DATA(CCameraFrame)
	enum { IDD = IDD_DIALOG_CAMERA_FRAME };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCameraFrame)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCameraFrame)
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC); // add this line
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
};
