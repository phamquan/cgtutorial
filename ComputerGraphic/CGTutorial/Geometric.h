#pragma once
#include "openglnode.h"
#include "HomoPoint.h"
#include "GL/gl.h"
#include "GL/glu.h"

class CGeometric :
	public COpenGLNode
{
public:
	CGeometric(void);
	virtual ~CGeometric(void);
	void Clear();
	void AddPoint(float x, float y, float z);

	virtual void DoOpenGL();
	virtual void EndOpenGL();

protected:
	inline float abs(float a) {return a>=0?a:-a;}
	CPtrArray m_listPoint;
};

