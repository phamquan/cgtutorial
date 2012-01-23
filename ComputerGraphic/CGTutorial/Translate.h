#pragma once
#include "transformation.h"
class CTranslate :
	public CTransformation
{
public:

	CTranslate(float x, float y, float z) : CTransformation(NODE_TRANSLATE)
	{
		SetData(x,y,z);
	}

	virtual ~CTranslate() {}

	void SetData(float x, float y, float z)
	{
		data.setCoords(x,y,z);
		toString.Format(CString("translate(x=%5.2f, y=%5.2f, z=%5.2f)"),x,y,z);
		GLCode.Format(CString("glTranslatef(%5.2f,%5.2f,%5.2f);"),x,y,z);
		serialize.Format(CString("translate x=%5.2f y=%5.2f z=%5.2f"),x,y,z);
	}

	void GetData(float &x, float &y, float &z)
	{
		x = data.getX();
		y = data.getY();
		z = data.getZ();
	}

	virtual void DoOpenGL()
	{
		glTranslatef(data.getX(),data.getY(),data.getZ());
	}
};

