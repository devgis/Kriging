// 3DGrapher.h: interface for the C3DGrapher class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_3DGrapher_H__85676EF1_4A9F_41BF_B3E9_B10462898B56__INCLUDED_)
#define AFX_3DGrapher_H__85676EF1_4A9F_41BF_B3E9_B10462898B56__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "gl\gl.h"
#include "gl\glu.h"
#include "Grapher.h"
#include "3DData.h"
#include <list>
#include <string>

#define BEGIN_GL	bool bNoRC=false; if(!::wglGetCurrentContext()) { bNoRC=true; ::wglMakeCurrent(m_hDC, m_hRC); }
#define END_GL	if(bNoRC) ::wglMakeCurrent(m_hDC, NULL);
	 
class C3DGrapher
{
public:
	enum { ORTHOGRAPHIC, PERSPECTIVE };
	enum { FLAT, SMOOTH };
	enum { OUTLINE, FILL };
	C3DGrapher() throw();
	virtual ~C3DGrapher();
	virtual void Init(HWND hWnd) throw();
	virtual void Destroy() throw();
	void Resize(int cx, int cy) throw();
	void Clear() throw();
	virtual void Render() throw() = 0;
	void Add3DData(C3DData* pdata) throw();
	void SetTitles(std::string title, std::string xTitle, std::string yTitle, std::string zTitle) throw();
	// Getter & Setter
	void SetProjectionType(int type) throw() { m_nProjectionType = type; }
	int GetProjectionType() const throw() { return m_nProjectionType; }
	void SetAxisRange(double xRange, double yRange, double zRange) throw();
	void SetXRotation(GLdouble rot) throw() { m_dXrot = rot; }
	GLdouble GetXRotation() const throw() { return m_dXrot; }
	void SetYRotation(GLdouble rot) throw() { m_dYrot = rot; }
	GLdouble GetYRotation() const throw() { return m_dYrot; }
	void SetZRotation(GLdouble rot) throw() { m_dZrot = rot; }
	GLdouble GetZRotation() const throw() { return m_dZrot; }
	void SetXTranslation(GLdouble trans) throw() { m_dXtran = trans; }
	GLdouble GetXTranslation() const throw() { return m_dXtran; }
	void SetYTranslation(GLdouble trans) throw() { m_dYtran = trans; }
	GLdouble GetYTranslation() const throw() { return m_dYtran; }
	void SetZTranslation(GLdouble trans) throw() { m_dZtran = trans; }
	GLdouble GetZTranslation() const throw() { return m_dZtran; }
	void SetBkGndColor(COLORREF col) throw();
	void SetDepthTest(bool bTest) throw() { m_bDepthTest = bTest; Initialize(); }
	bool IsDepthTest() const throw() { return m_bDepthTest; }
	void SetCullFace(bool bCull) throw() { m_bCullFace = bCull; Initialize(); }
	bool IsCullFace() const throw() { return m_bCullFace; }
	void SetShadeModel(int model) throw() { m_nShadeModel = model; Initialize(); }
	int  GetShadeModel() const throw() { return m_nShadeModel; }
	void SetPolygonMode(int mode) throw() { m_nPolygonMode = mode; Initialize(); }
	int  GetPolygonMode() const throw() { return m_nPolygonMode; }
	// Simple gl wrapper
	GLenum GetError() const throw() { ::glGetError(); }
	const GLubyte* ErrorString(GLenum errorCode) const throw() { return ::gluErrorString(errorCode); }
	const GLubyte* glGetString(GLenum name) const throw() { return ::glGetString(name); }
	const GLubyte* gluGetString(GLenum name) const throw() { return :: gluGetString(name); }
protected:
	void SetWindowPixelFormat() throw(CGrapherException);
	void CreateGLContext() throw(CGrapherException);
	void CreateFont(std::string fontName=_T("Times New Roman"), int height=16) throw(CGrapherException);
	void DeleteFont() throw();
	void PrintString(std::string str, double x, double y, double z) const throw();
	void Initialize() throw();
	HWND	m_hWnd;
	HDC		m_hDC;
	HGLRC	m_hRC;
	int		m_nProjectionType;
	GLdouble m_dXrange;
	GLdouble m_dYrange;
	GLdouble m_dZrange;
	bool	m_bDepthTest;
	bool	m_bCullFace;
	int		m_nShadeModel;
	int 	m_nPolygonMode;
	GLdouble m_dFOV;
	GLdouble m_dXrot;
	GLdouble m_dYrot;
	GLdouble m_dZrot;
	GLdouble	m_dXtran;
	GLdouble	m_dYtran;
	GLdouble m_dZtran;
	std::string m_strTitle;
	std::string m_strXtitle;
	std::string m_strYtitle;
	std::string m_strZtitle;
	int		m_nFontBase;
	COLORREF	m_colBkGnd;

	int m_nSize; // size of m_listData
	std::list<C3DData*> m_listData;
};

#endif // !defined(AFX_3DGrapher_H__85676EF1_4A9F_41BF_B3E9_B10462898B56__INCLUDED_)
