#pragma once
#include "OpenGLNode.h"

class CCamera :
	public COpenGLNode
{
public:
	CCamera(CPoint3D pos, CPoint3D look, CPoint3D up);
	virtual ~CCamera();
	CString ToString();

protected:
	void BeginOpenGL();
	void DoOpenGL();

protected:
	CPoint3D pos;
	CPoint3D look;
	CPoint3D up;
};

