#pragma once
#include "geometric.h"
class CRectangle :
	public CGeometric
{
public:
	CRectangle(float top, float left, float bottom, float right);
	virtual ~CRectangle();
	CString ToString();

protected:
	void BeginOpenGL();
	void DoOpenGL();
};

