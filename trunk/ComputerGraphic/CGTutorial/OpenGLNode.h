#pragma once
#include "HomoPoint.h"
#include "GL/gl.h"
#include "GL/glu.h"

class COpenGLNode
{
public:
	COpenGLNode();
	virtual ~COpenGLNode(void);
	void AddChild(COpenGLNode* child);
	void ClearChild();
	virtual void PaintOpenGL();

protected:
	virtual void BeginOpenGL() {};
	virtual void DoOpenGL() {};
	virtual void EndOpenGL() {};

protected:
	COpenGLNode *parent;
	CPtrArray m_listChild;
};

