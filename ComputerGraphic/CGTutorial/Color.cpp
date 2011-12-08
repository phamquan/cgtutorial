#include "StdAfx.h"
#include "Color.h"

CColor::CColor() : COpenGLNode("color",NODE_COLOR)
{
}

CColor::~CColor()
{
}

void CColor::SetData(float red, float green, float blue, float alpha)
{
	data.setCoords(red,green,blue,alpha);
}

CString CColor::ToString()
{
	CString result = label + " (";

	char buff[1024];

	sprintf(buff,"red=%5.2f, green=%5.2f, blue=%5.2f, alpha=%5.2f",
		data.getX(),data.getY(),data.getZ(),data.getW());

	return result + CString(buff) + ")";
}

void CColor::DoOpenGL()
{
	glColor4f(data.getX(),data.getY(),data.getZ(),data.getW());
}