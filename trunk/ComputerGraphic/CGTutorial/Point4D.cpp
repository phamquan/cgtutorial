#include "StdAfx.h"
#include "Point4D.h"

CPoint4D::CPoint4D(CPoint3D data) : CGeometric("point",NODE_POINT)
{
	this->data = data;
}

CPoint4D::~CPoint4D(void)
{
}

CString CPoint4D::ToString()
{
	CString result = label + " (";

	char buff[1024];

	sprintf(buff,"x=%5.2f, y=%5.2f, z=%5.2f",data.getX(),data.getY(),data.getZ());

	return result + CString(buff) + ")";
}

void CPoint4D::DoOpenGL()
{
	glVertex3f(data.getX(),data.getY(),data.getZ());
}

void CPoint4D::EndOpenGL()
{
}