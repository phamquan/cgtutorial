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
	ON_COMMAND(ID_ADDTRANSFORMATION_TRANSLATE, &CFileView::OnAddtransformationTranslate)
	ON_COMMAND(ID_ADDTRANSFORMATION_SCALE, &CFileView::OnAddtransformationScale)
	ON_COMMAND(ID_ADDTRANSFORMATION_ROTATE, &CFileView::OnAddtransformationRotate)
	ON_COMMAND(ID_OBJECT_EDIT, &CFileView::OnObjectEdit)
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
		result = new CCamera(atof(GetValue("xpos",node)),atof(GetValue("ypos",node)),atof(GetValue("zpos",node)),
							 atof(GetValue("xlook",node)),atof(GetValue("ylook",node)),atof(GetValue("zlook",node)),
							 atof(GetValue("xup",node)),atof(GetValue("yup",node)),atof(GetValue("zup",node)));
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
		result = new CTranslate(atof(GetValue("x",node)),atof(GetValue("y",node)),atof(GetValue("z",node)));
	}
	else if(CString(node->Value()) == "rotate")
	{
		result = new CRotate(atof(GetValue("x",node)),atof(GetValue("y",node)),atof(GetValue("z",node)),atof(GetValue("angle",node)));
	}
	else if(CString(node->Value()) == "scale")
	{
		result = new CScale(atof(GetValue("x",node)),atof(GetValue("y",node)),atof(GetValue("z",node)));
	}
	else if(CString(node->Value()) == "line")
	{
		result = new CLine(atof(GetValue("x1",node)),atof(GetValue("y1",node)),atof(GetValue("z1",node)),
						   atof(GetValue("x2",node)),atof(GetValue("y2",node)),atof(GetValue("z2",node)));
	}
	else if(CString(node->Value()) == "rectangle")
	{
		result = new CRectangle(atof(GetValue("top",node)),atof(GetValue("left",node)),atof(GetValue("bottom",node)),atof(GetValue("right",node)));
	}
	else if(CString(node->Value()) == "point")
	{
		result = new CPoint4D(atof(GetValue("x",node)),atof(GetValue("y",node)),atof(GetValue("z",node)));
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

	environment = m_wndFileView.InsertItem(CString("environment"), 0, 0);
	m_wndFileView.SetItemState(environment,TVIS_BOLD,TVIS_BOLD);

	m_wndFileView.myMap.SetAt(environment,oenvironment);

	pChild = NULL;
	while (pChild = tenvironment->IterateChildren(pChild)) {
		FillFile(pChild,environment,oenvironment);
	}

	AdjustLayout();
}

