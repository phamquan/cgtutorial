#include "StdAfx.h"
#include "Rectangle.h"
#include "Point4D.h"

CRectangle::CRectangle() : CGeometric(2,false)
{
}

CRectangle::~CRectangle(void)
{
}

void CRectangle::BeginOpenGL()
{
	glBegin(GL_QUADS);
}