#if !defined(AFX_CONTOURDOC_H__A90EE96B_170B_47C4_A3FF_70AFF5747013__INCLUDED_)
#define AFX_CONTOURDOC_H__A90EE96B_170B_47C4_A3FF_70AFF5747013__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ContourDoc.h : header file
//

#include "InputReader.h"

/////////////////////////////////////////////////////////////////////////////
// CContourDoc document

class CContourDoc : public CDocument
{
protected:
	CContourDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CContourDoc)

// Attributes
public:
	InputReader m_ir;

// Operations
public:
	void Init(LPCTSTR lpszPathName);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CContourDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CContourDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CContourDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONTOURDOC_H__A90EE96B_170B_47C4_A3FF_70AFF5747013__INCLUDED_)
