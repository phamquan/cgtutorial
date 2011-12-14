#pragma once

#include "Resource.h"
// CDlgShowMatrix dialog

class CDlgShowMatrix : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgShowMatrix)

public:
	CDlgShowMatrix(CString name, COpenGLNode* node, CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgShowMatrix();

	int m_nCurHeight;
	int m_nScrollPos;
	CRect m_rect;
	CString title;
	COpenGLNode* root;

	int count[3];
// Dialog Data
	enum { IDD = IDD_SHOW_MATRIX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	static void ShowMatrix(CDC* dc, CString name, float m[16], int &top, int left);
	void ShowNode(CDC* cdc, COpenGLNode* node, int &top, int left);

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnPaint();
};
