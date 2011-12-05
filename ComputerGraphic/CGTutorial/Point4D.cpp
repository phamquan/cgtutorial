#include "StdAfx.h"
#include "Point4D.h"

CPoint4D::CPoint4D(CPoint3D data)
{
	this->data = data;
}

CPoint4D::~CPoint4D(void)
{
}

void CPoint4D::DoOpenGL()
{
	glVertex3f(data.getX(),data.getY(),data.getZ());
}

void CPoint4D::EndOpenGL()
{
}