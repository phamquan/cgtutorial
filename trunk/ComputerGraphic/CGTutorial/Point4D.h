#pragma once
#include "geometric.h"
class CPoint4D :
	public CGeometric
{
public:
	CPoint4D(CPoint3D point);
	virtual ~CPoint4D();
	CString ToString();

protected:
	void BeginOpenGL();
	void DoOpenGL();
};

