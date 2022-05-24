// WaferPainterDoc.cpp : implementation of the CWaferPainterDoc class
//

#include "stdafx.h"
#include "WaferPainter.h"

#include "WaferPainterDoc.h"
#include "ContourDoc.h"
#include "3DContourDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWaferPainterDoc

IMPLEMENT_DYNCREATE(CWaferPainterDoc, CDocument)

BEGIN_MESSAGE_MAP(CWaferPainterDoc, CDocument)
	//{{AFX_MSG_MAP(CWaferPainterDoc)
	ON_COMMAND(ID_2DCONTOUR, On2dcontour)
	ON_COMMAND(ID_3DCONTOUR, On3dcontour)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWaferPainterDoc construction/destruction

CWaferPainterDoc::CWaferPainterDoc()
{
	// TODO: add one-time construction code here

}

CWaferPainterDoc::~CWaferPainterDoc()
{
}

BOOL CWaferPainterDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CWaferPainterDoc serialization

void CWaferPainterDoc::Serialize(CArchive& ar)
{
	// CEditView contains an edit control which handles all serialization
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CWaferPainterDoc diagnostics

#ifdef _DEBUG
void CWaferPainterDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWaferPainterDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWaferPainterDoc commands

void CWaferPainterDoc::On2dcontour() 
{
	// TODO: Add your command handler code here
	CWaferPainterApp* pApp = static_cast<CWaferPainterApp*>(::AfxGetApp());

	CContourDoc* pDoc = static_cast<CContourDoc*>(pApp->m_pContourTemplate->CreateNewDocument());
	pDoc->Init(GetPathName());
	CFrameWnd* pFrame = pApp->m_pContourTemplate->CreateNewFrame(pDoc, NULL);
	pApp->m_pContourTemplate->InitialUpdateFrame(pFrame, pDoc);
}

BOOL CWaferPainterDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here

	return TRUE;
}

void CWaferPainterDoc::On3dcontour() 
{
	// TODO: Add your command handler code here
	CWaferPainterApp* pApp = static_cast<CWaferPainterApp*>(::AfxGetApp());

	C3DContourDoc* pDoc = static_cast<C3DContourDoc*>(pApp->m_p3DContourTemplate->CreateNewDocument());
	pDoc->Init(GetPathName());
	CFrameWnd* pFrame = pApp->m_p3DContourTemplate->CreateNewFrame(pDoc, NULL);
	pApp->m_p3DContourTemplate->InitialUpdateFrame(pFrame, pDoc);
}
