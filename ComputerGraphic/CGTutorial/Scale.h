#pragma once
#include "transformation.h"
class CScale :
	public CTransformation
{
public:
	CScale(CPoint3D data);
	virtual ~CScale();

protected:
	virtual void DoOpenGL();
};

