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

// CGTutorialDoc.h : interface of the CCGTutorialDoc class
//


#pragma once

#include "CGTXParser.h"
#include "Environment.h"

class CCGTutorialDoc : public CDocument
{
protected: // create from serialization only
	CCGTutorialDoc();
	DECLARE_DYNCREATE(CCGTutorialDoc)
	CCGTXParser data;
	COpenGLNode* object;
	int tabsize;

	CString GenCode();
	void AddCode(char* data, int tab, int line);
	void AddCode(CString data, int tab, int line);
	void InitGLCode();
	void SizeGLCode();
	void PaintGLCode();
	void CoordinateGLCode();
	void ObjectGLCode(COpenGLNode *node);
	void DrawPoint();
	void DrawLine();
	void DrawRectangle();
	void DrawTriangle();
	void DrawCircle();
	void DrawEllipse();
	void DrawCube();
	void DrawTetrahedron();
	void DrawSphere();
	void DrawCylinder();
	void DrawRing();
// Attributes
public:
	CEnvironment* environment;
	CString openGLCode;
	CString title;
// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CCGTutorialDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	virtual void DeleteContents();
};
