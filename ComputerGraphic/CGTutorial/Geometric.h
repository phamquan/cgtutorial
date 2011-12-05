#pragma once
#include "openglnode.h"

class CGeometric :
	public COpenGLNode
{
public:
	CGeometric(void);
	virtual ~CGeometric(void);
	void AddPoint(CPoint3D *point);
	void AddPoint(float x, float y, float z);
	void ClearPoint();

protected:
	virtual void DoOpenGL();
	virtual void EndOpenGL();

protected:
	inline float abs(float a) {return a>=0?a:-a;}
	CPtrArray m_listPoint;
};

