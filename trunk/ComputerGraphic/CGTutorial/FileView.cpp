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

#include "stdafx.h"
#include "mainfrm.h"
#include "FileView.h"
#include "Resource.h"
#include "CGTutorial.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileView

CFileView::CFileView()
{
}

CFileView::~CFileView()
{
}

BEGIN_MESSAGE_MAP(CFileView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_ADDOBJECT_POINT, &CFileView::OnAddobjectPoint)
	ON_COMMAND(ID_ADDOBJECT_LINE, &CFileView::OnAddobjectLine)
	ON_COMMAND(ID_ADDOBJECT_RECTANGLE, &CFileView::OnAddobjectRectangle)
	ON_COMMAND(ID_OBJECT_DELETE, &CFileView::OnObjectDelete)
	ON_COMMAND(ID_OBJECT_ADDCOLOR, &CFileView::OnObjectAddcolor)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceBar message handlers

int CFileView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// Create view:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;

	if (!m_wndFileView.Create(dwViewStyle, rectDummy, this, 4))
	{
		TRACE0("Failed to create file view\n");
		return -1;      // fail to create
	}

	// Load view images:
	m_FileViewImages.Create(IDB_FILE_VIEW, 16, 0, RGB(255, 0, 255));
	m_wndFileView.SetImageList(&m_FileViewImages, TVSIL_NORMAL);

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_EXPLORER);
	m_wndToolBar.LoadToolBar(IDR_EXPLORER, 0, 0, TRUE /* Is locked */);

	OnChangeVisualStyle();

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetOwner(this);

	// All commands will be routed via this control , not via the parent frame:
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	// Fill in some static tree view data (dummy code, nothing magic here)
	AdjustLayout();

	return 0;
}

void CFileView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

const char* GetValue(char* name,TiXmlNode* node)
{
	TiXmlAttribute* pAttrib=node->ToElement()->FirstAttribute();
	while(pAttrib) {
		if(CString(pAttrib->Name()) == CString(name))
			return pAttrib->Value();
		pAttrib = pAttrib->Next();
	}
	return NULL;
}

COpenGLNode *CFileView::XmltoOpenGL(TiXmlNode *node)
{
	if(node == NULL)
		return NULL;

	COpenGLNode *result = NULL;
	if(CString(node->Value()) == "camera")
	{
		result = new CCamera(CPoint3D(atof(GetValue("xpos",node)),atof(GetValue("ypos",node)),atof(GetValue("zpos",node))),
									CPoint3D(atof(GetValue("xlook",node)),atof(GetValue("ylook",node)),atof(GetValue("zlook",node))),
									CPoint3D(atof(GetValue("xup",node)),atof(GetValue("yup",node)),atof(GetValue("zup",node))));
	}
	else if(CString(node->Value()) == "projection")
	{
		if(CString(GetValue("type",node)) == CString("ortho"))
			result = new CProjection(atof(GetValue("left",node)),atof(GetValue("right",node)),atof(GetValue("bottom",node)),
											atof(GetValue("top",node)),atof(GetValue("near",node)),atof(GetValue("far",node)),ORTHO);
		else
			result = new CProjection(atof(GetValue("left",node)),atof(GetValue("right",node)),atof(GetValue("bottom",node)),
											atof(GetValue("top",node)),atof(GetValue("near",node)),atof(GetValue("far",node)),FRUSTUM);
	}
	else if(CString(node->Value()) == "translate")
	{
		result = new CTranslate(CPoint3D(atof(GetValue("x",node)),atof(GetValue("y",node)),atof(GetValue("z",node))));
	}
	else if(CString(node->Value()) == "rotate")
	{
		result = new CRotate(CPoint3D(atof(GetValue("x",node)),atof(GetValue("y",node)),atof(GetValue("z",node)),atof(GetValue("angle",node))));
	}
	else if(CString(node->Value()) == "scale")
	{
		result = new CScale(CPoint3D(atof(GetValue("x",node)),atof(GetValue("y",node)),atof(GetValue("z",node))));
	}
	else if(CString(node->Value()) == "line")
	{
		result = new CLine(CPoint3D(atof(GetValue("x1",node)),atof(GetValue("y1",node)),atof(GetValue("z1",node))),
						   CPoint3D(atof(GetValue("x2",node)),atof(GetValue("y2",node)),atof(GetValue("z2",node))));
	}
	else if(CString(node->Value()) == "rectangle")
	{
		result = new CRectangle(atof(GetValue("top",node)),atof(GetValue("left",node)),atof(GetValue("bottom",node)),atof(GetValue("right",node)));
	}
	else if(CString(node->Value()) == "point")
	{
		result = new CPoint4D(CPoint3D(atof(GetValue("x",node)),atof(GetValue("y",node)),atof(GetValue("z",node))));
	}

	return result;
}

