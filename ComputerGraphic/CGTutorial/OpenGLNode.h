#pragma once
#include "HomoPoint.h"
#include "GL/gl.h"
#include "GL/glu.h"

class COpenGLNode
{
public:
	COpenGLNode(void);
	virtual ~COpenGLNode(void);
	void AddChild(COpenGLNode* child);
	void ClearChild();
	virtual void PaintOpenGL();

protected:
	virtual void BeginOpenGL() = 0;
	virtual void DoOpenGL() = 0;
	virtual void EndOpenGL() = 0;

protected:
	CPtrArray m_listChild;
};

