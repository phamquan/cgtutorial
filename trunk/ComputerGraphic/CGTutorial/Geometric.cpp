#include "StdAfx.h"
#include "Geometric.h"

CGeometric::CGeometric(char* label, int ID) : COpenGLNode(label,ID)
{
}

CGeometric::~CGeometric()
{
}

void CGeometric::EndOpenGL()
{
	glEnd();
}