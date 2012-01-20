#pragma once
#include "transformation.h"
class CRotate :
	public CTransformation
{
public:

	CRotate(float x, float y, float z, float angle) : CTransformation("rotate",NODE_ROTATE)
	{
		SetData(x,y,z,angle);
	}

	virtual ~CRotate() {}

	virtual CString ToString()
	{
		char buff[128];

		sprintf_s(buff,"(x=%5.2f, y=%5.2f, z=%5.2f, angle=%5.2f)",data.getX(),data.getY(),data.getZ(),data.getW());

		return label + CString(buff);
	}

	virtual void DoOpenGL()
	{
		glRotatef(data.getW(),data.getX(),data.getY(),data.getZ());
	}
};

