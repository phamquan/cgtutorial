#pragma once

#include "stdafx.h"
#include "HomoPoint.h"
#include "../Library/GL/glut.h"

#define NODE_VIEWPORT		-4
#define NODE_PROJECTION		-3
#define NODE_CAMERA			-2
#define NODE_ENVIRONMENT	-1
#define NODE_NONE			0
#define NODE_OBJECT			1
#define NODE_TRANSLATE		2
#define NODE_ROTATE			3
#define NODE_SCALE			4
#define NODE_POINT			5
#define NODE_LINE			6
#define NODE_RECTANGLE		7
#define NODE_TRIANGLE		8
#define NODE_CIRCLE			9
#define NODE_ELLIPSE		10
#define NODE_CUBE			11
#define NODE_TETRAHEDRON	12
#define NODE_SPHERE			13
#define NODE_CYLINDER		14
#define NODE_RING			15

class COpenGLNode
{
public:
	COpenGLNode* parent;
	CPtrArray* m_listChild;
	CString toString;
	CString GLCode;
	CString serialize;
	int ID;

public:

	COpenGLNode(int ID)
	{
		this->ID = ID;
		parent = NULL;
		m_listChild = new CPtrArray();
		toString = serialize = "object";
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

	virtual void Serialize(CArchive& ar, int tab=0)
	{
		CString t;
		for(int i=0; i<tab; i++)
			t += '\t';

		ar.WriteString(t + "<" + serialize + ">\r\n");

		for(int i=0; i<m_listChild->GetSize(); i++)
		{
			((COpenGLNode*)m_listChild->GetAt(i))->Serialize(ar,tab+1);
		}

		int i = 0;
		CString x = serialize.Tokenize(CString(" "),i);
		ar.WriteString(t + "</" + x + ">\r\n");
	}

protected:

	virtual void BeginOpenGL() {} ;

	virtual void EndOpenGL() {} ;
};

