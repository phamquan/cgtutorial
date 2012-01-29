// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://msdn.microsoft.com/officeui.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// CGTutorialDoc.cpp : implementation of the CCGTutorialDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "CGTutorial.h"
#endif

#include "MainFrm.h"
#include "CGTutorialDoc.h"
#include "Transformation.h"
#include "Geometric.h"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCGTutorialDoc
#include "Line.h"
#include "Point4D.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Circle.h"
#include "Ellipse.h"
#include "Cube.h"
#include "Tetrahedron.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Ring.h"

IMPLEMENT_DYNCREATE(CCGTutorialDoc, CDocument)

BEGIN_MESSAGE_MAP(CCGTutorialDoc, CDocument)
END_MESSAGE_MAP()


// CCGTutorialDoc construction/destruction

CCGTutorialDoc::CCGTutorialDoc()
{
	// TODO: add one-time construction code here
	object = new COpenGLNode(NODE_OBJECT);
	environment = new CEnvironment();
	DeleteContents();
	tabsize = 5;
}

CCGTutorialDoc::~CCGTutorialDoc()
{
	delete object;
	delete environment;
}

BOOL CCGTutorialDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	pMainFrame->m_wndFileView.FillView(object,environment);
	pMainFrame->ClearUndo();
	pMainFrame->ClearRedo();
	pMainFrame->Refresh();

	return TRUE;
}

// CCGTutorialDoc serialization

void CCGTutorialDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		ar.WriteString("<?xml version=\"1.0\" ?>\r\n");
		ar.WriteString("<watermelon program='Computer Graphic Tutorial'>\r\n");
		ar.WriteString("\r\n");
		environment->Serialize(ar);
		ar.WriteString("\r\n");
		object->Serialize(ar);
		ar.WriteString("\r\n");
		ar.WriteString("</watermelon>\r\n");
	}
	else
	{
		// TODO: add loading code here
		
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CCGTutorialDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CCGTutorialDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CCGTutorialDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CCGTutorialDoc diagnostics

#ifdef _DEBUG
void CCGTutorialDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCGTutorialDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CCGTutorialDoc commands


BOOL CCGTutorialDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  Add your specialized creation code here
	//char buf[1024];
	char *buf = const_cast<char*>(lpszPathName);
	//wcstombs(buf,CString(lpszPathName).GetBuffer(),1024);

	if(!data.Load(buf)) {
		CString error = data.error;
		AfxMessageBox("Wrong format file : " + error);
		return FALSE;
	}

	object->ClearChild();
	environment->ClearChild();

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	pMainFrame->m_wndFileView.FillView(data.object,data.environment,object,environment);
	pMainFrame->ClearUndo();
	pMainFrame->ClearRedo();
	pMainFrame->Refresh();

	return TRUE;
}


BOOL CCGTutorialDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: Add your specialized code here and/or call the base class
	return CDocument::OnSaveDocument(lpszPathName);
}


void CCGTutorialDoc::OnCloseDocument()
{
	// TODO: Add your specialized code here and/or call the base class

	CDocument::OnCloseDocument();
}


void CCGTutorialDoc::DeleteContents()
{
	// TODO: Add your specialized code here and/or call the base class
	object->ClearChild();
	environment->ClearChild();
	environment->AddChild(new CCamera(0,0,0,0,0,-1,0,1,0));
	environment->AddChild(new CProjection(-1,1,-1,1,1,-1,ORTHO));
	environment->AddChild(new CViewPort(0,0,0,0,VIEWPORT_DEFAULT));
	CDocument::DeleteContents();
}

void CCGTutorialDoc::AddCode(char* data, int tab, int line) {
	AddCode(CString(data),tab,line);
}

void CCGTutorialDoc::AddCode(CString data, int tab, int line)
{
	ASSERT(tab >= 0);
	ASSERT(line >= 0);

	for(int i=0; i<tab*tabsize; i++)
	{
		openGLCode += " ";
	}

	openGLCode += data;

	for(int i=0; i<line; i++)
	{
		openGLCode += "\r\n";
	}
}

