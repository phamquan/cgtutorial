#include "StdAfx.h"
#include "CGTutorial.h"
#include "DlgProjectionMatrix.h"

IMPLEMENT_DYNAMIC(CDlgProjectionMatrix, CDlgMatrix)

CDlgProjectionMatrix::CDlgProjectionMatrix(CProjection *proj, CWnd* pParent /*=NULL*/)
	: CDlgMatrix(pParent)
{
	projection = proj;
}

CDlgProjectionMatrix::~CDlgProjectionMatrix(void)
{
}

void CDlgProjectionMatrix::DoDataExchange(CDataExchange* pDX)
{
	CDlgMatrix::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDlgProjectionMatrix, CDlgMatrix)
	ON_WM_PAINT()
END_MESSAGE_MAP()

BOOL CDlgProjectionMatrix::OnInitDialog()
{
	CDlgMatrix::OnInitDialog();

	// TODO:  Add extra initialization here
	this->SetWindowTextW(CString("Projection Matrix"));
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgProjectionMatrix::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDlgMatrix::OnPaint() for painting messages
	int top = 0, left = 10;
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
	
	for(int i=0; i<out->GetSize(); i++)
	{
		char buff[128];
		sprintf_s(buff,"P%d''' = P*P%d''",i+1,i+1);
		ShowMatrixPoint(&dc,CString(buff),sum,(CPoint3D*)in->GetAt(i),(CPoint3D*)out->GetAt(i),top,left);
	}
}

void CDlgProjectionMatrix::SetData(CPtrArray* in, CPtrArray* out)
{
	this->in = in;
	this->out = out;

	CalProjection();
	CalMatrixPoint();

	Invalidate();
}

void CDlgProjectionMatrix::CalProjection()
{
	matrix.RemoveAll();

	float mleft,mright,mbottom,mtop,mnear,mfar;
	projection->GetData(mleft,mright,mbottom,mtop,mnear,mfar,type);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	if(type == ORTHO) {
		glLoadIdentity();
		glTranslatef(-(mleft+mright)/2, -(mbottom+mtop)/2, -(-mnear-mfar)/2);
		glGetFloatv(GL_MODELVIEW_MATRIX,sum);

		matrix.Add(new Element(CString("T"),CString("glTranslate(x=-(left+right)/2, y=-(bottom+top)/2, z=-(-near-far)/2)"),sum));

		float m[16];
		glLoadIdentity();
		glScalef(2/(mright-mleft), 2/(mtop-mbottom), -2/(mfar-mnear));
		glGetFloatv(GL_MODELVIEW_MATRIX,m);
		glMultMatrixf(sum);
		glGetFloatv(GL_MODELVIEW_MATRIX,sum);

		matrix.Add(new Element(CString("S"),CString("glScale(x=2/(right-left), y=2/(top-bottom), z=-2/(far-near))"),m));
		matrix.Add(new Element(CString("P = S*T"),CString(),sum));

	} else {
		glLoadIdentity();
		glGetFloatv(GL_MODELVIEW_MATRIX,sum);
		sum[8] = (mright+mleft)/2/mnear;
		sum[9] = (mtop+mbottom)/2/mnear;

		matrix.Add(new Element(CString("H"),CString(),sum));

		float m[16];
		glLoadIdentity();
		glScalef(2*mnear/(mright-mleft), 2*mnear/(mtop-mbottom), 1);
		glGetFloatv(GL_MODELVIEW_MATRIX,m);
		glMultMatrixf(sum);
		glGetFloatv(GL_MODELVIEW_MATRIX,sum);

		matrix.Add(new Element(CString("S"),CString("glScale(x=2*near/(right-left), y=2*near/(top-bottom), z=1)"),m));

		glLoadIdentity();
		glGetFloatv(GL_MODELVIEW_MATRIX,m);

		m[10] = (mnear+mfar)/(mnear-mfar);
		m[11] = -1;
		m[14] = 2*mnear*mfar/(mnear-mfar);
		m[15] = 0;

		glLoadMatrixf(m);
		glMultMatrixf(sum);
		glGetFloatv(GL_MODELVIEW_MATRIX,sum);
		
		matrix.Add(new Element(CString("N"),CString(),m));

		matrix.Add(new Element(CString("P = N*S*H"),CString(),sum));
	}

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}