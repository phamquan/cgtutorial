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
	return (CCamera*)m_listChild.GetAt(1);
}

CProjection* CEnvironment::GetProjection()
{
	return (CProjection*)m_listChild.GetAt(0);
}

void CEnvironment::DrawCamera()
{
	if(m_listChild.GetSize() < 2)
		return;

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
	float m[16];
	float n[16];
	float x1,y1,z1,x2,y2,z2;
	int type;
	CCamera* camera = GetCamera();
	CProjection* projection = GetProjection();
	projection->GetData(x1,y1,z1,x2,y2,z2,type),

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	
	if(type == ORTHO)
		glOrtho(x1,y1,z1,x2,y2,z2);
	else
		glFrustum(x1,y1,z1,x2,y2,z2);

	glGetFloatv(GL_PROJECTION_MATRIX,m);
	InvertMatrix(m,n);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
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

	glPopMatrix();
}