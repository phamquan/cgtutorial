#pragma once


// CDlgTetrahedron dialog

class CDlgTetrahedron : public CDialog
{
	DECLARE_DYNAMIC(CDlgTetrahedron)

public:
	CDlgTetrahedron(CWnd* pParent = NULL);   // standard constructor
	CDlgTetrahedron(float x1, float y1, float z1, float x2, float y2, float z2,
				float x3, float y3, float z3, float x4, float y4, float z4, CWnd* pParent = NULL);
	virtual ~CDlgTetrahedron();

// Dialog Data
	enum { IDD = IDD_TETRAHEDRON };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	float m_X1;
	float m_X2;
	float m_X3;
	float m_X4;
	float m_Y1;
	float m_Y2;
	float m_Y3;
	float m_Y4;
	float m_Z1;
	float m_Z2;
	float m_Z3;
	float m_Z4;
};
