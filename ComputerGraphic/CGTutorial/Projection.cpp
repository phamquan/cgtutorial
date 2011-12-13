#include "StdAfx.h"
#include "Projection.h"

CProjection::CProjection(float left, float right, float bottom, float top, float mnear, float mfar, int type) : COpenGLNode("projection",NODE_PROJECTION)
{
	SetData(left, right, bottom, top, mnear, mfar, type);
}

CProjection::~CProjection()
{
}

void CProjection::SetData(float left, float right, float bottom, float top, float mnear, float mfar, int type)
{
	data1.setCoords(left,right,bottom);
	data2.setCoords(top,mnear,mfar);
	this->type = type;
}

void CProjection::GetData(float &left, float &right, float &bottom, float &top, float &mnear, float &mfar, int &type)
{
	left = data1.getX();
	right = data1.getY();
	bottom = data1.getZ();
	top = data2.getX();
	mnear = data2.getY();
	mfar = data2.getZ();
	type = this->type;
}

	
CString CProjection::ToString()
{
	CString result = label + " (";

	char buff[1024];

	sprintf(buff,"left=%5.2f, right=%5.2f, bottom=%5.2f, top=%5.2f, near=%5.2f, far=%5.2f",
			data1.getX(),data1.getY(),data1.getZ(),data2.getX(),data2.getY(),data2.getZ());

	if(type == ORTHO)
		return result + "type=ortho " + CString(buff) + ")";	
	else
		return result + "type=frustum " + CString(buff) + ")";
}

void CProjection::BeginOpenGL()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

void CProjection::DoOpenGL()
{
	if(type == ORTHO)
		glOrtho(data1.getX(),data1.getY(),data1.getZ(),data2.getX(),data2.getY(),data2.getZ());
	else
		glFrustum(data1.getX(),data1.getY(),data1.getZ(),data2.getX(),data2.getY(),data2.getZ());
}