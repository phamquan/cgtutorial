#include "StdAfx.h"
#include "Line.h"

CLine::CLine(CPoint3D begin, CPoint3D end) : CGeometric("line",NODE_LINE)
{
	data1 = begin;
	data2 = end;
}

CLine::~CLine()
{
}

CString CLine::ToString()
{
	CString result = label + " (";

	char buff[1024];

	sprintf(buff,"x1=%5.2f, y1=%5.2f, z1=%5.2f, x2=%5.2f, y2=%5.2f, z2=%5.2f",data1.getX(),data1.getY(),data1.getZ(),data2.getX(),data2.getY(),data2.getZ());

	return result + CString(buff) + ")";
}

void CLine::BeginOpenGL()
{
	glBegin(GL_LINES);
}

void CLine::DoOpenGL()
{
	glVertex3f(data1.getX(),data1.getY(),data1.getZ());
	glVertex3f(data2.getX(),data2.getY(),data2.getZ());
}
