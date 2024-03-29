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

// ComputerGraphicDoc.cpp : implementation of the CComputerGraphicDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ComputerGraphic.h"
#endif

#include "ComputerGraphicDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CComputerGraphicDoc

IMPLEMENT_DYNCREATE(CComputerGraphicDoc, CDocument)

BEGIN_MESSAGE_MAP(CComputerGraphicDoc, CDocument)
END_MESSAGE_MAP()


// CComputerGraphicDoc construction/destruction

CComputerGraphicDoc::CComputerGraphicDoc()
{
	// TODO: add one-time construction code here

}

CComputerGraphicDoc::~CComputerGraphicDoc()
{
}

BOOL CComputerGraphicDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	CString title;
	title.Format(_T("Untiled%d"),++count);
	this->SetTitle(title);

	return TRUE;
}

//BOOL CComputerGraphicDoc::OnOpenDocument(CString pathName)
//{
//	if (!CDocument::OnOpenDocument(pathName))
//		return FALSE;
//
//	// TODO: add reinitialization code here
//	// (SDI documents will reuse this document)
//	this->SetTitle(pathName);
//
//	::AfxMessageBox(CString("dkm"));
//	char buf[1024];
//	wcstombs(buf,pathName,1024);
//
//	if(!data.Load(buf))
//		::AfxMessageBox(CString("dkm"));
//
//	return TRUE;
//}


CComputerGraphicDoc * CComputerGraphicDoc::GetDoc()
{
    CMDIChildWnd * pChild =
        ((CMDIFrameWnd*)(AfxGetApp()->m_pMainWnd))->MDIGetActive(false);

    if ( !pChild )
        return NULL;

    CDocument * pDoc = pChild->GetActiveDocument();

    if ( !pDoc )
        return NULL;

    if ( ! pDoc->IsKindOf( RUNTIME_CLASS(CComputerGraphicDoc) ) )
        return NULL;

    return (CComputerGraphicDoc *) pDoc;
}

// CComputerGraphicDoc serialization

void CComputerGraphicDoc::Serialize(CArchive& ar)
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
void CComputerGraphicDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CComputerGraphicDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CComputerGraphicDoc::SetSearchContent(const CString& value)
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

// CComputerGraphicDoc diagnostics

#ifdef _DEBUG
void CComputerGraphicDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CComputerGraphicDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG



BOOL CComputerGraphicDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDocument::OnSaveDocument(lpszPathName);
}


void CComputerGraphicDoc::OnCloseDocument()
{
	// TODO: Add your specialized code here and/or call the base class
	::AfxMessageBox(CString(this->GetPathName()));
	CDocument::OnCloseDocument();
}


BOOL CComputerGraphicDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  Add your specialized creation code here
	char buf[1024];
	wcstombs(buf,lpszPathName,1024);

	if(!data.Load(buf))
		return FALSE;

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

	pMainFrame->m_wndFileView.FillView(data.object);
	return TRUE;
}
