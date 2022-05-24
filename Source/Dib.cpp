// Dib.cpp: implementation of the CDib class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Dib.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CDib::CDib() throw()
{
	m_pBmpFileHeader = NULL;
	m_pBmpInfo = NULL;
	m_pBmpInfoHeader = NULL;
	m_pRGBTable = NULL;
	m_pDibBits = NULL;
	m_uiNumColors = 0;
}

CDib::~CDib()
{
	Clear();
}

void CDib::Clear() throw()
{
	if(m_pBmpFileHeader != NULL) {
		delete[] m_pBmpFileHeader;
		m_pBmpFileHeader = NULL;
	}
	if(m_pBmpInfo != NULL) {
		delete[] m_pBmpInfo;
		m_pBmpInfo = NULL;
	}
	if(m_pDibBits != NULL) {
		delete[] m_pDibBits;
		m_pDibBits = NULL;
	}
}

void CDib::Load(CString fileName) throw(CImageException) 
{
	CFile file(fileName, CFile::modeRead | CFile::shareDenyNone);
	Load(&file);
}

void CDib::Load(CFile* pFile) throw(CImageException)
{
	Clear();

	m_pBmpFileHeader = new BITMAPFILEHEADER;
	pFile->Read(static_cast<void*>(m_pBmpFileHeader), sizeof(BITMAPFILEHEADER));
	
	if(m_pBmpFileHeader->bfType != 0x4d42) {
		Clear();
		pFile->Close();
		throw CImageException(_T("Failed to load document"));
	} else {
		DWORD dwLength;
		dwLength = m_pBmpFileHeader->bfOffBits - sizeof(BITMAPFILEHEADER);

		m_pBmpInfo = reinterpret_cast<LPBITMAPINFO>(new BYTE[dwLength]);
		pFile->Read(static_cast<void*>(m_pBmpInfo), dwLength);
		m_pBmpInfoHeader = reinterpret_cast<LPBITMAPINFOHEADER>(m_pBmpInfo);

		if((m_pBmpInfoHeader->biClrUsed == 0))
			m_uiNumColors = 1 << m_pBmpInfoHeader->biBitCount;
		else
			m_uiNumColors = m_pBmpInfoHeader->biClrUsed;

		if(m_pBmpInfoHeader->biClrUsed == 0)
			m_pBmpInfoHeader->biClrUsed = m_uiNumColors;
		
		if(m_uiNumColors <= 256)
			m_pRGBTable = reinterpret_cast<RGBQUAD*>(reinterpret_cast<BYTE*>(m_pBmpInfo) + m_pBmpInfoHeader->biSize);

		DWORD dwDibLength = pFile->GetLength() - m_pBmpFileHeader->bfOffBits / 4;
		m_pDibBits = new BYTE[dwDibLength];
		pFile->Read(static_cast<void*>(m_pDibBits), dwDibLength);
	}
}

