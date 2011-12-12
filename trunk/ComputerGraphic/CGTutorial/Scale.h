#pragma once
#include "transformation.h"
class CScale :
	public CTransformation
{
public:
	CScale(float x, float y, float z);
	virtual ~CScale();

protected:
	virtual void DoOpenGL();
};

