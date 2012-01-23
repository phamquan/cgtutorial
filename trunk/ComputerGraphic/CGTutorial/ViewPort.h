#pragma once
#include "openglnode.h"

#define VIEWPORT_DEFAULT 0
#define VIEWPORT_CUSTOM 1

class CViewPort :
	public COpenGLNode
{
protected :
	int type;
	CPoint3D data;

public:

	CViewPort(float x, float y, float width, float height, int type) : COpenGLNode(NODE_VIEWPORT)
	{
		SetData(x, y, width, height, type);
	}
	
	virtual ~CViewPort() {}

	void SetData(float x, float y, float width, float height, int type)
	{
		data.setCoords(x,y,width,height);
		this->type = type;

		if(type == VIEWPORT_DEFAULT) {
			toString = "viewport(type=default)";
			GLCode = "glViewport(0,0,width,height);";
			serialize = "<viewport type='default' />";
		} else {
			toString.Format(CString("viewport(type=custom, x=%5.2f, y=%5.2f, width=%5.2f, height=%5.2f)"),x,y,width,height);
			GLCode.Format(CString("glViewport(%5.2f,%5.2f,%5.2f,%5.2f);"),x,y,width,height);
			serialize.Format(CString("<viewport type='custom' x=%5.2f y=%5.2f width=%5.2f height=%5.2f />"),x,y,width,height);
		}
	}

	void GetData(float &x, float &y, float &width, float &height, int &type)
	{
		x = data.getX();
		y = data.getY();
		width = data.getZ();
		height = data.getW();
		type = this->type;
	}

	virtual void Serialize(CArchive& ar, int tab=0)
	{
		CString t;
		for(int i=0; i<tab; i++)
			t += '\t';
		ar.WriteString(t + serialize + "\r\n");
	}
};

