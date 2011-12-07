#include "StdAfx.h"
#include "OpenGLNode.h"

COpenGLNode::COpenGLNode()
{
	ID = NODE_ROOT;
	name = "object";
	ClearChild();
}

COpenGLNode::~COpenGLNode()
{
	ClearChild();
}

COpenGLNode* COpenGLNode::GetParent()
{
	return parent;
}

CPtrArray* COpenGLNode::GetChilds()
{
	return &m_listChild;
}

void COpenGLNode::AddChild(COpenGLNode* child)
{
	child->parent = this;
	m_listChild.Add(child);
}

void COpenGLNode::RemoveChild(COpenGLNode* child)
{
	for(int i=0; i<m_listChild.GetSize(); i++)
	{
		if(child == m_listChild.ElementAt(i))
		{
			m_listChild.RemoveAt(i);
			break;
		}
	}
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

CString COpenGLNode::ToString()
{
	return name + "()";
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