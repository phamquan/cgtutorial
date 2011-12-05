#include "StdAfx.h"
#include "Transformation.h"

CTransformation::CTransformation(void)
{
	lockAdd = false;
	lockDelete = false;
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