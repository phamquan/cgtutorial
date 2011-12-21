#pragma once
#include "openglnode.h"

#define VIEWPORT_DEFAULT 0
#define VIEWPORT_CUSTOM 1

class CViewPort :
	public COpenGLNode
{
public:
	CViewPort(float x, float y, float width, float height, int type);
	virtual ~CViewPort();

	void SetData(float x, float y, float width, float height, int type);
	void GetData(float &x, float &y, float &width, float &height, int &type);
	CString ToString();

protected :
	int type;
	CPoint3D data;
};

