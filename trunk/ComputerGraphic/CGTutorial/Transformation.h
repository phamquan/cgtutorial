#pragma once
#include "openglnode.h"

class CTransformation :
	public COpenGLNode
{
public:
	CTransformation(CPoint3D src, char* label, int ID);
	virtual ~CTransformation();
	CString ToString();

protected:
	virtual void BeginOpenGL();
	virtual void EndOpenGL();

protected:
	CPoint3D data;
};

