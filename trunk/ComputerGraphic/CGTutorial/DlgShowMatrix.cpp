// DlgShowMatrix.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "DlgShowMatrix.h"
#include "afxdialogex.h"


// CDlgShowMatrix dialog

IMPLEMENT_DYNAMIC(CDlgShowMatrix, CDialogEx)

CDlgShowMatrix::CDlgShowMatrix(CString name, COpenGLNode* node, CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgShowMatrix::IDD, pParent)
{
	title = name;
	root = node;
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
	this->SetWindowTextW(title);
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

	float m[16];
	for(int i=0; i<16; i++)
		m[i] = 0;

	int left = 10, top = 0;
	ShowMatrix(&dc,CString("I"),m,top,left);
	ShowMatrix(&dc,CString("I"),m,top,left);
}

void CDlgShowMatrix::ShowMatrix(CDC* cdc, CString name, float m[16], int &top, int left)
{
	char buff[1024];

	top += 10;
	cdc->TextOutW(left, top+30, name += " =");
	left += (int)cdc->GetTextExtent(name += " = ").cx;

	for(int i=0; i<4; i++) {
		for(int j=0; j<4; j++) {
			sprintf(buff,"%5.2f",m[i*4+j]);
			cdc->TextOutW(left+j*50,top+i*20,CString(buff));
		}
	}

	top += 20*4 + 10;
}