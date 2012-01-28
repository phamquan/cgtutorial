#pragma once

#include "OpenGLNode.h"

#define ADD		1
#define EDIT	2
#define DELETE	3

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

