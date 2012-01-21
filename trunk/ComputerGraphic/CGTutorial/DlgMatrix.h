#pragma once

#include "HomoPoint.h"
// CDlgMatrix dialog
class Element
{
public :
	Element(CString f, CString t, float*d) : font(f),tail(t) {
		for(int i=0; i<16; i++)
			data[i] = d[i];
	}
	CString font;
	CString tail;
	float data[16];
};

class CDlgMatrix : public CDialog
{
	DECLARE_DYNAMIC(CDlgMatrix)

public:
	CDlgMatrix(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgMatrix();
	
// Dialog Data
	enum { IDD = IDD_TAB };

protected:
	CPtrArray matrix;
	float sum[16];

	int ShowMatrix(CDC* cdc, float m[16], const int top, int &left);
	int ShowMatrix(CDC* cdc, CString m[16], const int top, int &left);
	void ShowMatrix(CDC* cdc, CString name, CString rear, float m[16], int &top, int left);
	//void ShowMatrixPoint(CDC* cdc, CString name, float m[16], CPoint3D* in, CPoint3D* out, int &top, int left);
	void ShowMatrixMatrix(CDC* cdc, CString name, CString n[16], float m[16], int &top, int left);
	void ShowPoint(CDC* cdc, CHomoPoint point, const int top, int &left);
	void ShowPoint(CDC* cdc, CString name, CHomoPoint point, int top, int left);
	//void ShowPointPoint(CDC* cdc, CString name, CHomoPoint point1, CHomoPoint point2, int top, int left);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	void Clear();
	DECLARE_MESSAGE_MAP()
};
