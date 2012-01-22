#pragma once
#include "geometric.h"
class CLine :
	public CGeometric
{
public:

	CLine(float x1, float y1, float z1, float x2, float y2, float z2) : CGeometric(NODE_LINE)
	{
		SetData(x1, y1, z1, x2, y2, z2);
	}

	virtual ~CLine() {}

	void SetData(float x1, float y1, float z1, float x2, float y2, float z2)
	{
		data1.setCoords(x1,y1,z1);
		data2.setCoords(x2,y2,z2);
		string.Format(CString("line(x1=%5.2f, y1=%5.2f, z1=%5.2f, x2=%5.2f, y2=%5.2f, z2=%5.2f)"),x1,y1,z1,x2,y2,z2);
		openGL.Format(CString("drawLine(%5.2f,%5.2f,%5.2f,%5.2f,%5.2f,%5.2f);"),x1,y1,z1,x2,y2,z2);
	}

	void GetData(float &x1, float &y1, float &z1, float &x2, float &y2, float &z2)
	{
		x1 = data1.getX();
		y1 = data1.getY();
		z1 = data1.getZ();
		x2 = data2.getX();
		y2 = data2.getY();
		z2 = data2.getZ();
	}

	virtual void DoOpenGL()
	{
		glVertex3f(data1.getX(),data1.getY(),data1.getZ());
		glVertex3f(data2.getX(),data2.getY(),data2.getZ());
	}

protected:

	virtual void BeginOpenGL()
	{
		glBegin(GL_LINES);
	}
};

