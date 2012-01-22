#pragma once
#include "geometric.h"
class CEllipse :
	public CGeometric
{
public:

	CEllipse(float x, float y, float z, float a, float b) : CGeometric(NODE_ELLIPSE)
	{
		SetData(x,y,z,a,b);
	}

	virtual ~CEllipse() {}

	void SetData(float x, float y, float z, float a, float b)
	{
		data1.setCoords(x,y,z);
		data2.setCoords(a,b,0);
		toString.Format(CString("ellipse(x=%5.2f, y=%5.2f, z=%5.2f, a=%5.2f, b=%5.2f)"),x,y,z,a,b);
		GLCode.Format(CString("drawEllipse(%5.2f,%5.2f,%5.2f,%5.2f,%5.2f)"),x,y,z,a,b);
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

