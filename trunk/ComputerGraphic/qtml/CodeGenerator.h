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
	qtmlManager *repo;
	char *filename;

	String evalHeader();
	String evalonPaint();
	String evalMain();
public:
	String eval();
	void setFilename(const char* filename);
	char* getFilename();
};

