#pragma once
#include "openglnode.h"

class CTransformation :
	public COpenGLNode
{
public:
	CTransformation(char* label, int ID);
	virtual ~CTransformation();
	CString ToString();

	void SetData(float x, float y, float z, float angle = 0);
	void GetData(float &x, float &y, float &z, float &angle);
protected:
	virtual void BeginOpenGL();
	virtual void EndOpenGL();

protected:
	CPoint3D data;
};

