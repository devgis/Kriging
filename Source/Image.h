// Image.h: interface for the CImage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGE_H__D3142778_9555_4128_887F_104A5F9478E1__INCLUDED_)
#define AFX_IMAGE_H__D3142778_9555_4128_887F_104A5F9478E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseException.h"

/** ImageFormat constants */
enum IMAGE_FORMAT { IF_BMP, IF_JPG };

class CImageException : public BaseException
{
public:
	CImageException() throw() : BaseException(_T("ImageException")) {}
	CImageException(std::string message) throw() : BaseException(message) {}
	CImageException(std::string message, std::string location) throw() : BaseException(message, location) {}
};

class CImage  
{
public:
	virtual ~CImage(){}
	virtual void Load(CString fileName) throw(CImageException) = 0;
	virtual void Load(CFile* pFile) throw(CImageException) = 0;
	virtual void Save(CString fileName) throw(CImageException) = 0;
	virtual void Save(CFile* pFile) throw(CImageException) = 0;
	virtual void Draw(CDC* pdc, int x=0, int y=0, double scale = 1.0, DWORD dwROPCode = SRCCOPY) const throw(CImageException) = 0;
	virtual void Draw(CDC* pdc, int x, int y, int width, int height, DWORD dwROPCode = SRCCOPY) const throw(CImageException) = 0;
	virtual void Create(int width, int height, LPBYTE pData, int bitCount=24) throw(CImageException) = 0;
	virtual UINT GetWidth() const throw() = 0;
	virtual UINT GetHeight() const throw() = 0;
	virtual UINT GetBPP() const throw() = 0;
	virtual COLORREF GetPixel(int x, int y) const throw() = 0;
	virtual LPBYTE GetDibBits() const throw() = 0;
};

#endif // !defined(AFX_IMAGE_H__D3142778_9555_4128_887F_104A5F9478E1__INCLUDED_)
