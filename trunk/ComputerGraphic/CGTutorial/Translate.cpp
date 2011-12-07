#include "StdAfx.h"
#include "Translate.h"

CTranslate::CTranslate() : CTransformation("translate",NODE_TRANSLATE)
{
}

CTranslate::~CTranslate()
{
}

void CTranslate::DoOpenGL()
{
	glTranslatef(data.getX(),data.getY(),data.getZ());
}