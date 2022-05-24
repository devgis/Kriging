// WaferPainter.h : main header file for the WAFERPAINTER application
//

#if !defined(AFX_WAFERPAINTER_H__108C4813_579D_4679_9B56_B5D7FDDCD937__INCLUDED_)
#define AFX_WAFERPAINTER_H__108C4813_579D_4679_9B56_B5D7FDDCD937__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CWaferPainterApp:
// See WaferPainter.cpp for the implementation of this class
//

class CWaferPainterApp : public CWinApp
{
public:
	CWaferPainterApp();
	~CWaferPainterApp();

	CMultiDocTemplate* m_pContourTemplate;
	CMultiDocTemplate* m_p3DContourTemplate;

	int		m_nDiameter;
	int		m_nInterpolater;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWaferPainterApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CWaferPainterApp)
	afx_msg void OnAppAbout();
	afx_msg void OnInteroption();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WAFERPAINTER_H__108C4813_579D_4679_9B56_B5D7FDDCD937__INCLUDED_)
