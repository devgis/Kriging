// WaferPainterDoc.h : interface of the CWaferPainterDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WAFERPAINTERDOC_H__CBEED795_B3EC_470B_9D57_FD8BF8B9C7EC__INCLUDED_)
#define AFX_WAFERPAINTERDOC_H__CBEED795_B3EC_470B_9D57_FD8BF8B9C7EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Interpolater.h"
#include <vector>

class CWaferPainterDoc : public CDocument
{
protected: // create from serialization only
	CWaferPainterDoc();
	DECLARE_DYNCREATE(CWaferPainterDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWaferPainterDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWaferPainterDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CWaferPainterDoc)
	afx_msg void On2dcontour();
	afx_msg void On3dcontour();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WAFERPAINTERDOC_H__CBEED795_B3EC_470B_9D57_FD8BF8B9C7EC__INCLUDED_)
