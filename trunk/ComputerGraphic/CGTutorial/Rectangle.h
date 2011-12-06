#pragma once
#include "geometric.h"
class CRectangle :
	public CGeometric
{
public:
	CRectangle(void);
	virtual ~CRectangle(void);

protected:
	virtual void BeginOpenGL();
};

