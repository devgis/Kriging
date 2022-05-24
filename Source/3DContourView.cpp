// 3DContourView.cpp : implementation file

#include "stdafx.h"
#include "WaferPainter.h"
#include "3DContourView.h"
#include <algorithm>
#include "Dib.h"
#include "InverseDist.h"
#include "Kriging.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C3DContourView

IMPLEMENT_DYNCREATE(C3DContourView, CGLSurfaceView)

C3DContourView::C3DContourView() : m_dThickMin(0), m_dThickMax(0)
{
}

C3DContourView::~C3DContourView()
{
}


BEGIN_MESSAGE_MAP(C3DContourView, CGLSurfaceView)
	//{{AFX_MSG_MAP(C3DContourView)
	ON_COMMAND(ID_SHOWLEGEND, OnShowlegend)
	ON_UPDATE_COMMAND_UI(ID_SHOWLEGEND, OnUpdateShowlegend)
	ON_COMMAND(ID_CULLFACE, OnCullface)
	ON_UPDATE_COMMAND_UI(ID_CULLFACE, OnUpdateCullface)
	ON_COMMAND(ID_SMOOTH, OnSmooth)
	ON_UPDATE_COMMAND_UI(ID_SMOOTH, OnUpdateSmooth)
	ON_COMMAND(ID_FLAT, OnFlat)
	ON_UPDATE_COMMAND_UI(ID_FLAT, OnUpdateFlat)
	ON_COMMAND(ID_BGCOLOR, OnBgcolor)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_SHOWWALL, OnShowwall)
	ON_UPDATE_COMMAND_UI(ID_SHOWWALL, OnUpdateShowwall)
	ON_COMMAND(ID_SHOWBOUNDARY, OnShowboundary)
	ON_UPDATE_COMMAND_UI(ID_SHOWBOUNDARY, OnUpdateShowboundary)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C3DContourView drawing

