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
#include "Rotate.h"
#include "Scale.h"
#include "Translate.h"
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

#include "DlgTranslate.h"
#include "DlgRotate.h"
#include "DlgScale.h"
#include "DlgProjection.h"
#include "DlgCamera.h"
#include "DlgViewPort.h"
#include "DlgPoint.h"
#include "DlgLine.h"
#include "DlgRectangle.h"
#include "DlgTriangle.h"
#include "DlgCircle.h"
#include "DlgEllipse.h"
#include "DlgCube.h"
#include "DlgTetrahedron.h"
#include "DlgSphere.h"
#include "DlgCylinder.h"
#include "DlgRing.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileView
CFileView::CFileView()
{
	contextMenu = NULL;
}

CFileView::~CFileView()
{
	if(contextMenu != NULL)
		delete contextMenu;
}

BEGIN_MESSAGE_MAP(CFileView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_TRANSFORMATION_TRANSLATE, &CFileView::OnTransformationTranslate)
	ON_COMMAND(ID_TRANSFORMATION_ROTATE, &CFileView::OnTransformationRotate)
	ON_COMMAND(ID_TRANSFORMATION_SCALE, &CFileView::OnTransformationScale)
	ON_COMMAND(ID_FILEVIEW_EDIT, &CFileView::OnFileviewEdit)
	ON_COMMAND(ID_FILEVIEW_DELETE, &CFileView::OnFileviewDelete)
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

