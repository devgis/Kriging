// WaferPainterView.h : interface of the CWaferPainterView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WAFERPAINTERVIEW_H__66238478_97DA_4F70_B674_815B4E7E235C__INCLUDED_)
#define AFX_WAFERPAINTERVIEW_H__66238478_97DA_4F70_B674_815B4E7E235C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CWaferPainterView : public CEditView
{
protected: // create from serialization only
	CWaferPainterView();
	DECLARE_DYNCREATE(CWaferPainterView)

// Attributes
public:
	CWaferPainterDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWaferPainterView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWaferPainterView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CWaferPainterView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in WaferPainterView.cpp
inline CWaferPainterDoc* CWaferPainterView::GetDocument()
   { return (CWaferPainterDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WAFERPAINTERVIEW_H__66238478_97DA_4F70_B674_815B4E7E235C__INCLUDED_)
