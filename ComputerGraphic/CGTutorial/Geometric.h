#pragma once
#include "openglnode.h"

class CGeometric :
	public COpenGLNode
{
public:
	CGeometric(void);
	virtual ~CGeometric(void);

protected:
	virtual void EndOpenGL();
};

