// PipeLineTip.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "PipeLineTip.h"


// CPipeLineTip

// --------------------------------------------------------------------------
CPipeLineTip::CPipeLineTip()
{
	m_lpWndCls = AfxRegisterWndClass(0);
	m_bStuck = false;
	m_bSkipNextMove = false;
	m_pCurrwnd = NULL;
	m_iTimer = 0;
	m_iTimer2 = 0;
	m_iDelayHide = 5;			// seconds
	m_iDelayShow = 1000;		// ms
	isShow = FALSE;
	
	m_iHeight = 100;
	m_iWidth = 210;
}


// --------------------------------------------------------------------------
CPipeLineTip::~CPipeLineTip()
{
	if (m_iTimer > 0)
		KillHideTimer();

	if (m_iTimer2 > 0)
		KillShowTimer();
}


// --------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(CPipeLineTip, CWnd)
	//{{AFX_MSG_MAP(CPipeLineTip)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// --------------------------------------------------------------------------
BOOL CPipeLineTip::Create( CWnd* pParentWnd ) 
{
	if(!CWnd::CreateEx(NULL, m_lpWndCls, NULL, WS_POPUP, 0, 0, m_iWidth, m_iHeight, 
							   pParentWnd->GetSafeHwnd(), NULL, NULL ))
		return FALSE;
   
	m_hParentWnd = pParentWnd->GetSafeHwnd();
	SetOwner(pParentWnd);

	return TRUE;
}

void CPipeLineTip::OnPaint() 
{
	CPaintDC dc( this ); // device context for painting

	if(!isShow)
		return;

	CRect rectCl;
	GetClientRect( &rectCl );
	CRgn rgnComb;	
	rgnComb.CreateRectRgn( rectCl.left+10,rectCl.top,rectCl.right,rectCl.bottom );
	CBrush pBrush1;
	pBrush1.CreateSolidBrush( RGB(255,255,255) );

	dc.FillRgn( &rgnComb, &pBrush1 );

	ShowMatrix(&dc,matrix,10,10);
}

void CPipeLineTip::ShowMatrix(CDC* cdc, float m[16], int top, int left)
{
	char buff[128];
	CString n[16];
	for(int i=0; i<16; i++) {
		sprintf_s(buff,"%5.3f",m[i]);
		n[i] = CString(buff);
	}
	ShowMatrix(cdc,n,top,left);
}

void CPipeLineTip::ShowMatrix(CDC* cdc, CString m[16], int top, int left)
{
	int height = cdc->GetTextExtent(CString("ABC")).cy;
	int bottom = top + height*4 + 5*4;
	left += 5;
	cdc->MoveTo(left+10,top-5);
	cdc->LineTo(left,top-5);
	cdc->LineTo(left,bottom);
	cdc->LineTo(left+10,bottom);
	left += 5;
	for(int i=0; i<4; i++) {//col
		int max = 0;
		for(int j=0; j<4; j++) {//row
			int width = cdc->GetTextExtent(m[i*4+j]).cx;
			cdc->TextOutW(left,top+(height+5)*j,m[i*4+j]);
			if(max < width)
				max = width;
		}
		left += max + 10;
	}

	left -= 5;
	cdc->MoveTo(left-10,top-5);
	cdc->LineTo(left,top-5);
	cdc->LineTo(left,bottom);
	cdc->LineTo(left-10,bottom);
}

// --------------------------------------------------------------------------
int CPipeLineTip::OnCreate( LPCREATESTRUCT lpCreateStruct ) 
{
   if ( CWnd::OnCreate( lpCreateStruct ) == -1 )
      return -1;

   return 0;
}


// --------------------------------------------------------------------------
void CPipeLineTip::RelayEvent( LPMSG lpMsg )
{
	switch( lpMsg->message ) 
	{
	case WM_KEYDOWN:
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_NCLBUTTONDOWN:
	case WM_NCRBUTTONDOWN:
		Hide();
		break;
	case WM_MOUSEMOVE:
	case WM_NCMOUSEMOVE:
		// This is a fix to allow for messages to be made visible when not
		// using the mouse.
		if ( m_bSkipNextMove )
		{
			m_bSkipNextMove = false; 
			return;
		}

		HWND wndPt = lpMsg->hwnd;
		CPoint pt = lpMsg->pt;

		// Don't show the tooltips if the application does not have the input focus
		CWnd *pFocusWnd = AfxGetApp()->m_pMainWnd->GetFocus();

		if ( pFocusWnd == NULL )
			break;
		// There are 3 possible states regarding tooltip controls:
		// a) moving outside any ctrl
		// b) going from outside a ctrl to inside
		// c) moving inside the control
		// d) going from inside a ctrl to 
		if ( m_pCurrwnd == NULL ) // was not in a control
		{
			if ( wndPt == m_pControl ) // enters a control (now in a control)
			{
				Show( pt.x, pt.y );
				m_pCurrwnd = wndPt;
			}
		}
		else // was in a control
		{
			CRect rect;
			::GetWindowRect( m_pCurrwnd, &rect );
			if ( rect.PtInRect( lpMsg->pt ) ) // still in the same control
			{
				if ( m_bStuck )
					if ( IsWindowVisible() )
					{
						// may be over a tooltip, so look for previous control
						if (wndPt != m_pControl )
							Show( pt.x, pt.y );
					}
			}
			else // gone outside the control
			{
				Hide(); 
				m_pCurrwnd = NULL;
			}
		}
		break; //WM_MOUSEMOVE
	}
}

