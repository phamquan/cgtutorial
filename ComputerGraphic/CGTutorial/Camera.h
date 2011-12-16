#pragma once
#include "OpenGLNode.h"

class CCamera :
	public COpenGLNode
{
public:
	CCamera(float xpos, float ypos, float zpos, float xlook, float ylook, float zlook, float xup, float yup, float zup);
	virtual ~CCamera();

	void SetData(float xpos, float ypos, float zpos, float xlook, float ylook, float zlook, float xup, float yup, float zup);
	void GetData(float &xpos, float &ypos, float &zpos, float &xlook, float &ylook, float &zlook, float &xup, float &yup, float &zup);
	CString ToString();
	void DoOpenGL();

protected:
	void BeginOpenGL();

protected:
	CPoint3D pos;
	CPoint3D look;
	CPoint3D up;
};

