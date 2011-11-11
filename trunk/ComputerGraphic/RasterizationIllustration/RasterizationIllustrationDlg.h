
// RasterizationIllustrationDlg.h : header file
//

#pragma once

#include "RasterizationConfig.h"

// CRasterizationIllustrationDlg dialog
class CRasterizationIllustrationDlg : public CDialogEx
{
// Construction
public:
	CRasterizationIllustrationDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_RASTERIZATIONILLUSTRATION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	HGLRC m_hRC;
	HDC m_hDC;
	CRasterizationConfig *m_config;
	PIXELTYPE *m_pixelState;
	float m_width, m_height, m_dfLen;
	HANDLE hRunStep;
	DWORD  dwRunStepId;
public:
	void initParameter();
	void setupOpenGL(void);
	void removeOpenGL(void);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
	void drawBoard(void);
	CRasterizationConfig* getConfig();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	void drawOrigin(void);
	void Rasterize(PIXEL start, PIXEL end, RASTERIZEALG alg, bool isStep=false);
	void fillPixel(PIXEL pixel, COLOR color);
	void drawPixel(void);
	static DWORD WINAPI ThreadProc(LPVOID lpParam);
	void runStep(void);
	void runAll(void);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnContextriRunstep();
	afx_msg void OnContextriRunall();
	void Erase(void);
	afx_msg void OnContextriErase();
	void setCamera(void);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
};
