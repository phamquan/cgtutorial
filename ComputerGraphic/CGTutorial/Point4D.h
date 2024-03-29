#pragma once
#include "geometric.h"
class CPoint4D :
	public CGeometric
{
public:
	static int count;

	CPoint4D(float x, float y, float z, COLORREF color) : CGeometric(NODE_POINT)
	{
		SetData(x,y,z,color);
		count++;
	}

	virtual ~CPoint4D()
	{
		count--;
	}

	void SetData(float x, float y, float z, COLORREF color)
	{
		data1.setCoords(x,y,z);
		this->color = color;
		toString.Format(CString("point(x=%5.2f, y=%5.2f, z=%5.2f)"),x,y,z);
		GLCode.Format(CString("drawPoint(%5.2f,%5.2f,%5.2f);"),x,y,z);
		serialize.Format(CString("<point x=%5.2f y=%5.2f z=%5.2f red=%d green=%d blue=%d />"),x,y,z,GetRValue(color),GetGValue(color),GetBValue(color));
	}

	void GetData(float &x, float &y, float &z)
	{
		x = data1.getX();
		y = data1.getY();
		z = data1.getZ();
	}

	virtual void DoOpenGL()
	{
		glVertex3f(data1.getX(),data1.getY(),data1.getZ());
	}

protected:

	virtual void BeginOpenGL()
	{
		glBegin(GL_POINTS);
	}
};