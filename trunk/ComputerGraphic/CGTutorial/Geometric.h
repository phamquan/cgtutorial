#pragma once
#include "openglnode.h"
#include "Translate.h"
#include "Scale.h"
#include "Rotate.h"

class CGeometric :
	public COpenGLNode
{
public:
	CGeometric(char* label, int ID);
	virtual ~CGeometric();

protected:
	virtual void EndOpenGL();

protected:
	float tmp[16];
	CPoint3D data1;
	CPoint3D data2;
};