void CPipeLineTip::AddTool(CWnd *pWnd, int timerDelayHide /*= -1*/, int timerDelayShow /*=-1*/)
{
	ASSERT( pWnd->GetSafeHwnd() != NULL );

	if (timerDelayHide > 0)
		m_iDelayHide = timerDelayHide;

	if (timerDelayShow > 0)
		m_iDelayShow = timerDelayShow;

	m_pControl = pWnd->GetSafeHwnd();
}

//
// This callback is used by the EnumChildWindows function in the OnTimer Handler
//
BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam)
{
	BOOL bStatus = TRUE;
	TTWNDSTRUCT* pws = (TTWNDSTRUCT*)lParam;
	if (pws)
	{
		HWND hWndToolTip = pws->hWndToolTip;
		HWND hWndToolTipParent = pws->hWndToolTipParent;

		// Are we over the same window as when the timer message was fired?
		if (hwnd == hWndToolTipParent)
		{
			// Display the tooltip
			::ShowWindow(hWndToolTip, SW_SHOWNOACTIVATE);

			// Stop enumerating
			bStatus = FALSE;
		}
	}

	return bStatus;
}
 
void CPipeLineTip::OnTimer( UINT nIDEvent ) 
{
	if (nIDEvent == ID_TIMER_TOOLTIP_HIDE)
	{
		KillHideTimer();
		KillShowTimer();
		ShowWindow(SW_HIDE);

	}
	else if (nIDEvent == ID_TIMER_TOOLTIP_SHOW)
	{
		POINT pt;

		// Where is the mouse right now?
		if (GetCursorPos(&pt))
		{
			// Over which window?
			CWnd* pWnd = WindowFromPoint(pt);

			// Save the relevant window handles
			TTWNDSTRUCT ws;
			ZeroMemory(&ws, sizeof(ws));
			ws.hWndToolTip = GetSafeHwnd();
			ws.hWndToolTipParent = pWnd->GetSafeHwnd();

			// Now do the window handle comparisons
			EnumChildWindows(m_hParentWnd, EnumChildProc, (LPARAM)&ws); 
		}
	}
	CWnd::OnTimer(nIDEvent);
}

void CPipeLineTip::SetHideTimer( int iDelay )
{
	KillHideTimer(); 
	if ( iDelay > 0 ) // no timer if <= 0
		m_iTimer = CWnd::SetTimer( ID_TIMER_TOOLTIP_HIDE, iDelay*1000, NULL );
}

void CPipeLineTip::SetShowTimer(int iTimeTillShow)
{
	KillShowTimer(); 
	if ( iTimeTillShow > 0 ) // no timer if <= 0
		m_iTimer2 = CWnd::SetTimer(ID_TIMER_TOOLTIP_SHOW, iTimeTillShow, NULL );
}

void CPipeLineTip::KillHideTimer()
{
	if ( m_iTimer > 0 && m_hWnd != NULL ) 
		CWnd::KillTimer( m_iTimer ); 
	m_iTimer = 0;
}

void CPipeLineTip::KillShowTimer()
{
	if ( m_iTimer2 > 0 && m_hWnd != NULL ) 
		CWnd::KillTimer( m_iTimer2 ); 
	m_iTimer2 = 0;
}

void CPipeLineTip::Show( int x, int y ) // force apparition of the tooltip
{
	// Check to see if the tooltip has a portion outside the
	// screen, if so, adjust.
	if (x < 0)
		x = 0;

	if (y < 0)
		y = 0;

	RECT r;
	r.left = x;
	r.right = r.left + m_iWidth;
	r.top = y;
	r.bottom = r.top + m_iHeight;

	// Compare to screen coordinates (don't take in account the desktop toolbar)
	int screenHeight = GetSystemMetrics( SM_CYSCREEN );
	if ( r.bottom > screenHeight )
		r.top = screenHeight - m_iHeight;

	int screenWidth = GetSystemMetrics( SM_CXSCREEN );
	if ( r.right > screenWidth )
		r.left = screenWidth - m_iWidth;

	// Move the window
	SetWindowPos( &wndTop, r.left, r.top, m_iWidth, m_iHeight, SWP_NOACTIVATE );

	// Start the hide delay timer
	SetHideTimer(m_iDelayHide);

	// Start the show delay timer
	SetShowTimer(m_iDelayShow);
}

void CPipeLineTip::Hide()
{
	if ( IsWindowVisible() )
	{
		ShowWindow( SW_HIDE );
		KillHideTimer();
		KillShowTimer();
	}
}

BOOL CPipeLineTip::PreTranslateMessage( MSG *pMsg )
{
	RelayEvent( pMsg );
	return CWnd::PreTranslateMessage( pMsg );
}

void CPipeLineTip::Refresh(float m[16])
{
	isShow = TRUE;
	for(int i=0; i<16; i++)
		matrix[i] = m[i];
}

void CPipeLineTip::ReSet() 
{
	isShow = FALSE;
}