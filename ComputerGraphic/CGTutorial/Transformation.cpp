#include "StdAfx.h"
#include "Transformation.h"

CTransformation::CTransformation(char* label, int ID) : COpenGLNode(label,ID)
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