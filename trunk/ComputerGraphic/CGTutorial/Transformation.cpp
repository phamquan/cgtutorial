#include "StdAfx.h"
#include "Transformation.h"

CTransformation::CTransformation() : COpenGLNode(-1,false)
{
}

CTransformation::~CTransformation()
{
}

void CTransformation::SetData(CPoint3D src)
{
	data = src;
}

CString CTransformation::ToString()
{
	CString result = name + " (";

	char buff[1024];

	sprintf(buff,"x=%f, y=%f, z=%f",data.getX(),data.getY(),data.getZ());

	return result + CString(buff) + ")";
}

void CTransformation::BeginOpenGL()
{
	glPushMatrix();
}

void CTransformation::EndOpenGL()
{
	glPopMatrix();
}