const char* CFileView::GetValue(char* name,TiXmlNode* node)
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
		if(CString(GetValue("type",node)) == "ortho")
			result = new CProjection(atof(GetValue("left",node)),atof(GetValue("right",node)),atof(GetValue("bottom",node)),
											atof(GetValue("top",node)),atof(GetValue("near",node)),atof(GetValue("far",node)),ORTHO);
		else if(CString(GetValue("type",node)) == "frustum")
			result = new CProjection(atof(GetValue("left",node)),atof(GetValue("right",node)),atof(GetValue("bottom",node)),
											atof(GetValue("top",node)),atof(GetValue("near",node)),atof(GetValue("far",node)),FRUSTUM);
	}
	else if(CString(node->Value()) == "viewport")
	{
		if(CString(GetValue("type",node)) == "default")
			result = new CViewPort(0,0,0,0,VIEWPORT_DEFAULT);
		else if(CString(GetValue("type",node)) == "custom")
			result = new CViewPort(atof(GetValue("x",node)),atof(GetValue("y",node)),atof(GetValue("width",node)),
											atof(GetValue("height",node)),VIEWPORT_CUSTOM);
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
	else if(CString(node->Value()) == "point")
	{
		result = new CPoint4D(atof(GetValue("x",node)),atof(GetValue("y",node)),atof(GetValue("z",node)));
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
	else if(CString(node->Value()) == "triangle")
	{
		result = new CTriangle(atof(GetValue("x1",node)),atof(GetValue("y1",node)),atof(GetValue("z1",node)),atof(GetValue("x2",node)),atof(GetValue("y2",node)),atof(GetValue("z2",node)),atof(GetValue("x3",node)),atof(GetValue("y3",node)),atof(GetValue("z3",node)));
	}
	else if(CString(node->Value()) == "circle")
	{
		result = new CCircle(atof(GetValue("x",node)),atof(GetValue("y",node)),atof(GetValue("z",node)),atof(GetValue("R",node)));
	}
	else if(CString(node->Value()) == "ellipse")
	{
		result = new CEllipse(atof(GetValue("x",node)),atof(GetValue("y",node)),atof(GetValue("z",node)),atof(GetValue("a",node)),atof(GetValue("b",node)));
	}
	else if(CString(node->Value()) == "cube")
	{
		result = new CCube(atof(GetValue("left",node)),atof(GetValue("bottom",node)),atof(GetValue("near",node)),atof(GetValue("right",node)),atof(GetValue("top",node)),atof(GetValue("far",node)));
	}
	else if(CString(node->Value()) == "tetrahedron")
	{
		result = new CTetrahedron(atof(GetValue("x1",node)),atof(GetValue("y1",node)),atof(GetValue("z1",node)),atof(GetValue("x2",node)),atof(GetValue("y2",node)),atof(GetValue("z2",node)),
								atof(GetValue("x3",node)),atof(GetValue("y3",node)),atof(GetValue("z3",node)),atof(GetValue("x4",node)),atof(GetValue("y4",node)),atof(GetValue("z4",node)));
	}
	else if(CString(node->Value()) == "sphere")
	{
		result = new CSphere(atof(GetValue("x",node)),atof(GetValue("y",node)),atof(GetValue("z",node)),atof(GetValue("R",node)));
	}
	else if(CString(node->Value()) == "cylinder")
	{
		result = new CCylinder(atof(GetValue("x",node)),atof(GetValue("y",node)),atof(GetValue("z",node)),atof(GetValue("R",node)),atof(GetValue("height",node)));
	}
	else if(CString(node->Value()) == "ring")
	{
		result = new CRing(atof(GetValue("x",node)),atof(GetValue("y",node)),atof(GetValue("z",node)),atof(GetValue("R",node)),atof(GetValue("r",node)));
	}
	return result;
}


void CFileView::FillView(TiXmlNode* tobject, TiXmlNode* tenvironment, COpenGLNode* oobject, CEnvironment* oenvironment)
{
	m_wndFileView.DeleteAllItems();
	m_wndFileView.myMap.RemoveAll();

	object = m_wndFileView.InsertItem(oobject->toString, 0, 0);
	m_wndFileView.SetItemState(object,TVIS_BOLD,TVIS_BOLD);
	m_wndFileView.myMap.SetAt(object,oobject);

	TiXmlNode* pChild = NULL;
	while (pChild = tobject->IterateChildren(pChild)) {
		FillFile(pChild,object,oobject);
	}

	environment = m_wndFileView.InsertItem(oenvironment->toString, 0, 0);
	m_wndFileView.SetItemState(environment,TVIS_BOLD,TVIS_BOLD);
	m_wndFileView.myMap.SetAt(environment,oenvironment);

	pChild = NULL;
	while (pChild = tenvironment->IterateChildren(pChild)) {
		FillFile(pChild,environment,oenvironment);
	}

	m_wndFileView.Expand(object,TVE_EXPAND);
	m_wndFileView.Expand(environment,TVE_EXPAND);

	AdjustLayout();
}

void CFileView::FillView(COpenGLNode *oobject, COpenGLNode* oenvironment)
{
	m_wndFileView.DeleteAllItems();
	m_wndFileView.myMap.RemoveAll();

	object = m_wndFileView.InsertItem(oobject->toString, 0, 0);
	m_wndFileView.SetItemState(object,TVIS_BOLD,TVIS_BOLD);
	m_wndFileView.myMap.SetAt(object,oobject);

	environment = m_wndFileView.InsertItem(oenvironment->toString, 0, 0);
	m_wndFileView.SetItemState(environment,TVIS_BOLD,TVIS_BOLD);
	m_wndFileView.myMap.SetAt(environment,oenvironment);

	for(int i=0; i<oenvironment->m_listChild->GetSize(); i++)
	{
		COpenGLNode* childnode = (COpenGLNode*)oenvironment->m_listChild->GetAt(i);
		HTREEITEM child = m_wndFileView.InsertItem(childnode->toString, 0, 0, environment);
		m_wndFileView.myMap.SetAt(child,childnode);
	}

	m_wndFileView.Expand(environment,TVE_EXPAND);

	AdjustLayout();
}

void CFileView::FillFile(TiXmlNode *root, HTREEITEM hparrent, COpenGLNode *oparrent) {
	TiXmlNode* pChild = NULL;
	COpenGLNode *openGL = XmltoOpenGL(root);
	if(openGL==NULL) {
		AfxMessageBox(CString("invalid node : ") + root->Value());
		return;
	}
		
	oparrent->AddChild(openGL);

	HTREEITEM node = m_wndFileView.InsertItem(openGL->toString, 0, 0, hparrent);
	m_wndFileView.myMap.SetAt(node,openGL);

	while (pChild = root->IterateChildren(pChild)) {
		FillFile(pChild,node,openGL);
	}

	m_wndFileView.Expand(node,TVE_EXPAND);
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
			if(contextMenu != NULL)
				delete contextMenu;
			contextMenu = new CMenu();
			contextMenu->LoadMenu(IDR_FILEVIEW);

			int id = node->ID;
			if(id != NODE_ENVIRONMENT) {
				switch(id) {
				case NODE_CAMERA :
				case NODE_PROJECTION :
				case NODE_VIEWPORT :
					contextMenu->GetSubMenu(0)->DeleteMenu(2,MF_BYPOSITION);
					contextMenu->GetSubMenu(0)->DeleteMenu(0,MF_BYPOSITION);
					break;
				case NODE_OBJECT :
					contextMenu->GetSubMenu(0)->DeleteMenu(2,MF_BYPOSITION);
					contextMenu->GetSubMenu(0)->DeleteMenu(1,MF_BYPOSITION);
					break;
				case NODE_POINT :
				case NODE_LINE :
				case NODE_RECTANGLE :
				case NODE_TRIANGLE :
				case NODE_CIRCLE :
				case NODE_ELLIPSE :
				case NODE_CUBE :
				case NODE_TETRAHEDRON :
				case NODE_SPHERE :
				case NODE_CYLINDER :
				case NODE_RING :
					//contextMenu->GetSubMenu(0)->DeleteMenu(0,MF_BYPOSITION);
					break;
				}
				contextMenu->GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
			}
			//theApp.GetContextMenuManager()->ShowPopupMenu(IDR_FILEVIEW, point.x, point.y, this, TRUE);		
		}
	}

	pWndTree->SetFocus();
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

