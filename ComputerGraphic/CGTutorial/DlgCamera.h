#pragma once

#include "resource.h"

// CDlgCamera dialog

class CDlgCamera : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCamera)

public:
	CDlgCamera(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgCamera();

// Dialog Data
	enum { IDD = IDD_DIALOG_CAMERA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	float m_X1;
	float m_X2;
	float m_X3;
	float m_Y1;
	float m_Y2;
	float m_Y3;
	float m_Z1;
	float m_Z2;
};
