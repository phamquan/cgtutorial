#include "StdAfx.h"
#include "Rectangle.h"
#include "Point4D.h"

CRectangle::CRectangle()
{
}

CRectangle::CRectangle()
{
	AddChild(new CPoint4D(begin));
	AddChild(new CPoint4D(CPoint3D(begin.getX(),end.getY(),0)));
	AddChild(new CPoint4D(end));
	AddChild(new CPoint4D(CPoint3D(end.getX(),begin.getY(),0)));
}

CRectangle::~CRectangle(void)
{
}

void CRectangle::BeginOpenGL()
{
	glBegin(GL_QUADS);
}