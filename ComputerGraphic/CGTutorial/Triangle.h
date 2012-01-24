#pragma once
#include "geometric.h"
class CTriangle :
	public CGeometric
{
public:
	static int count;
	CTriangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3) : CGeometric(NODE_TRIANGLE)
	{
		SetData(x1,y1,z1,x2,y2,z2,x3,y3,z3);
		count++;
	}

	virtual ~CTriangle() 
	{
		count--;
	}

	void SetData(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3)
	{
		data1.setCoords(x1,y1,z1);
		data2.setCoords(x2,y2,z2);
		data3.setCoords(x3,y3,z3);
		toString.Format(CString("triangle(x1=%5.2f, y1=%5.2f, z1=%5.2f, x2=%5.2f, y2=%5.2f, z2=%5.2f, x3=%5.2f, y3=%5.2f, z3=%5.2f)"),x1,y1,z1,x2,y2,z2,x3,y3,z3);
		GLCode.Format(CString("drawTriangle(%5.2f,%5.2f,%5.2f,%5.2f,%5.2f,%5.2f,%5.2f,%5.2f,%5.2f)"),x1,y1,z1,x2,y2,z2,x3,y3,z3);
		serialize.Format(CString("<triangle x1=%5.2f y1=%5.2f z1=%5.2f x2=%5.2f y2=%5.2f z2=%5.2f x3=%5.2f y3=%5.2f z3=%5.2f />"),x1,y1,z1,x2,y2,z2,x3,y3,z3);
	}

	void GetData(float &x1, float &y1, float &z1, float &x2, float &y2, float &z2, float &x3, float &y3, float &z3)
	{
		x1 = data1.getX();
		y1 = data1.getY();
		z1 = data1.getZ();
		x2 = data2.getX();
		y2 = data2.getY();
		z2 = data2.getZ();
		x3 = data3.getX();
		y3 = data3.getY();
		z3 = data3.getZ();
	}

	virtual void DoOpenGL()
	{
		glVertex3f(data1.getX(),data1.getY(),data1.getZ());
		glVertex3f(data2.getX(),data2.getY(),data2.getZ());
		glVertex3f(data3.getX(),data3.getY(),data3.getZ());
	}

protected:
	virtual void BeginOpenGL()
	{
		glBegin(GL_TRIANGLES);
	}
};