void C3DContourView::OnDraw(CDC* pDC)
{
	C3DContourDoc* pDoc = GetDocument();
	// TODO: add draw code here
	CGLSurfaceView::OnDraw(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// C3DContourView diagnostics

#ifdef _DEBUG
void C3DContourView::AssertValid() const
{
	CGLSurfaceView::AssertValid();
}

void C3DContourView::Dump(CDumpContext& dc) const
{
	CGLSurfaceView::Dump(dc);
}

C3DContourDoc* C3DContourView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(C3DContourDoc)));
	return (C3DContourDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// C3DContourView message handlers

void C3DContourView::OnInitialUpdate() 
{	
	// TODO: Add your specialized code here and/or call the base class
	CWaitCursor wait;
	CWaferPainterApp* pApp = static_cast<CWaferPainterApp*>(::AfxGetApp());
	int nDia = pApp->m_nDiameter;
	int nDiameter = 200;
	if(nDia == 1)
		nDiameter = 300;
	int nInterpolater = pApp->m_nInterpolater;

	C3DContourDoc* pDoc = GetDocument();
	vector<Point3D>& input = const_cast<vector<Point3D>&>(pDoc->m_ir.Get3DPoints());

	Interpolater* pInterpolater = NULL;
	if(nInterpolater == 0)
		pInterpolater = new InverseDist(200, 4);
	else if(nInterpolater == 1)
		pInterpolater = new Kriging(input.begin(), input.end(), 4);

	vector<double> vecZs;

	for(int j=0; j<=nDiameter; j++) {
		for(int i=0; i<=nDiameter; i++) {
			double z = pInterpolater->GetInterpolatedZ(j - nDiameter/2, i - 0.5 * nDiameter, input.begin(), input.end());
			vecZs.push_back(z);
		}
	}

	delete pInterpolater;

	vector<double>::iterator iter2;
	iter2 = max_element(vecZs.begin(), vecZs.end());
	m_dThickMax = *iter2;
	iter2 = min_element(vecZs.begin(), vecZs.end());
	m_dThickMin = *iter2;

	// These 3 lines are for determining thickness range. Typical thickness range 4000~7000 is too big
	// compared to x, y range of 200 so I had to reduce it. 
	double MinMaxDiff = m_dThickMax - m_dThickMin;
	double widthRatio = nDiameter;
	double ratio = MinMaxDiff/widthRatio * 4;

	int dataSize = (nDiameter + 1) * (nDiameter + 1);
	C3DData* pdata = C3DData::GetInstance();
	pdata->SetSize(dataSize);

	int ii = 0;
	for(j=0; j<=nDiameter; j++) {
		for(int i=0; i<=nDiameter; i++) {
			pdata->SetAt(ii, i, j, (vecZs[ii]-m_dThickMin)/ratio);
			++ii;
		}
	}

	GetGrapher().Add3DData(pdata);
	GetGrapher().SetAxisRange(nDiameter + 1, (m_dThickMax-m_dThickMin)/ratio, nDiameter);
	GetGrapher().SetMinValue(0);
	GetGrapher().SetTitles(_T(""), _T("Y"), _T("Thickness(mm)"), _T("X"));
	GetGrapher().SetCullFace(false);

	CGLSurfaceView::OnInitialUpdate();
}

void C3DContourView::OnShowlegend() 
{
	// TODO: Add your command handler code here
	GetGrapher().SetLegend(!GetGrapher().IsLegend());
	Invalidate();
}

void C3DContourView::OnUpdateShowlegend(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(GetGrapher().IsLegend());
}

void C3DContourView::OnShowwall() 
{
	// TODO: Add your command handler code here
	GetGrapher().SetWall(!GetGrapher().IsWall());
	Invalidate();
}

void C3DContourView::OnUpdateShowwall(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(GetGrapher().IsWall());
}

void C3DContourView::OnShowboundary() 
{
	// TODO: Add your command handler code here
	GetGrapher().SetBoundary(!GetGrapher().IsBoundary());
	Invalidate();
}

void C3DContourView::OnUpdateShowboundary(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(GetGrapher().IsBoundary());
}

void C3DContourView::OnCullface() 
{
	// TODO: Add your command handler code here
	GetGrapher().SetCullFace(!GetGrapher().IsCullFace());
	Invalidate();
}

void C3DContourView::OnUpdateCullface(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(GetGrapher().IsCullFace());
}

void C3DContourView::OnSmooth() 
{
	// TODO: Add your command handler code here
	GetGrapher().SetShadeModel(C3DGrapher::SMOOTH);
	Invalidate();
}

void C3DContourView::OnUpdateSmooth(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(GetGrapher().GetShadeModel() == C3DGrapher::SMOOTH);
}

void C3DContourView::OnFlat() 
{
	// TODO: Add your command handler code here
	GetGrapher().SetShadeModel(C3DGrapher::FLAT);
	Invalidate();
}

void C3DContourView::OnUpdateFlat(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(GetGrapher().GetShadeModel() == C3DGrapher::FLAT);
}

void C3DContourView::OnBgcolor() 
{
	// TODO: Add your command handler code here
	CColorDialog dlg;
	if(dlg.DoModal() == IDOK) {
		GetGrapher().SetBkGndColor(dlg.GetColor());
		Invalidate();
	}
}

void C3DContourView::OnEditCopy() 
{
	// TODO: Add your command handler code here
	CWaitCursor wait;

	CClientDC scrDC(this);
	CDC memDC;           // screen DC and memory DC
	CBitmap bitmap;
	CBitmap* pOldBitmap;  // handles to deice-dependent bitmaps

	CRect rect;
	GetClientRect(&rect);

	memDC.CreateCompatibleDC(&scrDC);
	/* create a bitmap compatible with the screen DC */
	bitmap.CreateCompatibleBitmap(&scrDC, rect.Width(), rect.Height());

	pOldBitmap = memDC.SelectObject(&bitmap);// select new bitmap into memory DC

	memDC.BitBlt(0, 0, rect.Width(), rect.Height(), &scrDC, 0, 0, SRCCOPY);
	HBITMAP hBitmap = (HBITMAP)bitmap.Detach();

	memDC.SelectObject(pOldBitmap);

	// Place the copy on the clipboard.
	::OpenClipboard(m_hWnd);
    ::EmptyClipboard();
    ::SetClipboardData(CF_BITMAP, hBitmap);
    ::CloseClipboard();

	// clean up 
	memDC.DeleteDC();
}

void C3DContourView::OnFileSave() 
{
	// TODO: Add your command handler code here
	CWaitCursor wait;

	CClientDC scrDC(this);
	CDC memDC;           // screen DC and memory DC
	CBitmap bitmap;
	CBitmap* pOldBitmap;  // handles to deice-dependent bitmaps

	CRect rect;
	GetClientRect(&rect);

	memDC.CreateCompatibleDC(&scrDC);
	bitmap.CreateCompatibleBitmap(&scrDC, rect.Width(), rect.Height());

	pOldBitmap = memDC.SelectObject(&bitmap);// select new bitmap into memory DC

	memDC.BitBlt(0, 0, rect.Width(), rect.Height(), &scrDC, 0, 0, SRCCOPY);

	TCHAR szFilters[] = _T ("bmp files (*.bmp)|*.bmp|All files (*.*)|*.*||");
	CFileDialog dlg(FALSE, _T ("bmp"), _T ("*.bmp"), OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
		szFilters);
	
	CString filename;
	if(dlg.DoModal() == IDOK)
		filename = dlg.GetPathName();
	else
		return;

	CDib dib;
	try {
		dib.Create(&bitmap);
		dib.Save(filename);
	} catch(CImageException& e) {
		::AfxMessageBox(e.what());
	}

	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();

	C3DContourDoc* pDoc = GetDocument();
	pDoc->SetTitle(dlg.GetFileName());
}

