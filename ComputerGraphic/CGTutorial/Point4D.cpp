#include "StdAfx.h"
#include "Point4D.h"

CPoint4D::CPoint4D(CPoint3D point) : CGeometric("point",NODE_POINT)
{
	data1 = point;
}

CPoint4D::~CPoint4D()
{
}

CString CPoint4D::ToString()
{
	CString result = label + " (";

	char buff[1024];

	sprintf(buff,"x=%5.2f, y=%5.2f, z=%5.2f",data1.getX(),data1.getY(),data1.getZ());

	return result + CString(buff) + ")";
}

void CPoint4D::BeginOpenGL()
{
	glBegin(GL_POINT);
}

void CPoint4D::DoOpenGL()
{
	glVertex3f(data1.getX(),data1.getY(),data1.getZ());
}