// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "OD3.h"

#include "MainFrm.h"
#include "SplashThread.h"
#include "DlgWhatsNew.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------
// Global data 
//---------------------------------------------------------
#include "Line1.h"
CLine1 Line1;

#include "Line2.h"
CLine2 Line2;

#include "Line3.h"
CLine3 Line3;

#include "CeeSectFail.h"
CCeeSectFail ceeFailDlg;

#include "DlgListAcc.h"
CDlgListAcc	dlgAcc;
/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(IDT_STANDARD_TEMP, OnStandardTemp)
	ON_COMMAND(IDT_STANDARD_TEMP_LOAD, OnStandardTempLoad)
	ON_UPDATE_COMMAND_UI(IDT_STANDARD_TEMP, OnUpdateStandardTemp)
	ON_UPDATE_COMMAND_UI(IDT_STANDARD_TEMP_LOAD, OnUpdateStandardTempLoad)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, CMDIFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, CMDIFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CMDIFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CMDIFrameWnd::OnHelpFinder)
//	ON_UPDATE_COMMAND_UI(ID_INDICATOR_PROGRESS, OnUpdateProgress)

END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_SEPARATOR,			// Embedded progress bar control
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here

	// Setup basic registry path
	m_regPath = _T("Software\\Ayrshire\\OD3");

	// Set warning supress flag
	m_suppress = false;

	// Load registry settings
	if(setTemplateRegistry(""))
		m_standardTemplate = true;
	else
		m_standardTemplate = false;


}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	HBITMAP menuBitmaps;

	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	menuBitmaps = (HBITMAP)LoadImage(AfxGetApp()->m_hInstance, (LPCSTR)IDB_MAINTOOL, IMAGE_BITMAP, 0, 0,
								LR_DEFAULTSIZE | LR_LOADTRANSPARENT | LR_LOADMAP3DCOLORS);

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!(m_wndToolBar.LoadToolBar(IDR_MAINFRAME) && m_wndToolBar.SetBitmap(menuBitmaps)))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

// Standard 16 colour toolbar
///////////////////////////////////////////////////////////////////////////////////
#if 0
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
#endif
///////////////////////////////////////////////////////////////////////////////////
	if (!CreateStatusBar())
		return -1;      // fail to create

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	// Embedded progress bar not created
	m_bProgCreated = false;

	// Create cee section error dialog
	ceeFailDlg.Create(IDD_CEE_SECTION, this);

	// Create Accessories list dialog
	dlgAcc.Create(IDD_LISTACC, this);

	// Start the thread for the wait dialog
	m_pThread = AfxBeginThread(RUNTIME_CLASS(CSplashThread));

	// Set timer for spash screen
	SetTimer(SPLASHTIMER, 3000, NULL);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

BOOL CMainFrame::CreateStatusBar()
{
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return FALSE;       // fail to create
	}


	UINT	nID, nStyle;
	int		cxWidth;
	LPCTSTR lpszText =_T("");


	m_wndStatusBar.GetPaneInfo( 0, nID, nStyle, cxWidth);
	m_wndStatusBar.SetPaneInfo( 0, nID, SBPS_STRETCH|SBPS_NORMAL|SBPS_NOBORDERS, cxWidth);
	m_wndStatusBar.GetPaneInfo( 1, nID, nStyle, cxWidth);
	cxWidth = 200;
	m_wndStatusBar.SetPaneInfo( 1, nID, nStyle, cxWidth);
	m_wndStatusBar.SetPaneText( 1, lpszText, TRUE);

	m_wndStatusBar.GetStatusBarCtrl().SetMinHeight(24);
	m_wndStatusBar.GetStatusBarCtrl().SetBkColor(RGB(208,208,240));


	return TRUE;
}

/*
BOOL CMainFrame::CreateProgressIndicator()
{
	UINT nID, nStyle;
	int cxWidth;
	CRect rect;
	LPRECT lpRect = (LPRECT)rect;

	m_wndStatusBar.GetPaneInfo( 1, nID, nStyle, cxWidth);
//	m_wndStatusBar.GetItemRect( nID, lpRect);
	rect.bottom = 10;
	rect.top = 0;
	rect.left = 300;
	rect.right = rect.left + cxWidth;
	m_Progress.Create( WS_VISIBLE | WS_CHILD, rect, this, ID_INDICATOR_PROGRESS );
	m_Progress.SetRange( static_cast<short>(m_uiRangeFrom), static_cast<short>(m_uiRangeTo) );
	m_Progress.SetStep(static_cast<short>(m_uiStep));

	return TRUE;
}
*/

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

/////////////////////////////////////////////////////////////////////////////

