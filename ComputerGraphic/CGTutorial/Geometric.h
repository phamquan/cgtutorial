#pragma once
#include "openglnode.h"

class CGeometric :
	public COpenGLNode
{
public:
	CGeometric(int maxChild, BOOLEAN lockDelete);
	virtual ~CGeometric(void);

protected:
	virtual void EndOpenGL();
};

