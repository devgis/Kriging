// ContourView.cpp : implementation file
//

#include "stdafx.h"
#include "WaferPainter.h"
#include "ContourView.h"
#include "InverseDist.h"
#include "MainFrm.h"
#include "Kriging.h"
#include <algorithm>
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static COLORREF Colors[11] = { RGB(127, 127, 127), RGB(0, 0, 127), RGB(0, 0, 255), RGB(0, 127, 127), RGB(0, 255, 0), 
						RGB(127, 127, 0), RGB(255, 255, 0), RGB(0, 255, 255), RGB(255, 0, 255), RGB(255, 127, 0), 
						RGB(255, 0, 0) };

const int FLAT_HEIGHT = 600;
const int LEGEND_WIDTH = 200;

/////////////////////////////////////////////////////////////////////////////
// CContourView

IMPLEMENT_DYNCREATE(CContourView, CView)

CContourView::CContourView() : m_pImage(NULL), m_bImageReady(false), m_nZoom(3), m_nBaseWidth(208), m_nBaseHeight(208),
m_nNumOfLevels(11), m_bLegend(true), m_bValues(true), m_dThickMax(0), m_dThickMin(0)
{
}

CContourView::~CContourView()
{
	if(m_pImage)
		delete m_pImage;
}


BEGIN_MESSAGE_MAP(CContourView, CView)
	//{{AFX_MSG_MAP(CContourView)
	ON_COMMAND(ID_SHOWVALUES, OnShowvalues)
	ON_COMMAND(ID_SHOWLEGEND, OnShowlegend)
	ON_UPDATE_COMMAND_UI(ID_SHOWVALUES, OnUpdateShowvalues)
	ON_UPDATE_COMMAND_UI(ID_SHOWLEGEND, OnUpdateShowlegend)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CContourView drawing

void CContourView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
	if(m_bImageReady) {
		try {
			m_pImage->Draw(pDC, 0, 0, m_nZoom);
		} catch(CImageException& e) {
			::AfxMessageBox(e.what());
			m_bImageReady = false;
		}

		if(m_bValues)
			DrawValues(pDC);

		if(m_bLegend)
			DrawLegend(pDC);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CContourView diagnostics

#ifdef _DEBUG
void CContourView::AssertValid() const
{
	CView::AssertValid();
}

void CContourView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CContourDoc* CContourView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CContourDoc)));
	return (CContourDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CContourView message handlers

void CContourView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	CWaferPainterApp* pApp = static_cast<CWaferPainterApp*>(::AfxGetApp());
	int nDia = pApp->m_nDiameter;
	int nDiameter = 200;
	if(nDia == 1)
		nDiameter = 300;
	int nInterpolater = pApp->m_nInterpolater;

	CWaitCursor wait;

	CContourDoc* pDoc = GetDocument();
	vector<Point3D>& input = const_cast<vector<Point3D>&>(pDoc->m_ir.Get3DPoints());

	Interpolater* pInterpolater = NULL;
	if(nInterpolater == 0)
		pInterpolater = new InverseDist(200, 4);
	else if(nInterpolater == 1)
		pInterpolater = new Kriging(input.begin(), input.end(), 4);

	vector<double> vecZs;
	int nRadius = nDiameter / 2;
	for(int i=0; i<nDiameter; i++) {
		for(int j=0; j<nDiameter; j++) {
			double z = pInterpolater->GetInterpolatedZ(j - nRadius, i - nRadius, input.begin(), input.end());
			vecZs.push_back(z);			
		}
	}

	delete pInterpolater;

	vector<double>::iterator iter;
	iter = max_element(vecZs.begin(), vecZs.end());
	m_dThickMax = *iter;
	iter = min_element(vecZs.begin(), vecZs.end());
	m_dThickMin = *iter;
	double interval = (m_dThickMax - m_dThickMin) / (m_nNumOfLevels - 1);

	// fill in CDib structure
	int size = nDiameter * nDiameter;
	int iWidthBytes = ((nDiameter * 24 + 15) & ~15) >> 3 ;
	DWORD dwImgSize = iWidthBytes * nDiameter;

	// Data bits
	LPBYTE pDibBits;
	pDibBits = new BYTE[dwImgSize];
	LPBYTE pBit = pDibBits;

	for(i=0; i<vecZs.size(); i++) {
		double z = vecZs[i];
		int index = (int)((z - m_dThickMin) / interval);
		*pBit = GetBValue(Colors[index]);
		pBit++;
		*pBit = GetGValue(Colors[index]);
		pBit++;
		*pBit = GetRValue(Colors[index]);
		pBit++;
	}

	m_pImage = new CDib;
	try {
		m_pImage->Create(nDiameter, nDiameter, pDibBits);
	} catch(CImageException& e) {
		::AfxMessageBox(e.what());
		delete[] pDibBits;
		return;
	}
	m_bImageReady = true;

	ResizeFrame();
}

