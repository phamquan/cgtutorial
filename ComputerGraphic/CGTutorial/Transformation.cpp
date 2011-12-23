#include "StdAfx.h"
#include "Transformation.h"

CTransformation::CTransformation(char* label, int ID) : COpenGLNode(label,ID)
{
}

CTransformation::~CTransformation()
{
}

void CTransformation::SetData(float x, float y, float z, float angle)
{
	data.setCoords(x,y,z,angle);
}

void CTransformation::GetData(float &x, float &y, float &z, float &angle)
{
	x = data.getX();
	y = data.getY();
	z = data.getZ();
	angle = data.getW();
}

CString CTransformation::ToString()
{
	char buff[1024];

	sprintf_s(buff,"(x=%5.2f, y=%5.2f, z=%5.2f)",data.getX(),data.getY(),data.getZ());

	return label + CString(buff);
}

void CTransformation::BeginOpenGL()
{
	glPushMatrix();
}

void CTransformation::EndOpenGL()
{
	glPopMatrix();
}