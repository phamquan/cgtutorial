#pragma once
#include "transformation.h"
class CScale :
	public CTransformation
{
public:

	CScale(float x, float y, float z) : CTransformation(NODE_SCALE)
	{
		SetData(x,y,z);
	}

	virtual ~CScale() {}

	void SetData(float x, float y, float z)
	{
		data.setCoords(x,y,z);
		toString.Format(CString("scale(x=%5.2f, y=%5.2f, z=%5.2f)"),x,y,z);
		GLCode.Format(CString("glScalef(%5.2f,%5.2f,%5.2f);"),x,y,z);
	}

	void GetData(float &x, float &y, float &z)
	{
		x = data.getX();
		y = data.getY();
		z = data.getZ();
	}

	virtual void DoOpenGL()
	{
		glScalef(data.getX(),data.getY(),data.getZ());
	}
};

