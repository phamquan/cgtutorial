#pragma once
#include "openglnode.h"

#define ORTHO	0
#define FRUSTUM	1

class CProjection :
	public COpenGLNode
{
protected:
	int type;
	CPoint3D data1;
	CPoint3D data2;

public:

	CProjection(float left, float right, float bottom, float top, float mnear, float mfar, int type) : COpenGLNode(NODE_PROJECTION)
	{
		SetData(left, right, bottom, top, mnear, mfar, type);
	}

	virtual ~CProjection(void) {}

	void SetData(float left, float right, float bottom, float top, float mnear, float mfar, int type)
	{
		data1.setCoords(left,right,bottom);
		data2.setCoords(top,mnear,mfar);
		this->type = type;

		if(type == ORTHO) {
			toString.Format(CString("projection(type=ortho, left=%5.2f, right=%5.2f, bottom=%5.2f, top=%5.2f, near=%5.2f, far=%5.2f)"),left,right,bottom,top,mnear,mfar);
			GLCode.Format(CString("glOrtho(%5.2f,%5.2f,%5.2f,%5.2f,%5.2f,%5.2f);"),left,right,bottom,top,mnear,mfar);
			serialize.Format(CString("<projection type='ortho' left=%5.2f right=%5.2f bottom=%5.2f top=%5.2f near=%5.2f far=%5.2f />"),left,right,bottom,top,mnear,mfar);
		} else {
			toString.Format(CString("projection(type=frustum, left=%5.2f, right=%5.2f, bottom=%5.2f, top=%5.2f, near=%5.2f, far=%5.2f)"),left,right,bottom,top,mnear,mfar);
			GLCode.Format(CString("glFrustum(%5.2f,%5.2f,%5.2f,%5.2f,%5.2f,%5.2f);"),left,right,bottom,top,mnear,mfar);
			serialize.Format(CString("<projection type='frustum' left=%5.2f right=%5.2f bottom=%5.2f top=%5.2f near=%5.2f far=%5.2f />"),left,right,bottom,top,mnear,mfar);
		}
	}

	void GetData(float &left, float &right, float &bottom, float &top, float &mnear, float &mfar, int &type)
	{
		left = data1.getX();
		right = data1.getY();
		bottom = data1.getZ();
		top = data2.getX();
		mnear = data2.getY();
		mfar = data2.getZ();
		type = this->type;
	}

	virtual void Serialize(CArchive& ar, int tab=0)
	{
		CString t;
		for(int i=0; i<tab; i++)
			t += '\t';
		ar.WriteString(t + serialize + "\r\n");
	}

protected:

	virtual void BeginOpenGL()
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
	}

	void DoOpenGL()
	{
		if(type == ORTHO)
			glOrtho(data1.getX(),data1.getY(),data1.getZ(),data2.getX(),data2.getY(),data2.getZ());
		else
			glFrustum(data1.getX(),data1.getY(),data1.getZ(),data2.getX(),data2.getY(),data2.getZ());
	}
};