CString CCGTutorialDoc::GenCode()
{
	openGLCode = "";

	//header
	AddCode("#pragma comment(lib, \"opengl32.lib\")",0,1);
	AddCode("#pragma comment( linker, \"/subsystem:\\\"windows\\\" /entry:\\\"mainCRTStartup\\\"\" )",0,2);

	AddCode("#include <GL/glut.h>",0,1);
	AddCode("#include <math.h>",0,1);
	AddCode("#include <stdio.h>",0,2);

	AddCode("#define PI 3.14159265358979323846",0,1);
	AddCode("#define RAD_2_DEG (180.0/PI)",0,1);
	AddCode("#define DEG_2_RAD (PI/180.0)",0,2);

	//init openGL
	InitGLCode();
	
	//onsize
	SizeGLCode();

	//coordinate
	CoordinateGLCode();

	//draw object
	if(CPoint4D::count>0)
		DrawPoint();
	if(CLine::count>0)
		DrawLine();
	if(CRectangle::count>0)
		DrawRectangle();
	if(CTriangle::count>0)
		DrawTriangle();
	if(CCircle::count>0)
		DrawCircle();
	if(CEllipse::count>0)
		DrawEllipse();
	if(CCube::count>0)
		DrawCube();
	if(CTetrahedron::count>0)
		DrawTetrahedron();
	if(CSphere::count>0)
		DrawSphere();
	if(CCylinder::count>0)
		DrawCylinder();
	if(CRing::count>0)
		DrawRing();

	//onpaint
	PaintGLCode();
	
	//main
	AddCode("int main(int argc, char** argv) {",0,2);
	AddCode("// init GLUT and create Window",1,1);
	AddCode("glutInit(&argc, argv);",1,1);
	AddCode("glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE | GLUT_RGB);",1,1);
	AddCode("glutCreateWindow(\"Computer Graphic Tutorial\");",1,1);
	AddCode("initOpenGL();",1,2);
	AddCode("// register callbacks",1,1);
	AddCode("glutDisplayFunc(onPaint);",1,1);
	AddCode("glutReshapeFunc(onSize);",1,2);
	AddCode("// enter GLUT event processing cycle",1,1);
	AddCode("glutMainLoop();",1,2);
	AddCode("return 1;",1,1);
	AddCode("}",0,1);

	return openGLCode;
}

void CCGTutorialDoc::InitGLCode()
{
	AddCode("void initOpenGL() {",0,1);
		AddCode("glMatrixMode(GL_PROJECTION);",1,1);
		AddCode("glLoadIdentity();",1,1);
		AddCode(environment->GetProjection()->GLCode,1,2);

		AddCode("glMatrixMode(GL_MODELVIEW);",1,1);
		AddCode("glLoadIdentity();",1,1);
		AddCode(environment->GetCamera()->GLCode,1,2);

		AddCode("glClearColor(0.769f, 0.812f, 0.824f, 0.0f);",1,1);
		AddCode("glEnable(GL_DEPTH_TEST);",1,1);
		AddCode("glPointSize(4.0);",1,1);
	AddCode("}",0,2);
}

void CCGTutorialDoc::SizeGLCode()
{
	AddCode("void onSize(int width, int height) {",0,1);
		AddCode(environment->GetViewPort()->GLCode,1,1);
	AddCode("}",0,2);
}

void CCGTutorialDoc::PaintGLCode()
{
	AddCode("void onPaint() {",0,1);
		AddCode("glMatrixMode(GL_MODELVIEW);",1,1);
		AddCode("glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);",1,1);
		AddCode("drawCoordinate();",1,1);
		ObjectGLCode(object);
		AddCode("glFlush();",1,1);
	AddCode("}",0,2);
}

