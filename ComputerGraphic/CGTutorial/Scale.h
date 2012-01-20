#pragma once
#include "transformation.h"
class CScale :
	public CTransformation
{
public:

	CScale(float x, float y, float z) : CTransformation("scale",NODE_SCALE)
	{
		SetData(x,y,z);
	}

	CScale::~CScale() {}

	virtual void CScale::DoOpenGL()
	{
		glScalef(data.getX(),data.getY(),data.getZ());
	}
};

