#pragma once
#include "String.h"
#include "iostream"
using namespace std;

class CCodeGenerator
{
public:
	CCodeGenerator(void);
	virtual ~CCodeGenerator(void);
private:
	String evalHeader();
	String evalonPaint();
	String evalMain();
public:
	String eval();
};

