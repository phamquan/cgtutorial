#include "StdAfx.h"
#include "Line.h"

CLine::CLine() : CGeometric(2,false)
{
	name = "line";
}

CLine::~CLine(void)
{
}

void CLine::BeginOpenGL()
{
	glBegin(GL_LINES);
}