#include "StdAfx.h"
#include "Rectangle.h"
#include "Point4D.h"

CRectangle::CRectangle(float top, float left, float bottom, float right) : CGeometric("rectangle",NODE_RECTANGLE)
{
	SetData(top,left,bottom,right);
}

CRectangle::~CRectangle()
{
}

void CRectangle::SetData(float top, float left, float bottom, float right)
{
	data1.setCoords(top,left,0);
	data2.setCoords(bottom,right,0);
}

void CRectangle::GetData(float &top, float &left, float &bottom, float &right)
{
	top = data1.getX();
	left = data1.getY();
	bottom = data2.getX();
	right = data2.getY();
}

CString CRectangle::ToString()
{
	char buff[128];

	sprintf_s(buff,"(top=%5.2f, left=%5.2f, bottom=%5.2f, right=%5.2f)",data1.getX(),data1.getY(),data2.getX(),data2.getY());

	return label + CString(buff);
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