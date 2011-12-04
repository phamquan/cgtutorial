#include "StdAfx.h"
#include "Transformation.h"

CTransformation::CTransformation(void)
{
}

CTransformation::~CTransformation(void)
{
}

void CTransformation::SetData(CPoint3D src)
{
	data = src;
}

void CTransformation::BeginOpenGL()
{
	glPushMatrix();
}

void CTransformation::EndOpenGL()
{
	glPopMatrix();
}