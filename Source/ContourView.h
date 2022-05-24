#if !defined(AFX_CONTOURVIEW_H__F1D75CCE_6DF2_4DB6_96EE_F9207A771C9D__INCLUDED_)
#define AFX_CONTOURVIEW_H__F1D75CCE_6DF2_4DB6_96EE_F9207A771C9D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ContourView.h : header file
//

#include "ContourDoc.h"
#include "Dib.h"

/////////////////////////////////////////////////////////////////////////////
// CContourView view

class CContourView : public CView
{
protected:
	CContourView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CContourView)

// Attributes
public:
	CContourDoc* GetDocument();

// Operations
public:
	CImage* m_pImage;

private:
	bool	m_bImageReady;
	bool	m_bLegend;
	bool	m_bValues;
	int		m_nZoom;
	int		m_nNumOfLevels;

	int		m_nBaseWidth;
	int		m_nBaseHeight;

	double	m_dThickMax;
	double	m_dThickMin;

	void DrawValues(CDC* pDC);
	void DrawLegend(CDC* pDC);
	void ResizeFrame();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CContourView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CContourView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CContourView)
	afx_msg void OnShowvalues();
	afx_msg void OnShowlegend();
	afx_msg void OnUpdateShowvalues(CCmdUI* pCmdUI);
	afx_msg void OnUpdateShowlegend(CCmdUI* pCmdUI);
	afx_msg void OnEditCopy();
	afx_msg void OnFileSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in WaferPainterView.cpp
inline CContourDoc* CContourView::GetDocument()
   { return (CContourDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONTOURVIEW_H__F1D75CCE_6DF2_4DB6_96EE_F9207A771C9D__INCLUDED_)