BOOL CMainFrame::StatusBarMsgUpdate(LPCTSTR lpszText)
{
	UINT nID, nStyle;
	int cxWidth;

	m_wndStatusBar.GetPaneInfo( 0, nID, nStyle, cxWidth);
	m_wndStatusBar.SetPaneInfo( 0, nID, SBPS_STRETCH|SBPS_NORMAL|SBPS_NOBORDERS, cxWidth);
	m_wndStatusBar.SetPaneText( 0, lpszText, TRUE);

	return TRUE;
}



void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	CMDIFrameWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	CRect rc;

	if(m_wndStatusBar.m_hWnd && m_progressBar.m_hWnd)
	{
		m_wndStatusBar.GetItemRect(1, &rc);

		// Reposition the progress control correctly!
		m_progressBar.SetWindowPos(&wndTop, rc.left, rc.top, rc.right - rc.left,
			rc.bottom - rc.top, 0); 
	}

	return;	
}

void CMainFrame::OnStandardTemp() 
{
	// TODO: Add your command handler code here
	int res=0;

	if(!m_standardTemplate)
	{
		// Load and store template file
		res = loadStandardTemplate();
	}
	else
	{
		m_standardTemplate = false;
		return;
	}

	// Toggle flag
	if(res == IDOK)
		m_standardTemplate = true;
	else if(m_standardTemplatePath.IsEmpty())
		m_standardTemplate = false;

	return;
}

void CMainFrame::OnUpdateStandardTemp(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_standardTemplate)
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);
}

void CMainFrame::OnStandardTempLoad() 
{
	// TODO: Add your command handler code here
	CString	warn;

	// Test if the file exist (fo user default test)
	try
	{
		CFile user(m_standardTemplatePath, CFile::modeRead);
		// Release file pointer
		user.Close();

		// Suppress the warning message
		m_suppress = true;
		// Call open file
		AfxGetApp()->OpenDocumentFile(m_standardTemplatePath);
		// Allow warning
		m_suppress = false;
	}
	catch(CFileException *e)
	{
		// Test and report file error
		if(e->m_lOsError == CFileException::fileNotFound)
		{
			warn.Format(IDS_FILE_MISSING, m_standardTemplatePath);
			if(AfxMessageBox(warn, MB_YESNO|MB_ICONQUESTION) == IDYES)
			{
				if(loadStandardTemplate() == IDOK)
					OnStandardTempLoad();
			}
		}
		else
			e->ReportError(MB_OK);

		// Delete exception
		e->Delete();
	}

	return;	
}

int CMainFrame::loadStandardTemplate()
{
	CFileDialog openDlg(true);
	int			res=0;


	openDlg.m_ofn.lpstrFilter = "OD3 Document (*.od3)\0\0(*.*)\0";
	
	// Open common file dialog
	if((res = openDlg.DoModal()) == IDOK)
	{
		setTemplateRegistry(openDlg.GetPathName());
	}

	return(res);
}

bool CMainFrame::setTemplateRegistry(CString path)
{
	CRegKey		regKey;
	bool		created = false;
	char		ans[260] = {"\0"};
	DWORD		value=sizeof(ans)-1;
	CString		val;


	// Open the key
	if(regKey.Open(HKEY_CURRENT_USER, m_regPath+"\\Template", 
						KEY_ALL_ACCESS) != ERROR_SUCCESS)
	{
		
		if(!path.IsEmpty())
		{
			// Create new key
			regKey.Create(HKEY_CURRENT_USER, m_regPath+"\\Template", 
								NULL, REG_OPTION_NON_VOLATILE);

				
			// Set new path and file
			regKey.SetValue(path, "Path");
			m_standardTemplatePath = path;

			// Set flag
			created = true;
		}
	}


	// Valid registry key
	if(regKey.m_hKey)
	{
		// Test path length
		if(!path.IsEmpty())
		{
			// Set new path and file
			regKey.SetValue(path, "Path");
			m_standardTemplatePath = path;
		}
		else
		{
			regKey.QueryValue(ans, "Path", &value);
			m_standardTemplatePath = ans;
		}

		
		// Close registry key
		regKey.Close();
		// Set flag
		created=true;
	}

	// Return result
	return(created);
}

void CMainFrame::OnUpdateStandardTempLoad(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(!m_standardTemplate)
		pCmdUI->Enable(false);

	return;
}

void CMainFrame::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent==SPLASHTIMER)
	{
		unsigned int iShow;
		// Close the thread for the splash dialog
		m_pThread->PostThreadMessage(WM_QUIT, 0,0);	

		KillTimer(SPLASHTIMER);

		// Get registry value
		iShow = AfxGetApp()->GetProfileInt("Settings", "whatsNew", 0);

		if(iShow==0)
		{
			CDlgWhatsNew whatsNew;

			// Show whats new dialog
			whatsNew.DoModal();
		}
	}

	CMDIFrameWnd::OnTimer(nIDEvent);
}
