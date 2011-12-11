#pragma once
#include "openglnode.h"

class CGeometric :
	public COpenGLNode
{
public:
	CGeometric(char* label, int ID);
	virtual ~CGeometric();

protected:
	virtual void EndOpenGL();

protected:
	CPoint3D data1;
	CPoint3D data2;
};

