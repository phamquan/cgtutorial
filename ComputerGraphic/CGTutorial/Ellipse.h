#pragma once
#include "geometric.h"
class CEllipse :
	public CGeometric
{
public:
	static int count;
	CEllipse(float x, float y, float z, float a, float b, COLORREF color) : CGeometric(NODE_ELLIPSE)
	{
		SetData(x,y,z,a,b,color);
		count++;
	}

	virtual ~CEllipse() 
	{
		count--;
	}

	void SetData(float x, float y, float z, float a, float b, COLORREF color)
	{
		data1.setCoords(x,y,z);
		data2.setCoords(a,b,0);
		this->color = color;
		toString.Format(CString("ellipse(x=%5.2f, y=%5.2f, z=%5.2f, a=%5.2f, b=%5.2f)"),x,y,z,a,b);
		GLCode.Format(CString("drawEllipse(%5.2f,%5.2f,%5.2f,%5.2f,%5.2f);"),x,y,z,a,b);
		serialize.Format(CString("<ellipse x=%5.2f y=%5.2f z=%5.2f a=%5.2f b=%5.2f red=%d green=%d blue=%d />"),x,y,z,a,b,GetRValue(color),GetGValue(color),GetBValue(color));
	}

	void GetData(float &x, float &y, float &z, float &a, float &b)
	{
		x = data1.getX();
		y = data1.getY();
		z = data1.getZ();
		a = data2.getX();
		b = data2.getY();
	}

	virtual void DoOpenGL()
	{
		glBegin(GL_POLYGON);
		for(int i = 0; i<=360; i+=10) {
			glVertex3f(cos(i*DEG_2_RAD),
					   sin(i*DEG_2_RAD),
					   0.0f);
		}
		glEnd();
	}

protected:

	virtual void BeginOpenGL()
	{
		glPushMatrix();
		glTranslatef(data1.getX(),data1.getY(),data1.getZ());
		glScalef(data2.getX(),data2.getY(),1);
	}

	virtual void EndOpenGL()
	{
		glPopMatrix();
	}
};

