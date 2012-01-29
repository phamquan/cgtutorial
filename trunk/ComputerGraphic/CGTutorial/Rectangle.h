#pragma once
#include "geometric.h"
class CRectangle :
	public CGeometric
{
public:
	static int count;
	CRectangle(float top, float left, float bottom, float right, COLORREF color) : CGeometric(NODE_RECTANGLE)
	{
		SetData(top,left,bottom,right,color);
		count++;
	}

	virtual ~CRectangle()
	{
		count--;
	}

	void SetData(float top, float left, float bottom, float right, COLORREF color)
	{
		data1.setCoords(top,left,0);
		data2.setCoords(bottom,right,0);
		this->color = color;
		toString.Format(CString("rectangle(top=%5.2f, left=%5.2f, bottom=%5.2f, right=%5.2f)"),top,left,bottom,right);
		GLCode.Format(CString("drawRectangle(%5.2f,%5.2f,%5.2f,%5.2f);"),top,left,bottom,right);
		serialize.Format(CString("<rectangle top=%5.2f left=%5.2f bottom=%5.2f right=%5.2f red=%d green=%d blue=%d />"),top,left,bottom,right,GetRValue(color),GetGValue(color),GetBValue(color));
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

