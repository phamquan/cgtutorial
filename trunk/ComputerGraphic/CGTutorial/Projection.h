#pragma once
#include "OpenGLNode.h"

#define ORTHO	1
#define FRUSTUM	2

class CProjection :
	public COpenGLNode
{
public:
	CProjection(float left, float right, float bottom, float top, float mnear, float mdfar, int type);
	virtual ~CProjection(void);
	CString ToString();

protected:
	void DoOpenGL();

protected:
	int type;
	CPoint3D data1;
	CPoint3D data2;
};

