#pragma once
#include "geometric.h"
#include "Point4D.h"

class CLine :
	public CGeometric
{
public:
	CLine(CPoint3D begin, CPoint3D end);
	virtual ~CLine();
	CString ToString();

protected:
	void BeginOpenGL();
	void DoOpenGL();
};

