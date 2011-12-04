#include "StdAfx.h"
#include "Rotate.h"


CRotate::CRotate(void)
{
}

CRotate::~CRotate(void)
{
}

void CRotate::DoOpenGL()
{
	glScalef(data.getX(),data.getY(),data.getZ());
}
