#include "StdAfx.h"
#include "Geometric.h"


CGeometric::CGeometric(void)
{
	lockAdd = true;
	lockDelete = true;
}

CGeometric::~CGeometric(void)
{
}

void CGeometric::EndOpenGL()
{
	glEnd();
}