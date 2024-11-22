// DlgNewProject.cpp : implementation file
//

#include "stdafx.h"
#include "OD3.h"
#include "DlgNewProject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgNewProject dialog


CDlgNewProject::CDlgNewProject(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNewProject::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgNewProject)
	m_editProjectName = _T("");
	m_editCustomerName = _T("");
	m_editCustomerRef = _T("");
	m_editDueDate = _T("");
	m_radioProjectType = -1;
	m_editJobDestination = _T("");
	m_editComments = _T("");
	//}}AFX_DATA_INIT
}


void CDlgNewProject::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgNewProject)
	DDX_Control(pDX, IDC_EDIT_PROJNAME, m_ctrlProjName);
	DDX_Text(pDX, IDC_EDIT_PROJNAME, m_editProjectName);
	DDV_MaxChars(pDX, m_editProjectName, 6);
	DDX_Text(pDX, IDC_EDIT_CUSTOMER_NAME, m_editCustomerName);
	DDX_Text(pDX, IDC_EDIT_CUSTOMER_REF, m_editCustomerRef);
	DDX_Text(pDX, IDC_EDIT_DUEDATE, m_editDueDate);
	DDX_Radio(pDX, IDC_RADIO_PROJTYPE1, m_radioProjectType);
	DDX_Text(pDX, IDC_EDIT_JOB_DESTINATION, m_editJobDestination);
	DDX_Text(pDX, IDC_EDIT_COMMENTS, m_editComments);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgNewProject, CDialog)
	//{{AFX_MSG_MAP(CDlgNewProject)
	ON_NOTIFY(MCN_SELECT, IDC_DUEDATE_MONTHCALENDAR, OnSelectDuedateMonthcalendar)
	ON_BN_CLICKED(IDC_RADIO_PROJTYPE1, OnRadioProjtype1)
	ON_BN_CLICKED(IDC_RADIO_PROJTYPE2, OnRadioProjtype2)
	ON_BN_CLICKED(IDC_RADIO_PROJTYPE3, OnRadioProjtype3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgNewProject message handlers

void CDlgNewProject::OnSelectDuedateMonthcalendar(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	// VHF TODO: What I want to do here is capture the date selected
	// and assign it to the member variable m_nDueDate
	// and display the value in the due date edit box
	// What about type conversion - for keyboard entry
	// we need to use the string form mm/dd/yyyy.
	
	*pResult = 0;
}

void CDlgNewProject::OnRadioProjtype1() 
{
	this->m_nProjectType = 1;	//	Build single order
}

void CDlgNewProject::OnRadioProjtype2() 
{
	this->m_nProjectType = 2;	// Build multiple orders
}

void CDlgNewProject::OnRadioProjtype3() 
{
	this->m_nProjectType = 3;	// Integrated Processing
}

void CDlgNewProject::OnOK() 
{
	this->UpdateData(true);


	//	Check the we've got the project name
	if (this->m_editProjectName != "")
	{
		// VHF TODO: Need a function that will take CString variable and change it to CTime variable.
		// if (StartDlg.m_sDueDate != "")
		CDialog::OnOK();
	}
	else
	{
		if (AfxMessageBox("Please supply a project name") == IDOK)
		{
			m_ctrlProjName.SetFocus();
		}
	}
}

void CDlgNewProject::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL CDlgNewProject::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_radioProjectType = 0;	//	default to proces single order
	m_ctrlProjName.SetFocus();
	UpdateData(false);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
