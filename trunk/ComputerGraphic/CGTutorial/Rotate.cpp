#include "StdAfx.h"
#include "Rotate.h"

CRotate::CRotate(float x, float y, float z, float angle) : CTransformation("rotate",NODE_ROTATE)
{
	SetData(x,y,z,angle);
}

CRotate::~CRotate()
{
}

CString CRotate::ToString()
{
	char buff[128];

	sprintf_s(buff,"(x=%5.2f, y=%5.2f, z=%5.2f, alpha=%5.2f)",data.getX(),data.getY(),data.getZ(),data.getW());

	return label + CString(buff);
}

void CRotate::DoOpenGL()
{
	glRotatef(data.getW(),data.getX(),data.getY(),data.getZ());
}