void CCGTutorialDoc::CoordinateGLCode()
{
	AddCode("void drawCoordinate() {",0,1);
	AddCode("glBegin(GL_LINES);",1,1);
		AddCode("glColor3f(1.0f,0.0f,0.0f);",2,1);
		AddCode("glVertex3f(0.0f,0.0f,0.0f);",2,1);
		AddCode("glVertex3f(1000.0f,0.0f,0.0f);",2,1);
		AddCode("glColor3f(0.0f,1.0f,0.0f);",2,1);
		AddCode("glVertex3f(0.0f,0.0f,0.0f);",2,1);
		AddCode("glVertex3f(0.0f,1000.0f,0.0f);",2,1);
		AddCode("glColor3f(0.0f,0.0f,1.0f);",2,1);
		AddCode("glVertex3f(0.0f,0.0f,0.0f);",2,1);
		AddCode("glVertex3f(0.0f,0.0f,1000.0f);",2,1);
	AddCode("glEnd();",1,1);
	AddCode("}",0,2);
}

void CCGTutorialDoc::ObjectGLCode(COpenGLNode *node)
{
	int id = node->ID;
	//float x1,y1,z1,x2,y2,z2;
	if(id == NODE_TRANSLATE || id == NODE_ROTATE || id == NODE_SCALE)
	{
		if(node->parent->m_listChild->GetSize() > 1)
		{
			AddCode("glPushMatrix();",1,1);
		}
	}

	if(id != NODE_OBJECT) {
		if(id != NODE_TRANSLATE && id != NODE_ROTATE && id != NODE_SCALE) {
			char buf[128];
			sprintf_s(buf,"glColor3ub(%d,%d,%d);",GetRValue(node->color),GetGValue(node->color),GetBValue(node->color));
			AddCode(buf,1,1);
		}
		AddCode(node->GLCode,1,1);
	}

	CPtrArray *child = node->m_listChild;
	for(int i=0; i<child->GetSize(); i++)
	{
		ObjectGLCode((COpenGLNode*)child->GetAt(i));
	}

	if(id == NODE_TRANSLATE || id == NODE_ROTATE || id == NODE_SCALE)
	{
		if(node->parent->m_listChild->GetSize() > 1)
		{
			AddCode("glPopMatrix();",1,2);
		}
	}
}

void CCGTutorialDoc::DrawPoint()
{
	char buf[128];
	sprintf_s(buf,"void drawPoint(float x, float y, float z) { //%d",CPoint4D::count);
	//AddCode("void drawPoint(float x, float y, float z) {",0,1);
	AddCode(buf,0,1);
		AddCode("glBegin(GL_POINTS);",1,1);
			AddCode("glVertex3f(x,y,z);",2,1);	
		AddCode("glEnd();",1,1);
	AddCode("}",0,2);
}

void CCGTutorialDoc::DrawLine()
{
	char buf[128];
	sprintf_s(buf,"void drawLine(float x1, float y1, float z1, float x2, float y2, float z2) { //%d",CLine::count);
	//AddCode("void drawLine(float x1, float y1, float z1, float x2, float y2, float z2) {",0,1);
	AddCode(buf,0,1);
		AddCode("glBegin(GL_LINES);",1,1);
			AddCode("glVertex3f(x1,y1,z1);",2,1);	
			AddCode("glVertex3f(x2,y2,z2);",2,1);
		AddCode("glEnd();",1,1);
	AddCode("}",0,2);
}

void CCGTutorialDoc::DrawRectangle()
{
	char buf[128];
	sprintf_s(buf,"void drawRectangle(float  top, float left, float bottom, float right) { //%d",CRectangle::count);
	//AddCode("void drawRectangle(float  top, float left, float bottom, float right) {",0,1);
	AddCode(buf,0,1);
		AddCode("glBegin(GL_QUADS);",1,1);
			AddCode("glVertex3f(left,top,0);",2,1);	
			AddCode("glVertex3f(right,top,0);",2,1);
			AddCode("glVertex3f(right,bottom,0);",2,1);
			AddCode("glVertex3f(left,bottom,0);",2,1);
		AddCode("glEnd();",1,1);
	AddCode("}",0,2);
}

