#include "StdAfx.h"
#include "Geometric.h"


CGeometric::CGeometric(void)
{
	ClearPoint();
}

CGeometric::~CGeometric(void)
{
	ClearPoint();
}

void CGeometric::ClearPoint()
{
	m_listPoint.RemoveAll();
}

void CGeometric::AddPoint(CPoint3D *point)
{
	m_listPoint.Add(point);
}

void CGeometric::AddPoint(float x, float y, float z)
{
	AddPoint(new CPoint3D(x,y,z));
}

void CGeometric::DoOpenGL()
{
	for(int i=0; i<m_listPoint.GetSize(); i++)
	{
		CPoint3D *point = (CPoint3D*)m_listPoint.GetAt(i);
		glVertex3f(point->getX(),point->getY(),point->getZ());
	}
}

void CGeometric::EndOpenGL()
{
	glEnd();
}