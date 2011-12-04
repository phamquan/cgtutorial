// GeometricObject.cpp: implementation of the CGeometricObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GeometricObject.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


#define DIB_HEADER_MARKER   ((WORD) ('M' << 8) | 'B')
const int PADSIZE = 4;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CGeometricObject::~CGeometricObject()
{
}
void CGeometricObject::setBegin(CPoint3D begin)
{
	m_Begin = begin;
}

CPoint3D* CGeometricObject::getBegin()
{
	return &m_Begin;
}
void CGeometricObject::setEnd(CPoint3D end)
{
	m_End = end;
}

CPoint3D* CGeometricObject::getEnd()
{
	return &m_End;
}
void CGeometricObject::Draw() {
	float m[4];

	x = abs(m_Begin.getX()-m_End.getX())/2;
	y = abs(m_Begin.getY()-m_End.getY())/2;
	z = abs(m_Begin.getZ()-m_End.getZ())/2;

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glTranslatef(getCenter()->getX(),getCenter()->getY(),getCenter()->getZ());
	glMultMatrixf(m_RotateMatrix);
	glScalef(m_Scale.getX(),m_Scale.getY(),m_Scale.getZ());
	glColor4f(m_Color.getX(),m_Color.getY(),m_Color.getZ(),m_Color.getW());

	Draw_Object();
	glPopMatrix();
}