#pragma once
#include "geometric.h"
class CLine :
	public CGeometric
{
public:
	CLine(void);
	virtual ~CLine(void);

protected:
	virtual void BeginOpenGL();
};

