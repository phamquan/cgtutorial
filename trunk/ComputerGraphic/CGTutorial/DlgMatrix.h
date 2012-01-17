#pragma once

#include "Resource.h"
#include "Point4D.h"
#include "Line.h"

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

class CDlgMatrix : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgMatrix)

public:
	CDlgMatrix(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgMatrix();	
	CPtrArray* in;
	CPtrArray* out;
	CPtrArray matrix;
	float sum[16];

	enum { IDD = IDD_DIALOG_PIPELINE };
protected:
	int ShowMatrix(CDC* cdc, float m[16], const int top, int &left);
	int ShowMatrix(CDC* cdc, CString m[16], const int top, int &left);
	void ShowMatrix(CDC* cdc, CString name, CString rear, float m[16], int &top, int left);
	void ShowMatrixPoint(CDC* cdc, CString name, float m[16], CPoint3D* in, CPoint3D* out, int &top, int left);
	//void ShowMatrixPoint(CDC* cdc, CString matrix, CString point, int &top, int left);
	void ShowMatrixMatrix(CDC* cdc, CString name, CString n[16], float m[16], int &top, int left);
	void ShowPoint(CDC* cdc, CHomoPoint point, const int top, int &left);
	void ShowPoint(CDC* cdc, CString name, CHomoPoint point, int top, int left);
	void ShowPointPoint(CDC* cdc, CString name, CHomoPoint point1, CHomoPoint point2, int top, int left);

	void CalMatrixPoint();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
