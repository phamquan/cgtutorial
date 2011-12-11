#include "StdAfx.h"
#include "Camera.h"

CCamera::CCamera(CPoint3D pos, CPoint3D look, CPoint3D up) : COpenGLNode("camera",NODE_CAMERA)
{
	this->pos = pos;
	this->look = look;
	this->up = up;
}

CCamera::~CCamera()
{
}

CString CCamera::ToString()
{
	CString result = label + " (";

	char buff[1024];

	sprintf(buff,"xpos=%5.2f, ypos=%5.2f, zpos=%5.2f, xlook=%5.2f, ylook=%5.2f, zlook=%5.2f, xup=%5.2f, yup=%5.2f, zup=%5.2f",
		pos.getX(),pos.getY(),pos.getZ(),look.getX(),look.getY(),look.getZ(),up.getX(),up.getY(),up.getZ());

	return result + CString(buff) + ")";
}

void CCamera::BeginOpenGL()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void CCamera::DoOpenGL()
{

	gluLookAt(pos.getX(),pos.getY(),pos.getZ(),look.getX(),look.getY(),look.getZ(),up.getX(),up.getY(),up.getZ());
}