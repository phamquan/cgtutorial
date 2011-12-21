#include "StdAfx.h"
#include "Environment.h"

CEnvironment::CEnvironment() : COpenGLNode("environment",NODE_ENVIRONMENT)
{
}

CEnvironment::~CEnvironment()
{
}

CCamera* CEnvironment::GetCamera()
{
	for(int i=0; i<m_listChild.GetSize(); i++)
		if(((COpenGLNode*)m_listChild.GetAt(i))->GetID() == NODE_CAMERA)
			return (CCamera*)m_listChild.GetAt(i);
	return NULL;
}

CProjection* CEnvironment::GetProjection()
{
	for(int i=0; i<m_listChild.GetSize(); i++)
		if(((COpenGLNode*)m_listChild.GetAt(i))->GetID() == NODE_PROJECTION)
			return (CProjection*)m_listChild.GetAt(i);
	return NULL;
}

CViewPort* CEnvironment::GetViewPort()
{
	for(int i=0; i<m_listChild.GetSize(); i++)
		if(((COpenGLNode*)m_listChild.GetAt(i))->GetID() == NODE_VIEWPORT)
			return (CViewPort*)m_listChild.GetAt(i);
	return NULL;
}

void CEnvironment::DrawCamera()
{
	if(m_listChild.GetSize() < 2)
		return;

	float m[16];
	float n[16];
	CProjection* projection = GetProjection();
	CCamera* camera = GetCamera();

	//Calculate camera position
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	camera->PaintOpenGL();
	glGetFloatv(GL_MODELVIEW_MATRIX,m);
	glPopMatrix();
	//End calulate camera position

	//Reverse camera position;
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	InvertMatrix(m,n);
	glMultMatrixf(n);
	
	glBegin(GL_LINES);
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(1.0f,0.0f,0.0f);
		glVertex3f(1.1f,0.05f,0.0f);
		glVertex3f(1.2f,-0.05f,0.0f);
		glVertex3f(1.2f,0.05f,0.0f);
		glVertex3f(1.1f,-0.05f,0.0f);

		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,1.0f,0.0f);
		glVertex3f(-0.05f,1.2f,0.0f);
		glVertex3f(0.0f,1.15f,0.0f);
		glVertex3f(0.05f,1.2f,0.0f);
		glVertex3f(0.0f,1.15f,0.0f);
		glVertex3f(0.0f,1.1f,0.0f);
		glVertex3f(0.0f,1.15f,0.0f);

		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(0.0f,0.0f,-1.0f);
		glVertex3f(0.0f,0.0f,1.0f);
		glVertex3f(0.0f,0.05f,1.2f);
		glVertex3f(0.0f,0.05f,1.1f);
		glVertex3f(0.0f,-0.05f,1.2f);
		glVertex3f(0.0f,-0.05f,1.1f);
		glVertex3f(0.0f,0.05f,1.1f);
		glVertex3f(0.0f,-0.05f,1.2f);
	glEnd();

	int size = 7;
	double radius = 0.3;
	double offset = 0.03;
	double z = 0;
	glColor3f(0.5f,0.5f,0.5f);
	for(int i = 0; i<size; i++) {
		glBegin(GL_POLYGON);
			glVertex3f(-radius,-radius,z-offset);
			glVertex3f( radius,-radius,z-offset);
			glVertex3f( radius,-radius+0.05,z-offset);
			glVertex3f(-radius,-radius+offset,z-offset);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3f(-radius, radius,z-offset);
			glVertex3f( radius, radius,z-offset);
			glVertex3f( radius, radius-offset,z-offset);
			glVertex3f(-radius, radius-offset,z-offset);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3f(-radius,-radius,z-offset);
			glVertex3f(-radius, radius,z-offset);
			glVertex3f(-radius+offset, radius,z-offset);
			glVertex3f(-radius+offset,-radius,z-offset);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3f( radius,-radius,z-offset);
			glVertex3f( radius, radius,z-offset);
			glVertex3f( radius-offset, radius,z-offset);
			glVertex3f( radius-offset,-radius,z-offset);
		glEnd();
		glBegin(GL_QUAD_STRIP);
			glVertex3f(-radius,-radius,z);
			glVertex3f(-radius,-radius,z-offset);
			glVertex3f( radius,-radius,z);
			glVertex3f( radius,-radius,z-offset);
			glVertex3f( radius, radius,z);
			glVertex3f( radius, radius,z-offset);
			glVertex3f(-radius, radius,z);
			glVertex3f(-radius, radius,z-offset);
			glVertex3f(-radius,-radius,z);
			glVertex3f(-radius,-radius,z-offset);
		glEnd();
		radius-=offset;
		z -= offset;
	}

	//Calculate projection square
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	projection->PaintOpenGL();
	glGetFloatv(GL_PROJECTION_MATRIX,m);
	glPopMatrix();
	//End calculate projection square

	//Reverse projection square
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	InvertMatrix(m,n);
	glMultMatrixf(n);

	glColor3f(0.5,0.7,0.5);
	glBegin(GL_QUADS);
		glVertex3f(-1.0,-1.0,-1.0);
		glVertex3f( 1.0,-1.0,-1.0);
		glVertex3f( 1.0, 1.0,-1.0);
		glVertex3f(-1.0, 1.0,-1.0);
		glVertex3f(-1.0,-1.0, 1.0);
		glVertex3f( 1.0,-1.0, 1.0);
		glVertex3f( 1.0, 1.0, 1.0);
		glVertex3f(-1.0, 1.0, 1.0);
	glEnd();

	glColor3f(0.0,0.0,0.0);
	glBegin(GL_LINES);
		glVertex3f(-1.0,-1.0,-1.0);
		glVertex3f(-1.0,-1.0, 1.0);
		glVertex3f( 1.0,-1.0,-1.0);
		glVertex3f( 1.0,-1.0, 1.0);
		glVertex3f( 1.0, 1.0,-1.0);
		glVertex3f( 1.0, 1.0, 1.0);
		glVertex3f(-1.0, 1.0,-1.0);
		glVertex3f(-1.0, 1.0, 1.0);
	glEnd();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	//End reverse projeciton square

	glPopMatrix();
	//End reverse camera position
}