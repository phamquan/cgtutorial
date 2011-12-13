// DlgShowMatrix.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "DlgShowMatrix.h"
#include "afxdialogex.h"


// CDlgShowMatrix dialog

IMPLEMENT_DYNAMIC(CDlgShowMatrix, CDialogEx)

CDlgShowMatrix::CDlgShowMatrix(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgShowMatrix::IDD, pParent)
{

}

CDlgShowMatrix::~CDlgShowMatrix()
{
}

void CDlgShowMatrix::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgShowMatrix, CDialogEx)
	ON_WM_SIZE()
	ON_WM_VSCROLL()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgShowMatrix message handlers


BOOL CDlgShowMatrix::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	GetWindowRect(m_rect);
	m_nScrollPos = 0;
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgShowMatrix::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	m_nCurHeight = cy;
	int nScrollMax;
	if (cy < m_rect.Height())
	{
	     nScrollMax = m_rect.Height() - cy;
	}
	else
	     nScrollMax = 0;

	SCROLLINFO si;
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_ALL; // SIF_ALL = SIF_PAGE | SIF_RANGE | SIF_POS;
	si.nMin = 0;
	si.nMax = nScrollMax;
	si.nPage = si.nMax/10;
	si.nPos = 0;
	SetScrollInfo(SB_VERT, &si, TRUE); 
}


void CDlgShowMatrix::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	int nDelta;
	int nMaxPos = m_rect.Height() - m_nCurHeight;

	switch (nSBCode)
	{
	case SB_LINEDOWN:
		if (m_nScrollPos >= nMaxPos)
			return;
		nDelta = min(nMaxPos/100,nMaxPos-m_nScrollPos);
		break;

	case SB_LINEUP:
		if (m_nScrollPos <= 0)
			return;
		nDelta = -min(nMaxPos/100,m_nScrollPos);
		break;

         case SB_PAGEDOWN:
		if (m_nScrollPos >= nMaxPos)
			return;
		nDelta = min(nMaxPos/10,nMaxPos-m_nScrollPos);
		break;

	case SB_THUMBPOSITION:
		nDelta = (int)nPos - m_nScrollPos;
		break;

	case SB_PAGEUP:
		if (m_nScrollPos <= 0)
			return;
		nDelta = -min(nMaxPos/10,m_nScrollPos);
		break;
	
         default:
		return;
	}
	m_nScrollPos += nDelta;
	SetScrollPos(SB_VERT,m_nScrollPos,TRUE);
	ScrollWindow(0,-nDelta);

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CDlgShowMatrix::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialogEx::OnPaint() for painting messages

	dc.DrawText(CString("dasdasd"),-1,CRect(0,0,100,100),DT_TOP|DT_LEFT);
	dc.DrawText(CString("dasdasd"),-1,CRect(0,20,100,100),DT_TOP|DT_LEFT);
	dc.DrawText(CString("dasdasd"),-1,CRect(0,40,100,100),DT_TOP|DT_LEFT);
	dc.DrawText(CString("dasdasd"),-1,CRect(0,60,100,100),DT_TOP|DT_LEFT);
	dc.DrawText(CString("dasdasd"),-1,CRect(0,80,100,100),DT_TOP|DT_LEFT);
}
