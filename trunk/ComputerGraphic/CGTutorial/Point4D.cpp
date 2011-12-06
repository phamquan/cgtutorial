#include "StdAfx.h"
#include "Point4D.h"

CPoint4D::CPoint4D(CPoint3D data)
{
	this->data = data;
	name = "point";
}

CPoint4D::~CPoint4D(void)
{
}

CString CPoint4D::ToString()
{
	CString result = name + " (";

	char buff[1024];

	sprintf(buff,"x=%f, y=%f, z=%d",data.getX(),data.getY(),data.getZ());

	return result + CString(buff) + ")";
}

void CPoint4D::DoOpenGL()
{
	glVertex3f(data.getX(),data.getY(),data.getZ());
}

void CPoint4D::EndOpenGL()
{
}