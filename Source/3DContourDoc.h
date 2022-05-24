#if !defined(AFX_3DCONTOURDOC_H__9071BA97_C12F_4CEA_A11A_19B8E0E8F108__INCLUDED_)
#define AFX_3DCONTOURDOC_H__9071BA97_C12F_4CEA_A11A_19B8E0E8F108__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// 3DContourDoc.h : header file
//

#include "InputReader.h"

/////////////////////////////////////////////////////////////////////////////
// C3DContourDoc document

class C3DContourDoc : public CDocument
{
protected:
	C3DContourDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(C3DContourDoc)

// Attributes
public:
	InputReader m_ir;

// Operations
public:
	void Init(LPCTSTR lpszPathName);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C3DContourDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~C3DContourDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(C3DContourDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_3DCONTOURDOC_H__9071BA97_C12F_4CEA_A11A_19B8E0E8F108__INCLUDED_)
