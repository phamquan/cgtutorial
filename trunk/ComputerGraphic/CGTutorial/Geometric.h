#pragma once
#include "openglnode.h"
class CGeometric :
	public COpenGLNode
{
protected:
	float tmp[16];
	CPoint3D data1;
	CPoint3D data2;

public:

	CGeometric(char* label, int ID) : COpenGLNode(label,ID) {}

	virtual ~CGeometric() {}

protected:

	virtual void EndOpenGL()
	{
		glEnd();
	}
};

