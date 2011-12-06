#pragma once
#include "openglnode.h"

class CTransformation :
	public COpenGLNode
{
public:
	CTransformation();
	virtual ~CTransformation();
	void SetData(CPoint3D src);
	CString ToString();

protected:
	virtual void BeginOpenGL();
	virtual void DoOpenGL() = 0;
	virtual void EndOpenGL();

protected:
	CPoint3D data;
};

