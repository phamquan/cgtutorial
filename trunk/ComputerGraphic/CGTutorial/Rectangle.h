#pragma once
#include "geometric.h"

class CRectangle :
	public CGeometric
{
public:
	CRectangle(float top, float left, float bottom, float right);
	virtual ~CRectangle();

	void SetData(float top, float left, float bottom, float right);
	void GetData(float &top, float &left, float &bottom, float &right);
	CString ToString();
	void DoOpenGL();

protected:
	void BeginOpenGL();
};