void CCGTutorialDoc::DrawTriangle()
{
	char buf[128];
	sprintf_s(buf,"void drawTriangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3) { //%d",CTriangle::count);
	//AddCode("void drawTriangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3) {",0,1);
	AddCode(buf,0,1);
		AddCode("glBegin(GL_TRIANGLES);",1,1);
			AddCode("glVertex3f(x1,y1,z1);",2,1);	
			AddCode("glVertex3f(x2,y2,z2);",2,1);
			AddCode("glVertex3f(x3,y3,z3);",2,1);
		AddCode("glEnd();",1,1);
	AddCode("}",0,2);
}

void CCGTutorialDoc::DrawCircle()
{
	char buf[128];
	sprintf_s(buf,"void drawCircle(float x, float y, float z, float R) { //%d",CCircle::count);
	//AddCode("void drawCircle(float x, float y, float z, float R) {",0,1);
	AddCode(buf,0,1);
		AddCode("glPushMatrix();",1,1);
		AddCode("glTranslatef(x,y,z);",1,1);
		AddCode("glScalef(R,R,1);",1,1);
		AddCode("glBegin(GL_POLYGON);",1,1);
		AddCode("for(int i=0; i<=360; i+=10) {",1,1);	
			AddCode("glVertex3f(cos(i*DEG_2_RAD),sin(i*DEG_2_RAD),0.0f);",2,1);		
		AddCode("}",1,1);	
		AddCode("glEnd();",1,1);
		AddCode("glPopMatrix();",1,1);
	AddCode("}",0,2);
}

void CCGTutorialDoc::DrawEllipse()
{
	char buf[128];
	sprintf_s(buf,"void drawEllipse(float x, float y, float z, float a, float b) { //%d",CEllipse::count);
	//AddCode("void drawEllipse(float x, float y, float z, float a, float b) {",0,1);
	AddCode(buf,0,1);
		AddCode("glPushMatrix();",1,1);
		AddCode("glTranslatef(x,y,z);",1,1);
		AddCode("glScalef(a,b,1);",1,1);
		AddCode("glBegin(GL_POLYGON);",1,1);
		AddCode("for(int i=0; i<=360; i+=10) {",1,1);	
			AddCode("glVertex3f(cos(i*DEG_2_RAD),sin(i*DEG_2_RAD),0.0f);",2,1);		
		AddCode("}",1,1);	
		AddCode("glEnd();",1,1);
		AddCode("glPopMatrix();",1,1);
	AddCode("}",0,2);
}

