#if !defined(AFX_3DCONTOURVIEW_H__F84F20AB_C0FB_435B_A938_E48E8B1141F6__INCLUDED_)
#define AFX_3DCONTOURVIEW_H__F84F20AB_C0FB_435B_A938_E48E8B1141F6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// 3DContourView.h : header file
//

#include "GLSurfaceView.h"
#include "3DContourDoc.h"

/////////////////////////////////////////////////////////////////////////////
// C3DContourView view

class C3DContourView : public CGLSurfaceView
{
protected:
	C3DContourView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(C3DContourView)

// Attributes
public:
	C3DContourDoc* GetDocument();

// Operations
public:
	double m_dThickMin;
	double m_dThickMax;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C3DContourView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~C3DContourView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(C3DContourView)
	afx_msg void OnShowlegend();
	afx_msg void OnUpdateShowlegend(CCmdUI* pCmdUI);
	afx_msg void OnCullface();
	afx_msg void OnUpdateCullface(CCmdUI* pCmdUI);
	afx_msg void OnSmooth();
	afx_msg void OnUpdateSmooth(CCmdUI* pCmdUI);
	afx_msg void OnFlat();
	afx_msg void OnUpdateFlat(CCmdUI* pCmdUI);
	afx_msg void OnBgcolor();
	afx_msg void OnEditCopy();
	afx_msg void OnFileSave();
	afx_msg void OnShowwall();
	afx_msg void OnUpdateShowwall(CCmdUI* pCmdUI);
	afx_msg void OnShowboundary();
	afx_msg void OnUpdateShowboundary(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in C3DContourView.cpp
inline C3DContourDoc* C3DContourView::GetDocument()
   { return (C3DContourDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_3DCONTOURVIEW_H__F84F20AB_C0FB_435B_A938_E48E8B1141F6__INCLUDED_)
