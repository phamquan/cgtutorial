#include "StdAfx.h"
#include "Scale.h"

CScale::CScale()
{
	name = "scale";
}

CScale::~CScale()
{
}

void CScale::DoOpenGL()
{
	glScalef(data.getX(),data.getY(),data.getZ());
}