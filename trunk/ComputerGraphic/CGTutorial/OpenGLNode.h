#pragma once

class COpenGLNode
{
public:
	COpenGLNode(void);
	~COpenGLNode(void);

	virtual void BeginOpenGL() = 0;
	virtual void DoOpenGL() = 0;
	virtual void EndOpenGL() = 0;
};

