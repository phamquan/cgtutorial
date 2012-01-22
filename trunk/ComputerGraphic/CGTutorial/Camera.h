#pragma once
#include "openglnode.h"

class CCamera :
	public COpenGLNode
{
protected:
	CPoint3D pos;
	CPoint3D look;
	CPoint3D up;

public:

	CCamera(float xpos, float ypos, float zpos, float xlook, float ylook, float zlook, float xup, float yup, float zup) : COpenGLNode(NODE_CAMERA)
	{
		SetData(xpos, ypos, zpos, xlook, ylook, zlook, xup, yup, zup);
	}

	virtual ~CCamera() {}

	void SetData(float xpos, float ypos, float zpos, float xlook, float ylook, float zlook, float xup, float yup, float zup)
	{
		pos.setCoords(xpos, ypos, zpos);
		look.setCoords(xlook, ylook, zlook);
		up.setCoords(xup, yup, zup);
		toString.Format(CString("camera(xpos=%5.2f, ypos=%5.2f, zpos=%5.2f, xlook=%5.2f, ylook=%5.2f, zlook=%5.2f, xup=%5.2f, yup=%5.2f, zup=%5.2f)"),xpos,ypos,zpos,xlook,ylook,zlook,xup,yup,zup);
		GLCode.Format(CString("gluLookAt(%5.2f,%5.2f,%5.2f,%5.2f,%5.2f,%5.2f,%5.2f,%5.2f,%5.2f);"),xpos,ypos,zpos,xlook,ylook,zlook,xup,yup,zup);
	}
	
	void GetData(float &xpos, float &ypos, float &zpos, float &xlook, float &ylook, float &zlook, float &xup, float &yup, float &zup)
	{
		xpos = pos.getX();
		ypos = pos.getY();
		zpos = pos.getZ();
		xlook = look.getX();
		ylook = look.getY();
		zlook = look.getZ();
		xup = up.getX();
		yup = up.getY();
		zup = up.getZ();
	}

	virtual void DoOpenGL()
	{
		gluLookAt(pos.getX(),pos.getY(),pos.getZ(),look.getX(),look.getY(),look.getZ(),up.getX(),up.getY(),up.getZ());
	}

protected:

	virtual void BeginOpenGL()
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
};

