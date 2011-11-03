#pragma once
#include "String.h"
#include "qtmlManager.h"
#include "iostream"
using namespace std;

class CCodeGenerator
{
public:
	CCodeGenerator(void);
	CCodeGenerator(const char*);
	virtual ~CCodeGenerator(void);
private:
	qtmlManager *qtml;
	char filename[255];

	String evalHeader();
	String evalonPaint();
	String evalMain();
public:
	String eval();
	void setFilename(const char* filename);
	char* getFilename();
};

