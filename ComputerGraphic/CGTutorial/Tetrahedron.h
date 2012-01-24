#pragma once
#include "geometric.h"
class CTetrahedron :
	public CGeometric
{
public:
	static int count;
	CTetrahedron(float x1, float y1, float z1, float x2, float y2, float z2,
				float x3, float y3, float z3, float x4, float y4, float z4) : CGeometric(NODE_TETRAHEDRON)
	{
		SetData(x1,y1,z1,x2,y2,z2,x3,y3,z3,x4,y4,z4);
		count++;
	}

	virtual ~CTetrahedron()
	{
		count--;
	}

	void SetData(float x1, float y1, float z1, float x2, float y2, float z2,
				float x3, float y3, float z3, float x4, float y4, float z4)
	{
		data1.setCoords(x1,y1,z1);
		data2.setCoords(x2,y2,z2);
		data3.setCoords(x3,y3,z3);
		data4.setCoords(x4,y4,z4);
		toString.Format(CString("tetrahedron(x1=%5.2f, y1=%5.2f, z1=%5.2f, x2=%5.2f, y2=%5.2f, z2=%5.2f, x3=%5.2f, y3=%5.2f, z3=%5.2f, x4=%5.2f, y4=%5.2f, z4=%5.2f)"),
			x1,y1,z1,x2,y2,z2,x3,y3,z3,x4,y4,z4);
		GLCode.Format(CString("drawTetrahedron(%5.2f,%5.2f,%5.2f,%5.2f,%5.2f,%5.2f,%5.2f,%5.2f,%5.2f,%5.2f,%5.2f,%5.2f)"),x1,y1,z1,x2,y2,z2,x3,y3,z3,x4,y4,z4);
		serialize.Format(CString("<tetrahedron x1=%5.2f y1=%5.2f z1=%5.2f x2=%5.2f y2=%5.2f z2=%5.2f x3=%5.2f y3=%5.2f z3=%5.2f x4=%5.2f y4=%5.2f z4=%5.2f />"),x1,y1,z1,x2,y2,z2,x3,y3,z3,x4,y4,z4);
	}

	void GetData(float &x1, float &y1, float &z1, float &x2, float &y2, float &z2,
				float &x3, float &y3, float &z3, float &x4, float &y4, float &z4)
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
		x4 = data4.getX();
		y4 = data4.getY();
		z4 = data4.getZ();
	}

	virtual void DoOpenGL()
	{
		float x1,y1,z1,x2,y2,z2,x3,y3,z3,x4,y4,z4;
		GetData(x1,y1,z1,x2,y2,z2,x3,y3,z3,x4,y4,z4);
		glVertex3f(x1,y1,z1);
		glVertex3f(x2,y2,z2);
		glVertex3f(x3,y3,z3);

		glVertex3f(x1,y1,z1);
		glVertex3f(x2,y2,z2);
		glVertex3f(x4,y4,z4);

		glVertex3f(x1,y1,z1);
		glVertex3f(x3,y3,z3);
		glVertex3f(x4,y4,z4);

		glVertex3f(x2,y2,z2);
		glVertex3f(x3,y3,z3);
		glVertex3f(x4,y4,z4);
	}

protected:
	virtual void BeginOpenGL()
	{
		glBegin(GL_TRIANGLES);
	}
};