BOOL CFileView::ToParent()
{
	switch(node->ID) {
	case NODE_OBJECT:
		return false;
	}
	return true;
}

void CFileView::AddNode(COpenGLNode *newNode, BOOL isGeometric, BOOL toParent)
{
	ASSERT(!(isGeometric && toParent));

	HTREEITEM cur = hTreeItem;
	if(isGeometric) {
		hTreeItem = object;
		m_wndFileView.myMap.Lookup(object,node);
	}

	if(toParent) {
		hTreeItem = m_wndFileView.GetParentItem(hTreeItem);
		node = node->parent;
	}

	node->AddChild(newNode);
	HTREEITEM hnode = m_wndFileView.InsertItem(newNode->toString, 0, 0, hTreeItem);
	m_wndFileView.EnsureVisible(hnode);
	m_wndFileView.myMap.SetAt(hnode,newNode);

	if(toParent)
		m_wndFileView.SuccessfulDrag(hnode,cur);

	((CMainFrame*)AfxGetMainWnd())->Refresh();
}

void CFileView::OnTransformationTranslate()
{
	// TODO: Add your command handler code here
	CDlgTranslate dlg;
	if(dlg.DoModal() == IDOK)
		AddNode(new CTranslate(dlg.m_X,dlg.m_Y,dlg.m_Z),FALSE,ToParent());
}

void CFileView::OnTransformationRotate()
{
	// TODO: Add your command handler code here
	CDlgRotate dlg;
	if(dlg.DoModal() == IDOK)
		AddNode(new CRotate(dlg.m_X,dlg.m_Y,dlg.m_Z,dlg.m_A),FALSE,ToParent());
}

void CFileView::OnTransformationScale()
{
	// TODO: Add your command handler code here
	CDlgScale dlg;
	if(dlg.DoModal() == IDOK)
		AddNode(new CScale(dlg.m_X,dlg.m_Y,dlg.m_Z),FALSE,ToParent());
}