void CCGTutorialDoc::DrawCube()
{
	char buf[128];
	sprintf_s(buf,"void drawCube(float left, float bottom, float mnear, float right, float top, float mfar) { //%d",CCube::count);
	//AddCode("void drawCube(float left, float bottom, float mnear, float right, float top, float mfar) {",0,1);
	AddCode(buf,0,1);
		AddCode("glBegin(GL_QUADS);",1,1);
			AddCode("//font",2,1);
			AddCode("glVertex3f(left,top,mnear);",2,1);
			AddCode("glVertex3f(right,top,mnear);",2,1);
			AddCode("glVertex3f(right,bottom,mnear);",2,1);
			AddCode("glVertex3f(left,bottom,mnear);",2,1);
			AddCode("//back",2,1);
			AddCode("glVertex3f(left,top,mfar);",2,1);
			AddCode("glVertex3f(right,top,mfar);",2,1);
			AddCode("glVertex3f(right,bottom,mfar);",2,1);
			AddCode("glVertex3f(left,bottom,mfar);",2,1);
			AddCode("//left",2,1);
			AddCode("glVertex3f(left,top,mnear);",2,1);
			AddCode("glVertex3f(left,bottom,mnear);",2,1);
			AddCode("glVertex3f(left,bottom,mfar);",2,1);
			AddCode("glVertex3f(left,top,mfar);",2,1);
			AddCode("//right",2,1);
			AddCode("glVertex3f(right,top,mnear);",2,1);
			AddCode("glVertex3f(right,bottom,mnear);",2,1);
			AddCode("glVertex3f(right,bottom,mfar);",2,1);
			AddCode("glVertex3f(right,top,mfar);",2,1);
			AddCode("//up",2,1);
			AddCode("glVertex3f(left,top,mnear);",2,1);
			AddCode("glVertex3f(right,top,mnear);",2,1);
			AddCode("glVertex3f(right,top,mfar);",2,1);
			AddCode("glVertex3f(left,top,mfar);",2,1);
			AddCode("//down",2,1);
			AddCode("glVertex3f(left,bottom,mnear);",2,1);
			AddCode("glVertex3f(right,bottom,mnear);",2,1);
			AddCode("glVertex3f(right,bottom,mfar);",2,1);
			AddCode("glVertex3f(left,bottom,mfar);",2,1);
		AddCode("glEnd();",1,1);
	AddCode("}",0,2);
}

void CCGTutorialDoc::DrawTetrahedron()
{
	char buf[256];
	sprintf_s(buf,"void drawTetrahedron(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4) { //%d",CTetrahedron::count);
	//AddCode("void drawTetrahedron(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4) {",0,1);
	AddCode(buf,0,1);
		AddCode("glBegin(GL_TRIANGLES);",1,1);
			AddCode("glVertex3f(x1,y1,z1);",2,1);
			AddCode("glVertex3f(x2,y2,z2);",2,1);
			AddCode("glVertex3f(x3,y3,z3);",2,2);

			AddCode("glVertex3f(x1,y1,z1);",2,1);
			AddCode("glVertex3f(x2,y2,z2);",2,1);
			AddCode("glVertex3f(x4,y4,z4);",2,2);

			AddCode("glVertex3f(x1,y1,z1);",2,1);
			AddCode("glVertex3f(x3,y3,z3);",2,1);
			AddCode("glVertex3f(x4,y4,z4);",2,2);

			AddCode("glVertex3f(x2,y2,z2);",2,1);
			AddCode("glVertex3f(x3,y3,z3);",2,1);
			AddCode("glVertex3f(x4,y4,z4);",2,1);
		AddCode("glEnd();",1,1);
	AddCode("}",0,2);
}

void CCGTutorialDoc::DrawSphere()
{
	char buf[128];
	sprintf_s(buf,"void drawSphere(float x, float y, float z, float R) { //%d",CSphere::count);
	//AddCode("void drawSphere(float x, float y, float z, float R) {",0,1);
	AddCode(buf,0,1);
		AddCode("glPushMatrix();",1,1);
		AddCode("glTranslatef(x,y,z);",1,1);
		AddCode("glScalef(R,R,R);",1,1);
		AddCode("glBegin(GL_QUAD_STRIP);",1,1);
		AddCode("for(int i=-90; i<=90; i+=10) {",1,1);
			AddCode("for(int j=0; j<=360; j+=10) {",2,1);
				AddCode("double x1 = cos((i-10)*DEG_2_RAD)*cos(j*DEG_2_RAD);",3,1);
				AddCode("double y1 = sin((i-10)*DEG_2_RAD);",3,1);
				AddCode("double z1 = cos((i-10)*DEG_2_RAD)*sin(j*DEG_2_RAD);",3,1);
				AddCode("glVertex3f(x1,y1,z1);",3,1);
				AddCode("double x2 = cos(i*DEG_2_RAD)*cos(j*DEG_2_RAD);",3,1);
				AddCode("double y2 = sin(i*DEG_2_RAD);",3,1);
				AddCode("double z2 = cos(i*DEG_2_RAD)*sin(j*DEG_2_RAD);",3,1);
				AddCode("glVertex3f(x2,y2,z2);",3,1);
			AddCode("}",2,1);
		AddCode("}",1,1);	
		AddCode("glEnd();",1,1);
		AddCode("glPopMatrix();",1,1);
	AddCode("}",0,2);
}

