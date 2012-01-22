#pragma once
#include "geometric.h"
class CRectangle :
	public CGeometric
{
public:

	CRectangle(float top, float left, float bottom, float right) : CGeometric(NODE_RECTANGLE)
	{
		SetData(top,left,bottom,right);
	}

	virtual ~CRectangle() {}

	void SetData(float top, float left, float bottom, float right)
	{
		data1.setCoords(top,left,0);
		data2.setCoords(bottom,right,0);
		string.Format(CString("rectangle(top=%5.2f, left=%5.2f, bottom=%5.2f, right=%5.2f)"),top,left,bottom,right);
		openGL.Format(CString("drawRectangle(%5.2f,%5.2f,%5.2f,%5.2f)"),top,left,bottom,right);
	}

	void GetData(float &top, float &left, float &bottom, float &right)
	{
		top = data1.getX();
		left = data1.getY();
		bottom = data2.getX();
		right = data2.getY();
	}

	virtual void DoOpenGL()
	{
		glVertex3f(data1.getX(),data1.getY(),0);
		glVertex3f(data1.getX(),data2.getY(),0);
		glVertex3f(data2.getX(),data2.getY(),0);
		glVertex3f(data2.getX(),data1.getY(),0);
	}

protected:
	virtual void BeginOpenGL()
	{
		glBegin(GL_QUADS);
	}
};

