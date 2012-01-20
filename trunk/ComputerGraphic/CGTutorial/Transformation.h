#pragma once
#include "openglnode.h"
class CTransformation :
	public COpenGLNode
{
protected:
	CPoint3D data;

public:

	CTransformation(char* label, int ID) : COpenGLNode(label,ID) {}

	virtual ~CTransformation() {}

	void SetData(float x, float y, float z, float angle = 0)
	{
		data.setCoords(x,y,z,angle);
	}

	void GetData(float &x, float &y, float &z, float &angle)
	{
		x = data.getX();
		y = data.getY();
		z = data.getZ();
		angle = data.getW();
	}

	virtual CString ToString()
	{
		char buff[1024];

		sprintf_s(buff,"(x=%5.2f, y=%5.2f, z=%5.2f)",data.getX(),data.getY(),data.getZ());

		return label + CString(buff);
	}
	
protected:

	virtual void BeginOpenGL()
	{
		glPushMatrix();
	}

	virtual void EndOpenGL()
	{
		glPopMatrix();
	}
};