void CContourView::ResizeFrame()
{
	CMDIChildWnd* pChild = static_cast<CMDIChildWnd*>(GetParent());
	int nWidth = m_nBaseWidth * m_nZoom + 2*(::GetSystemMetrics(SM_CXSIZEFRAME)+::GetSystemMetrics(SM_CXEDGE));
	int nHeight = m_nBaseHeight * m_nZoom + 2*(::GetSystemMetrics(SM_CYSIZEFRAME)+::GetSystemMetrics(SM_CYEDGE))
		+ ::GetSystemMetrics(SM_CYCAPTION);
	if(m_bLegend)
		nWidth += LEGEND_WIDTH;

	WINDOWPLACEMENT wp;
	pChild->GetWindowPlacement(&wp);
	pChild->MoveWindow(wp.rcNormalPosition.left, wp.rcNormalPosition.top, nWidth, nHeight);
}

void CContourView::DrawValues(CDC* pDC)
{
	CContourDoc* pDoc = GetDocument();
	vector<Point3D>& input = const_cast<vector<Point3D>&>(pDoc->m_ir.Get3DPoints());

	CBrush br;
	br.CreateSolidBrush(RGB(0, 0, 0));
	CBrush* pOld;
	pOld = pDC->SelectObject(&br);
	CString thickness;
	pDC->SetBkMode(TRANSPARENT);
	for(int i=0; i<input.size(); i++) {
		int x1 = (int)(m_nZoom*(input[i].x+m_nBaseWidth/2-1));
		int y1 = (int)(m_nZoom*(0.5 * m_nBaseHeight-input[i].y+1));
		int x2 = (int)(m_nZoom*(input[i].x+m_nBaseWidth/2+1));
		int y2 = (int)(m_nZoom*(0.5 * m_nBaseHeight-input[i].y-1));
		pDC->Ellipse(x1, y1, x2, y2);
		thickness.Format(_T("%4.2f"), input[i].z);
		pDC->TextOut(x1-20, y1+4, thickness);
	}
	pDC->SelectObject(pOld);
}

void CContourView::DrawLegend(CDC* pDC)
{
	const int RECT_HEIGHT = 18;
	const int RECT_WIDTH = 40;

	int x1 = m_nZoom * m_nBaseWidth + 10;
	pDC->Rectangle(x1, 16, x1+164, (m_nNumOfLevels+1)*(RECT_HEIGHT+2));
	CString thickness;
	double interval = (m_dThickMax - m_dThickMin) / m_nNumOfLevels;
	for(int i=0; i<m_nNumOfLevels; i++) {
		CBrush br;
		br.CreateSolidBrush(Colors[i]);
		pDC->SelectObject(&br);
		pDC->Rectangle(x1+3, 20+i*20, x1+RECT_WIDTH, 30+i*20);
		thickness.Format(_T("%4.2f - %4.2f"), m_dThickMin+(i*interval), m_dThickMin+((i+1)*interval));
		pDC->TextOut(x1+RECT_WIDTH+4, 20+i*20, thickness);
	}
}

void CContourView::OnShowvalues() 
{
	// TODO: Add your command handler code here
	m_bValues = !m_bValues;
	Invalidate();
}

void CContourView::OnShowlegend() 
{
	// TODO: Add your command handler code here
	m_bLegend = !m_bLegend;
	Invalidate();
	ResizeFrame();
}

void CContourView::OnUpdateShowvalues(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_bValues);
}

void CContourView::OnUpdateShowlegend(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_bLegend);
}

void CContourView::OnEditCopy() 
{
	// TODO: Add your command handler code here
	if(!m_bImageReady)
		return;
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

void CContourView::OnFileSave() 
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

	CContourDoc* pDoc = GetDocument();
	pDoc->SetTitle(dlg.GetFileName());
}

