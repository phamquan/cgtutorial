#pragma once

#include "OpenGLNode.h"

#define ACTION_ADD			1
#define ACTION_EDIT			2
#define ACTION_DELETE		3

class CAction
{
public:
	int ID;
	BOOL con;
	COpenGLNode *first;
	COpenGLNode *second;

	CAction(int i, COpenGLNode *f, COpenGLNode *s, BOOL c)
	{
		ID = i;
		first = f;
		second = s;
		con = c;
	}

	virtual ~CAction(void)
	{
	}
};

