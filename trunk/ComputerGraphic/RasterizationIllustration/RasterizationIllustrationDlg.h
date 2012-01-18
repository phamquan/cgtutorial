
// RasterizationIllustrationDlg.h : header file
//

#pragma once

#include "RasterizationConfig.h"
#include "RasterizationInfoDlg.h"

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
	CRasterizationInfoDlg* m_infoDlg;
	CRasterizationConfig *m_config;
	PIXELTYPE *m_pixelState;
	COLOR *m_pixelColor;
	float m_width, m_height, m_dfLen;
	HANDLE hRunStep;
	DWORD  dwRunStepId;
	bool m_isLeftMouseDown, m_isMidMouseDown;
	float startX, startY, targetX, targetY;
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
	afx_msg void OnAlgorithmforrasterizationDigitaldifferentialanalyzer();
	afx_msg void OnUpdateAlgorithmforrasterizationDigitaldifferentialanalyzer(CCmdUI *pCmdUI);
	afx_msg void OnAlgorithmforrasterizationBresenhamlinealgorithm();
	afx_msg void OnUpdateAlgorithmforrasterizationBresenhamlinealgorithm(CCmdUI *pCmdUI);
protected:
	afx_msg void OnKickIdle();
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextriDda();
	afx_msg void OnUpdateContextriDda(CCmdUI *pCmdUI);
	afx_msg void OnContextriBresenham();
	afx_msg void OnUpdateContextriBresenham(CCmdUI *pCmdUI);
	afx_msg void OnContextriMoreinfo();
};
