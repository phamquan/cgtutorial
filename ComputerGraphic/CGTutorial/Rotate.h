#pragma once
#include "transformation.h"
class CRotate :
	public CTransformation
{
public:
	CRotate(void);
	virtual ~CRotate(void);

protected:
	virtual void DoOpenGL();
};

