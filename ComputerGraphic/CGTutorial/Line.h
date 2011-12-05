#pragma once
#include "geometric.h"
class CLine :
	public CGeometric
{
public:
	CLine();
	virtual ~CLine(void);

protected:
	void BeginOpenGL();
};