void CFileView::FillView(TiXmlNode* tobject, TiXmlNode* tenvironment, COpenGLNode* oobject, CEnvironment* oenvironment)
{
	m_wndFileView.DeleteAllItems();
	m_wndFileView.myMap.RemoveAll();

	HTREEITEM node = m_wndFileView.InsertItem(CString("object"), 0, 0);
	m_wndFileView.SetItemState(node,TVIS_BOLD,TVIS_BOLD);
	
	m_wndFileView.myMap.SetAt(node,oobject);

	TiXmlNode* pChild = NULL;
	while (pChild = tobject->IterateChildren(pChild)) {
		FillFile(pChild,node,oobject);
	}

	node = m_wndFileView.InsertItem(CString("environment"), 0, 0);
	m_wndFileView.SetItemState(node,TVIS_BOLD,TVIS_BOLD);

	m_wndFileView.myMap.SetAt(node,oenvironment);

	pChild = NULL;
	while (pChild = tenvironment->IterateChildren(pChild)) {
		FillFile(pChild,node,oenvironment);
	}

	AdjustLayout();
}

void CFileView::FillView(COpenGLNode *object, COpenGLNode* environment)
{
	m_wndFileView.DeleteAllItems();
	m_wndFileView.myMap.RemoveAll();

	HTREEITEM node = m_wndFileView.InsertItem(CString("object"), 0, 0);
	m_wndFileView.SetItemState(node,TVIS_BOLD,TVIS_BOLD);
	
	m_wndFileView.myMap.SetAt(node,object);

	node = m_wndFileView.InsertItem(CString("environment"), 0, 0);
	m_wndFileView.SetItemState(node,TVIS_BOLD,TVIS_BOLD);
	
	m_wndFileView.myMap.SetAt(node,environment);

	for(int i=0; i<environment->GetChilds()->GetSize(); i++)
	{
		COpenGLNode* childnode = (COpenGLNode*)environment->GetChilds()->GetAt(i);
		HTREEITEM child = m_wndFileView.InsertItem(childnode->ToString(), 0, 0, node);
		m_wndFileView.myMap.SetAt(child,childnode);
	}

	AdjustLayout();
}

void CFileView::FillFile(TiXmlNode *root, HTREEITEM hparrent, COpenGLNode *oparrent) {
	TiXmlNode* pChild = NULL;
	COpenGLNode *openGL = XmltoOpenGL(root);
	oparrent->AddChild(openGL);

	CString data = CString(root->Value()) + " (";
	TiXmlAttribute* pAttrib=root->ToElement()->FirstAttribute();
	while(pAttrib) {
		data+= pAttrib->Name();
		data+="=";
		data+=pAttrib->Value();
		pAttrib = pAttrib->Next();
		if(pAttrib!=NULL)
			data+=", ";
	}
	data+=")";

	HTREEITEM node = m_wndFileView.InsertItem(data, 0, 0, hparrent);
	m_wndFileView.myMap.SetAt(node,openGL);

	while (pChild = root->IterateChildren(pChild)) {
		FillFile(pChild,node,openGL);
	}
}

void CFileView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndFileView.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

void CFileView::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rectTree;
	m_wndFileView.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CFileView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_wndFileView.SetFocus();
}

