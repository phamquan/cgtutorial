#include "StdAfx.h"
#include "Color.h"

CColor::CColor(float red, float green, float blue) : COpenGLNode("color",NODE_COLOR)
{
	SetData(red,green,blue);
}

CColor::~CColor()
{
}

void CColor::SetData(float red, float green, float blue)
{
	data.setCoords(red,green,blue);
}

void CColor::GetData(float &red, float &green, float &blue)
{
	red = data.getX();
	green = data.getY();
	blue = data.getZ();
}

CString CColor::ToString()
{
	CString result = label + " (";

	char buff[1024];

	sprintf(buff,"red=%5.2f, green=%5.2f, blue=%5.2f",
		data.getX(),data.getY(),data.getZ());

	return result + CString(buff) + ")";
}

void CColor::BeginOpenGL()
{
	glGetFloatv(GL_CURRENT_COLOR,currentColor);
}

void CColor::DoOpenGL()
{
	glColor4f(data.getX(),data.getY(),data.getZ(),data.getW());
}

void CColor::EndOpenGL()
{
	glColor4fv(currentColor);
}