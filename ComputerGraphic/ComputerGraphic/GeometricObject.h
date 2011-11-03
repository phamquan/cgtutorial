#pragma once
class CGeometricObject
{
public:
	CGeometricObject(void);
	virtual ~CGeometricObject(void);
	
	virtual void Draw(void) = 0;
};

