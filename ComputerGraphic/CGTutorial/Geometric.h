#pragma once
#include "openglnode.h"
class CGeometric :
	public COpenGLNode
{
protected:
	float tmp[16];
	CPoint3D data1;
	CPoint3D data2;
	CPoint3D data3;
	CPoint3D data4;

public:

	CGeometric(int ID) : COpenGLNode(ID) {}

	virtual ~CGeometric() {}

protected:

	virtual void EndOpenGL()
	{
		glEnd();
	}
};

