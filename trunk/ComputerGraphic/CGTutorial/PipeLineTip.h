#pragma once


// CPipeLineTip

const int ID_TIMER_TOOLTIP_HIDE = 1;
const int ID_TIMER_TOOLTIP_SHOW = 2;	


// --------------------------------------------------------------------------
typedef struct tagTTWndStruct 
{
	HWND	hWndToolTip;
	HWND	hWndToolTipParent;
} TTWNDSTRUCT;
// --------------------------------------------------------------------------
class CPipeLineTip : public CWnd
{
public:
	CPipeLineTip();
	virtual ~CPipeLineTip();

	bool m_bStuck; // stuck to mouse pointer when moving inside a control

	void RelayEvent( LPMSG );
	BOOL Create( CWnd *parent );
	void AddTool(CWnd *pWnd, int timerDelayHide = -1, int timerDelayShow = -1);
	void Hide();
	void Refresh(float m[16]);
	void ReSet();
protected:
	//{{AFX_MSG(CToolTipWnd)
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg BOOL PreTranslateMessage( MSG *pMsg );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	float matrix[16];
	int      m_iDelayHide;
	int      m_iDelayShow;
	bool isShow;
	int m_iHeight;
	int m_iWidth;

	LPCTSTR m_lpWndCls;

	HWND    m_hParentWnd;
	HWND        m_pControl;
	HWND        m_pCurrwnd;	// control for which a tooltip is currently displayed

	bool m_bSkipNextMove; // to skip the next WM_MOUSEMOVE message
	UINT m_iTimer;
	UINT m_iTimer2;

	void Show( int x, int y);

	void SetHideTimer( int iDelay );
	void KillHideTimer();
	void SetShowTimer(int iTimeTillShow);
	void KillShowTimer(void);

	void ShowMatrix(CDC* cdc, float m[16], int top, int &left);
	void ShowMatrix(CDC* cdc, CString m[16], int top, int &left);
};

