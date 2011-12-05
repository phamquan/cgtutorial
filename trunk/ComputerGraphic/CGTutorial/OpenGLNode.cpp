#include "StdAfx.h"
#include "OpenGLNode.h"

COpenGLNode::COpenGLNode()
{
	lockAdd = false;
	lockDelete = true;
	ClearChild();
}

COpenGLNode::~COpenGLNode(void)
{
	ClearChild();
}

void COpenGLNode::AddChild(COpenGLNode* child)
{
	child->parent = this;
	m_listChild.Add(child);
}

void COpenGLNode::ClearChild()
{
	parent = NULL;
	m_listChild.RemoveAll();
}

void COpenGLNode::PaintOpenGL()
{
	BeginOpenGL();
	DoOpenGL();

	for(int i=0; i<m_listChild.GetSize(); i++)
	{
		((COpenGLNode*)m_listChild.GetAt(i))->PaintOpenGL();
	}

	EndOpenGL();
}

void COpenGLNode::BeginOpenGL()
{
}

void COpenGLNode::DoOpenGL()
{
}

void COpenGLNode::EndOpenGL()
{
}