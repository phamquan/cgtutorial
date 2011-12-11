#pragma once
#include "openglnode.h"
#include "Camera.h"
#include "Projection.h"

class CEnvironment :
	public COpenGLNode
{
public:
	CEnvironment();
	virtual ~CEnvironment();
	CCamera* GetCamera();
	CProjection* GetProjection();
};

