// WaferPainterView.cpp : implementation of the CWaferPainterView class
//

#include "stdafx.h"
#include "WaferPainter.h"

#include "WaferPainterDoc.h"
#include "WaferPainterView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWaferPainterView

IMPLEMENT_DYNCREATE(CWaferPainterView, CEditView)

BEGIN_MESSAGE_MAP(CWaferPainterView, CEditView)
	//{{AFX_MSG_MAP(CWaferPainterView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWaferPainterView construction/destruction

CWaferPainterView::CWaferPainterView()
{
	// TODO: add construction code here

}

CWaferPainterView::~CWaferPainterView()
{
}

BOOL CWaferPainterView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping

	return bPreCreated;
}

/////////////////////////////////////////////////////////////////////////////
// CWaferPainterView drawing

void CWaferPainterView::OnDraw(CDC* pDC)
{
	CWaferPainterDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CWaferPainterView printing

BOOL CWaferPainterView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default CEditView preparation
	return CEditView::OnPreparePrinting(pInfo);
}

void CWaferPainterView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView begin printing.
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CWaferPainterView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView end printing
	CEditView::OnEndPrinting(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CWaferPainterView diagnostics

#ifdef _DEBUG
void CWaferPainterView::AssertValid() const
{
	CEditView::AssertValid();
}

void CWaferPainterView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CWaferPainterDoc* CWaferPainterView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWaferPainterDoc)));
	return (CWaferPainterDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWaferPainterView message handlers
