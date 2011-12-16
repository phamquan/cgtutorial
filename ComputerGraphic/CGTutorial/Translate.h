#pragma once
#include "transformation.h"

class CTranslate :
	public CTransformation
{
public:
	CTranslate(float x, float y, float z);
	virtual ~CTranslate();

	void DoOpenGL();
};

