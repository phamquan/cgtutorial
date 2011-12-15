// DlgMatrix.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "DlgMatrix.h"
#include "afxdialogex.h"


// CDlgMatrix dialog

IMPLEMENT_DYNAMIC(CDlgMatrix, CDialogEx)

CDlgMatrix::CDlgMatrix(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgMatrix::IDD, pParent)
{

}

CDlgMatrix::~CDlgMatrix()
{
}

void CDlgMatrix::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgMatrix, CDialogEx)
END_MESSAGE_MAP()


// CDlgMatrix message handlers
void CDlgMatrix::ShowMatrix(CDC* cdc, float m[16], int top, int left)
{
	char buff[128];
	cdc->MoveTo(left+5,top-5);
	cdc->LineTo(left-5,top-5);
	cdc->LineTo(left-5,top+80);
	cdc->LineTo(left+5,top+80);
	for(int i=0; i<4; i++) {
		for(int j=0; j<4; j++) {
			sprintf(buff,"%5.3f",m[i+j*4]);
			cdc->TextOutW(left+j*50,top+i*20,CString(buff));
		}
	}
	left += 185;
	cdc->MoveTo(left-5,top-5);
	cdc->LineTo(left+5,top-5);
	cdc->LineTo(left+5,top+80);
	cdc->LineTo(left-5,top+80);
}

void CDlgMatrix::ShowPoint(CDC* cdc, CPoint3D point, int top, int left)
{
	char buff[128];
	cdc->MoveTo(left+5,top-5);
	cdc->LineTo(left-5,top-5);
	cdc->LineTo(left-5,top+80);
	cdc->LineTo(left+5,top+80);

	sprintf(buff,"%5.3f",point.getX());
	cdc->TextOutW(left,top,CString(buff));
	sprintf(buff,"%5.3f",point.getY());
	cdc->TextOutW(left,top+20,CString(buff));
	sprintf(buff,"%5.3f",point.getZ());
	cdc->TextOutW(left,top+40,CString(buff));
	sprintf(buff,"%5.3f",point.getW());
	cdc->TextOutW(left,top+60,CString(buff));

	left += 35;
	cdc->MoveTo(left-5,top-5);
	cdc->LineTo(left+5,top-5);
	cdc->LineTo(left+5,top+80);
	cdc->LineTo(left-5,top+80);
}