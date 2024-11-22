// OD3.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "OD3.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "OD3Doc.h"
#include "LeftView.h"

#include "DlgNewProject.h"
#include "DlgProjectOptions.h"
#include "SysConfig.h"
#include "od3gridctrl.h"
#include "ProductMods.h"
#include "HtmlHelp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CProductMods prodMods;	// Modified output codes

/////////////////////////////////////////////////////////////////////////////
// COD3App

BEGIN_MESSAGE_MAP(COD3App, CWinApp)
	//{{AFX_MSG_MAP(COD3App)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COD3App construction

COD3App::COD3App()
{
	// TODO: add construction code here,
	
	// Place all significant initialization in InitInstance
		/*	Version Info
			2		- 1st major revision of application
			2.3		- 2nd phase of development program
							phase 1 = compatibility with purlin detail
							phase 2 = inclusion of swagebeam sections
							phase 3 = compatibility with SBE
							phase 4 = mill swapping
			2.3.45	- use this application with database version 45
					  and any subsequent modifcations
			2.3.45.2002	- implemented in year 2002
		*/
}

/////////////////////////////////////////////////////////////////////////////
// The one and only COD3App object

COD3App theApp;

/////////////////////////////////////////////////////////////////////////////
// COD3App initialization

BOOL COD3App::InitInstance()
{
	REGISTER_GW_CUSTOM_CONTROL(COD3GridCtrl,NULL)
	
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Ayrshire"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_OD3TYPE,
		RUNTIME_CLASS(COD3Doc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CLeftView));
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// DON'T display a new MDI child window during startup!!!
    cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;

   // Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(SW_SHOWMAXIMIZED);
	pMainFrame->UpdateWindow();

	CString	sVer;

	sVer.LoadString(IDS_SOFTWARE_VERSION);
	m_sAppVer = _T("Version ") + sVer;


	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CAnimateCtrl	m_animate;
	CString	m_sAppVersion;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	m_sAppVersion = _T("");
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_ANIMATEOD3_A, m_animate);
	DDX_Text(pDX, IDC_STATIC_VERSION, m_sAppVersion);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void COD3App::OnAppAbout()
{
	CAboutDlg	aboutDlg;

	// Set version number
	aboutDlg.m_sAppVersion = m_sAppVer;
	
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// COD3App message handlers
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void COD3App::OnFileOpen() 
{
	int			result=0;
	CWinApp*	pApp=NULL;
	CWnd*		pAppWnd=NULL;
	CString		sDefaultDir;
	CString		sNewName;
	LPCTSTR		lpstrDefaultDir;
	CMainFrame	*pMainFrm = DYNAMIC_DOWNCAST(CMainFrame, AfxGetApp()->GetMainWnd());

	sDefaultDir = "M:\\OD3\\Projects\\";
	lpstrDefaultDir = sDefaultDir.GetBuffer(1);

	DWORD	flags = 
			OFN_FILEMUSTEXIST|
			OFN_HIDEREADONLY|
			OFN_PATHMUSTEXIST;

	pApp = AfxGetApp();
	pAppWnd = pApp->m_pMainWnd;
	
	CFileDialog dlgOpen(TRUE,
						"od3",
						NULL,
						flags,
						"Ayrshire OD3 (*.od3)|*.od3||",
						pAppWnd);

	dlgOpen.m_ofn.lpstrInitialDir = lpstrDefaultDir;

	if(!pMainFrm->m_suppress)
	{
		result = dlgOpen.DoModal();
		sNewName = dlgOpen.GetPathName();
	}
	else
		// Set user template path
		sNewName = pMainFrm->m_standardTemplatePath;


	if(result == IDOK)
	{
		try
		{
			BeginWaitCursor();
			AfxGetApp()->OpenDocumentFile(sNewName);
		}
		catch(CFileException *e)
		{
			// Report error
			e->ReportError(MB_OK);
			// Delete exception
			e->Delete();
		}
		
		EndWaitCursor();
	}

	return;
}


BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CString	path=getenv(_T("OD3_HOME"));

	SetDlgItemText( IDC_BUILD, APPLICATION_VERSION );

	path += _T("OD3.avi");
	m_animate.Open(path);

#if WINVER >= 0x0500
	AnimateWindow(this->m_hWnd, 300, AW_SLIDE|AW_VER_NEGATIVE|AW_ACTIVATE );
#endif
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAboutDlg::OnOK() 
{
	// TODO: Add extra validation here
	m_animate.Close();

#if WINVER >= 0x0500
	AnimateWindow(this->m_hWnd, 300, AW_BLEND|AW_HIDE );
#endif

	CDialog::OnOK();
}

void COD3App::WinHelp(DWORD dwData, UINT nCmd) 
{
	// TODO: Add your specialized code here and/or call the base class
	CString path, errStr;


	// Get the exe path
	path=getenv("OD3_HOME");

	// Append the help file name
	path += _T("Help\\AyrshireOD.chm");

#if 1
	if(!HtmlHelp(GetMainWnd()->m_hWnd, path, HH_DISPLAY_TOPIC, 0/*dwData*/))
	{
		errStr.Format(IDS_HELPFAIL, path);
		AfxMessageBox(errStr, MB_ICONINFORMATION);
	}
#else
	// Dont use windows atandard
	CWinApp::WinHelp(dwData, nCmd);
#endif

	
}
