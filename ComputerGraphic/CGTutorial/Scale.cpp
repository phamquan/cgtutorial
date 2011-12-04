#include "StdAfx.h"
#include "Scale.h"


CScale::CScale(void)
{
}

CScale::~CScale(void)
{
}

void CScale::DoOpenGL()
{
	glScalef(data.getX(),data.getY(),data.getZ());
}