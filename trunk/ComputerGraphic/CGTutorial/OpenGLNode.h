#pragma once
#include "HomoPoint.h"
#include "GL/glut.h"

#define NODE_VIEWPORT	-4
#define NODE_PROJECTION	-3
#define NODE_CAMERA		-2
#define NODE_ENVIRONMENT -1
#define NODE_NONE		0
#define NODE_OBJECT		1
#define NODE_TRANSLATE	2
#define NODE_ROTATE		3
#define NODE_SCALE		4
#define NODE_COLOR		5
#define NODE_POINT		6
#define NODE_LINE		7
#define NODE_RECTANGLE	8

class COpenGLNode
{
public:
	COpenGLNode(char* label, int ID);
	virtual ~COpenGLNode();
	int GetID();

	COpenGLNode* GetParent();
	CPtrArray* GetChilds();

	void AddChild(COpenGLNode* child);
	void RemoveChild(COpenGLNode* child);
	void ClearChild();

	void PaintOpenGL();
	virtual void DoOpenGL();

	virtual CString ToString();

protected:
	virtual void BeginOpenGL() {};
	virtual void EndOpenGL() {};

protected:
	COpenGLNode* parent;
	CPtrArray m_listChild;

	CString label;
	int ID;
};

