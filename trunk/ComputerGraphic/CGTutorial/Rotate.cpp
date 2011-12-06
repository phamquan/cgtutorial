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
	glRotatef(data.getW(),data.getX(),data.getY(),data.getZ());
}
