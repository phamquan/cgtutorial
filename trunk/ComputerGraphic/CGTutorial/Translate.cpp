#include "StdAfx.h"
#include "Translate.h"

CTranslate::CTranslate(CPoint3D data) : CTransformation(data,"translate",NODE_TRANSLATE)
{
}

CTranslate::~CTranslate()
{
}

void CTranslate::DoOpenGL()
{
	glTranslatef(data.getX(),data.getY(),data.getZ());
}