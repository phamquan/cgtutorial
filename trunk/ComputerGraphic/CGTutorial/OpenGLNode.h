#pragma once

#include "stdafx.h"
#include "HomoPoint.h"
#include "../Library/GL/glut.h"

#define NODE_VIEWPORT	-4
#define NODE_PROJECTION	-3
#define NODE_CAMERA		-2
#define NODE_ENVIRONMENT -1
#define NODE_NONE		0
#define NODE_OBJECT		1
#define NODE_TRANSLATE	2
#define NODE_ROTATE		3
#define NODE_SCALE		4
#define NODE_POINT		5
#define NODE_LINE		6
#define NODE_RECTANGLE	7
#define NODE_TRIANGLE	8

class COpenGLNode
{
public:
	COpenGLNode* parent;
	CPtrArray* m_listChild;
	CString toString;
	CString GLCode;
	int ID;

public:

	COpenGLNode(int ID)
	{
		this->ID = ID;
		parent = NULL;
		m_listChild = new CPtrArray();
		toString = "object";
	}

	virtual ~COpenGLNode()
	{
		ClearChild();
		delete m_listChild;
	}

	void AddChild(COpenGLNode* child)
	{
		child->parent = this;
		m_listChild->Add(child);
	}

	void RemoveChild(COpenGLNode* child)
	{
		for(int i=0; i<m_listChild->GetSize(); i++)
		{
			if(child == m_listChild->ElementAt(i))
			{
				delete m_listChild->GetAt(i);
				m_listChild->RemoveAt(i);
				break;
			}
		}
	}

	void ClearChild()
	{
		for(int i=0; i<m_listChild->GetSize(); i++) {
			delete m_listChild->GetAt(i);
		}
		m_listChild->RemoveAll();
	}

	void PaintOpenGL()
	{
		BeginOpenGL();
		DoOpenGL();

		for(int i=0; i<m_listChild->GetSize(); i++)
		{
			((COpenGLNode*)m_listChild->GetAt(i))->PaintOpenGL();
		}

		EndOpenGL();
	}

	virtual void DoOpenGL()
	{
		glMatrixMode(GL_MODELVIEW);
	}

protected:

	virtual void BeginOpenGL() {} ;

	virtual void EndOpenGL() {} ;
};

