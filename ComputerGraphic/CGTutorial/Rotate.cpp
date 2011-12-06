#include "StdAfx.h"
#include "Rotate.h"

CRotate::CRotate()
{
	name = "rotate";
}

CRotate::~CRotate()
{
}

CString CRotate::ToString()
{
	CString result = name + " (";

	char buff[1024];

	sprintf(buff,"x=%f, y=%f, z=%f, alpha=%f",data.getX(),data.getY(),data.getZ(),data.getW());

	return result + CString(buff) + ")";
}

void CRotate::DoOpenGL()
{
	glRotatef(data.getW(),data.getX(),data.getY(),data.getZ());
}
