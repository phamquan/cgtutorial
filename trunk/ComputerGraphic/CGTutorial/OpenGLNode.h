#pragma once
#include "HomoPoint.h"
#include "GL/gl.h"
#include "GL/glu.h"

class COpenGLNode
{
public:
	COpenGLNode(int maxChild, BOOLEAN lockDelete);
	virtual ~COpenGLNode(void);
	COpenGLNode* GetParent();
	CPtrArray *GetChilds();

	void AddChild(COpenGLNode* child);
	void RemoveChild(COpenGLNode* child);
	void ClearChild();
	void PaintOpenGL();

	virtual CString ToString();

	//int GetMaxChild();
	BOOLEAN IsLockAdd();
	BOOLEAN IsLockDelete();

protected:
	virtual void BeginOpenGL();
	virtual void DoOpenGL();
	virtual void EndOpenGL();

protected:
	BOOLEAN lockDelete;
	COpenGLNode *parent;
	CPtrArray m_listChild;
	CString name;
	int maxChild;
};

