#pragma once
#include "geometric.h"
class CPoint4D :
	public CGeometric
{
public:
	CPoint4D(float x, float y, float z);
	virtual ~CPoint4D();

	void SetData(float x, float y, float z);
	void GetData(float &x, float &y, float &z);
	CString ToString();

protected:
	void BeginOpenGL();
	void DoOpenGL();
};

