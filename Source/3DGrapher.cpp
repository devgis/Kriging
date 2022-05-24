// 3DGrapher.cpp: implementation of the C3DGrapher class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "3DGrapher.h"
#include "gl\glaux.h"
#include <cmath>
using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

C3DGrapher::C3DGrapher()
{
	m_nProjectionType = PERSPECTIVE;
	m_dXrange = 100.0f;
	m_dXrange = 100.0f;
	m_dXrange = 100.0f;
	m_bDepthTest = true;
	m_bCullFace = true;
	m_nShadeModel = SMOOTH;
	m_nPolygonMode = FILL;
	m_dFOV = 45.0f;
	m_dXrot = 20.0f;
	m_dYrot = -20.0f;
	m_dZrot = 0.0f;
	m_dXtran = 0.0f;
	m_dYtran = 0.0f;
	m_dZtran = 0.0f;
	m_strTitle = _T("Untitled");
	m_strXtitle = _T("X");
	m_strYtitle = _T("Y");
	m_strZtitle = _T("Z");
	m_nFontBase = 0;
	m_colBkGnd = RGB(127, 127, 0);
	m_nSize = 0;
}

C3DGrapher::~C3DGrapher()
{
	Clear();
}

void C3DGrapher::Init(HWND hWnd) throw()
{
	ASSERT(::IsWindow(hWnd));

	m_hWnd = hWnd;
	m_hDC = ::GetDC(m_hWnd);
	
	try {
		SetWindowPixelFormat();
		CreateGLContext();
	} catch(CGrapherException e) {
		::MessageBox(NULL, e.what(), _T("GrapherException"), MB_OK);
	}
	CreateFont();
	Initialize();
}

void C3DGrapher::Clear() throw()
{
	list<C3DData*>::iterator iter;

	C3DData* pdata = NULL;
	for(iter=m_listData.begin(); iter!=m_listData.end(); ++iter) {
		pdata = *iter;
		delete pdata;
	}
	m_listData.clear();
}

void C3DGrapher::Destroy() throw()
{
	if(::wglGetCurrentContext())
		::wglMakeCurrent(NULL, NULL);
	if(m_hRC) {
		::wglDeleteContext(m_hRC);
		m_hRC = NULL;
	}
	::ReleaseDC(m_hWnd, m_hDC);
	DeleteFont();
}

void C3DGrapher::Resize(int cx, int cy) throw()
{
	BEGIN_GL
	if(cy==0)
		cx = 1;

	::glViewport(0, 0, cx, cy);
	::glMatrixMode(GL_PROJECTION);
	::glLoadIdentity();

	if(m_nProjectionType == PERSPECTIVE) {
		GLdouble fAspect;
		fAspect = (GLdouble)cx/(GLdouble)cy;
		::gluPerspective(m_dFOV, fAspect, 1.0, m_dZrange*300);
	} else if(m_nProjectionType == ORTHOGRAPHIC) {
		if(cx <= cy)
			::glOrtho(-m_dXrange*1.2, m_dXrange*1.2, -m_dYrange*cy/cx*1.2, m_dYrange*cy/cx*1.2, m_dZrange*300.0, -300*m_dZrange);
		else
			::glOrtho(-m_dXrange*cx/cy*1.2, m_dXrange*cx/cy*1.2, -m_dYrange*1.2, m_dYrange*1.2, 300.0*m_dZrange, -300*m_dZrange);
	}

	::glMatrixMode(GL_MODELVIEW);
	END_GL
}

void C3DGrapher::SetAxisRange(double xRange, double yRange, double zRange) throw()
{
	m_dXrange = xRange;
	m_dYrange = yRange;
	m_dZrange = zRange;
}

void C3DGrapher::SetBkGndColor(COLORREF col) throw()
{
	m_colBkGnd = col;
	BEGIN_GL
	::glClearColor(GetRValue(col)/255.0f, GetGValue(col)/255.0f, GetBValue(col)/255.0f, 1.0);
	END_GL
}

