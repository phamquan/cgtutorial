#pragma once
#include "OpenGLNode.h"

#define ORTHO	0
#define FRUSTUM	1

class CProjection :
	public COpenGLNode
{
public:
	CProjection(float left, float right, float bottom, float top, float mnear, float mdfar, int type);
	virtual ~CProjection(void);

	void SetData(float left, float right, float bottom, float top, float mnear, float mdfar, int type);
	void GetData(float &left, float &right, float &bottom, float &top, float &mnear, float &mdfar, int &type);
	CString ToString();
	int GetType() {return type;}

protected:
	void BeginOpenGL();
	void DoOpenGL();

protected:
	int type;
	CPoint3D data1;
	CPoint3D data2;
};

