// DlgMatrix.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "DlgMatrix.h"
#include "afxdialogex.h"


// CDlgMatrix dialog

IMPLEMENT_DYNAMIC(CDlgMatrix, CDialog)

CDlgMatrix::CDlgMatrix(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMatrix::IDD, pParent)
{

}

CDlgMatrix::~CDlgMatrix()
{
	Clear();
}

void CDlgMatrix::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgMatrix, CDialog)
END_MESSAGE_MAP()


// CDlgMatrix message handlers
void CDlgMatrix::ShowMatrix(CDC* cdc, CString name, CString rear, float m[16], int &top, int left)
{
	top += 10;
	name += " =";
	cdc->TextOutW(left, top+30, name);
	left += (int)cdc->GetTextExtent(name).cx;

	int bottom = ShowMatrix(cdc,m,top,left);

	cdc->TextOutW(left+50,top+30,rear);

	top = bottom;
}

int CDlgMatrix::ShowMatrix(CDC* cdc, float m[16], const int top, int &left)
{
	char buff[128];
	CString n[16];
	for(int i=0; i<16; i++) {
		sprintf_s(buff,"%5.3f",m[i]);
		n[i] = CString(buff);
	}
	return ShowMatrix(cdc,n,top,left);
}

int CDlgMatrix::ShowMatrix(CDC* cdc, CString m[16], const int top, int &left)
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
	return bottom + 5;
}

void CDlgMatrix::ShowMatrixMatrix(CDC* cdc, CString name, CString n[16], float m[16], int &top, int left)
{
	top += 10;
	name += " =";
	cdc->TextOutW(left, top+30, name);
	left += (int)cdc->GetTextExtent(name).cx;

	int bottom = ShowMatrix(cdc,n,top,left);
	cdc->TextOutW(left+5,top+30,CString("="));
	left += cdc->GetTextExtent(CString(" =")).cx;
	ShowMatrix(cdc,m,top,left);
	top = bottom;
}

void CDlgMatrix::ShowPoint(CDC* cdc, CString name, CHomoPoint point, int top, int left)
{
	top += 10;
	name += " =";
	cdc->TextOutW(left, top+30, name);
	left += (int)cdc->GetTextExtent(name).cx;

	ShowPoint(cdc,point,top,left);
}

void CDlgMatrix::ShowPoint(CDC* cdc, CHomoPoint point, const int top, int &left)
{
	int height = cdc->GetTextExtent(CString("ABC")).cy;
	int bottom = top + height*4 + 5*4;
	left += 5;
	cdc->MoveTo(left+10,top-5);
	cdc->LineTo(left,top-5);
	cdc->LineTo(left,bottom);
	cdc->LineTo(left+10,bottom);
	left += 5;

	float *x = (float*)point;
	
	char buff[128];
	int max = 0;
	for(int i=0; i<4; i++) {//row
		sprintf_s(buff,"%5.3f",x[i]);
		int width = cdc->GetTextExtent(CString(buff)).cx;
		cdc->TextOutW(left,top+(height+5)*i,CString(buff));
		if(max < width)
			max = width;
	}
	left += max + 5;
	cdc->MoveTo(left-10,top-5);
	cdc->LineTo(left,top-5);
	cdc->LineTo(left,bottom);
	cdc->LineTo(left-10,bottom);
}

void CDlgMatrix::Clear()
{
	for(int i=0; i<matrix.GetSize(); i++) 
	{
		delete matrix.GetAt(i);
	}
	matrix.RemoveAll();
}