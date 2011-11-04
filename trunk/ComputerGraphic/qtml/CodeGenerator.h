#pragma once

#include "header.h"
#include "String.h"
#include "qtmlManager.h"
#include "iostream"
using namespace std;
using namespace CGTutorial;

class CCodeGenerator
{
public:
	CCodeGenerator(void);
	CCodeGenerator(const char*);
	virtual ~CCodeGenerator(void);
private:
	qtmlManager *qtml;
	char filename[255];
	CAMERA camera;
	

	String evalHeader();
	String evalinitOpenGL();
	String evalonPaint();
	String evalCamera();
	String evalMain();
public:
	String eval();
	void setFilename(const char* filename);
	char* getFilename();
};
