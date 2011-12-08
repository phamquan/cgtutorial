#pragma once
#include "OpenGLNode.h"

class CColor :
	public COpenGLNode
{
public:
	CColor();
	virtual ~CColor(void);
	void SetData(float red, float green, float blue, float alpha);
	CString ToString();

protected:
	void DoOpenGL();
	CPoint3D data;
};

