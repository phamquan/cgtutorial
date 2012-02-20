#pragma once
#include "resource.h"
#include "RasterizationInfoDlg.h"
#include "RasterizationConfig.h"

// CRasterizationIllustrationDlg dialog

class CRasterizationIllustrationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRasterizationIllustrationDlg)

public:
	CRasterizationIllustrationDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRasterizationIllustrationDlg();

// Dialog Data
	enum { IDD = IDD_RASTERIZATIONILLUSTRATION_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

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
	bool debugMode;
	POLYGONPIXEL p;

	void setupOpenGL();
	void removeOpenGL();
	void drawBoard();
	CRasterizationConfig* getConfig();
	void initParameter();
	void Rasterize(PIXEL start, PIXEL end,RASTERIZEALG alg, int delay = 0);
	void Rasterize(POLYGONPIXEL polygon, RASTERIZEALG alg, int delay = 0);
	void fillPixel(PIXEL pixel, COLOR color);
	void drawPixel();
	DWORD WINAPI ThreadProc(LPVOID lpParam);
	void runStep();
	void runAll();
	void Erase();
	void setCamera();

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
