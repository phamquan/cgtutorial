#pragma once
#include "openglnode.h"

class CTransformation :
	public COpenGLNode
{
public:
	CTransformation(void);
	virtual ~CTransformation(void);
	void SetData(CPoint3D src);

protected:
	virtual void BeginOpenGL();
	virtual void DoOpenGL() = 0;
	virtual void EndOpenGL();

protected:
	CPoint3D data;
};

