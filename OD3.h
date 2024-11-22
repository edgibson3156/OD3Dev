// OD3.h : main header file for the OD3 application
//

#if !defined(AFX_OD3_H__8BDEC0E5_1681_11D3_88B5_006008E6ADB9__INCLUDED_)
#define AFX_OD3_H__8BDEC0E5_1681_11D3_88B5_006008E6ADB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

#include "ProjectHeader.h"
#include "SysConfig.h"

#define new DEBUG_NEW

#define APPLICATION_VERSION "Build:( "__DATE__":"__TIME__" )"
#define ACCESSORY	0
#define PURLIN		1
#define	RAIL		2
#define SLEEVE		3
#define STOCK		4
#define SWAGEBEAM	7
#define	PRESSED		8
#define STUD		9
#define FLOOR_JOIST 10
#define	BEAM		1
#define LINE_1		1
#define LINE_2		2
#define LINE_3		3
#define D_BRACE		4
#define CURRENT_SHEET	0

/////////////////////////////////////////////////////////////////////////////
// COD3App:
// See OD3.cpp for the implementation of this class
//

class COD3App : public CWinApp
{
public:
	COD3App();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COD3App)
	public:
	virtual BOOL InitInstance();
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);
	//}}AFX_VIRTUAL

	CString m_sAppVer;
// Implementation
	//{{AFX_MSG(COD3App)
	afx_msg void OnAppAbout();
	afx_msg void OnFileOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OD3_H__8BDEC0E5_1681_11D3_88B5_006008E6ADB9__INCLUDED_)