void CDib::Create(CBitmap* pBitmap) throw(CImageException)
{
	BITMAP Bitmap;
	int rc = pBitmap->GetBitmap(&Bitmap);
	if(rc == 0)
		throw CImageException(_T("Can't get BITMAP from CBitmap*"));

	int iWidthBytes = ((Bitmap.bmWidth * Bitmap.bmBitsPixel + 15) & ~15) >> 3 ;
	DWORD dwImgSize = iWidthBytes * Bitmap.bmHeight;
	
	// File header
	m_pBmpFileHeader = new BITMAPFILEHEADER;
	m_pBmpFileHeader->bfType = 0x4d42;
	m_pBmpFileHeader->bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFO) + dwImgSize; 
	m_pBmpFileHeader->bfReserved1 = 0; 
	m_pBmpFileHeader->bfReserved2 = 0; 
	m_pBmpFileHeader->bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFO) + sizeof(RGBQUAD);
	
	// Bitmap Info header - no support for palette mode
	m_pBmpInfo = new BITMAPINFO;
	m_pBmpInfoHeader = reinterpret_cast<LPBITMAPINFOHEADER>(m_pBmpInfo);
	::ZeroMemory(m_pBmpInfoHeader, sizeof(BITMAPINFOHEADER));
	m_pBmpInfoHeader->biSize = sizeof(BITMAPINFOHEADER);
	m_pBmpInfoHeader->biWidth = Bitmap.bmWidth;
	m_pBmpInfoHeader->biHeight = Bitmap.bmHeight;
	m_pBmpInfoHeader->biPlanes = 1;
	m_pBmpInfoHeader->biBitCount = Bitmap.bmPlanes * Bitmap.bmBitsPixel;
	m_pBmpInfoHeader->biSizeImage = dwImgSize;

	// Color Table
	if((m_pBmpInfoHeader->biClrUsed == 0))
		m_uiNumColors = 1 << m_pBmpInfoHeader->biBitCount;
	else
		m_uiNumColors = m_pBmpInfoHeader->biClrUsed;
	if(m_pBmpInfoHeader->biClrUsed == 0)
		m_pBmpInfoHeader->biClrUsed = m_uiNumColors;
	if(m_uiNumColors <= 256) {
		Clear();
		throw CImageException("Palette mode is not supported");
	}
	// Data bits
	m_pDibBits = new BYTE[dwImgSize];
	pBitmap->GetBitmapBits(dwImgSize, m_pDibBits);
	LPBYTE pTemp = new BYTE[iWidthBytes];
	for(int i=0; i<Bitmap.bmHeight/2; i++) {
		::memcpy(pTemp, m_pDibBits+i*iWidthBytes, iWidthBytes);
		::memcpy(m_pDibBits+i*iWidthBytes, m_pDibBits+iWidthBytes*(Bitmap.bmHeight-1-i), iWidthBytes);
		::memcpy(m_pDibBits+iWidthBytes*(Bitmap.bmHeight-1-i), pTemp, iWidthBytes);
	}
	delete[] pTemp;
}

void CDib::Create(int width, int height, LPBYTE pData, int bitCount) throw(CImageException)
{
	ASSERT(pData);
	ASSERT(bitCount > 8);

	Clear();

	int iWidthBytes = ((width * bitCount + 15) & ~15) >> 3 ;
	DWORD dwImgSize = iWidthBytes * height;
	
	// File header
	m_pBmpFileHeader = new BITMAPFILEHEADER;
	m_pBmpFileHeader->bfType = 0x4d42;
	m_pBmpFileHeader->bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFO) + dwImgSize; 
	m_pBmpFileHeader->bfReserved1 = 0; 
	m_pBmpFileHeader->bfReserved2 = 0; 
	m_pBmpFileHeader->bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFO) + sizeof(RGBQUAD);

	// Bitmap Info header - no support for palette mode
	m_pBmpInfo = new BITMAPINFO;
	m_pBmpInfoHeader = reinterpret_cast<LPBITMAPINFOHEADER>(m_pBmpInfo);
	::ZeroMemory(m_pBmpInfoHeader, sizeof(BITMAPINFOHEADER));
	m_pBmpInfoHeader->biSize = sizeof(BITMAPINFOHEADER);
	m_pBmpInfoHeader->biWidth = width;
	m_pBmpInfoHeader->biHeight = height;
	m_pBmpInfoHeader->biPlanes = 1;
	m_pBmpInfoHeader->biBitCount = bitCount;
	m_pBmpInfoHeader->biSizeImage = dwImgSize;

	// Color Table
	if((m_pBmpInfoHeader->biClrUsed == 0))
		m_uiNumColors = 1 << m_pBmpInfoHeader->biBitCount;
	else
		m_uiNumColors = m_pBmpInfoHeader->biClrUsed;
	if(m_pBmpInfoHeader->biClrUsed == 0)
		m_pBmpInfoHeader->biClrUsed = m_uiNumColors;
	
	if(m_uiNumColors <= 256) {
		Clear();
		throw CImageException("Palette mode is not supported");
	}
	// data bits
	m_pDibBits = pData;		
}

void CDib::Save(CString fileName) throw(CImageException) 
{
	CFile file;
	if(file.Open(fileName, CFile::modeWrite | CFile::modeCreate) == 0)
		throw CImageException(_T("Cannot open a file"));
	Save(&file);
}

