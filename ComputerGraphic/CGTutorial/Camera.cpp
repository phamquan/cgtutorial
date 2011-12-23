#include "StdAfx.h"
#include "Camera.h"

CCamera::CCamera(float xpos, float ypos, float zpos, float xlook, float ylook, float zlook, float xup, float yup, float zup) : COpenGLNode("camera",NODE_CAMERA)
{
	SetData(xpos, ypos, zpos, xlook, ylook, zlook, xup, yup, zup);
}

CCamera::~CCamera()
{
}

void CCamera::SetData(float xpos, float ypos, float zpos, float xlook, float ylook, float zlook, float xup, float yup, float zup)
{
	pos.setCoords(xpos, ypos, zpos);
	look.setCoords(xlook, ylook, zlook);
	up.setCoords(xup, yup, zup);
}
void CCamera::GetData(float &xpos, float &ypos, float &zpos, float &xlook, float &ylook, float &zlook, float &xup, float &yup, float &zup)
{
	xpos = pos.getX();
	ypos = pos.getY();
	zpos = pos.getZ();
	xlook = look.getX();
	ylook = look.getY();
	zlook = look.getZ();
	xup = up.getX();
	yup = up.getY();
	zup = up.getZ();
}
	
CString CCamera::ToString()
{
	char buff[1024];

	sprintf_s(buff,"(xpos=%5.2f, ypos=%5.2f, zpos=%5.2f, xlook=%5.2f, ylook=%5.2f, zlook=%5.2f, xup=%5.2f, yup=%5.2f, zup=%5.2f)",
		pos.getX(),pos.getY(),pos.getZ(),look.getX(),look.getY(),look.getZ(),up.getX(),up.getY(),up.getZ());

	return label + CString(buff);
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