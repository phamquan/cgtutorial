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

	//Texturing
	if(isNoFill == false)
		texture.Load();

	//Material
	GLenum face = GL_FRONT;
	if(Material.m_Front == TRUE)
		if(Material.m_Back == TRUE)
			face = GL_FRONT_AND_BACK;
		else
			face = GL_FRONT;
	else
		if(Material.m_Back == TRUE)
			face = GL_BACK;

	glDisable(GL_COLOR_MATERIAL);
	if(Material.m_Use_Color) {
		glEnable(GL_COLOR_MATERIAL);
	} else {
		Material.GetAmbient(m);
		glMaterialfv(face,GL_AMBIENT,m);
		Material.GetDiffuse(m);
		glMaterialfv(face,GL_DIFFUSE,m);
		Material.GetSpecular(m);
		glMaterialfv(face,GL_SPECULAR,m);
		Material.GetEmission(m);
		glMaterialfv(face,GL_EMISSION,m);
		glMaterialf(face,GL_SHININESS,Material.m_Shininess);
	}
	Draw_Object();
	
	if(isSelected) {
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
		Draw_Bound();
	}
	glPopMatrix();
}
void CGeometricObject::Draw_BoundSquare(double x, double y, double z) {
	double sizeX = 0.02/m_Scale.getX();
	double sizeY = 0.02/m_Scale.getY();
	double sizeZ = 0.02/m_Scale.getZ();
	glColor4f(1.0f,1.0f,1.0f,1.0f);
	glBegin(GL_QUADS);
		glVertex3d(x+sizeX,y+sizeY,z+sizeZ);
		glVertex3d(x+sizeX,y+sizeY,z-sizeZ);
		glVertex3d(x+sizeX,y-sizeY,z-sizeZ);
		glVertex3d(x+sizeX,y-sizeY,z+sizeZ);

		glVertex3d(x-sizeX,y+sizeY,z+sizeZ);
		glVertex3d(x-sizeX,y+sizeY,z-sizeZ);
		glVertex3d(x-sizeX,y-sizeY,z-sizeZ);
		glVertex3d(x-sizeX,y-sizeY,z+sizeZ);

		glVertex3d(x+sizeX,y+sizeY,z+sizeZ);
		glVertex3d(x+sizeX,y+sizeY,z-sizeZ);
		glVertex3d(x-sizeX,y+sizeY,z-sizeZ);
		glVertex3d(x-sizeX,y+sizeY,z+sizeZ);

		glVertex3d(x+sizeX,y-sizeY,z+sizeZ);
		glVertex3d(x+sizeX,y-sizeY,z-sizeZ);
		glVertex3d(x-sizeX,y-sizeY,z-sizeZ);
		glVertex3d(x-sizeX,y-sizeY,z+sizeZ);

		glVertex3d(x+sizeX,y+sizeY,z+sizeZ);
		glVertex3d(x+sizeX,y-sizeY,z+sizeZ);
		glVertex3d(x-sizeX,y-sizeY,z+sizeZ);
		glVertex3d(x-sizeX,y+sizeY,z+sizeZ);

		glVertex3d(x+sizeX,y+sizeY,z-sizeZ);
		glVertex3d(x+sizeX,y-sizeY,z-sizeZ);
		glVertex3d(x-sizeX,y-sizeY,z-sizeZ);
		glVertex3d(x-sizeX,y+sizeY,z-sizeZ);
	glEnd();
	sizeX+= 0.003;
	sizeY+= 0.003;
	sizeZ+= 0.003;
	glColor4f(0.0f,0.0f,0.0f,1.0f);
	glBegin(GL_LINE_LOOP);
		glVertex3d(x+sizeX,y+sizeY,z+sizeZ);
		glVertex3d(x+sizeX,y+sizeY,z-sizeZ);
		glVertex3d(x+sizeX,y-sizeY,z-sizeZ);
		glVertex3d(x+sizeX,y-sizeY,z+sizeZ);
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex3d(x-sizeX,y+sizeY,z+sizeZ);
		glVertex3d(x-sizeX,y+sizeY,z-sizeZ);
		glVertex3d(x-sizeX,y-sizeY,z-sizeZ);
		glVertex3d(x-sizeX,y-sizeY,z+sizeZ);
	glEnd();
	glBegin(GL_LINES);
		glVertex3d(x+sizeX,y+sizeY,z+sizeZ);
		glVertex3d(x-sizeX,y+sizeY,z+sizeZ);

		glVertex3d(x+sizeX,y+sizeY,z-sizeZ);
		glVertex3d(x-sizeX,y+sizeY,z-sizeZ);

		glVertex3d(x+sizeX,y-sizeY,z-sizeZ);
		glVertex3d(x-sizeX,y-sizeY,z-sizeZ);

		glVertex3d(x+sizeX,y-sizeY,z+sizeZ);
		glVertex3d(x-sizeX,y-sizeY,z+sizeZ);
	glEnd();
}
void CGeometricObject::Zoom(float X, float Y, float Z) {
	m_Scale.setCoords(m_Scale.getX() + X,
					  m_Scale.getY() + Y,
					  m_Scale.getZ() + Z);

	if(m_Scale.getX() < 0.1)
		m_Scale.setX(0.1f);
	if(m_Scale.getY() < 0.1)
		m_Scale.setY(0.1f);
	if(m_Scale.getZ() < 0.1)
		m_Scale.setZ(0.1f);
}
void CGeometricObject::Rotate(float X, float Y, float Z) {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glRotatef(X,1,0,0);
	glRotatef(Y,0,1,0);
	glRotatef(Z,0,0,1);
	glMultMatrixf(m_RotateMatrix);
	glGetFloatv(GL_MODELVIEW_MATRIX,m_RotateMatrix);
	glPopMatrix();
}
void CGeometricObject::ChangeColor(float R, float G, float B) {
	isNoFill = false;
	m_Color.setCoords(R/255,G/255,B/255);
}
void CGeometricObject::Move(float X, float Y, float Z) {
	m_Begin.setCoords(m_Begin.getX()+X,
					  m_Begin.getY()+Y,
					  m_Begin.getZ()+Z);
	m_Middle.setCoords(m_Middle.getX()+X,
					   m_Middle.getY()+Y,
					   m_Middle.getZ()+Z);
	m_End.setCoords(m_End.getX()+X,
				    m_End.getY()+Y,
					m_End.getZ()+Z);
}
void CGeometricObject::ChangeTexture(CString FileName){
	texture.Change(FileName);
	isNoFill = false;
}