void CDib::Save(CFile* pFile) throw(CImageException)
{
	pFile->Write(static_cast<void*>(m_pBmpFileHeader), sizeof(BITMAPFILEHEADER));
	DWORD dwLength;
	if(m_uiNumColors <= 256)
		dwLength = sizeof(BITMAPINFOHEADER) + m_uiNumColors*sizeof(RGBQUAD);
	else
		dwLength = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD);
	pFile->Write(static_cast<void*>(m_pBmpInfo), dwLength);

	DWORD dwImgSize = (((GetWidth() * m_pBmpInfoHeader->biBitCount + 15) & ~15) >> 3) * GetHeight() ;
	pFile->Write(static_cast<void*>(m_pDibBits), dwImgSize);
}

void CDib::Draw(CDC* pdc, int x, int y, double scale, DWORD dwROPCode) const throw(CImageException) {
	if(!m_pBmpInfo)
		throw CImageException();
	int nScanLines = ::StretchDIBits(pdc->GetSafeHdc(), x, y, (int)(GetWidth()*scale) , (int)(GetHeight()*scale), 0, 0, GetWidth(), GetHeight(), 
									m_pDibBits, m_pBmpInfo, DIB_RGB_COLORS, dwROPCode);
	if(nScanLines == GDI_ERROR)
		throw CImageException(_T("CDib::Draw exception"));
}

void CDib::Draw(CDC* pdc, int x, int y, int width, int height, DWORD dwROPCode) const throw(CImageException) {
	if(!m_pBmpInfo)
		throw CImageException();
	int nScanLines = ::StretchDIBits(pdc->GetSafeHdc(), x, y, width , height, 0, 0, GetWidth(), GetHeight(), 
									m_pDibBits, m_pBmpInfo, DIB_RGB_COLORS, dwROPCode);
	if(nScanLines == GDI_ERROR)
		throw CImageException(_T("CDib::Draw exception"));
}

COLORREF CDib::GetPixel(int x, int y) const throw() {
	int width = GetWidth();
	int height = GetHeight();

	BYTE* pDibBits = m_pDibBits;
	BYTE Red;
	BYTE Green;
	BYTE Blue;
	int offset;

	SHORT* psDibBits; // for 16 bit
	BYTE Index;
	RGBQUAD* prgb;

	int bpp = GetBPP();
	switch(bpp) {
	case 1:
	case 2:
	case 4:
	case 8:
		offset = width * (height - 1 - y) + x + 1;
		pDibBits += offset;
		Index = *pDibBits;
		prgb = m_pRGBTable + Index;
		Red = prgb->rgbRed;
		Green = prgb->rgbGreen;
		Blue = prgb->rgbBlue;
		break;
	case 16: // assuming 565
		offset = width * 2 * (height - 1 - y) + (x + 1) * 2;
		pDibBits += offset;
		psDibBits = (SHORT*)pDibBits;
		Blue = *psDibBits >> 11;
		Green = (*psDibBits >> 5) & 63;
		Red = *psDibBits & 127;
		break;
	case 24:
		offset = width * 3 * (height -1 - y) + (x + 1) * 3;
		pDibBits += offset;
		Blue = *pDibBits;
		++pDibBits;
		Green = *pDibBits;
		++pDibBits;
		Red = *pDibBits;
		break;
	case 32:
		offset = width * 4 * (height -1 - y) + (x + 1) * 4;
		pDibBits += offset;
		Blue = *pDibBits;
		++pDibBits;
		Green = *pDibBits;
		++pDibBits;
		Red = *pDibBits;
		break;
	default:
		break;
	}

	return RGB(Red, Green, Blue);
}

void CDib::SetPixel(int x, int y, COLORREF col) throw() {
	int width = GetWidth();
	int height = GetHeight();

	BYTE* pDibBits = m_pDibBits;
	int offset;

	int bpp = GetBPP();
	switch(bpp) {
	case 1:
	case 2:
	case 4:
	case 8:
	case 16:
		break; // no support for these modes... yet.
	case 24:
		offset = width * 3 * (height -1 - y) + (x + 1) * 3;
		pDibBits += offset;
		*pDibBits = GetBValue(col);
		++pDibBits;
		*pDibBits = GetGValue(col);
		++pDibBits;
		*pDibBits = GetRValue(col);
		break;
	case 32:
		offset = width * 4 * (height -1 - y) + (x + 1) * 4;
		pDibBits += offset;
		*pDibBits = GetBValue(col);
		++pDibBits;
		*pDibBits = GetGValue(col);
		++pDibBits;
		*pDibBits = GetRValue(col);
		break;
	default:
		break;
	}
}