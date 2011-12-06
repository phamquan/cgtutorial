#include "StdAfx.h"
#include "Transformation.h"

CTransformation::CTransformation() : COpenGLNode(-1,false)
{
}

CTransformation::~CTransformation()
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