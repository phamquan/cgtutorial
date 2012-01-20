#pragma once
#include "transformation.h"
class CTranslate :
	public CTransformation
{
public:

	CTranslate(float x, float y, float z) : CTransformation("translate",NODE_TRANSLATE)
	{
		SetData(x,y,z);
	}

	CTranslate::~CTranslate() {}

	virtual void CTranslate::DoOpenGL()
	{
		glTranslatef(data.getX(),data.getY(),data.getZ());
	}
};

