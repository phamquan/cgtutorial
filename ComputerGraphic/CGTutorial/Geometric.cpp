#include "StdAfx.h"
#include "Geometric.h"

CGeometric::CGeometric(int maxChild, BOOLEAN lockDelete) : COpenGLNode(maxChild,lockDelete)
{
}

CGeometric::~CGeometric()
{
}

void CGeometric::EndOpenGL()
{
	glEnd();
}