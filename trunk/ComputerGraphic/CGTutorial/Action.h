#pragma once

#include "OpenGLNode.h"

#define ACTION_ADD		1
#define ACTION_EDIT		2
#define ACTION_DELETE	3

class CAction
{
public:
	int ID;
	COpenGLNode *first;
	COpenGLNode *second;

	CAction(int ID, COpenGLNode *f, COpenGLNode *s)
	{
		this->ID = ID;
		first = f;
		second = s;
	}

	virtual ~CAction(void)
	{
	}
};

