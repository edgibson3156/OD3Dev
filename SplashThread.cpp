// SplashThread.cpp : implementation file
//

#include "stdafx.h"
#include "od3.h"
#include "SplashThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSplashThread

IMPLEMENT_DYNCREATE(CSplashThread, CWinThread)

CSplashThread::CSplashThread()
{
}

CSplashThread::~CSplashThread()
{
}

BOOL CSplashThread::InitInstance()
{
	// Create dialog
	m_dlg.Create(IDD_SPLASH, AfxGetMainWnd());
	// Display dialog
	m_dlg.ShowWindow(SW_SHOWNORMAL);


	return TRUE;
}

int CSplashThread::ExitInstance()
{
	m_dlg.DestroyWindow();

	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CSplashThread, CWinThread)
	//{{AFX_MSG_MAP(CSplashThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSplashThread message handlers
