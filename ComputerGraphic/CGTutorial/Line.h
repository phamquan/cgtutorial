#pragma once
#include "geometric.h"
#include "Point4D.h"

class CLine :
	public CGeometric
{
public:
	CLine();
	virtual ~CLine(void);

protected:
	void BeginOpenGL();
};

