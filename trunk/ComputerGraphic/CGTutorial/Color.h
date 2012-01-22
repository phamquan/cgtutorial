#pragma once
#include "openglnode.h"
class CColor :
	public COpenGLNode
{
protected:
	CPoint3D data;
	float currentColor[4];

public:

	CColor(float red, float green, float blue) : COpenGLNode(NODE_COLOR)
	{
		SetData(red,green,blue);
	}

	virtual ~CColor() {}

	void SetData(float red, float green, float blue)
	{
		data.setCoords(red,green,blue);
		string.Format(CString("color(red=%5.2f, green=%5.2f, blue=%5.2f)"),red,green,blue);
	}

	void GetData(float &red, float &green, float &blue)
	{
		red = data.getX();
		green = data.getY();
		blue = data.getZ();
	}

protected:

	virtual void BeginOpenGL()
	{
		glGetFloatv(GL_CURRENT_COLOR,currentColor);
	}

	virtual void DoOpenGL()
	{
		glColor4f(data.getX(),data.getY(),data.getZ(),data.getW());
	}

	virtual void EndOpenGL()
	{
		glColor4fv(currentColor);
	}
};