void CFileView::OnFileviewEdit()
{
	// TODO: Add your command handler code here
	int id = node->ID;
	float x1,y1,z1,x2,y2,z2,x3,y3,z3,x4,y4,z4,w;
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
			((CCamera*)node)->SetData(dlg.m_EX,dlg.m_EY,dlg.m_EZ,dlg.m_RX,dlg.m_RY,dlg.m_RZ,dlg.m_UX,dlg.m_UY,dlg.m_UZ);
		}
	} else if(id == NODE_VIEWPORT) {
		((CViewPort*)node)->GetData(x1,y1,x2,y2,id);
		CDlgViewPort dlg(x1,y1,x2,y2,id);
		if(dlg.DoModal() == IDOK) {
			edit = true;
			((CViewPort*)node)->SetData(dlg.m_Left,dlg.m_Bottom,dlg.m_Width,dlg.m_Height,dlg.type);
		}
	} else if(id == NODE_TRANSLATE) {
		((CTranslate*)node)->GetData(x1,y1,z1);
		CDlgTranslate dlg(x1,y1,z1);
		if(dlg.DoModal() == IDOK) {
			edit = true;
			((CTranslate*)node)->SetData(dlg.m_X,dlg.m_Y,dlg.m_Z);
		}
	} else if(id == NODE_SCALE) {
		((CScale*)node)->GetData(x1,y1,z1);
		CDlgScale dlg(x1,y1,z1);
		if(dlg.DoModal() == IDOK) {
			edit = true;
			((CScale*)node)->SetData(dlg.m_X,dlg.m_Y,dlg.m_Z);
		}
	} else if(id == NODE_ROTATE) {
		((CRotate*)node)->GetData(x1,y1,z1,w);
		CDlgRotate dlg(x1,y1,z1,w);
		if(dlg.DoModal() == IDOK) {
			edit = true;
			((CRotate*)node)->SetData(dlg.m_X,dlg.m_Y,dlg.m_Z,dlg.m_A);
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
			((CLine*)node)->SetData(dlg.m_BX,dlg.m_BY,dlg.m_BZ,dlg.m_EX,dlg.m_EY,dlg.m_EZ);
		}
	} else if(id == NODE_RECTANGLE) {
		((CRectangle*)node)->GetData(x1,y1,x2,y2);
		CDlgRectangle dlg(x1,y1,x2,y2);
		if(dlg.DoModal() == IDOK) {
			edit = true;
			((CRectangle*)node)->SetData(dlg.m_Top,dlg.m_Left,dlg.m_Bottom,dlg.m_Right);
		}
	} else if(id == NODE_TRIANGLE) {
		((CTriangle*)node)->GetData(x1,y1,z1,x2,y2,z2,x3,y3,z3);
		CDlgTriangle dlg(x1,y1,z1,x2,y2,z2,x3,y3,z3);
		if(dlg.DoModal() == IDOK) {
			edit = true;
			((CTriangle*)node)->SetData(dlg.m_X1,dlg.m_Y1,dlg.m_Z1,dlg.m_X2,dlg.m_Y2,dlg.m_Z2,dlg.m_X3,dlg.m_Y3,dlg.m_Z3);
		}
	} else if(id == NODE_CIRCLE) {
		((CCircle*)node)->GetData(x1,y1,z1,w);
		CDlgCircle dlg(x1,y1,z1,w);
		if(dlg.DoModal() == IDOK) {
			edit = true;
			((CCircle*)node)->SetData(dlg.m_X,dlg.m_Y,dlg.m_Z,dlg.m_R);
		}
	} else if(id == NODE_ELLIPSE) {
		((CEllipse*)node)->GetData(x1,y1,z1,x2,y2);
		CDlgEllipse dlg(x1,y1,z1,x2,y2);
		if(dlg.DoModal() == IDOK) {
			edit = true;
			((CEllipse*)node)->SetData(dlg.m_X,dlg.m_Y,dlg.m_Z,dlg.m_A,dlg.m_B);
		}
	} else if(id == NODE_CUBE) {
		((CCube*)node)->GetData(x1,y1,z1,x2,y2,z2);
		CDlgCube dlg(x1,y1,z1,x2,y2,z2);
		if(dlg.DoModal() == IDOK) {
			edit = true;
			((CCube*)node)->SetData(dlg.m_Left,dlg.m_Bottom,dlg.m_Near,dlg.m_Right,dlg.m_Top,dlg.m_Far);
		}
	} else if(id == NODE_TETRAHEDRON) {
		((CTetrahedron*)node)->GetData(x1,y1,z1,x2,y2,z2,x3,y3,z3,x4,y4,z4);
		CDlgTetrahedron dlg(x1,y1,z1,x2,y2,z2,x3,y3,z3,x4,y4,z4);
		if(dlg.DoModal() == IDOK) {
			edit = true;
			((CTetrahedron*)node)->SetData(dlg.m_X1,dlg.m_Y1,dlg.m_Z1,dlg.m_X2,dlg.m_Y2,dlg.m_Z2,dlg.m_X3,dlg.m_Y3,dlg.m_Z3,dlg.m_X4,dlg.m_Y4,dlg.m_Z4);
		}
	} else if(id == NODE_SPHERE) {
		((CSphere*)node)->GetData(x1,y1,z1,w);
		CDlgSphere dlg(x1,y1,z1,w);
		if(dlg.DoModal() == IDOK) {
			edit = true;
			((CSphere*)node)->SetData(dlg.m_X,dlg.m_Y,dlg.m_Z,dlg.m_R);
		}
	} else if(id == NODE_CYLINDER) {
		((CCylinder*)node)->GetData(x1,y1,z1,x2,y2);
		CDlgCylinder dlg(x1,y1,z1,x2,y2);
		if(dlg.DoModal() == IDOK) {
			edit = true;
			((CCylinder*)node)->SetData(dlg.m_X,dlg.m_Y,dlg.m_Z,dlg.m_R,dlg.m_Height);
		}
	} else if(id == NODE_RING) {
		((CRing*)node)->GetData(x1,y1,z1,x2,y2);
		CDlgRing dlg(x1,y1,z1,x2,y2);
		if(dlg.DoModal() == IDOK) {
			edit = true;
			((CRing*)node)->SetData(dlg.m_X,dlg.m_Y,dlg.m_Z,dlg.m_R,dlg.m_R1);
		}
	}

	if(edit) {
		m_wndFileView.SetItemText(hTreeItem,node->toString);
		((CMainFrame*)AfxGetMainWnd())->Refresh();
	}
}

