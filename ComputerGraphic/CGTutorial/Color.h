#pragma once
#include "OpenGLNode.h"

class CColor :
	public COpenGLNode
{
public:
	CColor(float red, float green, float blue);
	virtual ~CColor();
	//void SetData();
	CString ToString();

protected:
	void BeginOpenGL();
	void DoOpenGL();
	void EndOpenGL();

protected:
	CPoint3D data;
	float currentColor[4];
};

