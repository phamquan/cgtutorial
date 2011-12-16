#pragma once
#include "geometric.h"
#include "Point4D.h"

class CLine :
	public CGeometric
{
public:
	CLine(float x1, float y1, float z1, float x2, float y2, float z2);
	virtual ~CLine();

	CLine* CalculateModel();
	void SetData(float x1, float y1, float z1, float x2, float y2, float z2);
	void GetData(float &x1, float &y1, float &z1, float &x2, float &y2, float &z2);
	CString ToString();
	void DoOpenGL();

protected:
	void BeginOpenGL();
};

