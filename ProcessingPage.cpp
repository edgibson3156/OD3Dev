// ProcessingPage.cpp : implementation file
//

#include "stdafx.h"
#include "OD3.h"
#include "ProcessingPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProcessingPage property page

IMPLEMENT_DYNCREATE(CProcessingPage, CPropertyPage)

CProcessingPage::CProcessingPage() : CPropertyPage(CProcessingPage::IDD)
{
	//{{AFX_DATA_INIT(CProcessingPage)
	m_radioProcessAll = -1;
	m_radioProcessAuto = -1;
	//}}AFX_DATA_INIT
}

CProcessingPage::~CProcessingPage()
{
}

void CProcessingPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProcessingPage)
	DDX_Radio(pDX, IDC_RADIO_PROCESS_ALL, m_radioProcessAll);
	DDX_Radio(pDX, IDC_RADIO_PROCESS_AUTO, m_radioProcessAuto);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProcessingPage, CPropertyPage)
	//{{AFX_MSG_MAP(CProcessingPage)
	ON_BN_CLICKED(IDC_RADIO_PROCESS_ALL, OnRadioProcessAll)
	ON_BN_CLICKED(IDC_RADIO_PROCESS_AUTO, OnRadioProcessAuto)
	ON_BN_CLICKED(IDC_RADIO_OPTIONS_PROMPT, OnRadioOptionsPrompt)
	ON_BN_CLICKED(IDC_RADIO_SELECT_FILES, OnRadioSelectFiles)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProcessingPage message handlers

BOOL CProcessingPage::OnApply() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CPropertyPage::OnApply();
}

void CProcessingPage::OnRadioProcessAll() 
{
	UpdateData(true);
	CPropertyPage::SetModified(true);
}

void CProcessingPage::OnRadioProcessAuto() 
{
	UpdateData(true);
	CPropertyPage::SetModified(true);
}

void CProcessingPage::OnRadioOptionsPrompt() 
{
	UpdateData(true);
	CPropertyPage::SetModified(true);
}

void CProcessingPage::OnRadioSelectFiles() 
{
	UpdateData(true);
	CPropertyPage::SetModified(true);
}
