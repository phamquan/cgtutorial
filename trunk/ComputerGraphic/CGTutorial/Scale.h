#pragma once
#include "transformation.h"
class CScale :
	public CTransformation
{
public:

	CScale(float x, float y, float z) : CTransformation("scale",NODE_SCALE)
	{
		SetData(x,y,z);
	}

	virtual ~CScale() {}

	virtual void DoOpenGL()
	{
		glScalef(data.getX(),data.getY(),data.getZ());
	}

	virtual CString GLCode()
	{
		char buf[128];
		sprintf_s(buf,"glScalef(%5.2f,%5.2f,%5.2f)",data.getX(),data.getY(),data.getZ());
		return CString(buf);
	}
};

