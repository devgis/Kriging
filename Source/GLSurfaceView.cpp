// GLSurfaceView.cpp : implementation file
//

#include "stdafx.h"
#include "GLSurfaceView.h"
#include "Dib.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGLSurfaceView

IMPLEMENT_DYNCREATE(CGLSurfaceView, CView)

CGLSurfaceView::CGLSurfaceView() : m_bResize(true)
{
	m_cur3Dmove = ::AfxGetApp()->LoadCursor(IDC_3DMOVECURSOR);
	m_curMagnify = ::AfxGetApp()->LoadCursor(IDC_MAGNIFYCURSOR);
}

CGLSurfaceView::~CGLSurfaceView()
{
}


BEGIN_MESSAGE_MAP(CGLSurfaceView, CView)
	//{{AFX_MSG_MAP(CGLSurfaceView)
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_WM_SETCURSOR()
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGLSurfaceView drawing

void CGLSurfaceView::OnDraw(CDC* pDC)
{
	// TODO: add draw code here
	if(m_bResize) {
		CRect rect;
		GetClientRect(&rect);
		m_thickGrapher.Resize(rect.Width(), rect.Height());
		m_bResize = false;
	}
	m_thickGrapher.Render();
}

/////////////////////////////////////////////////////////////////////////////
// CGLSurfaceView diagnostics

#ifdef _DEBUG
void CGLSurfaceView::AssertValid() const
{
	CView::AssertValid();
}

void CGLSurfaceView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGLSurfaceView message handlers

BOOL CGLSurfaceView::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	return CView::PreCreateWindow(cs);
}

void CGLSurfaceView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized creation code here
	m_thickGrapher.Init(m_hWnd);
}

void CGLSurfaceView::OnDestroy() 
{
	CView::OnDestroy();
	
	// TODO: Add your message handler code here
	m_thickGrapher.Destroy();
}

BOOL CGLSurfaceView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
	return FALSE;
}

void CGLSurfaceView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	m_thickGrapher.Resize(cx, cy);
}

void CGLSurfaceView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(nFlags & MK_LBUTTON) {
		CSize rotate = m_ptStart - point;
		m_ptStart = point;
		m_thickGrapher.SetXRotation(m_thickGrapher.GetXRotation() + rotate.cy);
		m_thickGrapher.SetYRotation(m_thickGrapher.GetYRotation() - rotate.cx);
		Invalidate(FALSE);
	} else if(nFlags & MK_RBUTTON) {
		SetCursor(m_curMagnify);
		CSize trans = m_ptStart - point;
		m_ptStart = point;
		m_thickGrapher.SetZTranslation(m_thickGrapher.GetZTranslation() + trans.cy/2);
		Invalidate(FALSE);
	}
	CView::OnMouseMove(nFlags, point);
}

void CGLSurfaceView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_ptStart = point;

	CView::OnLButtonDown(nFlags, point);
}

void CGLSurfaceView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_ptStart = point;
	SetCursor(m_curMagnify);
	CView::OnRButtonDown(nFlags, point);
}

void CGLSurfaceView::OnEditCopy() 
{
	// TODO: Add your command handler code here
	CWaitCursor wait;

	CClientDC scrDC(this);
	CDC memDC;           // screen DC and memory DC
	CBitmap bitmap;
	CBitmap* pOldBitmap;  // handles to deice-dependent bitmaps

	CRect rect;
	GetClientRect(&rect);

	memDC.CreateCompatibleDC(&scrDC);
	/* create a bitmap compatible with the screen DC */
	bitmap.CreateCompatibleBitmap(&scrDC, rect.Width(), rect.Height());

	pOldBitmap = memDC.SelectObject(&bitmap);// select new bitmap into memory DC

	memDC.BitBlt(0, 0, rect.Width(), rect.Height(), &scrDC, 0, 0, SRCCOPY);
	HBITMAP hBitmap = (HBITMAP)bitmap.Detach();

	memDC.SelectObject(pOldBitmap);

	// Place the copy on the clipboard.
	::OpenClipboard(m_hWnd);
    ::EmptyClipboard();
    ::SetClipboardData(CF_BITMAP, hBitmap);
    ::CloseClipboard();

	// clean up 
	memDC.DeleteDC();
}

BOOL CGLSurfaceView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	if(nHitTest == HTCLIENT) {
		SetCursor(m_cur3Dmove);
		return TRUE;
	}
	return CView::OnSetCursor(pWnd, nHitTest, message);
}

void CGLSurfaceView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	SetCursor(m_cur3Dmove);
	CView::OnRButtonUp(nFlags, point);
}
