#pragma once
#include "geometric.h"
class CTriangle :
	public CGeometric
{
public:

	CTriangle(float x1, float y1, float x2, float y2, float x3, float y3) : CGeometric(NODE_RECTANGLE)
	{
		SetData(x1,y1,x2,y2,x3,y3);
	}

	virtual ~CTriangle() {}

	void SetData(float x1, float y1, float x2, float y2, float x3, float y3)
	{
		data1.setCoords(x1,y1,x2);
		data2.setCoords(y2,x3,y3);
		toString.Format(CString("triangle(x1=%5.2f, y1=%5.2f, x2=%5.2f, y2=%5.2f, x3=%5.2f, y3=%5.2f)"),x1,y1,x2,y2,x3,y3);
		GLCode.Format(CString("drawTriangle(%5.2f,%5.2f,%5.2f,%5.2f,%5.2f,%5.2f)"),x1,y1,x2,y2,x3,y3);
	}

	void GetData(float &x1, float &y1, float &x2, float &y2, float &x3, float &y3)
	{
		x1 = data1.getX();
		y1 = data1.getY();
		x2 = data1.getZ();
		y2 = data2.getX();
		x3 = data2.getY();
		y3 = data2.getZ();
	}

	virtual void DoOpenGL()
	{
		glVertex3f(data1.getX(),data1.getY(),0);
		glVertex3f(data1.getZ(),data2.getX(),0);
		glVertex3f(data2.getY(),data2.getZ(),0);
	}

protected:
	virtual void BeginOpenGL()
	{
		glBegin(GL_TRIANGLES);
	}
};

