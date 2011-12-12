#include "StdAfx.h"
#include "Scale.h"

CScale::CScale(float x, float y, float z) : CTransformation("scale",NODE_SCALE)
{
	SetData(x,y,z);
}

CScale::~CScale()
{
}

void CScale::DoOpenGL()
{
	glScalef(data.getX(),data.getY(),data.getZ());
}