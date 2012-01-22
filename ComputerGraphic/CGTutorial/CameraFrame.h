#pragma once

#include "GL/glut.h"
#include "Environment.h"

// CCameraFrame dialog

class CCameraFrame : public CDialog
{
	DECLARE_DYNAMIC(CCameraFrame)

public:
	CCameraFrame(CEnvironment *environment, COpenGLNode *object, CWnd* pParent = NULL);
	virtual ~CCameraFrame();

	void ReSize();
// Dialog Data
	enum { IDD = IDD_CAMERA_FRAME };

protected:
	CEnvironment *environment;
	COpenGLNode *object;

	HDC  m_hDC;
	HGLRC m_hRC;

	int width, height;

	void SetupOpenGL();
	void DetroyOpenGL();
	void DrawCoordinate();

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
};
