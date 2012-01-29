#pragma once
#include "geometric.h"
class CSphere :
	public CGeometric
{
public:
	static int count;
	CSphere(float x, float y, float z, float R, COLORREF color) : CGeometric(NODE_SPHERE)
	{
		SetData(x,y,z,R,color);
		count++;
	}

	virtual ~CSphere()
	{
		count--;
	}

	void SetData(float x, float y, float z, float R, COLORREF color)
	{
		data1.setCoords(x,y,z,R);
		this->color = color;
		toString.Format(CString("sphere(x=%5.2f, y=%5.2f, z=%5.2f, R=%5.2f)"),x,y,z,R);
		GLCode.Format(CString("drawSphere(%5.2f,%5.2f,%5.2f,%5.2f);"),x,y,z,R);
		serialize.Format(CString("<sphere x=%5.2f y=%5.2f z=%5.2f R=%5.2f red=%d green=%d blue=%d />"),x,y,z,R,GetRValue(color),GetGValue(color),GetBValue(color));
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
		glBegin(GL_QUAD_STRIP);
		for(int i = -90; i<=90; i+=10) {
			for(int j=0; j<=360; j+=10) {
				double x1 = cos((i-10)*DEG_2_RAD)*cos(j*DEG_2_RAD);
				double y1 = sin((i-10)*DEG_2_RAD);
				double z1 = cos((i-10)*DEG_2_RAD)*sin(j*DEG_2_RAD);
				glVertex3f(x1,y1,z1);
				double x2 = cos(i*DEG_2_RAD)*cos(j*DEG_2_RAD);
				double y2 = sin(i*DEG_2_RAD);
				double z2 = cos(i*DEG_2_RAD)*sin(j*DEG_2_RAD);
				glVertex3f(x2,y2,z2);
			}
		}
		glEnd();
	}

protected:

	virtual void BeginOpenGL()
	{
		glPushMatrix();
		glTranslatef(data1.getX(),data1.getY(),data1.getZ());
		glScalef(data1.getW(),data1.getW(),data1.getW());
	}

	virtual void EndOpenGL()
	{
		glPopMatrix();
	}
};

