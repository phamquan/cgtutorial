#pragma once
#include "transformation.h"
class CRotate :
	public CTransformation
{
public:
	CRotate(CPoint3D data);
	virtual ~CRotate();
	CString ToString();

protected:
	virtual void DoOpenGL();
};

