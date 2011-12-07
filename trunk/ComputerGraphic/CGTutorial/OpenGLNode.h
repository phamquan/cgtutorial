#pragma once
#include "HomoPoint.h"
#include "GL/gl.h"
#include "GL/glu.h"

#define NODE_NONE		0
#define NODE_TRANSLATE	1
#define NODE_ROTATE		2
#define NODE_SCALE		3
#define NODE_COLOR		4
#define NODE_POINT		5
#define NODE_LINE		6
#define NODE_RECTANGLE	7

class COpenGLNode
{
public:
	COpenGLNode(CString label, int ID);
	virtual ~COpenGLNode();

	COpenGLNode* GetParent();
	CPtrArray *GetChilds();

	void AddChild(COpenGLNode* child);
	void RemoveChild(COpenGLNode* child);
	void ClearChild();

	void PaintOpenGL();

	virtual CString ToString();

protected:
	virtual void BeginOpenGL();
	virtual void DoOpenGL();
	virtual void EndOpenGL();


protected:
	COpenGLNode *parent;
	CPtrArray m_listChild;

	CString label;
	int ID;
};

