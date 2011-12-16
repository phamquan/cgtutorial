#include "StdAfx.h"
#include "Geometric.h"

CGeometric::CGeometric(char* label, int ID) : COpenGLNode(label,ID)
{
}

CGeometric::~CGeometric()
{
}

void CGeometric::EndOpenGL()
{
	glEnd();
}

void CGeometric::PreCalculateModel()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glGetFloatv(GL_MODELVIEW_MATRIX,tmp);

	COpenGLNode* parent = this->parent;
	while(parent != NULL)
	{
		glLoadIdentity();
		if(parent->GetID() == NODE_TRANSLATE)
		{
			parent->DoOpenGL();
			glMultMatrixf(tmp);
			glGetFloatv(GL_MODELVIEW_MATRIX,tmp);
		}

		parent = parent->GetParent();
	}
}

void CGeometric::PosCalculateModel()
{
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}