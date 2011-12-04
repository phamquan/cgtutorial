#include "StdAfx.h"
#include "OpenGLNode.h"

COpenGLNode::COpenGLNode(void)
{
	ClearChild();
}

COpenGLNode::~COpenGLNode(void)
{
	ClearChild();
}

void COpenGLNode::AddChild(COpenGLNode* child)
{
	m_listChild.Add(child);
}

void COpenGLNode::ClearChild()
{
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