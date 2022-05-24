// ContourDoc.cpp : implementation file
//

#include "stdafx.h"
#include "WaferPainter.h"
#include "ContourDoc.h"
#include "ContourView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CContourDoc

IMPLEMENT_DYNCREATE(CContourDoc, CDocument)

CContourDoc::CContourDoc()
{
}

BOOL CContourDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CContourDoc::~CContourDoc()
{
}


BEGIN_MESSAGE_MAP(CContourDoc, CDocument)
	//{{AFX_MSG_MAP(CContourDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CContourDoc diagnostics

#ifdef _DEBUG
void CContourDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CContourDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CContourDoc serialization

void CContourDoc::Serialize(CArchive& ar)
{
	CContourView* pView = static_cast<CContourView*>(m_viewList.GetHead());

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
// CContourDoc commands

void CContourDoc::Init(LPCTSTR lpszPathName)
{
	m_ir.Read(lpszPathName);
	SetTitle(_T("Untitled.bmp"));
}