void CCGTutorialDoc::DrawCylinder()
{
	char buf[128];
	sprintf_s(buf,"void drawCylinder(float x, float y, float z, float R, float height) { //%d",CCylinder::count);
	//AddCode("void drawCylinder(float x, float y, float z, float R, float r) {",0,1);
	AddCode(buf,0,1);
		AddCode("int j;",1,1);
		AddCode("glPushMatrix();",1,1);
		AddCode("glTranslatef(x,y,z);",1,1);
		AddCode("glBegin(GL_QUAD_STRIP);",1,1);
		AddCode("for(j=0; j<=360; j+=10) {",1,1);
			AddCode("glVertex3f(R*cos(j*DEG_2_RAD), height/2,R*sin(j*DEG_2_RAD));",2,1);
			AddCode("glVertex3f(R*cos(j*DEG_2_RAD),-height/2,R*sin(j*DEG_2_RAD));",2,1);
		AddCode("}",1,1);
		AddCode("glEnd();",1,2);

		AddCode("glBegin(GL_POLYGON);",1,1);
		AddCode("for(j=0; j<=360; j+=10) {",1,1);
			AddCode("glVertex3f(R*cos(j*DEG_2_RAD), height/2,R*sin(j*DEG_2_RAD));",2,1);
		AddCode("}",1,1);
		AddCode("glEnd();",1,2);
		
		AddCode("glBegin(GL_POLYGON);",1,1);
		AddCode("for(j=0; j<=360; j+=10) {",1,1);
			AddCode("glVertex3f(R*cos(j*DEG_2_RAD),-height/2,R*sin(j*DEG_2_RAD));",2,1);
		AddCode("}",1,1);
		AddCode("glEnd();",1,1);
		AddCode("glPopMatrix();",1,1);
	AddCode("}",0,2);
}

void CCGTutorialDoc::DrawRing()
{
	char buf[128];
	sprintf_s(buf,"void drawRing(float x, float y, float z, float R, float r) { //%d",CRing::count);
	//AddCode("void drawRing(float x, float y, float z, float R, float r) {",0,1);
	AddCode(buf,0,1);
		AddCode("glPushMatrix();",1,1);
		AddCode("glTranslatef(x,y,z);",1,1);
		AddCode("for(int i = 10; i<=360; i+=10) {",1,1);
			AddCode("glBegin(GL_QUAD_STRIP);",2,1);
			AddCode("for(int j=0; j<=360; j+=10) {",2,1);
				AddCode("double x1 = (R + r*cos(i*DEG_2_RAD))*cos(j*DEG_2_RAD);",3,1);
				AddCode("double y1 = (R + r*cos(i*DEG_2_RAD))*sin(j*DEG_2_RAD);",3,1);
				AddCode("double z1 = r*sin(i*DEG_2_RAD);",3,1);
				AddCode("glVertex3f(x1,y1,z1);",3,1);
				AddCode("double x2 = (R + r*cos((i-10)*DEG_2_RAD))*cos(j*DEG_2_RAD);",3,1);
				AddCode("double y2 = (R + r*cos((i-10)*DEG_2_RAD))*sin(j*DEG_2_RAD);",3,1);
				AddCode("double z2 = r*sin(i*DEG_2_RAD);",3,1);
				AddCode("glVertex3f(x2,y2,z2);",3,1);
			AddCode("}",2,1);
			AddCode("glEnd();",2,1);
		AddCode("}",1,1);
		AddCode("glPopMatrix();",1,1);
	AddCode("}",0,2);
}