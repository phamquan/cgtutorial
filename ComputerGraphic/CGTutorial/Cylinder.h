#pragma once
#include "geometric.h"
class CCylinder :
	public CGeometric
{
public:

	CCylinder(float x, float y, float z, float R, float height) : CGeometric(NODE_CYLINDER)
	{
		SetData(x,y,z,R,height);
	}

	virtual ~CCylinder() {}

	void SetData(float x, float y, float z, float R, float height)
	{
		data1.setCoords(x,y,z);
		data2.setCoords(R,height,0);
		toString.Format(CString("cylinder(x=%5.2f, y=%5.2f, z=%5.2f, R=%5.2f, height=%5.2f)"),x,y,z,R,height);
		GLCode.Format(CString("drawCylinder(%5.2f,%5.2f,%5.2f,%5.2f,%5.2f)"),x,y,z,R,height);
		serialize.Format(CString("<cylinder x=%5.2f y=%5.2f z=%5.2f R=%5.2f height=%5.2f />"),x,y,z,R,height);
	}

	void GetData(float &x, float &y, float &z, float &R, float &height)
	{
		x = data1.getX();
		y = data1.getY();
		z = data1.getZ();
		R = data2.getX();
		height = data2.getY();
	}

	virtual void DoOpenGL()
	{
		glBegin(GL_QUAD_STRIP);
		for(int j=0; j<=360; j+=10) {
			glVertex3f(data2.getX()*cos(j*DEG_2_RAD), data2.getY()/2,data2.getX()*sin(j*DEG_2_RAD));
			glVertex3f(data2.getX()*cos(j*DEG_2_RAD),-data2.getY()/2,data2.getX()*sin(j*DEG_2_RAD));
		}
		glEnd();

		glBegin(GL_POLYGON);
		for(int j=0; j<=360; j+=10) {
			glVertex3f(data2.getX()*cos(j*DEG_2_RAD), data2.getY()/2,data2.getX()*sin(j*DEG_2_RAD));
		}
		glEnd();
		
		glBegin(GL_POLYGON);
		for(int j=0; j<=360; j+=10) {
			glVertex3f(data2.getX()*cos(j*DEG_2_RAD),-data2.getY()/2,data2.getX()*sin(j*DEG_2_RAD));
		}
		glEnd();
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

