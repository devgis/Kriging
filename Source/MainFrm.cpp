// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "WaferPainter.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_PROGRESS_PANE,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	RECT MyRect;
	// substitute 4 with the zero-based index of your status bar pane. 
	// For example, if you put your pane first in the indicators array, 
	// you¡¯d put 0, second you¡¯d put 1, etc.
	m_wndStatusBar.GetItemRect(1, &MyRect);  

	//Create the progress control
	m_wndProgress.Create(WS_VISIBLE|WS_CHILD, MyRect, &m_wndStatusBar, ID_INDICATOR_PROGRESS_PANE);
	m_wndProgress.SetRange(0, 100); //Set the range to between 0 and 100
	m_wndProgress.SetPos(0);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.x = 0;
	cs.y = 0;
    
    cs.cx = ::GetSystemMetrics(SM_CXSCREEN);
    cs.cy = ::GetSystemMetrics(SM_CYSCREEN) - ::GetSystemMetrics(SM_CYMENU) - 2*(::GetSystemMetrics(SM_CYBORDER)) -
        2*(::GetSystemMetrics(SM_CYEDGE));

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::SetProgressPos(int pos) 
{
	CString status;
	m_wndProgress.SetPos(pos);
	status.Format(_T("%d %% completed"), pos);
	m_wndStatusBar.SetPaneText(0, status);
}

void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	CMDIFrameWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	RECT rc;
	m_wndStatusBar.GetItemRect(1, &rc);

	// Reposition the progress control correctly!
	m_wndProgress.SetWindowPos(&wndTop, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, 0); 
}
