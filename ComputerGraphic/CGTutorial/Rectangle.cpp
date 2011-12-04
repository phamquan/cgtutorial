#include "StdAfx.h"
#include "Rectangle.h"


CRectangle::CRectangle(void)
{
}

CRectangle::~CRectangle(void)
{
}

void CRectangle::BeginOpenGL()
{
	glBegin(GL_LINES);
}