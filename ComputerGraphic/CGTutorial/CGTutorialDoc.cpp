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

#include "CGTutorialDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCGTutorialDoc

IMPLEMENT_DYNCREATE(CCGTutorialDoc, CDocument)

BEGIN_MESSAGE_MAP(CCGTutorialDoc, CDocument)
END_MESSAGE_MAP()


// CCGTutorialDoc construction/destruction

CCGTutorialDoc::CCGTutorialDoc()
{
	// TODO: add one-time construction code here
	root = new COpenGLNode(false,true);
}

CCGTutorialDoc::~CCGTutorialDoc()
{
	delete root;
}

BOOL CCGTutorialDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	root->ClearChild();
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

	pMainFrame->m_wndFileView.FillView(root);

	return TRUE;
}

// CCGTutorialDoc serialization

void CCGTutorialDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
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
	size_t i;
	char buf[1024];
	wcstombs_s(&i,buf,lpszPathName,1024);

	if(!data.Load(buf))
		return FALSE;

	root->ClearChild();
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

	pMainFrame->m_wndFileView.FillView(data.object,root);

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
