#pragma once

#include "Resource.h"

// CDlgMatrix dialog

class CDlgMatrix : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgMatrix)

public:
	CDlgMatrix(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgMatrix();

	enum { IDD = IDD_DIALOG_PIPELINE };
protected:
	int ShowMatrix(CDC* cdc, float m[16], const int top, int &left);
	int ShowMatrix(CDC* cdc, CString m[16], const int top, int &left);
	void ShowMatrix(CDC* cdc, CString name, CString rear, float m[16], int &top, int left);
	void ShowMatrixPoint(CDC* cdc, CString matrix, CString name, float m[16], CPoint3D point, int &top, int left);
	void ShowMatrixMatrix(CDC* cdc, CString name, CString n[16], float m[16], int &top, int left);
	void ShowPoint(CDC* cdc, CHomoPoint point, const int top, int &left);
	void ShowPoint(CDC* cdc, CString name, CHomoPoint point, int top, int left);

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
