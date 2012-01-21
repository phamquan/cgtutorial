#pragma once


// CDlgPipeLine dialog

class CDlgPipeLine : public CDialog
{
	DECLARE_DYNAMIC(CDlgPipeLine)

public:
	CDlgPipeLine(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgPipeLine();

	void Refresh(COpenGLNode *obj);
// Dialog Data
	enum { IDD = IDD_PIPELINE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
