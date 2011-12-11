#include "StdAfx.h"
#include "Rectangle.h"
#include "Point4D.h"

CRectangle::CRectangle(float top, float left, float bottom, float right) : CGeometric("rectangle",NODE_RECTANGLE)
{
	data1.setCoords(top,left,0);
	data2.setCoords(bottom,right,0);
}

CRectangle::~CRectangle()
{
}

CString CRectangle::ToString()
{
	CString result = label + " (";

	char buff[1024];

	sprintf(buff,"top=%5.2f, left=%5.2f, bottom=%5.2f, right=%5.2f",data1.getX(),data1.getY(),data2.getX(),data2.getY());

	return result + CString(buff) + ")";
}

void CRectangle::BeginOpenGL()
{
	glBegin(GL_QUADS);
}

void CRectangle::DoOpenGL()
{
	glVertex3f(data1.getX(),data1.getY(),0);
	glVertex3f(data1.getX(),data2.getY(),0);
	glVertex3f(data2.getX(),data2.getY(),0);
	glVertex3f(data2.getX(),data1.getY(),0);
}