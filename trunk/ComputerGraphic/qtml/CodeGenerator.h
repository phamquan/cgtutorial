#pragma once
#include "iostream"
using namespace std;

class CCodeGenerator
{
public:
	CCodeGenerator(void);
	virtual ~CCodeGenerator(void);
private:
	string evalHeader();
	string evalMain();
public:
	char* eval();
};

