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

void CDlgMatrix::ShowMatrixPoint(CDC* cdc, CString name, float m[16], CPoint3D* in, CPoint3D* out, int &top, int left)
{
	top += 10;
	name += " =";
	cdc->TextOutW(left, top+30, name);
	left += (int)cdc->GetTextExtent(name).cx;

	int bottom = ShowMatrix(cdc,m,top,left);
	ShowPoint(cdc,*in,top,left);

	cdc->TextOutW(left+5,top+30,CString("="));
	left += cdc->GetTextExtent(CString(" =")).cx;

	ShowPoint(cdc,*out,top,left);

	top = bottom;
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

void CDlgMatrix::ShowPoint(CDC* cdc, CString name, CHomoPoint point, int top, int left)
{
	top += 10;
	name += " =";
	cdc->TextOutW(left, top+30, name);
	left += (int)cdc->GetTextExtent(name).cx;

	ShowPoint(cdc,point,top,left);
}

void CDlgMatrix::ShowPointPoint(CDC* cdc, CString name, CHomoPoint point1, CHomoPoint point2, int top, int left) {
	top += 10;
	name += " =";
	cdc->TextOutW(left, top+30, name);
	left += (int)cdc->GetTextExtent(name).cx;

	ShowPoint(cdc,point1,top,left);
	cdc->TextOutW(left+5,top+30,CString("="));
	left += cdc->GetTextExtent(CString(" =")).cx;
	ShowPoint(cdc,point2,top,left);
}

//void CDlgMatrix::ShowMatrixPoint(CDC* cdc, CString matrix, CString point, int &top, int left)
//{
//	if(in != NULL)
//	{
//		out->RemoveAll();
//		for(int i=0; i<in->GetSize(); i++) {
//			CPoint3D* p = (CPoint3D*)in->GetAt(i);
//			char buf[128];
//			_itoa_s(i+1,buf,10);
//			//out->Add(ShowMatrixPoint(cdc,matrix,CString("P") + CString(buf) + point,sum,*p,top,left));
//		}
//	}
//}

void CDlgMatrix::CalMatrixPoint()
{
	out->RemoveAll();
	for(int i=0; i<in->GetSize(); i++) {
		out->Add(new CPoint3D(MultMatrixPoint(sum,*((CPoint3D*)in->GetAt(i)))));
	}
}