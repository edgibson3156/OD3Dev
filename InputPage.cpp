// InputPage.cpp : implementation file
//

#include "stdafx.h"
#include "OD3.h"
#include "InputPage.h"
#include "FolderBrowse.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInputPage property page

IMPLEMENT_DYNCREATE(CInputPage, CPropertyPage)

CInputPage::CInputPage() : CPropertyPage(CInputPage::IDD)
{
	//{{AFX_DATA_INIT(CInputPage)
	m_editAutoInputPath = _T("");
	m_editProjectPath = _T("");
	//}}AFX_DATA_INIT
}

CInputPage::~CInputPage()
{
}

void CInputPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInputPage)
	DDX_Text(pDX, IDC_AUTOINPUT, m_editAutoInputPath);
	DDX_Text(pDX, IDC_PROJECTDIR, m_editProjectPath);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInputPage, CPropertyPage)
	//{{AFX_MSG_MAP(CInputPage)
	ON_EN_UPDATE(IDC_AUTOINPUT, OnUpdateAutoinput)
	ON_EN_UPDATE(IDC_PROJECTDIR, OnUpdateProjectdir)
	ON_BN_CLICKED(IDC_AUTOPATH_BUTTON, OnAutopathButton)
	ON_BN_CLICKED(IDC_PROJPATH_BUTTON, OnProjpathButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInputPage message handlers

void CInputPage::OnUpdateAutoinput() 
{
	UpdateData(true);
	CPropertyPage::SetModified(true);
	CPropertyPage::OnApply();
}

void CInputPage::OnUpdateProjectdir() 
{
	UpdateData(true);
	CPropertyPage::SetModified(true);
	CPropertyPage::OnApply();
}

void CInputPage::OnAutopathButton() 
{
	// TODO: Add your control notification handler code here
	CFolderBrowse	browse;
	CString			path;
	CEdit			*editBox=NULL;

	editBox = (CEdit *)GetDlgItem(IDC_AUTOINPUT);
	path = browse.getFolder();

	if(path.GetLength() && editBox)
	{
		// Set new path
		editBox->SetWindowText(path);
	}

	return;
}

void CInputPage::OnProjpathButton() 
{
	// TODO: Add your control notification handler code here
	CFolderBrowse	browse;
	CString			path;
	CEdit			*editBox=NULL;

	editBox = (CEdit *)GetDlgItem(IDC_PROJECTDIR);
	path = browse.getFolder();

	if(path.GetLength() && editBox)
	{
		// Set new path
		editBox->SetWindowText(path);
	}

	return;
}
