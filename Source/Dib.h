// Dib.h: interface for the CDib class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIB_H__3C441908_83F8_4989_BEB1_7F05D9BD732E__INCLUDED_)
#define AFX_DIB_H__3C441908_83F8_4989_BEB1_7F05D9BD732E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Image.h"

class CDib : public CImage
{
public:
	CDib() throw();
	virtual ~CDib();

	virtual void Create(int width, int height, LPBYTE pData, int bitCount=24) throw(CImageException);
	virtual void Load(CString fileName) throw(CImageException);
	virtual void Load(CFile* pFile) throw(CImageException);
	virtual void Save(CString fileName) throw(CImageException);
	virtual void Save(CFile* pFile) throw(CImageException);
	virtual void Draw(CDC* pdc, int x = 0, int y = 0, double scale = 1.0, DWORD dwROPCode = SRCCOPY) const throw(CImageException);
	virtual void Draw(CDC* pdc, int x, int y, int width, int height, DWORD dwROPCode = SRCCOPY) const throw(CImageException);
	virtual UINT GetWidth() const throw() { return m_pBmpInfoHeader->biWidth; }
	virtual UINT GetHeight() const throw() { return m_pBmpInfoHeader->biHeight; }
	virtual UINT GetBPP() const throw() { return m_pBmpInfoHeader->biBitCount; }
	virtual COLORREF GetPixel(int x, int y) const throw();
	virtual LPBYTE GetDibBits() const throw() { return m_pDibBits; }

	void Create(CBitmap* pBitmap) throw(CImageException);
	void SetPixel(int x, int y, COLORREF col) throw();
private:
	void Clear() throw();
	LPBITMAPFILEHEADER	m_pBmpFileHeader;
	LPBITMAPINFO		m_pBmpInfo;
	LPBITMAPINFOHEADER	m_pBmpInfoHeader;
	LPRGBQUAD			m_pRGBTable;
	LPBYTE				m_pDibBits;
	UINT				m_uiNumColors;
};

#endif // !defined(AFX_DIB_H__3C441908_83F8_4989_BEB1_7F05D9BD732E__INCLUDED_)
