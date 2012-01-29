#pragma once
#include "geometric.h"
class CCube :
	public CGeometric
{
public:
	static int count;
	CCube(float left, float bottom, float mnear, float right, float top, float mfar, COLORREF color) : CGeometric(NODE_CUBE)
	{
		SetData(left,bottom,mnear,right,top,mfar,color);
		count++;
	}

	virtual ~CCube() 
	{
		count--;
	}

	void SetData(float left, float bottom, float mnear, float right, float top, float mfar, COLORREF color)
	{
		data1.setCoords(left,bottom,mnear);
		data2.setCoords(right,top,mfar);
		this->color = color;
		toString.Format(CString("cube(left=%5.2f, bottom=%5.2f, near=%5.2f, right=%5.2f, top=%5.2f, far=%5.2f)"),left,bottom,mnear,right,top,mfar);
		GLCode.Format(CString("drawCube(%5.2f,%5.2f,%5.2f,%5.2f,%5.2f,%5.2f);"),left,bottom,mnear,right,top,mfar);
		serialize.Format(CString("<cube left=%5.2f bottom=%5.2f near=%5.2f right=%5.2f top=%5.2f far=%5.2f red=%d green=%d blue=%d />"),left,bottom,mnear,right,top,mfar,GetRValue(color),GetGValue(color),GetBValue(color));
	}

	void GetData(float &left, float &bottom, float &mnear, float &right, float &top, float &mfar)
	{
		left = data1.getX();
		bottom = data1.getY();
		mnear = data1.getZ();
		right = data2.getX();
		top = data2.getY();
		mfar = data2.getZ();
	}

	virtual void DoOpenGL()
	{
		float left,bottom,mnear,right,top,mfar;
		GetData(left,bottom,mnear,right,top,mfar);
		//font
		glVertex3f(left,top,mnear);
		glVertex3f(right,top,mnear);
		glVertex3f(right,bottom,mnear);
		glVertex3f(left,bottom,mnear);
		//back
		glVertex3f(left,top,mfar);
		glVertex3f(right,top,mfar);
		glVertex3f(right,bottom,mfar);
		glVertex3f(left,bottom,mfar);
		//left
		glVertex3f(left,top,mnear);
		glVertex3f(left,bottom,mnear);
		glVertex3f(left,bottom,mfar);
		glVertex3f(left,top,mfar);
		//right
		glVertex3f(right,top,mnear);
		glVertex3f(right,bottom,mnear);
		glVertex3f(right,bottom,mfar);
		glVertex3f(right,top,mfar);
		//up
		glVertex3f(left,top,mnear);
		glVertex3f(right,top,mnear);
		glVertex3f(right,top,mfar);
		glVertex3f(left,top,mfar);
		//down
		glVertex3f(left,bottom,mnear);
		glVertex3f(right,bottom,mnear);
		glVertex3f(right,bottom,mfar);
		glVertex3f(left,bottom,mfar);
	}

protected:
	virtual void BeginOpenGL()
	{
		glBegin(GL_QUADS);
	}
};

