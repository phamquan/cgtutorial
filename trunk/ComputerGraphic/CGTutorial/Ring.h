#pragma once
#include "geometric.h"
class CRing :
	public CGeometric
{
public:

	CRing(float x, float y, float z, float R, float r) : CGeometric(NODE_RING)
	{
		SetData(x,y,z,R,r);
	}

	virtual ~CRing() {}

	void SetData(float x, float y, float z, float R, float r)
	{
		data1.setCoords(x,y,z);
		data2.setCoords(R,r,0);
		toString.Format(CString("ring(x=%5.2f, y=%5.2f, z=%5.2f, R=%5.2f, r=%5.2f)"),x,y,z,R,r);
		GLCode.Format(CString("drawRing(%5.2f,%5.2f,%5.2f,%5.2f,%5.2f)"),x,y,z,R,r);
	}

	void GetData(float &x, float &y, float &z, float &R, float &r)
	{
		x = data1.getX();
		y = data1.getY();
		z = data1.getZ();
		R = data2.getX();
		r = data2.getY();
	}

	virtual void DoOpenGL()
	{
		for(int i = 10; i<=360; i+=10) {
			glBegin(GL_QUAD_STRIP);
			for(int j=0; j<=360; j+=10) {
				double x1 = (data2.getX() + data2.getY()*cos(i*DEG_2_RAD))*cos(j*DEG_2_RAD);
				double y1 = (data2.getX() + data2.getY()*cos(i*DEG_2_RAD))*sin(j*DEG_2_RAD);
				double z1 = data2.getY()*sin(i*DEG_2_RAD);
				glVertex3f(x1,y1,z1);
				double x2 = (data2.getX() + data2.getY()*cos((i-10)*DEG_2_RAD))*cos(j*DEG_2_RAD);
				double y2 = (data2.getX() + data2.getY()*cos((i-10)*DEG_2_RAD))*sin(j*DEG_2_RAD);
				double z2 = data2.getY()*sin((i-10)*DEG_2_RAD);
				glVertex3f(x2,y2,z2);
			}
			glEnd();
		}
	}

protected:

	virtual void BeginOpenGL()
	{
		glPushMatrix();
		glTranslatef(data1.getX(),data1.getY(),data1.getZ());
	}

	virtual void EndOpenGL()
	{
		glPopMatrix();
	}
};

