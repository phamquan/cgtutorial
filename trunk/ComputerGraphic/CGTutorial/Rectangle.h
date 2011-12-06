#pragma once
#include "geometric.h"
class CRectangle :
	public CGeometric
{
public:
	CRectangle(void);
	CRectangle(CPoint3D begin, CPoint3D end);
	virtual ~CRectangle(void);

protected:
	virtual void BeginOpenGL();
};