void C3DGrapher::Add3DData(C3DData* pdata) throw()
{
	m_listData.push_back(pdata);
	m_nSize++;
}

void C3DGrapher::SetTitles(string title, string xTitle, string yTitle, string zTitle) throw()
{
	m_strTitle = title;
	m_strXtitle = xTitle;
	m_strYtitle = yTitle;
	m_strZtitle = zTitle;
}

void C3DGrapher::SetWindowPixelFormat() throw(CGrapherException)
{
	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, PFD_TYPE_RGBA,
			24, 
			0, 0, 0, 0, 0, 0,
			0, 0,
			0, 0, 0, 0, 0,
			32,
			0,
			0,
			PFD_MAIN_PLANE,
			0,
			0, 0, 0
	};

	int nPixelFormat = ChoosePixelFormat(m_hDC, &pfd);
	if(!SetPixelFormat(m_hDC, nPixelFormat, &pfd))
		throw CGrapherException(_T("Failed to set pixel format"));
}

void C3DGrapher::CreateGLContext() throw(CGrapherException)
{
	m_hRC = ::wglCreateContext(m_hDC);
	if(!m_hRC)
		throw CGrapherException(_T("Failed to Create RC"));
	if(!::wglMakeCurrent(m_hDC, m_hRC))
		throw CGrapherException(_T("Failed to set current RC"));
	::wglMakeCurrent(m_hDC, NULL);
}

void C3DGrapher::CreateFont(string fontName, int height) throw(CGrapherException)
{
	BEGIN_GL
	CFont font;
	
	if((m_nFontBase = ::glGenLists(96)) == 0)
		throw CGrapherException(_T("Can't create font"));;

	if(fontName == _T("symbol"))
		font.CreateFont(height, 0, 0, 0, FW_NORMAL, 0, FALSE, FALSE, SYMBOL_CHARSET, OUT_TT_PRECIS,
							CLIP_DEFAULT_PRECIS, DRAFT_QUALITY, DEFAULT_PITCH, fontName.c_str());
	else
		font.CreateFont(height, 0, 0, 0, FW_NORMAL, 0, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS,
							CLIP_DEFAULT_PRECIS, DRAFT_QUALITY, DEFAULT_PITCH, fontName.c_str());

	::SelectObject(m_hDC, font);
	::wglUseFontBitmaps(m_hDC, 32, 96, m_nFontBase);
	END_GL
}

void C3DGrapher::DeleteFont()
{
	BEGIN_GL
	if(m_nFontBase == 0)
		return;
	::glDeleteLists(m_nFontBase, 96);
	END_GL
}

void C3DGrapher::PrintString(string str, double x, double y, double z) const throw()
{
	BEGIN_GL
	::glRasterPos3f(x, y, z);
	::glPushAttrib(GL_LIST_BIT);
	::glListBase(m_nFontBase-32);
	::glCallLists(str.length(), GL_UNSIGNED_BYTE, str.c_str());
	::glPopAttrib();
	END_GL
}

void C3DGrapher::Initialize()
{
	BEGIN_GL
	::glClearDepth(1.0);
	if(m_bDepthTest)
		::glEnable(GL_DEPTH_TEST);
	else
		::glDisable(GL_DEPTH_TEST);
	if(m_bCullFace)
		::glEnable(GL_CULL_FACE);
	else
		::glDisable(GL_CULL_FACE);
	if(m_nShadeModel == FLAT)
		::glShadeModel(GL_FLAT);
	else if(m_nShadeModel == SMOOTH)
		::glShadeModel(GL_SMOOTH);

	if(m_nPolygonMode == FILL)
		::glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	else if(m_nPolygonMode == OUTLINE)
		::glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	::glClearColor(GetRValue(m_colBkGnd)/255.0f, GetGValue(m_colBkGnd)/255.0f, GetBValue(m_colBkGnd)/255.0f, 1.0);

	::glLineWidth(2.0); // required
	::glPointSize(2.0);
	END_GL
}