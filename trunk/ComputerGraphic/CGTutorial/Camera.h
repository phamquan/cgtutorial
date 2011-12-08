#pragma once
#include "OpenGLNode.h"

class CCamera :
	public COpenGLNode
{
public:
	CCamera();
	virtual ~CCamera(void);
	void SetData(CPoint3D pos, CPoint3D look, CPoint3D up);
	CString ToString();

protected:
	void DoOpenGL();

	CPoint3D pos;
	CPoint3D look;
	CPoint3D up;
};

