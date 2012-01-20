#pragma once
#include "geometric.h"
class CPoint4D :
	public CGeometric
{
public:

	CPoint4D(float x, float y, float z) : CGeometric("point",NODE_POINT)
	{
		SetData(x, y, z);
	}

	virtual ~CPoint4D() {}

	void SetData(float x, float y, float z)
	{
		data1.setCoords(x, y, z);
	}

	void GetData(float &x, float &y, float &z)
	{
		x = data1.getX();
		y = data1.getY();
		z = data1.getZ();
	}

	virtual CString ToString()
	{
		char buff[1024];

		sprintf_s(buff,"(x=%5.2f, y=%5.2f, z=%5.2f)",data1.getX(),data1.getY(),data1.getZ());

		return label + CString(buff);
	}

	virtual void DoOpenGL()
	{
		glVertex3f(data1.getX(),data1.getY(),data1.getZ());
	}

protected:

	virtual void BeginOpenGL()
	{
		glBegin(GL_POINT);
	}
};

