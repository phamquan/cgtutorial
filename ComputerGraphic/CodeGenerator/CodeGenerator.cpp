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
		+ String("#include <stdio.h>\r\n",0,0)
		+ String("\r\n")
		+ String("#define DEG2RAD (3.14159f/180.0f)\r\n")
		+ String("\r\n");
	return header;
}

String CCodeGenerator::evalonPaint() {
	String onPaint=
		String("void onPaint() {\r\n")
		+ String("\tglMatrixMode(GL_MODELVIEW);\r\n")
		+ String("\tglLoadIdentity();\r\n")
		+ evalCamera()
		+ String("\tglClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);\r\n")
		+ String("}\r\n")
		+ String("\r\n")
		;
	return onPaint;
}

String CCodeGenerator::evalCamera() {
	if (!qtml->camera) return String("");
	TiXmlAttribute* pAttrib = qtml->camera->FirstAttribute();
	double dval;
	while(pAttrib) {
		String t = String(pAttrib->Name()).toUpperCase();
		if (pAttrib->QueryDoubleValue(&dval)==TIXML_SUCCESS) {
			if (!t.compareTo("XPOS"))
				camera.xpos = dval;
			else if (!t.compareTo("YPOS"))
				camera.ypos = dval;
			else if (!t.compareTo("ZPOS"))
				camera.zpos = dval;
			else if (!t.compareTo("XLOOK"))
				camera.xlook = dval;
			else if (!t.compareTo("YLOOK"))
				camera.ylook = dval;
			else if (!t.compareTo("ZLOOK"))
				camera.zlook = dval;
			else if (!t.compareTo("XUP"))
				camera.xup = dval;
			else if (!t.compareTo("YUP"))
				camera.yup = dval;
			else if (!t.compareTo("ZUP"))
				camera.zup = dval;
		}
		pAttrib = pAttrib->Next();
	}
	char buffer[200];
	sprintf(buffer,"gluLookat(%f,%f,%f,\r\n\t\t%f,%f,%f,\r\n\t\t%f,%f,%f);\r\n",
					camera.xpos, camera.ypos, camera.zpos,
					camera.xlook, camera.ylook, camera.zlook,
					camera.xup, camera.yup, camera.zup);
	return String(buffer);
}

String CCodeGenerator::evalinitOpenGL() {
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
		+ String("\tglutCreateWindow(\"Computer Graphic Tutorial\");\r\n")
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