// DlgProjectionMatrix.cpp : implementation file
//

#include "stdafx.h"
#include "CGTutorial.h"
#include "DlgProjectionMatrix.h"


// CDlgProjectionMatrix dialog

IMPLEMENT_DYNAMIC(CDlgProjectionMatrix, CDlgMatrix)

CDlgProjectionMatrix::CDlgProjectionMatrix(CEnvironment *env, CWnd* pParent /*=NULL*/)
	: CDlgMatrix(pParent)
{
	environment = env;
}

CDlgProjectionMatrix::~CDlgProjectionMatrix()
{
}

void CDlgProjectionMatrix::DoDataExchange(CDataExchange* pDX)
{
	CDlgMatrix::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgProjectionMatrix, CDlgMatrix)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgProjectionMatrix message handlers

void CDlgProjectionMatrix::Refresh()
{
	matrix.RemoveAll();

	float mleft,mright,mbottom,mtop,mnear,mfar;
	environment->GetProjection()->GetData(mleft,mright,mbottom,mtop,mnear,mfar,type);

	if(type == ORTHO) {
		float T[16];
		T[0] = 1;		T[4] = 0;		T[8] = 0;		T[12] = -(mleft+mright)/2;
		T[1] = 0;		T[5] = 1;		T[9] = 0;		T[13] = -(mbottom+mtop)/2;
		T[2] = 0;		T[6] = 0;		T[10] = 1;		T[14] = -(-mnear-mfar)/2;
		T[3] = 0;		T[7] = 0;		T[11] = 0;		T[15] = 1;

		matrix.Add(new Element(CString("T"),CString("glTranslate(x=-(left+right)/2, y=-(bottom+top)/2, z=-(-near-far)/2)"),T));

		float S[16];
		S[0] = 2/(mright-mleft);		S[4] = 0;						S[8] = 0;						S[12] = 0;
		S[1] = 0;						S[5] = 2/(mtop-mbottom);		S[9] = 0;						S[13] = 0;
		S[2] = 0;						S[6] = 0;						S[10] = -2/(mfar-mnear);		S[14] = 0;
		S[3] = 0;						S[7] = 0;						S[11] = 0;						S[15] = 1;

		matrix.Add(new Element(CString("S"),CString("glScale(x=2/(right-left), y=2/(top-bottom), z=-2/(far-near))"),S));

		MultMatrixMatrix(S,T,sum);
		
		matrix.Add(new Element(CString("P = S*T"),CString(),sum));

	} else {
		float H[16];
		H[0] = 1;		H[4] = 0;		H[8] = (mright+mleft)/2/mnear;		H[12] = 0;
		H[1] = 0;		H[5] = 1;		H[9] = (mtop+mbottom)/2/mnear;		H[13] = 0;
		H[2] = 0;		H[6] = 0;		H[10] = 1;							H[14] = 0;
		H[3] = 0;		H[7] = 0;		H[11] = 0;							H[15] = 1;

		matrix.Add(new Element(CString("H"),CString(),H));

		float S[16];
		S[0] = 2*mnear/(mright-mleft);		S[4] = 0;							S[8] = 0;		S[12] = 0;
		S[1] = 0;							S[5] = 2*mnear/(mtop-mbottom);		S[9] = 0;		S[13] = 0;
		S[2] = 0;							S[6] = 0;							S[10] = 1;		S[14] = 0;
		S[3] = 0;							S[7] = 0;							S[11] = 0;		S[15] = 1;

		matrix.Add(new Element(CString("S"),CString(),S));
		
		float N[16];
		N[0] = 1;		N[4] = 0;		N[8] = 0;								N[12] = 0;
		N[1] = 0;		N[5] = 1;		N[9] = 0;								N[13] = 0;
		N[2] = 0;		N[6] = 0;							N[10] = (mnear+mfar)/(mnear-mfar);		N[14] = 2*mnear*mfar/(mnear-mfar);
		N[3] = 0;		N[7] = 0;							N[11] = -1;								N[15] = 0;

		matrix.Add(new Element(CString("N"),CString(),N));
		

		

		glLoadIdentity();
		glGetFloatv(GL_MODELVIEW_MATRIX,m);

		m[10] = ;
		m[11] = ;
		m[14] = ;
		m[15] = 0;

		glLoadMatrixf(m);
		glMultMatrixf(sum);
		glGetFloatv(GL_MODELVIEW_MATRIX,sum);
		
		matrix.Add(new Element(CString("N"),CString(),m));

		matrix.Add(new Element(CString("P = N*S*H"),CString(),sum));
	}
	Invalidate();
}

void CDlgProjectionMatrix::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDlgMatrix::OnPaint() for painting messages
	CRect rect;
	GetClientRect(&rect);

	rect.top += 10;

	dc.DrawText(CString("CALCULATION"),-1,rect,DT_CENTER);

	int top = 30, left = 10;

	if(type == ORTHO) {
		for(int i=0; i<matrix.GetSize(); i++)
		{
			Element* e = (Element*)matrix.GetAt(i);
			ShowMatrix(&dc,e->font,e->tail,e->data,top,left);
		}
	} else {
		CString n[16] = {CString("1.000"),CString("0.000"),CString("0.000"),CString("0.000"),
						CString("0.000"),CString("1.000"),CString("0.000"),CString("0.000"),
						CString("(right+left)/(2*near)"), CString("(top+bottom)/(2*near)"),CString("1.000"),CString("0.000"),
						CString("0.000"),CString("0.000"),CString("0.000"),CString("1.000")};
		Element* e = (Element*)matrix.GetAt(0);
		ShowMatrixMatrix(&dc,e->font,n,e->data,top,left);
	
		e = (Element*)matrix.GetAt(1);
		ShowMatrix(&dc,e->font,e->tail,e->data,top,left);

		n[8] = CString("0.000");
		n[9] = CString("0.000");
		n[10] = CString("(near+far)/(near-far)");
		n[11] = CString("-1.000");
		n[14] = CString("2*near*far/(near-far)");
		n[15] = CString("0.000");

		e = (Element*)matrix.GetAt(2);
		ShowMatrixMatrix(&dc,e->font,n,e->data,top,left);

		e = (Element*)matrix.GetAt(3);
		ShowMatrix(&dc,e->font,e->tail,e->data,top,left);
	}
}
