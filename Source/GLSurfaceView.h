#if !defined(AFX_GLSURFACEVIEW_H__295C42EB_DBBB_4D78_9C8A_7320C57619D7__INCLUDED_)
#define AFX_GLSURFACEVIEW_H__295C42EB_DBBB_4D78_9C8A_7320C57619D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GLSurfaceView.h : header file
//

#include "Surfer.h"
#include "Image.h"

/////////////////////////////////////////////////////////////////////////////
// CGLSurfaceView view

class CGLSurfaceView : public CView
{
protected:
	CGLSurfaceView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CGLSurfaceView)

// Attributes
public:
	CSurfer& GetGrapher() { return m_thickGrapher; }

private:
	CSurfer	m_thickGrapher;
	bool	m_bResize;
	CPoint	m_ptStart;
	HCURSOR m_cur3Dmove;
	HCURSOR m_curMagnify;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGLSurfaceView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CGLSurfaceView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CGLSurfaceView)
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnEditCopy();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THICKNESSVIEW_H__295C42EB_DBBB_4D78_9C8A_7320C57619D7__INCLUDED_)
