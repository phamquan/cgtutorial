#include "StdAfx.h"
#include "Translate.h"

CTranslate::CTranslate()
{
	name = "translate";
}

CTranslate::~CTranslate()
{
}

void CTranslate::DoOpenGL()
{
	glTranslatef(data.getX(),data.getY(),data.getZ());
}