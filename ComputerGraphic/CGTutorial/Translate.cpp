#include "StdAfx.h"
#include "Translate.h"

CTranslate::CTranslate(float x, float y, float z) : CTransformation("translate",NODE_TRANSLATE)
{
	SetData(x,y,z);
}

CTranslate::~CTranslate()
{
}

void CTranslate::DoOpenGL()
{
	glTranslatef(data.getX(),data.getY(),data.getZ());
}