// 3DContourDoc.cpp : implementation file
//

#include "stdafx.h"
#include "WaferPainter.h"
#include "3DContourDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C3DContourDoc

IMPLEMENT_DYNCREATE(C3DContourDoc, CDocument)

C3DContourDoc::C3DContourDoc()
{
}

BOOL C3DContourDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

C3DContourDoc::~C3DContourDoc()
{
}


BEGIN_MESSAGE_MAP(C3DContourDoc, CDocument)
	//{{AFX_MSG_MAP(C3DContourDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C3DContourDoc diagnostics

#ifdef _DEBUG
void C3DContourDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void C3DContourDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// C3DContourDoc serialization

void C3DContourDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// C3DContourDoc commands

void C3DContourDoc::Init(LPCTSTR lpszPathName)
{
	m_ir.Read(lpszPathName);
	SetTitle(_T("Untitled.3dc"));
}