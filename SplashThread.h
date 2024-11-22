#if !defined(AFX_SPLASHTHREAD_H__A7647A82_8045_483B_9522_D8B4546760C0__INCLUDED_)
#define AFX_SPLASHTHREAD_H__A7647A82_8045_483B_9522_D8B4546760C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SplashThread.h : header file
//
#define SPLASHTIMER 1
#include "SplashDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CSplashThread thread

class CSplashThread : public CWinThread
{
	DECLARE_DYNCREATE(CSplashThread)
protected:
	CSplashThread();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSplashThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSplashThread();

	CSplashDlg m_dlg;

	// Generated message map functions
	//{{AFX_MSG(CSplashThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPLASHTHREAD_H__A7647A82_8045_483B_9522_D8B4546760C0__INCLUDED_)
