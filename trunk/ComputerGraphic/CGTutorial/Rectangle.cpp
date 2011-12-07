#include "StdAfx.h"
#include "Rectangle.h"
#include "Point4D.h"

CRectangle::CRectangle() : CGeometric("rectangle",NODE_RECTANGLE)
{
}

CRectangle::~CRectangle(void)
{
}

void CRectangle::BeginOpenGL()
{
	glBegin(GL_QUADS);
}