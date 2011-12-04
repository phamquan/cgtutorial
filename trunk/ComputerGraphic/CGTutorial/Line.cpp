#include "StdAfx.h"
#include "Line.h"


CLine::CLine(void)
{
}

CLine::~CLine(void)
{
}

void CLine::BeginOpenGL()
{
	glBegin(GL_LINES);
}