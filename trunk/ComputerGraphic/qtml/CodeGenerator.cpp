#include "CodeGenerator.h"

CCodeGenerator::CCodeGenerator(void)
{
	qtml = new qtmlManager();
}

CCodeGenerator::CCodeGenerator(const char* filename) {
	qtml = new qtmlManager(filename);
	strcpy(this->filename,filename);
}

CCodeGenerator::~CCodeGenerator(void)
{
}

String CCodeGenerator::evalHeader() {
	String header=
		String("#include <GL/glut.h>\r\n")
		+ String("#include <math.h>\r\n")
		+ String("#include <stdio.h>\r\n")
		+ String("\r\n")
		+ String("#define DEG2RAD (3.14159f/180.0f)\r\n")
		+ String("\r\n");
	return header;
}

String CCodeGenerator::evalonPaint() {
	String onPaint=
		String("void onPaint() {\r\n")
		+ String("\r\n")
		+ String("}\r\n")
		+ String("\r\n")
		;
	return onPaint;
}

String evalinitOpenGL() {
	String initOpenGL=
		String("void initOpenGL() {\r\n")
		+ String("\tglMatrixMode(GL_PROJECTION);\r\n")
		+ String("\tglLoadIdentity();\r\n")
		+ String("\tglMatrixMode(GL_MODELVIEW);\r\n")
		+ String("}\r\n")
		+ String("\r\n")
		;
	return initOpenGL;
}

String CCodeGenerator::evalMain() {
	String program=
		String("int main(int argc, char** argv) {				\r\n")
		+ String("\tglutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);\r\n")
		+ String("\tglutCreateWindow(\"simple\");\r\n")
		+ String("\tinitOpenGL();\r\n")
		+ String("\tglutDisplayFunc(onPaint);\r\n")
		+ String("\tglutMainLoop();\r\n")
		+ String("}\r\n")
		;
	return program;
}

String CCodeGenerator::eval() {
	qtml->Load(this->filename);
	return evalHeader() 
		+ evalonPaint()
		+ evalinitOpenGL()
		+ evalMain();
}

void CCodeGenerator::setFilename(const char* filename) {
	strcpy(this->filename, filename);
}

char* CCodeGenerator::getFilename() {
	char *t;
	strcpy(this->filename, t);
	return t;
}