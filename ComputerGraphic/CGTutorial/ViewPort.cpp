#include "StdAfx.h"
#include "ViewPort.h"

CViewPort::CViewPort(float x, float y, float width, float height, int type) : COpenGLNode("viewport",NODE_VIEWPORT)
{
	SetData(x, y, width, height, type);
}

CViewPort::~CViewPort()
{
}

void CViewPort::SetData(float x, float y, float width, float height, int type)
{
	data.setCoords(x,y,width,height);
	this->type = type;
}

void CViewPort::GetData(float &x, float &y, float &width, float &height, int &type)
{
	x = data.getX();
	y = data.getY();
	width = data.getZ();
	height = data.getW();
	type = this->type;
}
	
CString CViewPort::ToString()
{
	char buff[1024];

	sprintf_s(buff,"x=%5.2f, y=%5.2f, width=%5.2f, height=%5.2f)",
			data.getX(),data.getY(),data.getZ(),data.getW());

	if(type == VIEWPORT_DEFAULT)
		return label + CString("(type=default)");	
	else
		return label + CString("(type=custom, ") + CString(buff);
}