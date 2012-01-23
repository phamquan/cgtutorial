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

// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "CGTutorial.h"

#include "MainFrm.h"
#include "CGTutorialDoc.h"

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
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_COMMAND(ID_FILE_PRINT, &CMainFrame::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CMainFrame::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMainFrame::OnFilePrintPreview)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, &CMainFrame::OnUpdateFilePrintPreview)
	ON_COMMAND(ID_GENCODE, &CMainFrame::OnGencode)
	ON_COMMAND(ID_MATRIX, &CMainFrame::OnMatrix)
	ON_COMMAND(ID_PIPELINE, &CMainFrame::OnPipeline)
	ON_COMMAND(ID_CAMERA, &CMainFrame::OnCamera)
	ON_COMMAND(ID_POINT, &CMainFrame::OnPoint)
	ON_COMMAND(ID_LINE, &CMainFrame::OnLine)
	ON_COMMAND(ID_TRIANGLE, &CMainFrame::OnTriangle)
	ON_COMMAND(ID_RECTANGLE, &CMainFrame::OnRectangle)
	ON_COMMAND(ID_CIRCLE, &CMainFrame::OnCircle)
	ON_COMMAND(ID_ELLIPSE, &CMainFrame::OnEllipse)
	ON_COMMAND(ID_CUBE, &CMainFrame::OnCube)
	ON_COMMAND(ID_TETRAHEDRON, &CMainFrame::OnTetrahedron)
	ON_COMMAND(ID_SPHERE, &CMainFrame::OnSphere)
	ON_COMMAND(ID_CYLINDER, &CMainFrame::OnCylinder)
	ON_COMMAND(ID_RING, &CMainFrame::OnRing)
END_MESSAGE_MAP()

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_WINDOWS_7);
	dlgGenCode = NULL;
	dlgMatrixFormula = NULL;
	dlgPipeLine = NULL;
	cameraFrame = NULL;
}

CMainFrame::~CMainFrame()
{
	if(dlgGenCode != NULL)
		delete dlgGenCode;

	if(dlgMatrixFormula != NULL)
		delete dlgMatrixFormula;

	if(dlgPipeLine != NULL)
		delete dlgPipeLine;

	if(cameraFrame != NULL)
		delete cameraFrame;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;
	// set the visual manager and style based on persisted value
	OnApplicationLook(theApp.m_nAppLook);

	m_wndRibbonBar.Create(this);
	m_wndRibbonBar.LoadFromResource(IDR_RIBBON);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	CString strTitlePane1;
	CString strTitlePane2;
	bNameValid = strTitlePane1.LoadString(IDS_STATUS_PANE1);
	ASSERT(bNameValid);
	bNameValid = strTitlePane2.LoadString(IDS_STATUS_PANE2);
	ASSERT(bNameValid);
	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE1, strTitlePane1, TRUE), strTitlePane1);
	m_wndStatusBar.AddExtendedElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE2, strTitlePane2, TRUE), strTitlePane2);

	// enable Visual Studio 2005 style docking window behavior
	CDockingManager::SetDockingMode(DT_SMART);
	// enable Visual Studio 2005 style docking window auto-hide behavior
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// Load menu item image (not placed on any standard toolbars):
	CMFCToolBar::AddToolBarForImageCollection(IDR_MENU_IMAGES, theApp.m_bHiColorIcons ? IDB_MENU_IMAGES_24 : 0);

	// create docking windows
	if (!CreateDockingWindows())
	{
		TRACE0("Failed to create docking windows\n");
		return -1;
	}

	m_wndFileView.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndFileView);
	CDockablePane* pTabbedBar = NULL;

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		 | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE | WS_SYSMENU;

	return TRUE;
}

