#pragma once
#include "transformation.h"
class CRotate :
	public CTransformation
{
public:
	CRotate(float x, float y, float z, float angle);
	virtual ~CRotate();

	CString ToString();
	void DoOpenGL();
};

