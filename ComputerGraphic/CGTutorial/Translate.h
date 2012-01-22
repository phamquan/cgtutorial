#pragma once
#include "transformation.h"
class CTranslate :
	public CTransformation
{
public:

	CTranslate(float x, float y, float z) : CTransformation("translate",NODE_TRANSLATE)
	{
		SetData(x,y,z);
	}

	virtual ~CTranslate() {}

	virtual void DoOpenGL()
	{
		glTranslatef(data.getX(),data.getY(),data.getZ());
	}

	virtual CString GLCode()
	{
		char buf[128];
		sprintf_s(buf,"glTranslatef(%5.2f,%5.2f,%5.2f)",data.getX(),data.getY(),data.getZ());
		return CString(buf);
	}
};