BOOL CMainFrame::CreateDockingWindows()
{
	BOOL bNameValid;

	// Create file view
	CString strFileView;
	bNameValid = strFileView.LoadString(IDS_FILE_VIEW);
	ASSERT(bNameValid);
	if (!m_wndFileView.Create(strFileView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_FILEVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT| CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create File View window\n");
		return FALSE; // failed to create
	}

	SetDockingWindowIcons(theApp.m_bHiColorIcons);
	return TRUE;
}

void CMainFrame::SetDockingWindowIcons(BOOL bHiColorIcons)
{
	HICON hFileViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_FILE_VIEW_HC : IDI_FILE_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndFileView.SetIcon(hFileViewIcon, FALSE);
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(TRUE);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}

void CMainFrame::OnFilePrint()
{
	if (IsPrintPreview())
	{
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_PRINT);
	}
}

void CMainFrame::OnFilePrintPreview()
{
	if (IsPrintPreview())
	{
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_CLOSE);  // force Print Preview mode closed
	}
}

void CMainFrame::OnUpdateFilePrintPreview(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(IsPrintPreview());
}

void CMainFrame::Refresh()
{
	if(GetActiveView() != NULL)
		GetActiveView()->Invalidate();

	if(dlgGenCode != NULL)
		dlgGenCode->Refresh(((CCGTutorialDoc*)GetActiveDocument())->GenCode());

	if(dlgMatrixFormula != NULL)
		dlgMatrixFormula->Refresh(m_wndFileView.GetObject());

	if(dlgPipeLine != NULL)
		dlgPipeLine->Refresh(m_wndFileView.GetObject());

	if(cameraFrame != NULL)
		cameraFrame->ReSize();
}

void CMainFrame::OnGencode()
{
	// TODO: Add your command handler code here
	if(dlgGenCode == NULL)
	{
		dlgGenCode = new CDlgGenCode();
		dlgGenCode->Create(CDlgGenCode::IDD,this);
	}
	dlgGenCode->Refresh(((CCGTutorialDoc*)GetActiveDocument())->GenCode());
	dlgGenCode->ShowWindow(SW_SHOW);
}

void CMainFrame::OnMatrix()
{
	// TODO: Add your command handler code here
	if(dlgMatrixFormula == NULL)
	{
		dlgMatrixFormula = new CDlgMatrixFormula(((CCGTutorialDoc*)GetActiveDocument())->environment);
		dlgMatrixFormula->Create(CDlgMatrixFormula::IDD,this);

	}
	dlgMatrixFormula->Refresh(m_wndFileView.GetObject());
	dlgMatrixFormula->ShowWindow(SW_SHOW);
}

void CMainFrame::OnPipeline()
{
	// TODO: Add your command handler code here
	if(dlgPipeLine == NULL)
	{
		dlgPipeLine = new CDlgPipeLine(((CCGTutorialDoc*)GetActiveDocument())->environment);
		dlgPipeLine->Create(CDlgPipeLine::IDD,this);
	}
	dlgPipeLine->Refresh(m_wndFileView.GetObject());
	dlgPipeLine->ShowWindow(SW_SHOW);
}

void CMainFrame::OnCamera()
{
	// TODO: Add your command handler code here
	if(cameraFrame == NULL){
		CCGTutorialDoc* doc = (CCGTutorialDoc*)GetActiveDocument();
		cameraFrame = new CCameraFrame(doc->environment,doc->object);
		cameraFrame->Create(CCameraFrame::IDD,this);
	}
	cameraFrame->ShowWindow(SW_SHOW);
}

void CMainFrame::ShowModelMatrix()
{
	OnMatrix();
	dlgMatrixFormula->SetFocus();
	dlgMatrixFormula->ChangeTab(0);
}

void CMainFrame::ShowViewMatrix()
{
	OnMatrix();
	dlgMatrixFormula->SetFocus();
	dlgMatrixFormula->ChangeTab(1);
}

void CMainFrame::ShowProjectionMatrix()
{
	OnMatrix();
	dlgMatrixFormula->SetFocus();
	dlgMatrixFormula->ChangeTab(2);
}

void CMainFrame::ShowViewPort()
{
	OnMatrix();
	dlgMatrixFormula->SetFocus();
	dlgMatrixFormula->ChangeTab(3);
}

CSize CMainFrame::GetViewPort()
{
	OnCamera();
	CRect rect;
	cameraFrame->GetClientRect(&rect);
	return CSize(rect.Width(),rect.Height());
}

