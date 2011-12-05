#pragma once
#include "geometric.h"
class CPoint4D :
	public CGeometric
{
public:
	CPoint4D(CPoint3D data);
	virtual ~CPoint4D(void);

protected:
	void DoOpenGL();
	void EndOpenGL();
	CPoint3D data;
};

