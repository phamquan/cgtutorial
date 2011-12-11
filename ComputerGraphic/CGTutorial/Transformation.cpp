#include "StdAfx.h"
#include "Transformation.h"

CTransformation::CTransformation(CPoint3D src, char* label, int ID) : COpenGLNode(label,ID)
{
	data = src;
}

CTransformation::~CTransformation()
{
}

CString CTransformation::ToString()
{
	CString result = label + " (";

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