void CFileView::FillView(COpenGLNode *object, COpenGLNode* oenvironment)
{
	m_wndFileView.DeleteAllItems();
	m_wndFileView.myMap.RemoveAll();

	HTREEITEM node = m_wndFileView.InsertItem(CString("object"), 0, 0);
	m_wndFileView.SetItemState(node,TVIS_BOLD,TVIS_BOLD);
	
	m_wndFileView.myMap.SetAt(node,object);

	environment = m_wndFileView.InsertItem(CString("environment"), 0, 0);
	m_wndFileView.SetItemState(environment,TVIS_BOLD,TVIS_BOLD);
	
	m_wndFileView.myMap.SetAt(environment,oenvironment);

	for(int i=0; i<oenvironment->GetChilds()->GetSize(); i++)
	{
		COpenGLNode* childnode = (COpenGLNode*)oenvironment->GetChilds()->GetAt(i);
		HTREEITEM child = m_wndFileView.InsertItem(childnode->ToString(), 0, 0, environment);
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

void CFileView::ShowModelMatrix()
{
	hTreeItem = m_wndFileView.GetSelectedItem();

	if(hTreeItem != NULL) {
		m_wndFileView.myMap.Lookup(hTreeItem,node);
		CDlgModelMatrix dlg(node);
		switch(node->GetID()) {
		case NODE_POINT:
		case NODE_LINE:
		case NODE_RECTANGLE:
			dlg.DoModal();
			break;
		default:
			AfxMessageBox(CString("Please choose geometric object"));
		}
	}
}

void CFileView::ShowViewMatrix()
{
	COpenGLNode *envi;
	m_wndFileView.myMap.Lookup(environment,envi);
	hTreeItem = m_wndFileView.GetSelectedItem();

	if(hTreeItem == NULL) {
		CDlgViewMatrix dlg(((CEnvironment*)envi)->GetCamera(),NULL);
		dlg.DoModal();
	} else {
		m_wndFileView.myMap.Lookup(hTreeItem,node);
		if(node->GetID() == NODE_POINT || node->GetID() == NODE_LINE || node->GetID() == NODE_RECTANGLE) {
			CDlgViewMatrix dlg(((CEnvironment*)envi)->GetCamera(),node);
			dlg.DoModal();
		} else {
			CDlgViewMatrix dlg(((CEnvironment*)envi)->GetCamera(),NULL);
			dlg.DoModal();
		}
	}
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

void CFileView::OnObjectEdit()
{
	// TODO: Add your command handler code here
	int id = node->GetID();
	float x1,y1,z1,x2,y2,z2,x3,y3,z3,w;
	BOOLEAN edit = false;
	if(id == NODE_PROJECTION) {
		((CProjection*)node)->GetData(x1,y1,z1,x2,y2,z2,id);
		CDlgProjection dlg(x1,y1,z1,x2,y2,z2,id);
		if(dlg.DoModal() == IDOK) {
			edit = true;
			((CProjection*)node)->SetData(dlg.m_Left,dlg.m_Right,dlg.m_Bottom,dlg.m_Top,dlg.m_Near,dlg.m_Far,dlg.type);
		}
	} else if(id == NODE_CAMERA) {
		((CCamera*)node)->GetData(x1,y1,z1,x2,y2,z2,x3,y3,z3);
		CDlgCamera dlg(x1,y1,z1,x2,y2,z2,x3,y3,z3);
		if(dlg.DoModal() == IDOK) {
			edit = true;
			((CCamera*)node)->SetData(dlg.m_X1,dlg.m_Y1,dlg.m_Z1,dlg.m_X2,dlg.m_Y2,dlg.m_Z2,dlg.m_X3,dlg.m_Y3,dlg.m_Z3);
		}
	} else if(id == NODE_TRANSLATE) {
		((CTranslate*)node)->GetData(x1,y1,z1,w);
		CDlgPoint dlg(x1,y1,z1);
		if(dlg.DoModal() == IDOK) {
			edit = true;
			((CTranslate*)node)->SetData(dlg.m_X,dlg.m_Y,dlg.m_Z);
		}
	} else if(id == NODE_SCALE) {
		((CScale*)node)->GetData(x1,y1,z1,w);
		CDlgPoint dlg(x1,y1,z1);
		if(dlg.DoModal() == IDOK) {
			edit = true;
			((CScale*)node)->SetData(dlg.m_X,dlg.m_Y,dlg.m_Z);
		}
	} else if(id == NODE_ROTATE) {
		((CRotate*)node)->GetData(x1,y1,z1,w);
		CDlgRotate dlg(x1,y1,z1,w);
		if(dlg.DoModal() == IDOK) {
			edit = true;
			((CRotate*)node)->SetData(dlg.m_X,dlg.m_Y,dlg.m_Z,dlg.m_Angle);
		}
	} else if(id == NODE_POINT) {
		((CPoint4D*)node)->GetData(x1,y1,z1);
		CDlgPoint dlg(x1,y1,z1);
		if(dlg.DoModal() == IDOK) {
			edit = true;
			((CPoint4D*)node)->SetData(dlg.m_X,dlg.m_Y,dlg.m_Z);
		}
	} else if(id == NODE_LINE) {
		((CLine*)node)->GetData(x1,y1,z1,x2,y2,z2);
		CDlgLine dlg(x1,y1,z1,x2,y2,z2);
		if(dlg.DoModal() == IDOK) {
			edit = true;
			((CLine*)node)->SetData(dlg.m_X1,dlg.m_Y1,dlg.m_Z1,dlg.m_X2,dlg.m_Y2,dlg.m_Z2);
		}
	} else if(id == NODE_RECTANGLE) {
		((CRectangle*)node)->GetData(x1,y1,x2,y2);
		CDlgRectangle dlg(x1,y1,x2,y2);
		if(dlg.DoModal() == IDOK) {
			edit = true;
			((CRectangle*)node)->SetData(dlg.m_Top,dlg.m_Left,dlg.m_Bottom,dlg.m_Right);
		}
	}

	if(edit) {
		m_wndFileView.SetItemText(hTreeItem,node->ToString());
		((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,0)->Invalidate();
		((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0,1)->Invalidate();
	}
}

void CFileView::OnAddtransformationTranslate()
{
	// TODO: Add your command handler code here
	if(ValidateAdd()) {
		CDlgPoint dlg;
		if(dlg.DoModal() == IDOK)
			AddNode(new CTranslate(dlg.m_X,dlg.m_Y,dlg.m_Z));
	}
}

void CFileView::OnAddtransformationScale()
{
	// TODO: Add your command handler code here
	if(ValidateAdd()) {
		CDlgPoint dlg;
		if(dlg.DoModal() == IDOK)
			AddNode(new CScale(dlg.m_X,dlg.m_Y,dlg.m_Z));
	}
}

void CFileView::OnAddtransformationRotate()
{
	// TODO: Add your command handler code here
	if(ValidateAdd()) {
		CDlgRotate dlg;
		if(dlg.DoModal() == IDOK)
			AddNode(new CRotate(dlg.m_X,dlg.m_Y,dlg.m_Z,dlg.m_Angle));
	}
}

void CFileView::OnAddobjectPoint()
{
	// TODO: Add your command handler code here
	if(ValidateAdd()) {
		CDlgPoint dlg;
		if(dlg.DoModal() == IDOK)
			AddNode(new CPoint4D(dlg.m_X,dlg.m_Y,dlg.m_Z));
	}
}

void CFileView::OnAddobjectLine()
{
	// TODO: Add your command handler code here
	if(ValidateAdd()) {
		CDlgLine dlg;
		if(dlg.DoModal() == IDOK)
			AddNode(new CLine(dlg.m_X1,dlg.m_Y1,dlg.m_Z1,dlg.m_X2,dlg.m_Y2,dlg.m_Z2));
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
