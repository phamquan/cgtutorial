#include "StdAfx.h"
#include "Point4D.h"

CPoint4D::CPoint4D(float x, float y, float z) : CGeometric("point",NODE_POINT)
{
	SetData(x, y, z);
}

CPoint4D::~CPoint4D()
{
}

void CPoint4D::SetData(float x, float y, float z)
{
	data1.setCoords(x, y, z);
}

void CPoint4D::GetData(float &x, float &y, float &z)
{
	x = data1.getX();
	y = data1.getY();
	z = data1.getZ();
}

CString CPoint4D::ToString()
{
	char buff[1024];

	sprintf_s(buff,"(x=%5.2f, y=%5.2f, z=%5.2f)",data1.getX(),data1.getY(),data1.getZ());

	return label + CString(buff);
}

void CPoint4D::BeginOpenGL()
{
	glBegin(GL_POINT);
}

void CPoint4D::DoOpenGL()
{
	glVertex3f(data1.getX(),data1.getY(),data1.getZ());
}