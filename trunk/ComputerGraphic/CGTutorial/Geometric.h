#pragma once
#include "openglnode.h"
class CGeometric :
	public COpenGLNode
{
protected:
	float tmp[16];
	CPoint3D data1;
	CPoint3D data2;
	CPoint3D data3;
	CPoint3D data4;

public:

	CGeometric(int ID) : COpenGLNode(ID) {}

	virtual ~CGeometric() {}

	virtual void Serialize(CArchive& ar, int tab=0)
	{
		CString t;
		for(int i=0; i<tab; i++)
			t += '\t';
		ar.WriteString(t + serialize + "\r\n");
	}

protected:

	virtual void EndOpenGL()
	{
		glEnd();
	}
};

