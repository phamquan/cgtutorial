#pragma once
#include "transformation.h"
class CRotate :
	public CTransformation
{
public:

	CRotate(float x, float y, float z, float angle) : CTransformation(NODE_ROTATE)
	{
		SetData(x,y,z,angle);
	}

	virtual ~CRotate() {}

	void SetData(float x, float y, float z, float angle)
	{
		data.setCoords(x,y,z,angle);
		toString.Format(CString("rotate(x=%5.2f, y=%5.2f, z=%5.2f, angle=%5.2f)"),x,y,z,angle);
		GLCode.Format(CString("glRotatef(%5.2f,%5.2f,%5.2f,%5.2f);"),angle,x,y,z);
	}

	void GetData(float &x, float &y, float &z, float &angle)
	{
		x = data.getX();
		y = data.getY();
		z = data.getZ();
		angle = data.getW();
	}

	virtual void DoOpenGL()
	{
		glRotatef(data.getW(),data.getX(),data.getY(),data.getZ());
	}
};

