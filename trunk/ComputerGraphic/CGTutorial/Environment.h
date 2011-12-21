#pragma once
#include "openglnode.h"
#include "Camera.h"
#include "Projection.h"
#include "ViewPort.h"

class CEnvironment :
	public COpenGLNode
{
public:
	CEnvironment();
	virtual ~CEnvironment();
	CCamera* GetCamera();
	CProjection* GetProjection();
	CViewPort* GetViewPort();

	void DrawCamera();
};