void CMainFrame::OnPoint()
{
	// TODO: Add your command handler code here
	CDlgPoint dlg;
	if(dlg.DoModal() == IDOK)
		m_wndFileView.AddNode(new CPoint4D(dlg.m_X,dlg.m_Y,dlg.m_Z),TRUE);
}

void CMainFrame::OnLine()
{
	// TODO: Add your command handler code here
	CDlgLine dlg;
	if(dlg.DoModal() == IDOK)
		m_wndFileView.AddNode(new CLine(dlg.m_BX,dlg.m_BY,dlg.m_BZ,dlg.m_EX,dlg.m_EY,dlg.m_EZ),TRUE);
}

void CMainFrame::OnTriangle()
{
	// TODO: Add your command handler code here
	CDlgTriangle dlg;
	if(dlg.DoModal() == IDOK)
		m_wndFileView.AddNode(new CTriangle(dlg.m_X1,dlg.m_Y1,dlg.m_Z1,dlg.m_X2,dlg.m_Y2,dlg.m_Z2,dlg.m_X3,dlg.m_Y3,dlg.m_Z3),TRUE);
}


void CMainFrame::OnRectangle()
{
	// TODO: Add your command handler code here
	CDlgRectangle dlg;
	if(dlg.DoModal() == IDOK)
		m_wndFileView.AddNode(new CRectangle(dlg.m_Top,dlg.m_Left,dlg.m_Bottom,dlg.m_Right),TRUE);
}


void CMainFrame::OnCircle()
{
	// TODO: Add your command handler code here
	CDlgCircle dlg;
	if(dlg.DoModal() == IDOK)
		m_wndFileView.AddNode(new CCircle(dlg.m_X,dlg.m_Y,dlg.m_Z,dlg.m_R),TRUE);
}


void CMainFrame::OnEllipse()
{
	// TODO: Add your command handler code here
	CDlgEllipse dlg;
	if(dlg.DoModal() == IDOK)
		m_wndFileView.AddNode(new CEllipse(dlg.m_X,dlg.m_Y,dlg.m_Z,dlg.m_A,dlg.m_B),TRUE);
}


void CMainFrame::OnCube()
{
	// TODO: Add your command handler code here
	CDlgCube dlg;
	if(dlg.DoModal() == IDOK)
		m_wndFileView.AddNode(new CCube(dlg.m_Left,dlg.m_Bottom,dlg.m_Near,dlg.m_Right,dlg.m_Top,dlg.m_Far),TRUE);
}


void CMainFrame::OnTetrahedron()
{
	// TODO: Add your command handler code here
	CDlgTetrahedron dlg;
	if(dlg.DoModal() == IDOK)
		m_wndFileView.AddNode(new CTetrahedron(dlg.m_X1,dlg.m_Y1,dlg.m_Z1,dlg.m_X2,dlg.m_Y2,dlg.m_Z2,dlg.m_X3,dlg.m_Y3,dlg.m_Z3,dlg.m_X4,dlg.m_Y4,dlg.m_Z4),TRUE);
}


void CMainFrame::OnSphere()
{
	// TODO: Add your command handler code here
	CDlgSphere dlg;
	if(dlg.DoModal() == IDOK)
		m_wndFileView.AddNode(new CSphere(dlg.m_X,dlg.m_Y,dlg.m_Z,dlg.m_R),TRUE);
}


void CMainFrame::OnCylinder()
{
	// TODO: Add your command handler code here
	CDlgCylinder dlg;
	if(dlg.DoModal() == IDOK)
		m_wndFileView.AddNode(new CCylinder(dlg.m_X,dlg.m_Y,dlg.m_Z,dlg.m_R,dlg.m_Height),TRUE);
}


void CMainFrame::OnRing()
{
	// TODO: Add your command handler code here
	CDlgRing dlg;
	if(dlg.DoModal() == IDOK)
		m_wndFileView.AddNode(new CRing(dlg.m_X,dlg.m_Y,dlg.m_Z,dlg.m_R,dlg.m_R1),TRUE);
}
