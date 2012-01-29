#pragma once
#include "geometric.h"
class CCircle :
	public CGeometric
{
public:
	static int count;
	CCircle(float x, float y, float z, float R, COLORREF color) : CGeometric(NODE_CIRCLE)
	{
		SetData(x,y,z,R,color);
		count++;
	}

	virtual ~CCircle() 
	{
		count--;
	}

	void SetData(float x, float y, float z, float R, COLORREF color)
	{
		data1.setCoords(x,y,z,R);
		this->color = color;
		toString.Format(CString("circle(x=%5.2f, y=%5.2f, z=%5.2f, R=%5.2f)"),x,y,z,R);
		GLCode.Format(CString("drawCircle(%5.2f,%5.2f,%5.2f,%5.2f);"),x,y,z,R);
		serialize.Format(CString("<circle x=%5.2f y=%5.2f z=%5.2f R=%5.2f red=%d green=%d blue=%d />"),x,y,z,R,GetRValue(color),GetGValue(color),GetBValue(color));
	}

	void GetData(float &x, float &y, float &z, float &R)
	{
		x = data1.getX();
		y = data1.getY();
		z = data1.getZ();
		R = data1.getW();
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
		glScalef(data1.getW(),data1.getW(),1);
	}

	virtual void EndOpenGL()
	{
		glPopMatrix();
	}
};

