#include "StdAfx.h"
#include "Geometric.h"


CGeometric::CGeometric(void)
{
	Clear();
}

CGeometric::~CGeometric(void)
{
	Clear();
}

void CGeometric::Clear()
{
	m_listPoint.RemoveAll();
}

void CGeometric::AddPoint(float x, float y, float z)
{
	CPoint3D *point = new CPoint3D(x,y,z);
	m_listPoint.Add(point);
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