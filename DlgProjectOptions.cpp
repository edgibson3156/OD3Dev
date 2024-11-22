// DlgProjectOptions.cpp : implementation file
//

#include "stdafx.h"
#include "OD3.h"
#include "DlgProjectOptions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgProjectOptions dialog


CDlgProjectOptions::CDlgProjectOptions(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgProjectOptions::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgProjectOptions)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgProjectOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgProjectOptions)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgProjectOptions, CDialog)
	//{{AFX_MSG_MAP(CDlgProjectOptions)
	ON_BN_CLICKED(IDC_PROJECT_SETUP_BUTTON, OnProjectSetupButton)
	ON_BN_CLICKED(ID_FILE_IMPORT_PROJECTSETTINGS, OnFileImportProjectsettings)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgProjectOptions message handlers

void CDlgProjectOptions::OnProjectSetupButton() 
{
	m_nProjectSettings = 1;
	CDialog::OnOK();
}

void CDlgProjectOptions::OnCancel() 
{
	m_nProjectSettings = 3;
	CDialog::OnCancel();
}

void CDlgProjectOptions::OnFileImportProjectsettings() 
{
	m_nProjectSettings = 2;
	CDialog::OnOK();
}