void CFileView::OnFileviewDelete()
{
	// TODO: Add your command handler code here
	node->parent->DeleteChild(node);
	m_wndFileView.DeleteItem(hTreeItem);
	((CMainFrame*)AfxGetMainWnd())->Refresh();
}

COpenGLNode* CFileView::GetObject()
{
	hTreeItem = m_wndFileView.GetSelectedItem();

	if(hTreeItem != NULL) {
		m_wndFileView.myMap.Lookup(hTreeItem,node);
		switch(node->ID) {
		case NODE_TRANSLATE :
		case NODE_ROTATE :
		case NODE_SCALE :
		case NODE_POINT :
		case NODE_LINE :
		case NODE_RECTANGLE :
		case NODE_TRIANGLE :
		case NODE_CIRCLE :
		case NODE_ELLIPSE :
		case NODE_CUBE :
		case NODE_TETRAHEDRON :
		case NODE_SPHERE :
		case NODE_CYLINDER :
		case NODE_RING :
			return node;
		}
	}
	return NULL;
}

//COpenGLNode* CFileView::GetGeometric()
//{
//	hTreeItem = m_wndFileView.GetSelectedItem();
//
//	if(hTreeItem != NULL) {
//		m_wndFileView.myMap.Lookup(hTreeItem,node);
//		switch(node->ID) {
//		case NODE_POINT :
//		case NODE_LINE :
//		case NODE_RECTANGLE :
//		case NODE_TRIANGLE :
//		case NODE_CIRCLE :
//		case NODE_ELLIPSE :
//		case NODE_CUBE :
//		case NODE_TETRAHEDRON :
//		case NODE_SPHERE :
//		case NODE_CYLINDER :
//		case NODE_RING :
//			return node;
//		}
//	}
//	return NULL;
//}