void CFileView::OnChangeVisualStyle()
{
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_EXPLORER_24 : IDR_EXPLORER, 0, 0, TRUE /* Locked */);

	m_FileViewImages.DeleteImageList();

	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_FILE_VIEW_24 : IDB_FILE_VIEW;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TRACE(_T("Can't load bitmap: %x\n"), uiBmpId);
		ASSERT(FALSE);
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	m_FileViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	m_FileViewImages.Add(&bmp, RGB(255, 0, 255));

	m_wndFileView.SetImageList(&m_FileViewImages, TVSIL_NORMAL);
}

void CFileView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndFileView;
	ASSERT_VALID(pWndTree);

	if (pWnd != pWndTree)
	{
		CDockablePane::OnContextMenu(pWnd, point);
		return;
	}

	if (point != CPoint(-1, -1))
	{
		// Select clicked item:
		CPoint ptTree = point;
		pWndTree->ScreenToClient(&ptTree);

		UINT flags = 0;
		hTreeItem = pWndTree->HitTest(ptTree, &flags);
		if (hTreeItem != NULL)
		{
			m_wndFileView.myMap.Lookup(hTreeItem,node);
			pWndTree->SelectItem(hTreeItem);
			theApp.GetContextMenuManager()->ShowPopupMenu(IDR_OBJECT, point.x, point.y, this, TRUE);
		}
	}

	pWndTree->SetFocus();
}

BOOLEAN CFileView::ValidateAdd()
{
	switch(node->GetID()) {
	case NODE_OBJECT:
	case NODE_TRANSLATE:
	case NODE_ROTATE:
	case NODE_SCALE:
	case NODE_COLOR:
		return true;
	}
	return false;
}

BOOLEAN CFileView::ValidateDelete()
{
	switch(node->GetID()) {
	case NODE_OBJECT:
	case NODE_ENVIRONMENT:
	case NODE_CAMERA:
	case NODE_PROJECTION:
		return false;
	}
	return true;
}

void CFileView::AddNode(COpenGLNode *newNode)
{
	node->AddChild(newNode);
	HTREEITEM node = m_wndFileView.InsertItem(newNode->ToString(), 0, 0, hTreeItem);
	m_wndFileView.myMap.SetAt(node,newNode);

	((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0)->Invalidate();
	((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,1)->Invalidate();
}

void CFileView::OnObjectDelete()
{
	// TODO: Add your command handler code here
	if(ValidateDelete()) {
		node->GetParent()->RemoveChild(node);
		m_wndFileView.DeleteItem(hTreeItem);
		((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0)->Invalidate();
		((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,1)->Invalidate();
	}
}

void CFileView::OnAddobjectPoint()
{
	// TODO: Add your command handler code here
	if(ValidateAdd()) {
		CDlgPoint dlg;
		if(dlg.DoModal() == IDOK)
			AddNode(new CPoint4D(CPoint3D(dlg.m_X,dlg.m_Y,dlg.m_Z)));
	}
}

void CFileView::OnAddobjectLine()
{
	// TODO: Add your command handler code here
	if(ValidateAdd()) {
		CDlgLine dlg;
		if(dlg.DoModal() == IDOK)
			AddNode(new CLine(CPoint3D(dlg.m_X1,dlg.m_Y1,dlg.m_Z1),CPoint3D(dlg.m_X2,dlg.m_Y2,dlg.m_Z2)));
	}
}

void CFileView::OnAddobjectRectangle()
{
	// TODO: Add your command handler code here
	if(ValidateAdd()) {
		CDlgRectangle dlg;
		if(dlg.DoModal() == IDOK)
			AddNode(new CRectangle(dlg.m_Top,dlg.m_Left,dlg.m_Bottom,dlg.m_Right));
	}
}



void CFileView::OnObjectAddcolor()
{
	// TODO: Add your command handler code here
	if(ValidateAdd()) {
		CColorDialog dlg;
		if(dlg.DoModal() == IDOK) {
			COLORREF color = dlg.GetColor();
			AddNode(new CColor(GetRValue(color)/255.0,GetGValue(color)/255.0,GetBValue(color)/255.0));
		}
	}
}
