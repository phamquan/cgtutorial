#include "StdAfx.h"
#include "Line.h"

CLine::CLine() : CGeometric("line",NODE_LINE)
{
}

CLine::~CLine()
{
}

void CLine::BeginOpenGL()
{
	glBegin(GL_LINES);
}