#pragma once
#include "transformation.h"

class CTranslate :
	public CTransformation
{
public:
	CTranslate(CPoint3D data);
	virtual ~CTranslate();

protected:
	virtual void DoOpenGL();
};

