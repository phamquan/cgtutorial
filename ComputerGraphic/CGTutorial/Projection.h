#pragma once
#include "OpenGLNode.h"

#define ORTHO	1
#define FRUSTUM	2

class CProjection :
	public COpenGLNode
{
public:
	CProjection();
	virtual ~CProjection(void);
	void SetData(float left, float right, float top, float bottom, float mnear, float mdfar, int type);
	CString ToString();

protected:
	void DoOpenGL();
	int type;
	CPoint3D data1;
	CPoint3D data2;
};

