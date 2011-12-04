#include "StdAfx.h"
#include "Translate.h"

CTranslate::CTranslate(void)
{
}

CTranslate::~CTranslate(void)
{
}

void CTranslate::DoOpenGL()
{
	glTranslatef(data.getX(),data.getY(),data.getZ());
}