#include "CodeGenerator.h"
#include "iostream"
using namespace std;

CCodeGenerator::CCodeGenerator(void)
{
}


CCodeGenerator::~CCodeGenerator(void)
{
}

string CCodeGenerator::evalHeader() {

}

string CCodeGenerator::evalMain() {
	string program[]={
		"int main(int argc, char** argv){				\n"
		,"glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);\n"
		,"glutCreateWindow(\"simple\");\n"
		,"glutDisplayFunc(mydisplay);\n"
		,"glutMainLoop();\n"
	};
	return program;
}