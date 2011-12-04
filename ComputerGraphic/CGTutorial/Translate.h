#pragma once
#include "transformation.h"

class CTranslate :
	public CTransformation
{
public:
	CTranslate(void);
	virtual ~CTranslate(void);

protected:
	virtual void DoOpenGL();
};

