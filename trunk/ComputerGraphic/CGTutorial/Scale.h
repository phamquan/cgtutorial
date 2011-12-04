#pragma once
#include "transformation.h"
class CScale :
	public CTransformation
{
public:
	CScale(void);
	virtual ~CScale(void);

protected:
	virtual void DoOpenGL();
};

