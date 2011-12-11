#include "StdAfx.h"
#include "Scale.h"

CScale::CScale(CPoint3D data) : CTransformation(data,"scale",NODE_SCALE)
{
}

CScale::~CScale()
{
}

void CScale::DoOpenGL()
{
	glScalef(data.getX(),data.getY(),data.getZ());
}