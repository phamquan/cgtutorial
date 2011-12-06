#include "StdAfx.h"
#include "Line.h"

CLine::CLine(CPoint3D begin, CPoint3D end)
{
	name = "line";
	AddChild(new CPoint4D(begin));
	AddChild(new CPoint4D(end));
}

CLine::~CLine(void)
{
}

void CLine::BeginOpenGL()
{
	glBegin(GL_LINES);
}