#pragma once
#include "openglnode.h"
class CTransformation :
	public COpenGLNode
{
protected:
	CPoint3D data;

public:

	CTransformation(int ID) : COpenGLNode(ID) {}

	virtual ~CTransformation() {}

protected:

	virtual void BeginOpenGL()
	{
		glPushMatrix();
	}

	virtual void EndOpenGL()
	{
		glPopMatrix();
	}
};

